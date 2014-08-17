#include <RegionGraph.hpp>

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
		throw;
	}
}


RegionGraph::RegionGraph () {
	// auxiliares pra criar o grafo com distâncias legais
	int x, y, id = 0;
	unsigned int i, j;
	srand (time (NULL));
	
	for (i = 0; i < graph_height; i ++) {
		for (j = 0; j < graph_width; j ++) {
			y = (i * block_size) + (rand () % block_size);
			x = (j * block_size) + (rand () % block_size);
			newRegion (id++, (Region_Type) (rand () % 4), x, y);
		}
	}

	for (Region *R : regions) {
		checkNeighbourhood (R);
	}

	// printGraph ();
	// printGraphInfo ();
}


RegionGraph::~RegionGraph () {
	std::cout << "\tdestruindo o RegionGraph:\n";
	for (Region *&R : regions)
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
	unsigned int min_distance = ~0;	// menor distância, pra caso ninguém se conecte ao indivíduo
	int closer = R->ID;		// região mais perto (a q tem a min_distance)
	unsigned int distance;	// a distância real (calculada pra cada um)
	
	int i, j, current;
	
	// pra cada região adjacente (num quadrado 3x3);
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			current = R->ID + (i * graph_width) + j;
			if (current > 0 && current < (int) regions.size () && (i || j)) {	// exclui o próprio R (0x0, centro do quadradim lá), os menores q 0 e maiores q size
				Region *current_region = regions[current];
				distance = R->getDistance (regions[current]);
				// atualiza a menor distância
				if (distance < min_distance) {
					min_distance = distance;
					closer = current;
				}
				
				// Se puder serem vizinhos, os liga (dum pro outro, d'outro pro um)
				if (liga (R, current_region) && R->getAdjQuantity () < Region::MaxNeighbours && 
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


bool RegionGraph::liga (Region *A, Region *B) {
	int x = (A->x / RegionGraph::block_size) - (B->x / RegionGraph::block_size);
	int y = (A->y / RegionGraph::block_size) - (B->y / RegionGraph::block_size);
	
	if (std::abs (x) > 1 || std::abs (y) > 1)
		return false;
	else
		return true;
}


void RegionGraph::printGraphInfo () {
	for (Region *R : regions)
		R->print ();
}


void RegionGraph::printGraph () {
	int width = graph_width * block_size;
	int height = graph_height * block_size;
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


RegionGraphIterator RegionGraph::begin () const {
	return RegionGraphIterator (this, 0);
}


RegionGraphIterator RegionGraph::end () const {
	return RegionGraphIterator (this, graph_height * graph_width);
}


/* * * * * * * * * * *
 * ITERADOR DO GRAFO *
 * * * * * * * * * * */
RegionGraphIterator::RegionGraphIterator (const RegionGraph *graph, int pos) 
	: graph (graph), pos (pos) {}

bool RegionGraphIterator::operator!= (const RegionGraphIterator& other) const {
	return pos != other.pos;
}

const RegionGraphIterator& RegionGraphIterator::operator++ () {
	pos++;
	return *this;
}

Region *& RegionGraphIterator::operator* () const {
	return (*graph)[pos];	// Ignore o warning que aparece aqui
}
