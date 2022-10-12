/** @file Especie.hh
    @brief Especificación de la clase Especie
*/

#ifndef ESPECIE_HH
#define ESPECIE_HH
#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#endif
using namespace std;

/*
* Clase Especie
*/

/** @class Especie
    @brief Representa la información y las operaciones asociadas a una especie.

    Damos por hecho que las especies son válidas y están definidas correctamente, es decir, estas contienen 
    toda la información relativa a las especies completa (kmer y gen).

    Ofrece el método para obtener las divisiones del gen en k carácteres, el método para la distancia
    entre el parámetro implícito y otra especie y métodos básicos de consulta, lectura y escritura.
    Se crea una constructora con la k para poder llamar a esta constructora desde el conjunto de especies; 
    de esta forma podemos añadir la función relacionada con la división del gen entre k carácteres en la parte privada.
*/

class Especie {

    private:
        /** @brief Identificador de la especie */
        string id_especie;
        /** @brief Gen de la especie */
        string gen; 
        /** @brief Conjunto de substrings generados al dividir el gen de la especie en k carácteres junto con sus repeticiones */
        map<string,int> kmer;

            /** 
            @brief Modificadora: Calcula los substrings del gen divididos en k carácteres.
            \pre <em>Cierto.</em>
            \post Rellena la información del p.i. con los substrings del gen divididos en k carácteres junto 
            con un <em>integer</em> que indica las repeticiones de cada substring diferente del gen.
            */
        void obtener_kmer(const int k);    
        

    public:

    //Constructora
            /** 
            @brief Creadora por defecto.
            \pre <em>Cierto. </em>
            \post Crea una especie vacía.
            */
        Especie();

            /** 
            @brief Creadora con identificador y gen.
            \pre <em>Cierto. </em>
            \post Crea una especie con los parámetros pasados por referencia de la función del identificador y el gen.
            Rellena la información del p.i. con los substrings asociados al gen divididos en k carácteres.
            */   
        Especie(const string& id_especie, const string& gen, const int k);


    //Destructora
            /** 
             @brief Destructora por defecto.
            */
        ~Especie();


    //Consultoras
            /** 
            @brief Consultora: Consulta el gen asociado a la especie.
            \pre <em>Cierto. </em>
            \post Devuelve el gen asociado a una especie.
            */
        string consultar_gen() const;
        
            /** 
            @brief Consultora: Consulta el identificador asociado a la especie.
            \pre <em>Cierto. </em>
            \post Devuelve el identificador asociado a una especie.
            */
        string consultar_id_especie() const;

            /**
            @brief Consultora: Determina la distancia entre dos especies.
            \pre Ambas especies existen y tienen un gen asociado. 
            \post Devuelve la distancia entre la especie del p.i. y la especie b. La distancia estará comprendida 
            entre 0 y 100 (distancia mínima y máxima entre dos especies).
            */ 
        double distancia(const Especie& b) const;


    //Lectura y escritura
            /**
            @brief Lectura: Acción que lee una especie.
            \pre Hay preparados en el canal estándar de entrada un identificador y un gen.
            \post Se ha leído por el canal estándar de entrada el identificador y el gen del p.i. y se ha calculado
            la información de todos los substrings del gen en k carácteres del p.i.
            */
        void lee_especie(const int k);

            /**
            @brief Escritura: Acción que imprime una especie.
            \pre <em>Cierto.</em>
            \post Se ha escrito por el canal estándar de salida la especie del p.i.
            */
        void imprime_especie() const;      
};

#endif 
