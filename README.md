# Práctica Primavera 2020: Árbol filogenético

## GEI-PRO2 (2019-2020 Q2)

Nota: 9.6

## Autora

Maria Montalvo Falcón

## Proposito

El programa principal de la práctica pertenece al módulo program.cc. Este módulo será el encargado de leer la constante k, y de crear un conjunto de especies y un conjunto de clústers vacíos para posteriormente hacer las llamadas a los métodos solicitados y lanzar los mensajes de error en caso de ser necesarios.

Atendiendo a los tipos de datos sugeridos en el enunciado, se necesitan módulos para representar el Cjt_clusters (finalmente se reducirá a un único clúster identificado como árbol filogenético), otro para el Cjt_especies y otro para Especie.

Entre otras funcionalidades de la práctica, la más importante será la creación de un árbol filogenético de un conjunto de clústers (inicialmente especies), es decir, calcular cuales son los predecesores más cercanos e ir fusionándolos para su posterior impresión.

Lenguaje: C++

Versión: 3.4

Fecha: 19/05/2020

## Clases

Lista de las clases, estructuras, uniones e interfaces con una breve descripción:
```
 - Cjt_clusters: Representa el conjunto de características y operaciones relativas a los clústers
 - Cjt_especies: Representa el conjunto de características y operaciones relativas al conjunto de especies
 - Especie: Representa la información y las operaciones asociadas a una especie
```

## Archivos

Lista de todos los archivos con descripciones breves:
```
 - Cjt_clusters.cc: Código de la clase Cjt_clusters
 - Cjt_clusters.hh: Representa el conjunto de características y operaciones relativas a los clústers
 - Cjt_especies.cc: Código de la clase Cjt_especies
 - Cjt_especies.hh: Representa el conjunto de características y operaciones relativas al conjunto de especies
 - Especie.cc: Código de la clase Especie
 - Especie.hh: Especificación de la clase Especie
 - program.cc: Programa principal para la práctica Primavera 2020 - Árbol filogenético
 - Makefile
```
