#pragma once

#include <string>
#include <vector>

#include <rVal/rVal.hpp>
#include <statement/statement.hpp>
#include <evaluable/evaluable.hpp>
#include <runable/runable.hpp>

// varDecleration : (let | const) Id (= expr)? (, Id (= expr)?)*;
// default value will be undefined
class VarDecleration : public Statement, public Runable
{
private:
    std::vector<std::pair<std::string, std::shared_ptr<Evaluable>>> declerations;

public:
    VarDecleration(std::vector<std::pair<std::string, std::shared_ptr<Evaluable>>>);
    std::vector<std::pair<std::string, std::shared_ptr<Evaluable>>> getDeclerations();
    void acceptVisitor(Visitor *) override;
};