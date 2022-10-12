/** @file Cjt_clusters.cc
    @brief Código de la clase Cjt_clusters
*/

#include "Cjt_clusters.hh"

//Constructora y destructora

Cjt_clusters::Cjt_clusters(){}

Cjt_clusters::~Cjt_clusters(){}


//Consultoras

void Cjt_clusters::imprime_cluster(const string& id_especie) const{
    // Encuentra el BinTree asociado al identificador y llama al método encargado de imprimirlo
    map<string,BinTree <pair <string,double> > >::const_iterator it = Arbol.find(id_especie);
    imprime_arbol(it->second);
}

bool Cjt_clusters::existe_cluster(const string& id_especie) const{
    // Indica si el clúster existe dentro del conjunto
    map<string,BinTree < pair <string,double> > >::const_iterator it= Arbol.find(id_especie);
    return it!=Arbol.end();
} 

void Cjt_clusters::dist_minima(string& a, string& b, double& d) const {
    //Esta función encuentra la distancia mínima dentro de la tabla de clústers
    map<string, map<string,double> >::const_iterator it=Tab_clu.begin();
    map<string,double>::const_iterator it_sec=it->second.begin();
    // Inicialización de las variables con los valores de los iteradores iniciales
    a=it->first;
    b=it_sec->first;
    d=it_sec->second;
    // Inv: los iteradores posteriors a it no han sido visitados.
    // d es el mínimo de los maps "second" de los elementos entre Tab_clu.begin y el anterior a it, 
    // a y b son los identificadores que tienen distancia d
    while (it!=Tab_clu.end()) {
        // Se inicializa el segundo iterador con el valor del segundo elemento del primer iterador
        // para la iteración actual
        it_sec=it->second.begin();
        // Inv: los iteradores posteriors a it_sec no han sido visitados.
        // d es el mínimo de los elementos entre it->second.begin y el anterior a it_sec, 
        // a y b son los identificadores que tienen distancia d
        while (it_sec!=it->second.end()) {
            if (it_sec->second<d) { // Se ha encontrado una distancia menor
                a=it->first;
                b=it_sec->first;
                d=it_sec->second;
            }
            ++it_sec;
        }
        // Post: a, b y d tienen los valores de los clústers a menor distancia desde Tab_clu.begin
        // hasta el último elemento del it_sec de it (it->second.end()-1)
        ++it;
    }
    // Post: Han sido recorridos y comprobados todos los elementos de la tabla, por tanto, a, b y d tienen 
    // los valores de los clústers a menor distancia desde el inicio de la tabla hasta Tab_clu.end()-1
}

double Cjt_clusters::distancia_cl (const string& a, const string& c) const{
    // Comprueba si el identificador a es menor que c para buscarlo en la tabla. 
    if (a<c) return Tab_clu.find(a)->second.find(c)->second; 
    // Sino, busca en la tabla la distancia de c con a.
    return Tab_clu.find(c)->second.find(a)->second; 
}

bool Cjt_clusters::arbol_vacio() const{
    // Indica si el árbol está vacío
    return Arbol.empty();
}

bool Cjt_clusters::apto_para_wpgma() const{
    // Indica si el árbol tiene más de un clúster
    return Arbol.size()>1;
}

int Cjt_clusters::calcula_hijos(const BinTree <pair<string,double> >& c, int& f) const {
    while (not c.empty()) {
        if (not c.left.empty()) ++f; 
        if (not c.right.empty()) ++f; 
        calcula_hijos(c.left());
        calcula_hijos(c.right());
    }
}

//Modificadoras

void Cjt_clusters::fusiona_cluster(const string& a, const string& b, const double& d) {
    // Fusiona dos clústers
    map<string, BinTree < pair<string,double> > >::const_iterator it_a=Arbol.find(a);
    map<string, BinTree < pair<string,double> > >::const_iterator it_b=Arbol.find(b);

    pair<string,double> aux=pair<string,double> (a+b, d/2);
    BinTree < pair<string,double> > F=BinTree<pair<string,double> >(aux, it_a->second, it_b->second);
    // Inserta la fusión en el conjunto
    Arbol.insert(make_pair(a+b,F));
}

void Cjt_clusters::ejecuta_paso_wpgma () {
    // Ejecuta un paso del algoritmo wpgma completamente
    string a,b;
    double d;
    // Busca la distancia mínima
    dist_minima(a,b,d);
    // Fusiona los clústers con la distancia mínima
    fusiona_cluster (a,b,d);
    // Actualiza la tabla de distancias después de crear el nuevo clúster
    actualiza_tab(a,b);
    // Imprime la tabla de distancias
    imprime_tab_distancias();
    // Elimina los árboles fusionados
    Arbol.erase(a);
    Arbol.erase(b);
}

