/** @file Cjt_especies.cc
    @brief Código de la clase Cjt_especies
*/

#include "Cjt_especies.hh"

//Constructora y destructora

Cjt_especies::Cjt_especies(){}

Cjt_especies::~Cjt_especies(){}  


//Consultoras

bool Cjt_especies::existe_especie(const string& id_especie) const {
    // Indica si la especie existe en el conjunto
    map<string,Especie>::const_iterator it = Cjt.find(id_especie);
    if (it != Cjt.end()) return true;
    return false;
}

string Cjt_especies::obtener_gen(const string& id_especie) const {
    // Proporciona el gen del identificador 
    map<string,Especie>::const_iterator it=Cjt.find(id_especie);
    return (*it).second.consultar_gen();
}

double Cjt_especies::distancia_cjt(const string& id_a, const string& id_b) const{
    // Devuelve la distancia entre dos identificadores
    map<string,Especie>::const_iterator it_a=Cjt.find(id_a);
    map<string,Especie>::const_iterator it_b=Cjt.find(id_b);
    //Llama a la función distancia con las especies encontradas 
    //de los identificadores id_a y id_b
    return it_a->second.distancia(it_b->second);
}


//Modificadoras

void Cjt_especies::crea_especie(const Especie& e) {
    // Inserta la especie e al conjunto de especies
    Cjt.insert(make_pair(e.consultar_id_especie(),e));
    inserta_tab(e);
}

void Cjt_especies::elimina_especie(const string& id_especie) {
    // Elimina la especie e del conjunto de especies
    elimina_tab(id_especie);
    Cjt.erase(id_especie);
}

void Cjt_especies::crea_distancias () {
    // Crea la tabla de distancias para el conjunto de especies
    map<string,Especie>::iterator it_a=Cjt.begin();

    // Inv: it<=Cjt.end()
    // Se han calculado y añadido a la tabla de distancias las distancias de los elementos anteriores a it_a
    // con el resto de especies. Las distancias de los elementos posteriores a it_a no han sido tratadas.
    while (it_a!=Cjt.end()) {
        map<string,Especie>::iterator it_b=it_a;
        ++it_b;
        map<string,double> aux;
        // Inv: it_a<it_b<=Cjt.end()
        // Se han calculado y añadido las distancias de los elementos anteriores a it_b
        // con it_a. Las distancias de it_a con los elementos posteriores a it_b no han sido tratadas.
        while (it_b!=Cjt.end()){
            double d=it_a->second.distancia(it_b->second);
            aux.insert(make_pair((*it_b).first,d));
            ++it_b;
        }
        // Post: se han calculado todas las distancias de los elementos desde it_b=it_a+1
        // hasta Cjt.end()-1
        Tabla.insert(make_pair((*it_a).first,aux));
        ++it_a;
    }
    // Post: se han calculado todas las distancias de los elementos desde Cjt.begin()
    // hasta Cjt.end()-1
}

void Cjt_especies::inserta_tab(const Especie& e) {
    // Inserta las distancias en la tabla del conjunto con la nueva especie e
    map<string, map<string,double> >::iterator it = Tabla.begin();
    string id=e.consultar_id_especie();
    map<string,double> aux;
    // Inv: it<=Tabla.end()
    // Se han recalculado las distancias de los elementos anteriores a it.
    // Las distancias de los elementos posteriores a it no han sido calculadas.
    while (it!=Tabla.end()) {
        if (id>(*it).first) {
            double d=e.distancia(Cjt.find(it->first)->second);
            it->second.insert(make_pair(id,d));
        }
        else if (id<(*it).first) {
            double d=e.distancia(Cjt.find(it->first)->second);
            aux.insert(make_pair((*it).first,d));
        }
        ++it;
    }
    // Post: se han recalculado todas las distancias de los elementos desde Tabla.begin()
    // hasta Tabla.end()-1
    Tabla.insert(make_pair(id,aux));
}

