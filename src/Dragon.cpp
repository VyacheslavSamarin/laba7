#include "Dragon.hpp"
#include "Elf.hpp"

Dragon::Dragon(const std::string& name, int x, int y) : NPC(name, x, y) {}
void Dragon::accept(Visitor& visitor) { visitor.visit(this); }
bool Dragon::fight(NPC* other) { return dynamic_cast<Elf*>(other) != nullptr; }

const std::string Dragon::type = "Dragon";