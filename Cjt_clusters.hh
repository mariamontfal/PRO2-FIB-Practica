/** @file Cjt_clusters.hh
    @brief Representa el conjunto de características y operaciones relativas a los clústers
*/

#ifndef CJT_CLUSTERS_HH
#define CJT_CLUSTERS_HH
#ifndef NO_DIAGRAM    
#include "BinTree.hh"
#include <iostream>
#include <map>
using namespace std;
#endif


/** @class Cjt_clusters
    @brief Representa el conjunto de características y operaciones relativas a los clústers

    Esta clase es la encargada de gestionar toda la información relativa a los clústers.
    Por tanto, tiene definidos los métodos correspondientes a: crear un clúster y crear la tabla de distancias
    para el conjunto de clústers incializadas originalmente a -1. Se encarga también de ejecutar un paso wpgma, y 
    por ello contiene métodos para: encontrar la distancia mínima de la tabla y fusionar los clústers correspondientes.
    Además, se encarga de actualizar la tabla de distancias siempre que fusiona dos clústers.
    Contiene también, los métodos de consulta para saber si es posible ejecutar un paso wpgma o si el arbol está vacío, 
    a parte de la típica boolena de existencia.
    Finalmente, tiene implementados los métodos dedicados a la impresión del árbol filogenético (llama iterativamente a los
    métodos responsables de ir fusionando clústers), impresión de un clúster e impresión de la tabla de distancias de
    los grupos.

*/

class Cjt_clusters {

    private:
        /** @brief Conjunto de clústers: el primer elemento es el identificador y el segundo es la clúster 
        con su identificador y distancia */
        map< string, BinTree < pair<string,double> > >Arbol; 

        /** @brief Conjunto de distancias entre clústers. 
        El primer elemento del primer bloque es el identificador del clúster, y el primer elemento del segundo
        bloque es el identificador del segundo clúster. El segundo elemento del segundo bloque es la distancia entre ambas.*/
        map<string,map<string,double> > Tab_clu;
            
            /** 
            @brief Consultora: Pasa por referencia los identificadores y la distancia mínima
            \pre <em>Cierto.</em>
            \post Pasa por referencia los dos identificadores con menor distancia entre si junto con la distancia entre ambos.
            */
        void dist_minima(string& a, string& b, double& d) const;

            /** 
            @brief Consultora: Devuelve la distancia. 
            \pre <em>Cierto.</em>
            \post Devuelve la distancia entre los clústers de los parámetros.
            */
        double distancia_cl(const string& a, const string& c) const;

            /**
            @brief Acción que imprime el clúster del parámetro.
            \pre El clúster existe en el conjunto.
            \post Imprime el clúster (su “estructura arborescente”).
            */
        void imprime_arbol(const BinTree < pair <string,double> >& c) const;

            /** 
            @brief Modificadora: Actualiza la tabla de distancias con el nuevo clúster.
            \pre <em>Cierto.</em>
            \post Modifica las tabla de distancias con el nuevo clúster después de ejecutar un paso wpgma.
            Ha recalculado las distancias con la fusión del clúster creado y ha eliminado las anteriores referentes a
            a y a b.
            */
        void actualiza_tab(const string& a, const string& b);

            /** 
            @brief Modificadora: Añade al p.i.la fusión de los clústers a menor distancia.
            \pre Existen al menos, dos clústers con distancia mínima.
            \post Los clústers con distancia mínima han sido fusionados en el árbol (conjunto de clústers) y se ha 
            calculado la nueva distancia del clúster creado.
            */
        void fusiona_cluster(const string& a, const string& b, const double& d);



    public:

    //Constructora

            /** 
            @brief Constructora por defecto.
            \pre <em>Cierto.</em>
            \post Crea un Cjt_clusters vacío.
            */
        Cjt_clusters();


    //Destructora

            /** 
            @brief Destructora por defecto.
            */
        ~Cjt_clusters();


    //Consultora

            /** 
            @brief Consultora: Encuentra el clúster a imprimir.
            \pre La especie existe dentro del conjunto de clústers.
            \post Encuentra el clúster asociado al identificador pasado por referencia y llama a la función imprime_arbol, 
            pasándole por referencia el clúster encontrado.
            */
        void imprime_cluster(const string& id_especie) const;

            /** 
            @brief Consultora: Indica si existe el clúster.
            \pre <em>Cierto.</em>
            \post Indica si existe un clúster asociado al identificador en el conjunto del p.i.
            */
        bool existe_cluster(const string& id_especie) const;

            /** 
            @brief Consultora: Indica si el árbol está vacío.
            \pre <em>Cierto.</em>
            \post Indica si el árbol está vacío.
            */
        bool arbol_vacio() const;

            /** 
            @brief Consultora: Indica si el árbol contiene más de un clúster.
            \pre <em>Cierto.</em>
            \post Indica si el árbol contiene más de un clúster y es apto para ejecutar un paso del algoritmo wpgma.
            */
        bool apto_para_wpgma() const;

        int calcula_hijos() const;
        

    //Modificadora

            /** 
            @brief Modificadora: Ejecuta un paso del algoritmo wpgma.
            \pre Existen dos clústers o más.
            \post Algoritmo que localiza los dos clústers a menor distancia, los fusiona y añade la fusión al conjunto del p.i. 
            Actualiza la tabla de distancias para el p.i. con el nuevo clúster y la imprime por el canal estándar de salida.
            Además, han sido eliminados del p.i. los árboles inicialices antes de fusionarlos.
            */
        void ejecuta_paso_wpgma();

            /** 
            @brief Modificadora: Crea un clúster.
            \pre <em>Cierto.</em>
            \post Crea un clúster con la información pasada por referencia (que contiene el identificador y distancia=-1) y los 
            añade al conjunto de clústers (p.i). 
            */
        void crea_clusters(const pair<string,double>& e);

            /** 
            @brief Modificadora: Crea una tabla de distancias.
            \pre <em>Cierto.</em>
            \post Añade la distancia entre el identificador a y el resto de clústers iniciados.
            */
        void crea_tabla_cluster(const string& a, const map<string,double>& b);

 
    //Lectura y escritura
    
            /**
            @brief Acción que imprime la tabla de distancias entre clústers
            \pre <em>Cierto.</em>
            \post Imprime la tabla de distancias del p.i. entre clústers por el canal estándar de salida.
            */
        void imprime_tab_distancias() const;

            /**
            @brief Acción que imprime el clúster. 
            \pre <em>Cierto.</em>
            \post El algoritmo ha fusionado los clústers hasta unirlos en un único árbol. 
            Imprime por el canal estándar de salida el árbol generado.
            */
        void imprime_arbol_filogenetico();

};

#endif
