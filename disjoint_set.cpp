#include "disjoint_set.h"


// Constructor:
DisjointSet::DisjointSet(int cant_nodos) : representantes(cant_nodos), componentes(cant_nodos), alturas(cant_nodos, 1) {
	for(int i = 0; i < cant_nodos; ++i){
		// Cada nodo es representante de sí mismo:
		representantes[i] = i;
		// Cada uno empieza siendo un nodo aislado.
		componentes[i].push_back(i);
	}
}


int DisjointSet::ds_find(int x) {
	return representantes[x];
}


void DisjointSet::ds_union(int x, int y) {
    int c;
    // Obtener los representantes de ambos.
	x = representantes[x];
    y = representantes[y];

	if (componentes[x].size() > componentes[y].size()){
		swap(x, y);
	}

	while(!componentes[x].empty()){
		c = componentes[x].front();
		representantes[c] = y;
        componentes[y].push_back(c);
		componentes[x].pop_front();
	}
}


int DisjointSet::pc_find(int x){
	// Chequear si el representante de x no es sí mismo.
	if(representantes[x] != x)
		// Aplicar recursivamente la función.
		representantes[x] = pc_find(representantes[x]);
	return representantes[x];
}


void DisjointSet::pc_union(int x, int y){
	// Obtener los representantes de ambos.
	x = pc_find(x);
	y = pc_find(y);

	if (alturas[x] > alturas[y]){
		representantes[y] = x;
	} 
	else{
		if(alturas[x] == alturas[y]){
			representantes[y] = x;
			alturas[x] +=1;
		}
		else{
			representantes[x] = y;
		}	
	} 
}


bool DisjointSet::conjuntos_unidos(){
	// Si el tamaño de los representantes coincide con la cantidad de componentes que tiene el primer elemento de representantes, todos los conjuntos disjuntos han sido unidos.
	return componentes[representantes[0]].size() == representantes.size();
}