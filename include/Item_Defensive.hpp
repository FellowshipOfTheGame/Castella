#ifndef DEFENSIVE_HPP
#define DEFENSIVE_HPP

#include "Item.hpp"

class Defensive : public Item
{
    private:
        double defence;

    protected:
		static const std::string scriptPath;

    public:
        Defensive(const std::string scriptFile);
        Defensive(const std::string name = "none", const std::string imgFile = "none", const double baseCost = 0.0,
                        const double defence = 0.0);

        void buildDefensive(LuaTable &defensive);
};

#endif // DEFENSIVE_HPP
