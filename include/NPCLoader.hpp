#ifndef NPCLOADER_HPP
#define NPCLOADER_HPP

#include "NPC.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <memory>
#include "NPCFactory.hpp"

class NPCLoader {
public:
    static std::vector<std::unique_ptr<NPC>> loadNPCs(const std::string& filename);
};

#endif