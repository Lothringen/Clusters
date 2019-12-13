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
#include <queue>


Trabajo Practico II

typedef vector<vector<int> > MatrizDist;
typedef pair<int,int> par;

struct punto{
    int x;
    int y;
    int cluster;

};


struct eje{

    int p;		//nodo origen
    int q;		//nodo destino
    int dist;   //dist = peso de la arista = distancia manhattan (|Xa - Xb| + |Ya -Yb|)

};

vector<eje> algoritmoDePrim(MatrizDist &g){
    int n = g[0].size();
    vector<bool> visitado(n, false);
    visitado[0] = true;
    vector<eje> distancia(n);	//creo un vector de tamaño n
    for(int k=0; k<n; k++){
        distancia[k] = {0, k, g[0][k]}; //es la arista con extremo en 0 y k y el peso correspondiente
    }
    int visitados = 1;
    int min, indice_min;
    while(visitados < n){
        min = INT_MAX;
        for(int i=0; i<n; i++){
            if(-1 < distancia[i].dist && distancia[i].dist < min && !visitado[i]){	//Busco el minimo en el vector distancias entre los no visitados
                min = distancia[i].dist;
                indice_min = i;
            }
        }
        visitado[indice_min] = true;	//lo agrego a visitados
        visitados++;
        if(visitados < n){
            for(int j=0; j<n; j++){   //veo sucesores del nodo que halle como distancia minima
                if(g[indice_min][j] != -1 && !visitado[j] && (distancia[j].dist > g[indice_min][j] || distancia[j].dist == -1)){
                    distancia[j].p = indice_min;
                    distancia[j].q = j;
                    distancia[j].dist = g[indice_min][j];
                }
            }

        }

    }
    return distancia;
}



