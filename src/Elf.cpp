#include "Elf.hpp"
#include "Druid.hpp"

Elf::Elf(const std::string& name, int x, int y) : NPC(name, x, y) {}
void Elf::accept(Visitor& visitor) { visitor.visit(this); }
bool Elf::fight(NPC* other) { return dynamic_cast<Druid*>(other) != nullptr; }

const std::string Elf::type = "Elf";