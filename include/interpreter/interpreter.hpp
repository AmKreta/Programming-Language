#pragma once

#include <visitor/visitor.hpp>
#include <parser/parser.hpp>

class Interpreter : public Visitor
{
private:
    Parser parser;

public:
    Interpreter(Parser);
    std::shared_ptr<RVal> visitRValConst(RVal *) override;
    std::shared_ptr<RVal> visitUnaryOperation(UnaryOperation *) override;
    std::shared_ptr<RVal> visitBinaryOperation(BinaryOperation *) override;
    void interpret();
};