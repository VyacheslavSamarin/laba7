#ifndef NPCFACTORY_HPP
#define NPCFACTORY_HPP

#include <map>
#include <memory>
#include "NPC.hpp"

class NPCFactory {
public:
    virtual std::unique_ptr<NPC> createNPC(const std::string& name, int x, int y) = 0;
    static void registerFactory(const std::string& type, NPCFactory* factory);
    static std::unique_ptr<NPC> create(const std::string& type, const std::string& name, int x, int y);
private:
    static std::map<std::string, NPCFactory*> factories;
};

#endif