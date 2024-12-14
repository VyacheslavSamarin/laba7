#include "NPCLoader.hpp"

std::vector<std::unique_ptr<NPC>> NPCLoader::loadNPCs(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::unique_ptr<NPC>> result;

    if (file.is_open()) {
        std::string type, name;
        int x, y;
        while (file >> type >> name >> x >> y) {
            std::unique_ptr<NPC> npc = NPCFactory::create(type, name, x, y);
            if (npc) {
                result.push_back(std::move(npc));
            } else {
                std::cerr << "Failed to create NPC of type " << type << std::endl;
            }
        }
    }
    return result;
}