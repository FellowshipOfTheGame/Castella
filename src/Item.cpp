#include <Item.hpp>

Item::Item(const std::string scriptFile) {
	ScriptHandler sH(Item::scriptPath + scriptFile);
	LuaTable item = sH.getTable("item");
	buildItem(item);
}

Item::Item(const std::string name, const std::string imgFile, const double baseCost) {
    this->name = name;
    this->imgFile = imgFile;
    this->baseCost = baseCost;
}

void Item::buildItem(LuaTable &item) {
    name = item.getString("nome");
    imgFile = item.getString("imgArq");
    baseCost = item.getDouble("custoBase");
}

const std::string Item::scriptPath("script/items/");
