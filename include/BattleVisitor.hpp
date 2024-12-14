#ifndef BATTLE_VISITOR_HPP
#define BATTLE_VISITOR_HPP

#include "Visitor.hpp"
#include "Elf.hpp"
#include "Druid.hpp"
#include "Dragon.hpp"
#include <vector>
#include <memory>

class BattleVisitor : public Visitor {
public:
    BattleVisitor(int range, std::vector<std::unique_ptr<NPC>>& npcs);
    void visit(Elf* elf) override;
    void visit(Druid* druid) override;
    void visit(Dragon* dragon) override;

private:
    int range;
    std::vector<std::unique_ptr<NPC>>& npcs;
};

#endif