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
#include "prim.cpp"
#include "kruskal.cpp"
#include "kruskal_pc.cpp"

Trabajo Practico II

void calcularDist(MatrizDist &grafo, vector<punto>& nodos){
    int n = nodos.size();
    int distM;
    //inicialmente toda la matriz tiene ceros, que luego quedaran en la diagonal unicamente
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            distM = abs(nodos[i].x - nodos[j].x) + abs(nodos[i].y - nodos[j].y);
            grafo[i][j] = distM;	//La matriz de distancias es simetrica, y tiene ceros en la diagonal
            grafo[j][i] = distM;
        }
    }

}


bool maxima_distancia(eje &a, eje &b){
    return a.dist >= b.dist;
}



//Es un BFS que recorre nodos hasta la profundidad d, y devuelve un vector de los pesos de los ejes que se encuentran a profundidad d del origen
vector<int> vecinos(MatrizDist &M, int origen, int d){  //d = local neighborhood depth, el origen es el numero del nodo = numero de orden de entrada
    int n = M[0].size();
    int i;
    vector<int> vecinos;
    queue<int> cola;
    vector<int> profundidad(n,n);		//El tamaño es n, e inicialmente la profundidad de todos los elementos es n (es mayor a la max posible 											que es n-1)
    cola.push(origen);
    profundidad[origen] = 0;			//El nodo origen esta a profundidad 0 de si mismo
    while(!cola.empty()){
        i = cola.front();
        cola.pop();
        for(int j = 0; j<n; j++){
            if(profundidad[j] == n && M[i][j] != -1){	 //si la profundidad es n -> el nodo no fue visitado, si M[i][j] != -1 es un nodo 															vecino
                profundidad[j] = profundidad[i] + 1;	//actualizo la profundidad -> pasa a estar visitado
                if(profundidad[j] <= d){				//si el nodo esta a una profundidad menor o igual a d encolo el nodo
                    cola.push(j);						//repito luego para los vecinos de ese nodo que no hayan sido visitados
                    vecinos.push_back(M[i][j]);						//agrego el peso de la arista
                }
            }
        }
    }

        return vecinos;
}

//Es un BFS que recorre todos los niveles del arbol y va asignando un valor al cluster
void clusterizarLadoB(MatrizDist &M, int &num_cluster, vector<punto> &nodos, int origen){	//origen = valor de la fila --> (en el ladoB = j)
   
    int n = M[0].size();
    int i;
    queue<int> cola;
    vector<int> profundidad(n,n);		//El tamaño es n, e inicialmente la profundidad de todos los elementos es n (es mayor a la max posible 											que es n-1)
    cola.push(origen);
    profundidad[origen] = 0;			//El nodo origen esta a profundidad 0 de si mismo
    while(!cola.empty()){
        i = cola.front();
        cola.pop();
        nodos[i].cluster = num_cluster;		//voy cambiando en el vector de nodos el numero de cluster al que pertenece
        for(int j = 0; j<n; j++){
            if(profundidad[j] == n && M[i][j] != -1){ 	//nodo no visitado y es vecino
                profundidad[j] = profundidad[i] + 1;		//actualizo la profundidad -> pasa a estar visitado
                cola.push(j);					//repito luego para los vecinos de ese nodo que no hayan sido visitados
            }

        }
    }

}

float promedio(vector<int>& v) {
    int n = v.size();
    float suma = 0;
    for (int i = 0; i < n; i++) {
        suma += v[i];
    }
    if(n == 0){
        return 0;
    }else{
        return suma/n;
    }
}


MatrizDist matrixAGM(vector<eje>& ejes, int n){    //tiene un costo espacial de crear una nueva matriz
   int m = ejes.size();
    MatrizDist agm(n,vector<int>(n,-1));		//inicialmente toda la matriz tiene infinitos = -1
    for(int i=0; i<m; i++){
        agm[i][i] = 0;
        agm[ejes[i].p][ejes[i].q] = ejes[i].dist;
        agm[ejes[i].q][ejes[i].p] = ejes[i].dist;
    }
    return agm;
}




