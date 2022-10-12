/** @file Cjt_especies.hh
    @brief Representa el conjunto de características y operaciones relativas al conjunto de especies
*/

#ifndef CJT_ESPECIES_HH
#define CJT_ESPECIES_HH

#include "Especie.hh"
#include "Cjt_clusters.hh"


/** @class Cjt_especies
    @brief Representa el conjunto de características y operaciones relativas al conjunto de especies.

    Implementa los métodos para crear la tabla distancias entre cada par de especies, así como las que la mofifican
    al añadir o eliminar una especie al conjunto (funcionalidades también de este módulo).
    Ofrece también, el método que iniciliza clústers con la información del conjunto de especies y un método distancia
    como paso previo para calcular la distancia entre dos especies.
    A parte, contiene los típicos métodos boolena de existencia y de lectura y escritura. y la consultora para obtener
    el gen asociado a un identificador. 
    Finalmente, contiene un método para imprimir la tabla de distancias del parámetro implícito.
*/


class Cjt_especies {

    private: 

    /** @brief Conjunto de especies; el primer elemento es el identificador y el segundo es la especie */
    map<string,Especie> Cjt; 

    /** @brief Conjunto de distancias entre especies. 
    El primer elemento del primer bloque es el identificador de una especie, y el primer elemento del segundo
    bloque es el identificador de la segunda especie. El segundo elemento del segundo bloque es la distancia entre ambas.*/
    map <string, map<string,double> > Tabla; // Las dos claves son los dos id_especies diferentes y su distancia.

            /** 
            @brief Modificadora: Crea una tabla de distancias para el conjunto.
            \pre <em>Cierto.</em>
            \post Crea una tabla de distancias para el p.i.
            */
        void crea_distancias ();

            /** 
            @brief Modificadora: Modifica la tabla de distancias después de añadir una especie.
            \pre Las distancias de la nueva especie añadida al conjunto no existen en la tabla del p.i.
            \post Se añaden las distancias con todo el conjunto de la especie nueva pasada por referencia en la tabla de distancias.
            */
        void inserta_tab(const Especie& e);

            /** 
            @brief Modificadora: Modifica la tabla de distancias después de eliminar una especie.:
            \pre La especie con el id pasado por referencia existía en el conjunto pero ha sido eliminada.
            \post Se han eliminado las distancias de la tabla asociadas a la especie pasada por referencia que ha sido previamente eliminada.
            */
        void elimina_tab(const string& id);



    public:

    //Constructora

            /** 
            @brief Constructora por defecto.
            \pre <em>Cierto.</em>
            \post Crea un Cjt_especies vacío.
            */
        Cjt_especies();

    
    //Destructora

            /** 
            @brief Destructora por defecto.
            */
        ~Cjt_especies();


    //Consultora

            /** 
            @brief Consultora: Indica si la especie existe o no.
            \pre <em>Cierto.</em>
            \post El resultado indica si la especie existe en el p.i. o no.
            */
        bool existe_especie(const string& id_especie) const;

            /** 
            @brief Consultora: Devuelve el gen asociado al identificador.
            \pre La especie existe en el p.i.
            \post Devuelve el gen asociado al identificador id_especie.
            */
        string obtener_gen(const string& id_especie) const;

            /** 
            @brief Consultora: Devuelve la distancia entre dos especies.
            \pre <em>Cierto.</em>
            \post Devuelve la distancia entre los dos identificadores de los parámetros pasados por referencia.
            */
        double distancia_cjt(const string& id_a, const string& id_b) const;


    //Modificadora

            /**
            @brief Modificadora: Acción que añade la especie al conjunto del p.i.
            \pre La especie no existe en el conjunto.
            \post La especie pasa a tener los atributos leídos en el programa principal (se calculan también los 
            substrings asociados a las divisiones en k de su gen) y se añade al p.i. 
            */
        void crea_especie(const Especie& e);

            /**
            @brief Modificadora: Acción que elimina una especie del conjunto de especies.
            \pre La especie existe en el conjunto.
            \post Elimina toda la información de la especie del p.i.
            */
        void elimina_especie(const string& id_especie);

            /** 
            @brief Modificadora: Inicializa un conjunto de clústers con las especies del p.i.
            \pre <em>Cierto.</em>
            \post Se han inicializado un conjunto de clústers con las especies del p.i.
            Cada especie ha formado un clúster individual con distancia=-1 (no existe la distancia con ellos mismos). 
            Ha inicializado también, la tabla de distancias de los diferentes clústers (al inicio, está tabla tomará 
            los valores de las distancias entre las especies del conjunto).
            */
        void inicializa_clusters(Cjt_clusters& clu);


    //Lectura y escritura

        /**
            @brief Lectura: Acción que lee un conjunto de especies.
            \pre Hay preparados en el canal estándar de entrada un entero n ≥ 0 y a continuación una secuencia de n especies 
            con sus correspondientes id_especie-gen. No hay id_especies repetidas. Los contenidos previos del conjunto de 
            especies se descartan y las n especies nuevas leídas se agregan al conjunto.
            \post Se han leído por el canal estándar de entrada el conjunto de especies del parámetro implicito.
            */
        void lee_cjt_especies(const int k);

            /**
            @brief Escritura: Acción que imprime un conjunto de especies.
            \pre <em>Cierto.</em>
            \post Se han escrito por el canal estándar de salida el conjunto de especies del parámetro implicito.
            */
        void imprime_cjt_especies() const; 

            /** 
            @brief Escritura: Acción que imprime la tabla de distancias.
            \pre <em>Cierto.</em>
            No hay pares de especiesrepetidos ni distancias duplicadas. 
            \post Imprime la tabla de distancias entre cada par de especies del conjunto (p.i.).
            */
        void tabla_distancias() const;
};

#endif