void Cjt_clusters::actualiza_tab(const string& a, const string& b) {
    // Actualiza la tabla de distancias
    map<string,map<string,double> >::iterator it = Tab_clu.begin();
    string id_fusion=a+b;
    map<string,double> aux;
    // Inv: it<=Tab_clu.end()
    // Se han recalculado y añadido las distancias de los elementos anteriores a it.
    // Las distancias de los elementos posteriores a it no han sido modificadas.
    while (it!=Tab_clu.end()) {
        if (it->first != a and it->first != b) {
            if (it->first < id_fusion) { // el identificador del clúster fusionado será el segundo identificador del map
                // recalculo de la distancia del elemento del iterador con el nuevo clúster fusionado
                double d = (distancia_cl(it->first,a) + distancia_cl(it->first,b))/2; 
                it->second.insert(make_pair(id_fusion,d));
            }
            else { // el identificador del clúster fusionado será el primer identificador del map
                double d = (distancia_cl(a,it->first) + distancia_cl(b,it->first))/2;
                aux.insert(make_pair(it->first,d));
            }
        }
        ++it;
    }
    // Post: se han recalculado todas las distancias de los elementos desde Tab_clu.begin()
    // hasta Tab_clu.end()-1
    Tab_clu.erase(Tab_clu.find(a));
    Tab_clu.erase(Tab_clu.find(b));
    Tab_clu.insert(make_pair(id_fusion,aux));

    // Inv: it<=Tab_clu.end(). Se han eliminado los elementos anteriores a it relacionados con a o b. 
    // Las distancias de los elementos posteriores a it no han sido modificadas.
    // Condición extra para evitar iteraciones innecesarias: el primer elemento de la tabla es menor a a o a b.
    // Si es mayor, ya no existirán ni a ni b en las distancias.
    it=Tab_clu.begin();
    while (it!=Tab_clu.end() and (it->first<a or it->first<b)) {
        it->second.erase(a);
        it->second.erase(b);
        ++it;
    }
    // Post: se han eliminado las distancias relacionadas con a y b desde Tab_clu.begin() hasta el 
    // elemento anterior a it.
}

void Cjt_clusters::crea_clusters(const pair<string,double>& e) {
    // Inserta en el p.i. un clúster con su identificación y el árbol c
    BinTree <pair<string,double> > c(e);
    Arbol.insert(make_pair(e.first, c));
}

void Cjt_clusters::crea_tabla_cluster(const string& id_a, const map<string,double>& b) {
    // Inserta en el p.i. la distancia con sus dos identificadores y el double correspondiente
    Tab_clu.insert(make_pair(id_a,b));
}


//Escritura

void Cjt_clusters::imprime_tab_distancias () const {
    // Imprime la tabla de distancias
    map<string, map <string,double> >::const_iterator it = Tab_clu.begin();
    // Inv: Los iteradores posteriors a it no han sido imprimidos
    // Se han imprimido los valores de it "first" y "second" de los elementos 
    // entre Tab_clu.begin() y el anterior a it
    while (it!=Tab_clu.end()) {
        map <string, double>::const_iterator it_sec = it->second.begin();
        cout<< (*it).first << ":";
        // Inv: los iteradores posteriors a it_sec no han sido imprimidos.
        // Se han imprimido los valores desde it->second.begin al anterior a it_sec
        while (it_sec!=it->second.end()) { 
            cout << " "<<(*it_sec).first << " (" << (*it_sec).second <<")";
            ++it_sec;
        }
        // Post: se han imprimido los elementos desde it->second.begin() hasta it->second.end()-1.
        cout<<endl;
        ++it;
    }
    // Post: se han imprimido los elementos de la tabla desde Tab_clu.begin() hasta Tab_clu.end()-1
}

void Cjt_clusters::imprime_arbol(const BinTree <pair <string,double> >& c) const {
    // Imprime el árbol c
    if (not c.empty()) {
        if(c.value().second==-1) {
            cout << '[' << c.value().first << ']';
        }
        else {
            cout << "[(" << c.value().first << ", " << c.value().second << ") ";
            //BinTree<pair <string,double> >esq = c.left();
            imprime_arbol(c.left());
            //BinTree<pair <string,double> >dre = c.right();
            imprime_arbol(c.right());
            cout << "]";
        }
        // HI: Si c es vacío, imprimimos el identificador y hemos acabado. 
        // Sinó, imprimiremos los valores de la raíz (identificador y distancia) 
        // e imprimerimos su árbol izquierdo y derecho.
    }
    
}

void Cjt_clusters::imprime_arbol_filogenetico() {
    // Esta es sin duda la operación más importante del módulo. 
    // Se han añadido varios métodos para completar la funcionalidad de esta, entre
    // los cuales esta el comprobar si aún siguen existiendo más de un clúster los cuales 
    // se pueden fusionar. Después se encuentra cuales son los clústers a menor distancia
    // para fusionarlos y recalcular la tabla de distancias.
    // Finalmente, cuando no quedan elementos que fusionar, se imprime el resultado del
    // árbol filogenético por el terminal.

    // Inv: Arbol.size()>=1. 
    // Se ha reducido el tamaño del árbol tantas veces como iteraciones hayamos ejecutado
    // y entrado en el bucle.
    while (apto_para_wpgma()){
        string a,b;
        double d;
        dist_minima(a,b,d);
        fusiona_cluster (a,b,d);
        actualiza_tab(a,b);
        Arbol.erase(a);
        Arbol.erase(b);
    }
    // Post: el Arbol.size()=1
    map<string, BinTree <pair<string,double> > >::iterator it=Arbol.begin();
    imprime_arbol(it->second);

}