//El parametro h es la cota de f, el parametro l es el factor multiplicativo para la cota de la desviacion media
//d es la profundidad a la que quiero ver los vecinos
void clusterizar(vector<punto>& nodos, char metodo,int d, int h, int u, string agmMetodo){
		 int n = nodos.size();
		 int x = 0;	  
		 MatrizDist grafo(n, vector<int>(n, 0));
		 vector<eje> lista_ejes_agm;		     
		 if(agmMetodo == "Prim"){
	
        	calcularDist(grafo, nodos);
        	lista_ejes_agm = algoritmoDePrim(grafo);            //obtengo el AGM
			//ordenare de mayor a menor, a partir del segundo elemento, el primero no lo considero no es arista en realidad, (origen, origen, 0).
			x = 1;

		}else if(agmMetodo == "Kruskal"){

			lista_ejes_agm = listaEjes(nodos);
			lista_ejes_agm = kruskal(lista_ejes_agm, n);
					

		}else if(agmMetodo == "Kruskal_pc"){

			lista_ejes_agm = listaEjes(nodos);
			lista_ejes_agm = kruskal_pc(lista_ejes_agm, n);

		} 


		sort(lista_ejes_agm.begin() + x, lista_ejes_agm.end(), maxima_distancia);
		grafo = matrixAGM(lista_ejes_agm, n);    	//Ahora grafo contiene el agm
		int num_cluster = 0;     				//le asigno un numero al cluster   
		int l = lista_ejes_agm.size();
        int i, j, w_eje;
        float ladoA, ladoB,f,s, prom;        	
        vector<int> vecinosA, vecinosB;
        for (int k = x; k < l; k++) {   //k=0 no lo considero porque es la arista (origen, origen, 0), que se crea en el algoritmo de prim
            i = lista_ejes_agm[k].p;
            j = lista_ejes_agm[k].q;
            w_eje = lista_ejes_agm[k].dist;   	//preservo el valor del max
            grafo[i][j] = -1;            		//preventivamente saco el posible eje inconsistente
            grafo[j][i] = -1;

  			//lo calculo para profundidad d
            vecinosA = vecinos(grafo, i, d);
            vecinosB = vecinos(grafo, j, d);
            
			if(metodo == 'f' || metodo == 'a'){			
				ladoA = promedio(vecinosA);                      
		        ladoB = promedio(vecinosB);

		        if(ladoA == 0 && ladoB == 0){
		                f = w_eje;
		                prom = 0;
		        }else if(ladoA == 0) {
		                prom = ladoB;
		                f = w_eje / prom;

		        }else if(ladoB == 0) {
		                prom = ladoA;
		                f = w_eje / prom;
		        }else {
		                prom = (ladoA + ladoB) / 2;
		                f = w_eje / prom;        		//calculo del factor de inconsistencia = Wi/promedio vecinos Wj
		        }
			}
			if(metodo == 's' || metodo == 'a'){
		        float suma = 0;
		        float dif;
		        long longA = vecinosA.size();
		        long longB = vecinosB.size();
		        for(int i = 0; i<longA; i++){
		            dif = vecinosA[i] - ladoA;
		            suma+= pow(dif,2);

		        }
		        for(int i = 0; i<longB; i++){
		            dif = vecinosB[i] - ladoB;
		            suma+= pow(dif,2);
		        }
		        s = sqrt(suma/(longA + longB -1));  				// obtengo desviacion estandar, es sobre n-1
			}
            if(metodo == 'f') {
                if (f < h) {                                    //si no era inconsistente, vuelvo a restaurar el valor del maximo
                    grafo[i][j] = w_eje;
                    grafo[j][i] = w_eje;
                } else {
					num_cluster++;
                    clusterizarLadoB(grafo, num_cluster, nodos, j);        //arranco viendo la fila de nodos vecinos de j
                }
            }else if (metodo == 's'){							//calculo desviacion estandar
                if( w_eje  > (u*s + prom)){  					//podria ser tambien mayor a 4*s + prom
                	num_cluster++;	   
					clusterizarLadoB(grafo, num_cluster, nodos, j);
                }else{
                    grafo[i][j] = w_eje;
                    grafo[j][i] = w_eje;
                }
            }else if(metodo == 'a'){
                if(f>=h && w_eje  > (u*s + prom)){
					num_cluster++;
                    clusterizarLadoB(grafo, num_cluster, nodos, j);
                }else{
                    grafo[i][j] = w_eje;
                    grafo[j][i] = w_eje;
                }
            }
        }

}
