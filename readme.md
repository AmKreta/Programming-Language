**Programming Language**

A simple Interpreter to parse a programming language with javascript like syntax

**Class Diagram**

```mermaid
classDiagram
    class AstNode {
        <<abstract>>
        +virtual ~AstNode()
    }

    class Evaluable {
        <<abstract>>
        +virtual double acceptVisitor(Visitor* v)
    }

    class RValConst {
        +...
    }

    class NumberConst {
        +double value
        +NumberConst(double val)
        +double getData()
        +double acceptVisitor(Visitor* v)
    }

    class UnaryOperation {
        +Token::Type type
        +std::shared_ptr<Evaluable> child
        +UnaryOperation(Token::Type t, std::shared_ptr<Evaluable> c)
        +Token::Type getType()
        +std::shared_ptr<Evaluable> getChild()
        +double acceptVisitor(Visitor* v)
    }

    class BinaryOperation {
        +Token::Type operation
        +std::shared_ptr<Evaluable> leftChild
        +std::shared_ptr<Evaluable> rightChild
        +BinaryOperation(std::shared_ptr<Evaluable> left, Token::Type op, std::shared_ptr<Evaluable> right)
        +Token::Type getOperation()
        +std::shared_ptr<Evaluable> getLeftChild()
        +std::shared_ptr<Evaluable> getRightChild()
        +double acceptVisitor(Visitor* v)
    }

    class Visitor {
        +double visitNumberConst(NumberConst* nc)
        +double visitUnaryOperation(UnaryOperation* uo)
        +double visitBinaryOperation(BinaryOperation* bo)
    }

    AstNode <|-- Evaluable
    Evaluable <|-- NumberConst
    Evaluable <|-- UnaryOperation
    Evaluable <|-- BinaryOperation
    Evaluable <|-- RValConst
    Visitor <|-- NumberConst
    Visitor <|-- UnaryOperation
    Visitor <|-- BinaryOperation
