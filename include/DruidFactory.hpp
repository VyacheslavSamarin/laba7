#ifndef DRUIDFACTORY_HPP
#define DRUIDFACTORY_HPP

#include "NPCFactory.hpp"
#include "Druid.hpp"

class DruidFactory : public NPCFactory {
public:
    std::unique_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_unique<Druid>(name, x, y);
    }
};

#endif