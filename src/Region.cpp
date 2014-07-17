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
	for (unsigned int i = 0; i < aux.size(); i++) {
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
	for (unsigned int i = 0; i < inner_structures.size (); i++)
		delete (inner_structures[i]);
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


bool Region::liga (Region *region) {
	int x = (this->x / RegionGraph::block_size) - (region->x / RegionGraph::block_size);
	int y = (this->y / RegionGraph::block_size) - (region->y / RegionGraph::block_size);
	
	if (std::abs (x) > 1 || std::abs (y) > 1)
		return false;
	else
		return true;
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


/* * * * * * * * * * * *
 *                     *
 * GRAFO DAS REGIÕES   *
 *                     *
 * * * * * * * * * * * */
Region *& RegionGraph::operator[] (unsigned int i) {
	try {
		return regions.at (i);
	}
	catch (const std::out_of_range& oor) {
		throw oor;
	}
}


RegionGraph::RegionGraph () {
	// auxiliares pra criar o grafo com distâncias legais
	int x, y;
	unsigned int i, j;
	srand (time (NULL));
	
	for (i = 0; i < map_height; i ++) {
		for (j = 0; j < map_width; j ++) {
			y = (i * block_size) + (rand () % block_size);
			x = (j * block_size) + (rand () % block_size);
			newRegion ((i * map_width) + j, (Region_Type) (rand () % 4), x, y);
		}
	}

	for (Region *R : regions) {
		checkNeighbourhood (R);
	}
	
	printGraph ();
	printGraphInfo ();
}


RegionGraph::~RegionGraph () {
	for (Region *R : regions)
		delete (R);
}


int RegionGraph::newRegion (int ID, Region_Type new_type, int x, int y) {
	// mais uma região!
	Region* aux = new Region (ID, new_type, x, y);
	// e guarda ela lá no grafo
	regions.push_back (aux);
	
	return regions.size () - 1;
}


void RegionGraph::checkNeighbourhood (Region *R) {
	int min_distance = HUGE_VAL;	// menor distância, pra caso ninguém se conecte ao indivíduo
	int closer = R->ID;		// região mais perto (a q tem a min_distance)
	int distance;	// a distância real (calculada pra cada um)
	
	int i, j, current;
	
	// pra cada região adjacente (num quadrado 3x3);
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			current = R->ID + (i * map_width) + j;
			if (current > 0 && current < (int) regions.size () && (i || j)) {	// exclui o próprio R (0x0, centro do quadradim lá), os menores q 0 e maiores q size
				Region *current_region = regions[current];
				distance = R->getDistance (regions[current]);
				// atualiza a menor distância
				if (distance < min_distance) {
					min_distance = distance;
					closer = current;
				}
				
				// Se puder serem vizinhos, os liga (dum pro outro, d'outro pro um)
				if (R->liga (current_region) && R->getAdjQuantity () < Region::MaxNeighbours && 
						current_region->getAdjQuantity () < Region::MaxNeighbours && 
						rand () % Region::bond_chance) {
					R->neighbourhood.insert (current_region);
					current_region->neighbourhood.insert (R);
				}
			}
		}
	}
	
	if (R->neighbourhood.empty ()) {
		R->neighbourhood.insert (regions[closer]);
	}
}


void RegionGraph::printGraphInfo () {
	for (Region *R : regions)
		R->print ();
}


void RegionGraph::printGraph () {
	int width = map_width * block_size;
	int height = map_height * block_size;
	char to_print[height + 2][width + 1];
	int i, j;
	
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			to_print[i + 1][j] = ' ';
			to_print[0][j] = '-';	// linha de cima
			to_print[height + 1][j] = '-';	// linha de baixo
		}
		to_print[i + 1][j] = '|';	// lateral
	}
	to_print[0][j] = '\\';
	to_print[i + 1][j] = '/';
	
	for (Region *R : regions) {
		to_print[R->y + 1][R->x] = R->getAdjQuantity () + '0';
	}
	
	for (i = 0; i < height + 2; i++) {
		for (j = 0; j < width + 1; j++) {
			std::cout << to_print[i][j];
		}
		std::cout << "\n";
	}
}
