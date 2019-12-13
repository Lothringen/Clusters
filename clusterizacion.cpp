#include "clusters.cpp" 


int main(){

/*****Entrada de datos*****/
    int n, x, y;
    punto p;
    cin >> n;
    vector<punto> nodos;
    for(int k = 0; k < n; k++){
        cin >> x >> y;
        p.x = x;
        p.y = y;
        p.cluster = 0;			//inicialmente todos van a estar en el mismo cluster, 0.
        nodos.push_back(p);		//cargo todos los nodos del plano en un vector

    }

		 

    /******************************************************************************
     clusterizar(vector<punto>& nodos, char metodo,int d, int h, int u, string agmMetodo)

     opciones de clusterizacion:

     metodo:
     
     * 'f' = factor de inconsistencia,
     * 's' = desviacion estandar
     * 'a' = para utilizar ambos metodos al mismo tiempo


     parametros:
	* d: profundidad a la que quiero ver los vecinos d =1, 2 o 3.
     * h: es la cota de f , h>=2.
     * u: factor multiplicativo para la cota de la desviacion media, u=3 o 4.
     

	 agm:

	 * Prim
	 * Kruskal
	 * Kruskal_pc	

     ****************************************************************************/

    clusterizar(nodos, 'a',2, 2, 3, "Kruskal_pc");

/*****Salida de datos*****/

    for(int i=0; i<n; i++){
        cout << i << " " << nodos[i].cluster << endl;
    }

    return 0;
}

