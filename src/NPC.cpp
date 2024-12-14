#include "NPC.hpp"

NPC::NPC(const std::string& name, int x, int y) : name(name), x(x), y(y), alive(true) {}

void NPC::setX(int x) { this->x = x; }
void NPC::setY(int y) { this->y = y; }


