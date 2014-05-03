#ifndef LUAWBIND_HPP
#define LUAWBIND_HPP

extern "C" {
    #include <lua/lua.h>
    #include <lua/lualib.h>
    #include <lua/lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/discard_result_policy.hpp>
#include <luabind/object.hpp>


typedef luabind::object LuaObject;

typedef luabind::object LuaFunction;

#endif
