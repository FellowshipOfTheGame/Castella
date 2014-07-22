#include <Region.hpp>

std::string typeName (Region_Type tipo) {
	const std::string names[] = {
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
Region::Region (int ID, Region_Type new_type, int x, int y) {
	this->ID = ID;
	this->x = x;
	this->y = y;
	type = new_type;
	diplomacy = 0;

	// dependendo do tipo, precisamos das tais estruturas
	std::vector<Structure_Type> aux;
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
	for (Structure_Type structype : aux) {
		// a nova estrutura
		// pra cada uma que tiver que criar, faça-o		
		// e joga lá dentro do vetor
		inner_structures.push_back (factory.createStructure (structype));
	}
}


Region::~Region () {
	for (Structure *&S : inner_structures)
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


std::set<Region*> Region::getNeighbourhood () {
	return neighbourhood;
}


int Region::getDistance (Region *region) {
	int x = this->x - region->x;
	int y = this->y - region->y;
	return (pow (x, 2) + pow (y, 2));
}


void Region::print () {
	std::cout << "Tipo: " << typeName (type) << "; ";
	std::cout << ID << ':' << x << "x" << y << '\n';
	std::cout << "Adjacentes: ";
	for (Region *R : neighbourhood) {
		std::cout << R->ID << ", ";
	}
	std::cout << "\n\n";
}
