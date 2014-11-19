#include "Region.hpp"

string Region::RegionTypeName (Region_Type tipo) {
	const string names[] = {
		"castle",
		"village",
		"forest",
		"cave"
	};
	
	return names[tipo];
}

/* * * * * * * * * * * *
 * REGIÃO ctor e dtor  *
 * * * * * * * * * * * */
Region::Region (int ID, Region_Type new_type, int x, int y) 
		: ID (ID), type (new_type), x (x), y (y) {
	diplomacy = 0;

	// dependendo do tipo, precisamos das tais estruturas
	vector<Structure_Type> aux;
	StructureFactory factory;
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
	for (auto structype : aux) {
		// a nova estrutura
		// pra cada uma que tiver que criar, faça-o		
		// e joga lá dentro do vetor
		inner_structures.push_back (factory.createStructure (structype));
	}
}


Region::~Region () {
	for (auto & S : inner_structures)
		delete (S);
}


/* * * * * * * * * * * * *
 * REGIÃO outras coisas  *
 * * * * * * * * * * * * */
Region_Type Region::getType () {
	return type;
}


int Region::getX () {
	return x;
}


int Region::getY () {
	return y;
}


unsigned int Region::getAdjQuantity () {
	return neighbourhood.size ();
}


set<Region *> Region::getNeighbourhood () {
	return neighbourhood;
}


vector<Structure *> Region::getStructures () {
	return inner_structures;
}


int Region::getDistance (Region *region) {
	int x = this->x - region->x;
	int y = this->y - region->y;
	return (x * x + y * y);
}


void Region::print () {
	cout << "Região " << ID << ": " << x << "x" << y << '\n';
	cout << "Tipo: " << RegionTypeName (type) << "; ";
	cout << "Adjacentes: ";
	for (auto R : neighbourhood) {
		cout << R->ID << ", ";
	}
	cout << "\n\n";
}
