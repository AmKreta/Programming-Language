#pragma once

#include <rVal/rVal.hpp>
#include <token/token.hpp>

class BitwiseOperation
{
private:
public:
    // binary operations !
    static std::shared_ptr<RVal> evaluate(std::shared_ptr<RVal>, Token::Type, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> evaluate(Token::Type, std::shared_ptr<RVal>);

    // binary operations
    static std::shared_ptr<RVal> And(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> Or(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> Xor(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> LShift(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> Rshift(std::shared_ptr<RVal>, std::shared_ptr<RVal>);

    // unaryOperation
    static std::shared_ptr<RVal> Not(std::shared_ptr<RVal>);
};