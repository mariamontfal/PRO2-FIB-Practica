/** @file Especie.cc
    @brief Código de la clase Especie
*/

#include "Especie.hh"
#include <cmath>

//Constructoras y destructora

Especie::Especie(){}

Especie::Especie(const string& id_especie, const string& gen, const int k){
    //Inicializa una especie con el id y el gen de los parámetros pasados por referencia y 
    //obtiene los kmeros asociados a su gen
    this->id_especie=id_especie;
    this->gen=gen;

    obtener_kmer(k);
}

Especie::~Especie(){}


//Consultoras

string Especie::consultar_gen() const{
    return gen;
}

string Especie::consultar_id_especie() const{
    return id_especie;
}

double Especie::distancia(const Especie& b) const{ 

    map<string,int>::const_iterator it_a = kmer.begin();
    map<string,int>::const_iterator it_b = b.kmer.begin();
    double v=0;
    double w=0;
    double top=0;
    double aux=0;

    while (it_a!=kmer.end() and it_b!=b.kmer.end()) {
        if ((*it_a).first==(*it_b).first) {
            aux=(*it_a).second-(*it_b).second;
            top+=aux*aux;

            v+=(*it_a).second*(*it_a).second;
            w+=(*it_b).second*(*it_b).second;
            ++it_a;
            ++it_b;
        } 
        else if ((*it_a).first<(*it_b).first) {
            top+=(*it_a).second*(*it_a).second;
            v+=(*it_a).second*(*it_a).second;
            ++it_a;
        }
        else {
            aux=0-(*it_b).second;
            top+=aux*aux;
            w+=(*it_b).second*(*it_b).second;
            ++it_b;
        }
    }
    while (it_a!=kmer.end()) {
        top+=(*it_a).second*(*it_a).second;
        v+=(*it_a).second*(*it_a).second;
        ++it_a;
    }

    while (it_b!=b.kmer.end()) {
        aux=0-(*it_b).second;
        top+=aux*aux;
        w+=(*it_b).second*(*it_b).second;
        ++it_b;
    }
    
    top=sqrt(top);
    v = sqrt(v);
    w = sqrt(w);
    double res= v + w;

    return ((1-(top/res))*100);
}




//Modificadora

void Especie::obtener_kmer(const int k) {  
    // Tratamos de obtener el conjunto de substrings que forman las divisiones del gen en k 
    // divisiones de la especie del p.i.

    // Inv: Los carácteres posteriores a i no se han visitado. Se han generado substrings para
    // las i anteriores de la forma: i+k-1
    for (int i=0; i<gen.length()-k+1; ++i) {
        string aux="";
        // Inv: j<k. 
        // Se han concatenado los valores anteriores a j 
        for (int j=i; j<k+i; ++j) {
            aux+=gen[j];
        }
        if (i==0) kmer.insert(make_pair(aux,1));
        else {
            map<string,int>::iterator it;
            it=kmer.find(aux);
            if (it != kmer.end()) (*it).second +=1;
            else kmer.insert(make_pair(aux,1));
        }
        // Post: aux tiene el valor concatenado de j+k-1. Se ha añadido a kmer el pair aux que 
        // toma el valor del substring generado junto con sus repeticiones desde i=0 hasta la i actual
    }
    // Post: se han generado todos los substrings posibles y se han añadido de forma correcta al kmer
    // hasta i=gen.length()-k+1
}


//Lectura y escitura

void Especie::lee_especie(const int k) {
    //Lee una especie y obtiene el map de substrings asociados al gen en k carácteres
    cin>>id_especie>>gen;
    obtener_kmer(k);
}

void Especie::imprime_especie() const {
    //Imprime una especie
    cout<<id_especie<<" "<<gen<<endl;
}





