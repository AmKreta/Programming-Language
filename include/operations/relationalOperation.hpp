#pragma once

#include <rVal/rVal.hpp>
#include <token/token.hpp>

class RelationalExpression
{
private:
public:
    // binary operations !
    static std::shared_ptr<RVal> evaluate(std::shared_ptr<RVal>, Token::Type, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> evaluate(std::shared_ptr<RVal>, Token::Type);
    
    // binary operations
    static std::shared_ptr<RVal> equalTo(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> notEqualTo(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> lessThan(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> greaterThan(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> lessThanEqualTo(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> greaterThanEqualTo(std::shared_ptr<RVal>, std::shared_ptr<RVal>);

};