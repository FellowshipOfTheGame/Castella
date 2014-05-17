#include <LuaTable.hpp>

using namespace luabind;

LuaTable::LuaTable() {}

LuaTable::LuaTable(LuaObject obj) {
    if ( type(obj) == LUA_TTABLE ) { table = obj; }
    else std::cout << "Warning ! Failed to create luatable !" << std::endl;
}

int LuaTable::getInt(int key) { return object_cast<int>( table[key] ); }
int LuaTable::getInt(const char *key) { return object_cast<int>( table[key] ); }

double LuaTable::getDouble(int key) { return object_cast<double>( table[key] ); }
double LuaTable::getDouble(const char *key) { return object_cast<double>( table[key] ); }

const char *LuaTable::get_cString(int key) { return object_cast<const char *>( table[key] ); }
const char *LuaTable::get_cString(const char *key) { return object_cast<const char *>( table[key] ); }

std::string LuaTable::getString(int key) { return std::string( object_cast<const char *>( table[key] ) ); }
std::string LuaTable::getString(const char *key) { return std::string( object_cast<const char *>( table[key] ) ); }

LuaObject LuaTable::getLuaType(int key) { return table[key]; }
LuaObject LuaTable::getLuaType(const char *key) { return table[key]; }

LuaTable LuaTable::getLuaTable(int key) { return LuaTable( table[key] ); }
LuaTable LuaTable::getLuaTable(const char *key) { return LuaTable( table[key] ); }

const LuaTable& LuaTable::operator=(const LuaObject &rhs) {
    if ( type(rhs) == LUA_TTABLE ) { this->table = rhs; }
    else std::cout << "Warning ! Failed to get luatable operator= LuaTable" << std::endl;
    return *this;
}

const LuaTable& LuaTable::operator=(const LuaTable &rhs) {
    if ( type(rhs.table) == LUA_TTABLE ) { this->table = rhs.table; }
    else std::cout << "Warning ! Failed to get luatable operator= LuaTable" << std::endl;
    return *this;
}

LuaObject LuaTable::operator[](int key) { return table[key]; }
LuaObject LuaTable::operator[](const char *key) { return table[key]; }
