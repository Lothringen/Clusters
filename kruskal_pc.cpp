#define Trabajo using
#define Practico namespace
#define II std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <tuple>
#include <cstdlib>
#include <fstream>
#include <string>
#include <utility>
#include <list>
#include <climits>



Trabajo Practico II



vector<eje> kruskal_pc(vector<eje> &lista_aristas, int n){
    // Inicializar la variable de solución:
    vector<eje> agm_kruskal_pc;

    // Caso lista de aristas vacías:
    if(lista_aristas.empty()){
        return agm_kruskal_pc;
    }

    // Ordenar de menor a mayor por peso de las aristas.
    sort(lista_aristas.begin(), lista_aristas.end(), minima_distancia);
    
    // Inicializar el conjunto disjunto c, con n componentes conexas:
    DisjointSet c(n);
    // Iterador entre las aristas del grafo completo.
    int j = 0;
    // Contador de cantidad de aristas del AGM.
    int i = 0;
    while(i < n-1){
        if(c.pc_find(lista_aristas[j].p) != c.pc_find(lista_aristas[j].q)){
            c.pc_union(lista_aristas[j].p, lista_aristas[j].q);
            // La arista forma parte del AGM.
            agm_kruskal_pc.push_back(lista_aristas[j]);
            ++i;
        }
        ++j;
    }
    return agm_kruskal_pc;
}


