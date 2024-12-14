#include "LoggingVisitior.hpp"

LoggingVisitor::LoggingVisitor(std::ostream& os) : os(os) {}

void LoggingVisitor::visit(Elf* elf) {
    os << "Elf: " << elf->getName() << " at (" << elf->getX() << ", " << elf->getY() << ")\n";
}

void LoggingVisitor::visit(Druid* druid) {
    os << "Druid: " << druid->getName() << " at (" << druid->getX() << ", " << druid->getY() << ")\n";
}

void LoggingVisitor::visit(Dragon* dragon) {
    os << "Dragon: " << dragon->getName() << " at (" << dragon->getX() << ", " << dragon->getY() << ")\n";
}