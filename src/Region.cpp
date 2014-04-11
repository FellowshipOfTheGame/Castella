#include "Region.hpp"

/* * * * * * * * * * * *
 * REGIÃO ctor e dtor  *
 * * * * * * * * * * * */
Region::Region (Region_Type new_type) {
	type = new_type;
	diplomacy = 0;

	/// @todo ver como por o x/y da região, talvez aleatoriamente incrementado dos já existentes

	// dependendo do tipo, precisamos das tais estruturas
	std::vector<Structure_Type> aux;
	switch ((int) type) {
		case castle:
			aux.push_back (throne);
			aux.push_back (tavern);
			aux.push_back (blacksmith);
			break;

		case village:
			aux.push_back (townhall);
			aux.push_back (tavern);
			aux.push_back (blacksmith);
			break;

		case forest:
			aux.push_back (woods);
			break;

		case cave:
			aux.push_back (mines);
			break;
	}
	// e põe as tais dentro da região
	for (int i = 0; i < aux.size(); i++) {
		// a nova estrutura
		Structure *new_structure;
		// pra cada uma que tiver que criar, faça-o
		switch (aux[i]) {
			case throne: new_structure = new Throne (); break;
			case townhall: new_structure = new Townhall (); break;
			case blacksmith: new_structure = new Blacksmith (); break;
			case tavern: new_structure = new Tavern (); break;
			case woods: new_structure = new Woods (); break;
			case mines: new_structure = new Mines (); break;
		}
		// e joga lá dentro do vetor
		inner_structures.push_back (new_structure);
	}
}


Region::~Region () {
	inner_structures.clear();
}


/* * * * * * * * * * * * *
 * REGIÃO outras coisas  *
 * * * * * * * * * * * * */
Region_Type Region::getType () {
	return type;
}


int Region::Distance (Region *region) {
	return (std::abs ((pow (x, 2) - pow (region->x, 2)) + (pow (y, 2) - pow (region->y, 2))));
}





/* * * * * * * * * * * *
 *                     *
 * GRAFO DAS REGIÕES   *
 *                     *
 * * * * * * * * * * * */
RegionGraph::RegionGraph () {
	
}


int RegionGraph::NewRegion (Region_Type new_type) {
	// mais uma região!
	Region* aux = new Region (new_type);
	// e guarda ela lá no grafo
	regions.push_back (aux);
	
	// aumenta a matriz de arestas
	int size = adjacency_matrix.size ();
	adjacency_matrix.resize (++size);
	for (int i = 0; i < size; i++) {
		adjacency_matrix[i].resize (size);
	}
	// e vê se liga com os vizinhos
	findLastNeighbours ();

	return 0;
}


void RegionGraph::findLastNeighbours () {
	int last = regions.size ();
	bool aux;
	// pra cada possível candidato a vizinho
	for (int i = 0; i < last; i++) {
		// se for mesmo vizinho
		aux = (regions[i]->Distance (regions[last]) < NEIGHBOUR_MAX_DISTANCE) ? true : false;
		
		adjacency_matrix[i][last] = adjacency_matrix[last][i] = aux;
	}
}
