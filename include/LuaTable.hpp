#ifndef LUATABLE_HPP
#define LUATABLE_HPP

#include <cstdio>
#include <string>

#include "LuaWBind.hpp"

/**
* This class works as a wrapper for the luabind::objects that are tables, making it easier to retrieve values.
*/

class LuaTable
{

    private:
        LuaObject table;

    public:
        LuaTable();
        LuaTable(LuaObject obj);

        int getInt(int key);
        int getInt(const char *key);

        double getDouble(int key);
        double getDouble(const char *key);

        const char *get_cString(int key);
        const char *get_cString(const char *key);

		template <class T>
		std::function<T> getFunction (int key);

        std::string getString(int key);
        std::string getString(const char *key);

        LuaObject getLuaType(int key);
        LuaObject getLuaType(const char *key);

        LuaTable getLuaTable(int key);
        LuaTable getLuaTable(const char *key);

        const LuaTable& operator=(const LuaObject obj);
        const LuaTable& operator=(const LuaTable &obj);

        LuaObject operator[](int key);
        LuaObject operator[](const char *key);

        template<typename T>
        T get(int key){ return luabind::object_cast<T>( table[key] ); }

        template<typename T>
        T get(const char *key){ return luabind::object_cast<T>( table[key] ); }

		/// Iterador pro começo da LuaTable (pra iterar por índices)
		LuaTableIterator begin () const;
		/// Iterador pro fim da LuaTable (pra iterar por índices)
		LuaTableIterator end () const;
};

#endif
