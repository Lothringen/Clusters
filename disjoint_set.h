#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class DisjointSet {

private:

	vector<int> representantes; 		// Representantes de cada conjunto.
	vector<int> alturas; 				// Vector de alturas.
	vector<list<int> > componentes;

public:

	DisjointSet(int cant_nodos);					// Constructor.
	
	int ds_find(int x); 							// Dado un elemento x, indica el representante del conjunto al que pertenece.
	void ds_union(int x, int y);		// Dados dos elementos x e y , une en uno los conjuntos a los que pertenecen.
	
	int pc_find(int x);					// Íd ds_find, pero para path compression.
	void pc_union(int x, int y); 		// Íd ds_union, pero para path compression.

	bool conjuntos_unidos();			// Indica si se terminaron de unir todos los conjuntos disjuntos.
};

#endif