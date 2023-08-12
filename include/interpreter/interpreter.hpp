#pragma once

#include <visitor/visitor.hpp>
#include <parser/parser.hpp>

class Interpreter : public Visitor
{
private:
    Parser parser;

public:
    Interpreter(Parser);
    double visitNumberConst(NumberConst *) override;
    double visitUnaryOperation(UnaryOperation *) override;
    double visitBinaryOperation(BinaryOperation *) override;
    double interpret();
};