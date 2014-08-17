#include <Item_Defensive.hpp>

Defensive::Defensive(const std::string scriptFile) {
	ScriptHandler sH(Defensive::scriptPath + scriptFile);
	LuaTable defensive = sH.getTable("defesa");
	buildItem(defensive);
	buildDefensive(defensive);
}

Defensive::Defensive(const std::string name, const std::string imgFile, const double baseCost,
                                const double defence)
                : Item(name, imgFile, baseCost) {
    this->defence = defence;
}

void Defensive::buildDefensive(LuaTable &defensive) {
    defence = defensive.getDouble("defence");
}

const std::string Defensive::scriptPath(Item::scriptPath + "defensive/");
