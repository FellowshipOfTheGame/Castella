#include <Region.hpp>


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


int Region::getDistance (Region *region) {
	int x = this->x - region->x;
	int y = this->y - region->y;
	return (std::abs ((pow (x, 2)) + (pow (y, 2))));
}


int Region::getAdjQuantity () {
	return neighbourhood.size ();
}


void Region::print () {
	std::cout << ID << ':' << x << "x" << y << '\n';
	std::cout << "Adjacentes: ";
	for (unsigned int i = 0; i < neighbourhood.size (); i++)
		std::cout << neighbourhood[i]->ID << ", ";
	std::cout << "\n\n";
}


Region *Region::getNeighbour (unsigned int i) {
	if (i >= neighbourhood.size ())
		return NULL;
	else {
		return neighbourhood[i];
	}
}


/* * * * * * * * * * * *
 *                     *
 * GRAFO DAS REGIÕES   *
 *                     *
 * * * * * * * * * * * */
RegionGraph::RegionGraph () {
	// auxiliares pra criar o grafo com distâncias legais
	int x, y;
	unsigned int i, j;
	
	for (i = 0; i < map_height; i ++) {
		for (j = 0; j < map_width; j ++) {
			y = (i * block_size) + (rand () % block_size);
			x = (j * block_size) + (rand () % block_size);
			newRegion ((i * map_height) + j, (Region_Type) (rand () % 4), x, y);
		}
	}
	
	for (i = 0; i < regions.size (); i ++) {
		checkNeighbourhood (regions[i]);
	}
	
	printGraph ();
}


RegionGraph::~RegionGraph () {
	for (unsigned int i = 0; i < regions.size (); i++)
		delete (regions[i]);
}


int RegionGraph::newRegion (int ID, Region_Type new_type, int x, int y) {
	// mais uma região!
	Region* aux = new Region (ID, new_type, x, y);
	// e guarda ela lá no grafo
	regions.push_back (aux);
	
	return regions.size () - 1;
}


void RegionGraph::checkNeighbourhood (Region *R) {
	int min_distance = HUGE_VAL;		// menor distância, pra caso ninguém alcance a distância mínima
	int closer = R->ID;		// região mais perto (a q tem a min_distance)
	int distance;
	
	int i, j, current;
	
	// pra cada região adjacente (num quadrado 3x3);
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			current = R->ID + (i * map_height) + j;
			if (current > 0 && current < (int) regions.size () && i && j) {	// exclui o próprio R (0x0, centro do quadradim lá), os menores q 0 e maiores q size
				
				distance = R->getDistance (regions[current]);
				// atualiza a menor distância
				if (distance < min_distance) {
					min_distance = distance;
					closer = current;
				}
				if (distance < NEIGHBOUR_MAX_DISTANCE) {
					R->neighbourhood.push_back (regions[current]);
				}
			}
		}
	}
	
	if (R->neighbourhood.empty ()) {
		R->neighbourhood.push_back (regions[closer]);
	}
}


void RegionGraph::printGraphInfo () {
	for (unsigned int i = 0; i < regions.size (); i++)
		regions[i]->print ();
}


void RegionGraph::printGraph () {
	int width = map_width * block_size;
	int height = map_height * block_size;
	char to_print[height][width];
	int i, j;
	
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++)
			to_print[i][j] = ' ';
	}
	
	for (i = 0; i < (int) regions.size (); i++) {
		to_print[regions[i]->y][regions[i]->x] = regions[i]->getAdjQuantity () + '0';
	}
	
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			std::cout << to_print[i][j];
		}
		std::cout << "\n";
	}
}


Region *RegionGraph::get (int i) {
	return regions[i];
}
