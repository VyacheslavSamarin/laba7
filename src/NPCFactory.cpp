#include "NPCFactory.hpp"

std::map<std::string, NPCFactory*> NPCFactory::factories;

void NPCFactory::registerFactory(const std::string& type, NPCFactory* factory) {
    factories[type] = factory;
}

std::unique_ptr<NPC> NPCFactory::create(const std::string& type, const std::string& name, int x, int y) {
    if (factories.find(type) != factories.end()) {
        return factories[type]->createNPC(name, x, y);
    }
    return nullptr;
}