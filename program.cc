/**
  @mainpage Práctica Primavera 2020: Árbol filogenético. Documentación.
  
  Documentación final para la Práctica Primavera 2020. En ella se encuentran tanto los atributos
  privados como públicos, así como el código final utilizado. 

  El programa principal de la práctica pertenece al módulo program.cc. 
  Este módulo será el encargado de leer la constante k, y de crear un conjunto de especies y un conjunto de clústers vacíos 
  para posteriormente hacer las llamadas a los métodos solicitados y lanzar los mensajes de error en caso de ser necesarios.
  
  Atendiendo a los tipos de datos sugeridos en el enunciado, se necesitan módulos para representar el Cjt_clusters 
  (finalmente se reducirá a un único clúster identificado como árbol filogenético), otro para el Cjt_especies 
  y otro para Especie.
  
  Entre otras funcionalidades de la práctica, la más importante será la creación de un árbol filogenético de un conjunto
  de clústers (inicialmente especies), es decir, calcular cuales son los predecesores más cercanos e ir fusionándolos 
  para su posterior impresión. 

  Lenguaje: c++

  Versión: 3.4

  Autora: Maria Montalvo Falcón

  Fecha: 19/05/2020
 */


/** @file program.cc
    @brief Programa principal para la práctica Primavera 2020 - Árbol filogenético.
    
    Se toma como asunción que los datos leídos son siempre correctos, ya que no se incluyen comprobaciones
    para verificar esto. Esto implica, entre otras cosas, que el k leído al inicio del programa principal
    nunca será mayor a la longitud de un gen de cualquier especie.

    Al inicio del programa se lee una constante k la cual nos indica los carácteres en los que dividir el gen de las especies
    del conjunto; después se crean un conjunto de especies y un conjunto de clústers vacíos con los que se
    trabaja a lo largo de la ejecución.
    Además, este módulo es el encargado de hacer las llamadas a los métodos solicitados y lanzar los mensajes 
    de error en caso de ser necesarios.
*/


#ifndef NO_DIAGRAM 
#include <iostream>
#endif
#include "Cjt_especies.hh"

using namespace std;

int main () {
  
  int k;
  cin>>k; //número de carácteres que se utilizará para generar los subtstrings del gen
  string op; //operación a ejecutar

  Cjt_especies cjt;
  Cjt_clusters clu;
  
  while (cin>>op and op!="fin") {

    if (op=="lee_cjt_especies"){
  
      cjt.lee_cjt_especies(k);

      cout<<"# " <<op<<endl;
    }

    else if (op=="crea_especie"){
      string id_especie,gen;
      cin>>id_especie>>gen;
      cout << "# "<< op << " " << id_especie << " " << gen<<endl;
      if (cjt.existe_especie(id_especie)) cout<<"ERROR: La especie "<< id_especie << " ya existe."<<endl;
      else {
        Especie e (id_especie,gen,k);
        cjt.crea_especie(e);
      }
    }
    
    else if (op=="obtener_gen"){
      string id_especie;
      cin>>id_especie;
      cout<<"# "<<op<<" "<<id_especie<<endl;
      if (cjt.existe_especie(id_especie)) cout<<cjt.obtener_gen(id_especie)<<endl;
      else cout<<"ERROR: La especie "<<id_especie<< " no existe."<<endl;
    }
    
    else if (op=="distancia"){
      string id_a, id_b;
      cin>>id_a>>id_b;
      cout<<"# "<<op<<" "<<id_a<<" "<< id_b<<endl;

      if (cjt.existe_especie(id_a) and cjt.existe_especie(id_b)) {
        double d=0;
        if (id_a==id_b) cout<<d;
        else {
          d = cjt.distancia_cjt(id_a,id_b);
        }
        cout << d << endl;
      }
      else if (not cjt.existe_especie(id_a) and not cjt.existe_especie(id_b)) {
        cout << "ERROR: La especie " << id_a <<" y la especie " << id_b << " no existen." <<endl;
      }
      else if (not cjt.existe_especie(id_a)) cout << "ERROR: La especie " <<  id_a << " no existe." << endl;
      else cout << "ERROR: La especie " << id_b << " no existe." << endl;
    }

    else if (op=="elimina_especie"){
      string id_especie;
      cin >> id_especie;
      if (cjt.existe_especie(id_especie)) {
        cout<<"# elimina_especie "<<id_especie<<endl;
        cjt.elimina_especie(id_especie);
      } 
      else {
        cout<<"# elimina_especie "<<id_especie<<endl;
        cout << "ERROR: La especie " <<id_especie<< " no existe."<<endl;
      }
    }

    else if (op=="existe_especie"){
      string id_especie;
      cin >> id_especie;
      cout<<"# "<<op<<" "<<id_especie<<endl;
      if (cjt.existe_especie(id_especie)) cout << "SI"<<endl;
      else cout << "NO" << endl;
    } 
        
    else if (op=="imprime_cjt_especies"){
      cout<<"# "<<op<<endl;
      cjt.imprime_cjt_especies();
    }

    else if (op=="tabla_distancias"){
      cout<<"# "<<op<<endl;
      cjt.tabla_distancias();
    }

    else if (op=="inicializa_clusters"){
      cout<<"# "<<op<<endl;
      clu=Cjt_clusters();
      cjt.inicializa_clusters(clu);
      clu.imprime_tab_distancias();

    }
     
    else if (op=="ejecuta_paso_wpgma"){
      cout<<"# "<<op<<endl;
      if (clu.apto_para_wpgma()) {
        clu.ejecuta_paso_wpgma();
      }
      else {
        cout<<"ERROR: num_clusters <= 1"<<endl;
      }
    }
    
    else if (op=="imprime_cluster"){
      string id_especie;
      cin >> id_especie;
      cout<<"# "<<op<<" "<<id_especie<<endl;
      if (clu.existe_cluster(id_especie)) {
        clu.imprime_cluster(id_especie);
        cout<<endl;
      }
      else cout<< "ERROR: El cluster " <<id_especie<< " no existe."<<endl;

    }

    else if (op=="ejecuta_paso_clust"){
      cout<<"# "<<op<<endl;
      clu=Cjt_clusters();
      cjt.inicializa_clusters(clu);
      if (clu.arbol_vacio()) cout<<"ERROR: El conjunto de clusters es vacio.";
      else {
        clu.imprime_arbol_filogenetico();
      }
      cout<<endl;
    }
    cout<<endl;
  }
}