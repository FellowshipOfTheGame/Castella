#include <cassert>
#include <LuaTable.hpp>

using namespace luabind;

LuaTable::LuaTable() {}

LuaTable::LuaTable(LuaObject obj) {
    assert( type(obj) == LUA_TTABLE );
	table = obj;
}

int LuaTable::getInt(int key) { return object_cast<int>( table[key] ); }
int LuaTable::getInt(const char *key) { return object_cast<int>( table[key] ); }

double LuaTable::getDouble(int key) { return object_cast<double>( table[key] ); }
double LuaTable::getDouble(const char *key) { return object_cast<double>( table[key] ); }

const char *LuaTable::get_cString(int key) { return object_cast<const char *>( table[key] ); }
const char *LuaTable::get_cString(const char *key) { return object_cast<const char *>( table[key] ); }

std::string LuaTable::getString(int key) {
	try {
		std::string str = object_cast<const char *>( table[key] );
		return str;
	}
	// se não tem a key, retorna uma string vazia
	catch (...) {
		return "";
	}
}
std::string LuaTable::getString(const char *key) {
	try {
		std::string str = object_cast<const char *>( table[key] );
		return str;
	}
	// se não tem a key, retorna uma string vazia
	catch (...) {
		return "";
	}
}

LuaObject LuaTable::getLuaType(int key) { return table[key]; }
LuaObject LuaTable::getLuaType(const char *key) { return table[key]; }

LuaTable LuaTable::getLuaTable(int key) { return LuaTable( table[key] ); }
LuaTable LuaTable::getLuaTable(const char *key) { return LuaTable( table[key] ); }

const LuaTable& LuaTable::operator=(const LuaObject rhs) {
    assert( type(rhs) == LUA_TTABLE );
	this->table = rhs;
    return *this;
}

const LuaTable& LuaTable::operator=(const LuaTable &rhs) {
    assert( type(rhs.table) == LUA_TTABLE );
	this->table = rhs.table;
    return *this;
}

LuaObject LuaTable::operator[](int key) { return table[key]; }
LuaObject LuaTable::operator[](const char *key) { return table[key]; }
