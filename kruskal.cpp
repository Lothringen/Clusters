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
#include "disjoint_set.cpp"



Trabajo Practico II


vector<eje> listaEjes(vector<punto>& nodos){
	int n = nodos.size();	
	int distM;
	vector<eje> ejes;
	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			distM = abs(nodos[i].x - nodos[j].x) + abs(nodos[i].y - nodos[j].y);		
			eje e = {i, j, distM};			
			ejes.push_back(e);

		} 
	}
	return ejes;
}


bool minima_distancia(eje &a, eje &b){
     return a.dist <= b.dist;
}


vector<eje> kruskal(vector<eje> &lista_aristas, int n){
    // Inicializar la variable de salida>
    vector<eje> agm_kruskal;
    // Caso lista de aristas vacías:
    if(lista_aristas.empty()){
    	return agm_kruskal;
    }

    // Ordenar de menor a mayor por distancia en la lista de aristas.
    sort(lista_aristas.begin(), lista_aristas.end(), minima_distancia);
	// Inicializar el conjunto disjunto c, con n componentes conexas:
	DisjointSet c(n);

    int i = 0;
	while(!c.conjuntos_unidos()){
		// Chequear si el representante del nodo a no es el mismo que el del nodo b:
		if(c.ds_find(lista_aristas[i].p) != c.ds_find(lista_aristas[i].q)){
			// Si son distintos, se unen.
			c.ds_union(lista_aristas[i].p, lista_aristas[i].q);
			// La arista forma parte del AGM.
			agm_kruskal.push_back(lista_aristas[i]);
		}
        ++i;
	}
    return agm_kruskal;
}





