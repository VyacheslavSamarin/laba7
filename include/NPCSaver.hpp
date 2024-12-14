#ifndef NPCSAVER_HPP
#define NPCSAVER_HPP

#include "NPC.hpp"
#include <vector>
#include <fstream>
#include <memory>

class NPCSaver {
public:
    static void saveNPCs(const std::vector<std::unique_ptr<NPC>>& npcs, const std::string& filename);
};

#endif