#include <Structure.hpp>

/* * * * * * * * * *
 * ESTRUTURA ctor  *
 * * * * * * * * * */
Structure::Structure () {

}


Structure::~Structure () {
	
}


/* * * * * *
 * FABRICA *
 * * * * * */
Structure *StructureFactory::createStructure (Structure_Type structype) {
	Structure *new_structure;
	switch (structype) {
		case throne: new_structure = new Throne (); break;
		case townhall: new_structure = new Townhall (); break;
		case blacksmith: new_structure = new Blacksmith (); break;
		case tavern: new_structure = new Tavern (); break;
		case woods: new_structure = new Woods (); break;
		case mines: new_structure = new Mines (); break;
	}
	
	return new_structure;
}

/* * * * * * * * * * *
 * ESTRUTURAS FILHAS *
 * * * * * * * * * * */
Throne::Throne () {
	type = throne;
}


Townhall::Townhall () {
	type = townhall;
}


Tavern::Tavern () {
	type = tavern;
}


Blacksmith::Blacksmith () {
	type = blacksmith;
}


Woods::Woods () {
	type = woods;
}


Mines::Mines () {
	type = mines;
}
