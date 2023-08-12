#include <interpreter/interpreter.hpp>

Interpreter::Interpreter(Parser parser) : parser(parser) {}

double Interpreter::visitNumberConst(NumberConst *)
{
}

double Interpreter::visitUnaryOperation(UnaryOperation *)
{
}

double Interpreter::visitBinaryOperation(BinaryOperation *)
{
}