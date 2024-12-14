#ifndef DRUID_HPP
#define DRUID_HPP

#include "NPC.hpp"
#include "Visitor.hpp"

class Druid : public NPC {
public:
    Druid(const std::string& name, int x, int y);
    void accept(Visitor& visitor) override;
    bool fight(NPC* other) override;
    std::string getType() const override { return type; }

private:
    static const std::string type;
};

#endif