void Cjt_especies::elimina_tab(const string& id) {
    // Elimina las distancias de la tabla del conjunto con la especie del identificador
    map<string, map<string,double> >::iterator it = Tabla.begin();
    // Inv: it<=Tabla.end()
    // Se han eliminado las distancias de los elementos anteriores a it.
    // Las distancias de los elementos posteriores a it no han sido tratadas.
    while (it!=Tabla.end() and (it->first)<id) {
        it->second.erase(id);
        ++it;
    }
    // Post: se han eliminado todas las distancias de los elementos desde Tabla.begin()
    // hasta el anterior a it
    Tabla.erase(it);
}

void Cjt_especies::inicializa_clusters (Cjt_clusters& clu) {
    // Función que comunica información del conjunto de especies con el conjunto de clústers
    // consiguiendo así incializar un clúster para cada especie y crear la tabla inicial
    // del conjunto de clústers    
    if (not Cjt.empty()) {
        map<string,map<string,double>>::const_iterator it=Tabla.begin();
        map<string,double>::const_iterator it_sec=it->second.begin();

        // Inv: it<=Tabla.end()
        // Se han creado los clústers de los elementos anteriores a it.
        // Las distancias de los elementos posteriores a it no han sido tratados.
        while (it!=Tabla.end()) {
            pair <string,double> aux;
            aux.first=it->first;
            aux.second=-1;
            clu.crea_clusters(aux);
            map<string,double> b;
            it_sec=it->second.begin();
            // Inv: it_sec<=it->second.end()
            // b ha recogido la información de los identificadores y distancias desde
            // it->second.begin() hasta el elemento anterior a it_sec con el it actual
            while (it_sec!=it->second.end()) {
                b.insert(make_pair(it_sec->first,it_sec->second));
                ++it_sec;
            }
            // Post: b ha recogido la información de los identificadores y distancias desde
            // it->second.begin() hasta it->second.end()-1 con el it actual
            clu.crea_tabla_cluster(it->first,b);
            ++it;
        }
        // Post: se han creado los clústers desde los elementos "first" de Tabla.begin()
        // a Tabla.end()-1. Se han creado también todas las distancias de entre elementos sin 
        // repetición de información
    }
}


//Lectura y escritura

void Cjt_especies::lee_cjt_especies(const int k) {
    // Lee un conjunto de especies
    Cjt.clear();
    Tabla.clear();
    int n;
    cin>>n;
    // Inv: 0<=i<=n. Se han leído y añadido al conjunto las especies anteriores a i.
    // Las especies entre [i...n-1] aún no han sido tratadas.
    for (int i=0; i<n; ++i) {
        Especie e;
        e.lee_especie(k);
        Cjt.insert(make_pair(e.consultar_id_especie(), e));
    }
    // Post: han sido leídas y añadidas al conjunto las especies desde [i=0...i=n-1].
    crea_distancias();
}

void Cjt_especies::imprime_cjt_especies() const{
    // Imprime un conjunto de especies
    map<string,Especie>::const_iterator it = Cjt.begin();
    // Inv: Los iteradores posteriors a it no han sido imprimidos
    // Se han imprimido los valores de it "second" (especies) de los elementos entre Cjt.begin()
    // y el anterior a it
	while(it != Cjt.end()) {
		(*it).second.imprime_especie();
        ++it;
	}
    // Post: se han imprimido los elementos del conjunto desde Cjt.begin() hasta Cjt.end()-1
}

void Cjt_especies::tabla_distancias() const{
    // Imprime la tabla de distancias del conjunto de especies
    map<string, map <string,double> >::const_iterator it = Tabla.begin();
    // Inv: Los iteradores posteriors a it no han sido imprimidos
    // Se han imprimido los valores de it de los elementos entre Tabla.begin() y el anterior a it
    while (it!=Tabla.end()) {
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
    // Post: se han imprimido los elementos de la tabla desde Tabla.begin() hasta Tabla.end()-1
}

