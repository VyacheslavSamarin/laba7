#ifndef DRAGONFACTORY_HPP
#define DRAGONFACTORY_HPP

#include "NPCFactory.hpp"
#include "Dragon.hpp"

class DragonFactory : public NPCFactory {
public:
    std::unique_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_unique<Dragon>(name, x, y);
    }
};

#endif