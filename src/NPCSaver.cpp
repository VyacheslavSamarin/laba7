#include "NPCSaver.hpp"

void NPCSaver::saveNPCs(const std::vector<std::unique_ptr<NPC>>& npcs, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& npc : npcs) {
            if (npc) {
                file << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << "\n";
            }
        }
    }
}