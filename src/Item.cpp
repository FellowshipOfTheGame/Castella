#include "Item.hpp"

/*
void registerStringAtLua(lua_State *state) {
    using namespace luabind;
    using namespace std;
    module(state) [
        class_<string>("string")
            .def( constructor<const char *>() )
            .def( constructor<const string&>() )
            .def( "c_str", &string::c_str )
            .def( "__eq", ( string&(string::*)(const string&) ) &string::operator= )
            .def( "__eq", ( string&(string::*)(const char*) ) &string::operator= )
            .def( "__eq", ( string&(string::*)(char) ) &string::operator= )
            .def( "__concat", ( string(*)(const string&, const string&) ) &std::operator+ )
            .def( "__concat", ( string(*)(const string&, const char*) ) &std::operator+ )
            .def( "__concat", ( string(*)(const char*, const string&) ) &std::operator+ )
    ];
}
*/

/*Item::Item(const Item& that) {
    this->name = that.name;
    this->imgFile = that.imgFile;
    this->baseCost = that.baseCost;
}
*/

Item::Item(const char *scriptFile, ScriptHandler &sh) {

   //Pizza.lua
    luaL_dofile( sh.state(), scriptFile );

    LuaTable global = luabind::globals( sh.state() );

    name = sh.get<const char *>("name");
    imgFile = sh.get<const char *>("imgFile");
    baseCost = sh.get<double>("baseCost");
    print();


    /* Pizza1.lua ( Não registra a classe mas tem que converter tudo )
     * luaL_dofile(state, scriptFile.c_str() );
     * luabind::object global_table = luabind::globals(state);
     * this->name = to_cppString(global_table, "name");
     * this->imgFile = to_cppString(global_table, "imgFile");
     * this->baseCost = to_cDouble(global_table, "baseCost");
     */

/*
     //Pizza2.lua
        luabind::module(state) [
           luabind::class_<Item>("Item")
                .def( luabind::constructor<const char *, const char *, const double>() )
                .def( "setName", &Item::setName )
                .def( "setImgFile", &Item::setImgFile )
                .def( "setCost", &Item::setCost )
                .def( "print", &Item::print )
      ];
      luabind::globals(state)["item"] = this;
      luaL_dofile(state, scriptFile);
*/

     /* Pizza3.lua  ( Não dá erro mas "viola" o estado "private" das variáveis )
      luabind::module(state) [
        luabind::class_<Item, boost::shared_ptr<Item> >("Item")
            .def( luabind::constructor<const char *, const char *, const double>() )
            .def( "print", &Item::print )
      ];
      luabind::globals(state)["item"] = this;
      LuaTable table = to_luaTable(luabind::globals(state), "item");
      luaL_dofile(state, scriptFile);
      std::cout << "Address: " << this << std::endl;
      this->name = to_cppString(table, "name");
      this->imgFile = to_cppString(table, "imgFile");
      this->baseCost = to_cDouble(table, "baseCost");
      */
}

/*
Item::Item(const char *name, const char *imgFile, const double baseCost) {
    this->name = name;
    this->imgFile = imgFile;
    this->baseCost = baseCost;
}
*/

Item::Item(const std::string &name, const std::string &imgFile, const double baseCost) {
    this->name = name;
    this->imgFile = imgFile;
    this->baseCost = baseCost;
}

/*
void Item::setName(std::string rhs) { this->name = rhs; }

void Item::setImgFile(std::string rhs) { this->imgFile = rhs; }

void Item::setBaseCost(const double &rhs) { this->baseCost = rhs; }
*/

void Item::print() {
    std::cout << "name: " << name << std::endl
                << "imgFile: " << imgFile << std::endl
                << "baseCost: " << baseCost << std::endl;
}

/*
void Item::registerAtLua(lua_State *state) {
    using namespace luabind;
        module(state) [
            class_<Item>("Item")
                .def( "print", &Item::print )
                .property( "name", &Item::name, &Item::setName )
                .property( "imgFile", &Item::imgFile, &Item::setImgFile )
                .property( "baseCost", &Item::baseCost, &Item::setBaseCost )
    ];
}
*/
