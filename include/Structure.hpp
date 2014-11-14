/** @file Structure.hpp
 *
 * @brief Estruturas das @ref Region "regiões"
 *
 * Header do gamedata/Structure.cpp
 */


#ifndef _CASTELLA_STRUCTURE_HPP_
#define _CASTELLA_STRUCTURE_HPP_

#include <iostream>

/** Enum do tipo da estrutura */
enum Structure_Type {
	// lugar do dono da região (se tiver: aplica-se a castelo e vila)
	throne,
	townhall,
	// comércios e afins, coisa de cidade
	tavern,
	blacksmith,
	// naturais, pra retirada de materiais
	woods,
	mines
};




/** @brief As estruturas dentro das regiões
 *
 * @sa Region.hpp
 * 
 * @todo Dtor
 */
class Structure {
private:

protected:
	Structure_Type type;	///< tipo da estrutura

public:
	Structure ();	///< Ctor
	~Structure ();	///< Dtor

	Structure_Type getType ();

	/** @brief Representação em string dos tipos de estruturas */
	static std::string Structure_TypeName (Structure_Type tipo);
};


/** @brief Fábrica de estruturas */
class StructureFactory {
public:
	/** @brief Cria uma estrutura dependendo do tipo pedido.
	 *
	 * @param[in] structype Tipo da estrutura a ser criada
	 *
	 * @return Nova estrutura, se tipo válido
	 * @return nullptr se tipo inválido
	 */
	Structure *createStructure (Structure_Type structype);
};



/* Classes Filhas: estruturas específicas */


/** @brief Sala do Trono. O lorde o aguarda!
 *
 * __Sala do trono__ é o lugar no @ref Castle "castelo" para se conseguir missões oficiais e exercitar relações diplomáticas.
 */
class Throne: public Structure {
private:
	std::string Lord;	///< Nome do Lorde da região

protected:

public:
    Throne ();
};


/** @brief Taverna! Ahoy!
 *
 * __Prefeitura__ é o lugar na @ref Village "vila" para se conseguir missões oficiais e exercitar relações diplomáticas.
 */
class Townhall : public Structure {
private:
	std::string Mayor;

protected:

public:
    Townhall ();
};


/** @brief Taverna! Ahoy!
 *
 * __Tavernas__ são lugares para se conseguir missões de pessoas da @ref Village "vila" ou @ref Castle "castelo".
 * Pode-se também comprar suprimentos para batalha, como por exemplo comidas e remédios.
 */
class Tavern : public Structure {
private:

protected:

public:
    Tavern();
};


/** @brief Taverna! Ahoy!
 *
 * __Tavernas__ são lugares para se conseguir missões de pessoas da @ref Village "vila" ou @ref Castle "castelo".
 * Pode-se também comprar suprimentos para batalha, como por exemplo comidas e remédios.
 */
class Blacksmith : public Structure {
private:

protected:

public:
	Blacksmith();
};


/** @brief Taverna! Ahoy!
 *
 * __Tavernas__ são lugares para se conseguir missões de pessoas da @ref Village "vila" ou @ref Castle "castelo".
 * Pode-se também comprar suprimentos para batalha, como por exemplo comidas e remédios.
 */
class Woods : public Structure {
private:

protected:

public:
    Woods();
};


/** @brief Taverna! Ahoy!
 *
 * __Tavernas__ são lugares para se conseguir missões de pessoas da @ref Village "vila" ou @ref Castle "castelo".
 * Pode-se também comprar suprimentos para batalha, como por exemplo comidas e remédios.
 */
class Mines : public Structure {
private:

protected:

public:
    Mines();
};

#endif
