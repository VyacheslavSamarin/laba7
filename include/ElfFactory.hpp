#ifndef ELFFACTORY_HPP
#define ELFFACTORY_HPP

#include "NPCFactory.hpp"
#include "Elf.hpp"

class ElfFactory : public NPCFactory {
public:
    std::unique_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_unique<Elf>(name, x, y);
    }
};

#endif