#ifndef LUAWBIND_HPP
#define LUAWBIND_HPP

extern "C" {
    #include <lua/lua.h>
    #include <lua/lualib.h>
    #include <lua/lauxlib.h>
}

#include <luabind/function.hpp>
#include <luabind/class.hpp>
#include <luabind/object.hpp>
#include <luabind/operator.hpp>

//Include luabind policies for calling functions
//TODO include only the ones neeeded
/*
#include <luabind/adopt_policy.hpp>
#include <luabind/copy_policy.hpp>
#include <luabind/dependency_policy.hpp>
#include <luabind/discard_result_policy.hpp>
#include <luabind/iterator_policy.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>
#include <luabind/yield_policy.hpp>
*/

typedef luabind::object LuaObject;

typedef luabind::object LuaFunction;

#endif
