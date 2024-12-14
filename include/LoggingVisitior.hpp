#ifndef LOGGINGVISITOR_HPP
#define LOGGINGVISITOR_HPP

#include "Visitor.hpp"
#include "NPC.hpp"
#include "Elf.hpp"
#include "Druid.hpp"
#include "Dragon.hpp"
#include <ostream>

class LoggingVisitor : public Visitor {
    public:
        LoggingVisitor(std::ostream& os);
        void visit(Dragon* dragon) override;
        void visit(Elf* elf) override;
        void visit(Druid* druid) override;
    private:
        std::ostream& os;
};

#endif