#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include "Visitor.hpp"

class NPC {
public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;
    virtual void accept(Visitor&) = 0;
    virtual bool isAlive() const { return alive; }
    virtual void setAlive(bool alive) { this->alive = alive; }
    virtual std::string getName() const { return name; }
    virtual int getX() const { return x; }
    virtual int getY() const { return y; }
    virtual void setX(int x);
    virtual void setY(int y);
    virtual std::string getType() const = 0;
    virtual bool fight(NPC* other) = 0;

protected:
    std::string name;
    int x, y;
    bool alive;
};

#endif