#ifndef VISITOR_HPP
#define VISITOR_HPP

class Dragon;
class Elf;
class Druid;

class Visitor {
    public:
        virtual void visit(Dragon* dragon) = 0;
        virtual void visit(Elf* elf) = 0;
        virtual void visit(Druid* druid) = 0;
};

#endif