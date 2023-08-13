#pragma once

#include <visitor/visitor.hpp>
#include <parser/parser.hpp>

class Interpreter : public Visitor
{
private:
    Parser parser;

public:
    Interpreter(Parser);
    RVal *visitRValConst(RVal *) override;
    RVal *visitUnaryOperation(UnaryOperation *) override;
    RVal *visitBinaryOperation(BinaryOperation *) override;
    void interpret();
};