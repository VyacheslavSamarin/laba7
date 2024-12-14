#include "Druid.hpp"
#include "Dragon.hpp"

Druid::Druid(const std::string& name, int x, int y) : NPC(name, x, y) {}
void Druid::accept(Visitor& visitor) { visitor.visit(this); }
bool Druid::fight(NPC* other) { return dynamic_cast<Dragon*>(other) != nullptr; }

const std::string Druid::type = "Druid";