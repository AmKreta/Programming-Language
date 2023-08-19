#include <lexer/lexer.hpp>
#include <token/tokenFactory.hpp>
#include <sstream>

Lexer::Lexer(std::string input) : input(input), line(1), column(1), currentPosition(0) {}

void Lexer::advance(int times = 1) // advances the cursor one step ahead and keeps track of line and col
{
    for (int i = 0; i < times; i++)
    {
        if (this->input[this->currentPosition] == '\n')
        {
            this->line++;
            this->column = 1;
        }
        this->column++;
        this->currentPosition++;
    }
}

int Lexer::getLine()
{
    return this->line;
}

int Lexer::getColumn()
{
    return this->column;
}

void Lexer::skipSkippable()
{

    while (this->currentPosition < this->input.size() &&
           (this->input[this->currentPosition] == '\n' ||
            this->input[this->currentPosition] == '\t' ||
            this->input[this->currentPosition] == ' '))
        this->advance();
}

std::string Lexer::peek(int position = 1)
{
    if (this->currentPosition + position < this->input.size())
        return this->input.substr(this->currentPosition, position + 1);
    return this->input.substr(this->currentPosition, 1);
}

Token Lexer::getNextToken()
{
    this->skipSkippable();

    if (this->currentPosition >= this->input.size())
        return this->currentToken =  TokenFactory::build(Token::Type::END_OF_FILE);

    while (this->currentPosition < this->input.size())
    {
        switch (this->input[this->currentPosition])
        {
        // comparision / relational operator
        case '<':
            if (this->peek() == "<=")
            {
                this->advance(2);
                return this->currentToken =  TokenFactory::build(Token::Type::LESS_THAN_EQUAL_TO);
            }
            if(this->peek() == "<<"){
                this->advance(2);
                return this->currentToken =  TokenFactory::build(Token::Type::BITWISE_L_SHIFT);
            }
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::LESS_THAN);

        case '>':
            if (this->peek() == ">=")
            {
                this->advance(2);
                return this->currentToken =  TokenFactory::build(Token::Type::GREATER_THAN_EQUAL_TO);
            }
            if(this->peek() == ">>"){
                this->advance(2);
                return this->currentToken =  TokenFactory::build(Token::Type::BITWISE_R_SHIFT);
            }
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::GREATER_THAN);

        case '=':
            if (this->peek() == "==")
            {
                this->advance(2);
                return this->currentToken =  TokenFactory::build(Token::Type::EQUAL_TO);
            }
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::ASSIGNMENT);

        case '!':
            if (this->peek() == "!=")
            {
                this->advance(2);
                return this->currentToken =  TokenFactory::build(Token::Type::NOT_EQUAL_TO);
            }
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::LOGICAL_NOT);

        // bitwise and logical operators
        case '&':
            if (this->peek() == "&&")
            {
                this->advance(2);
                return this->currentToken =  TokenFactory::build(Token::Type::LOGICAL_AND);
            }
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::BITWISE_AND);

        case '|':
            if (this->peek() == "||")
            {
                this->advance(2);
                return this->currentToken =  TokenFactory::build(Token::Type::LOGICAL_OR);
            }
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::BITWISE_OR);

        case '~':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::BITWISE_NOT);

        case '^':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::BITWISE_XOR);

        // colon, comma, semicolon, question
        case ':':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::COLON);

        case ',':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::COMMA);

        case ';':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::SEMI_COLON);
        
        case '?':
            this->advance();
            return this->currentToken = TokenFactory::build(Token::Type::QUESTION);

        // mathemetical operators
        case '+':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::PLUS);

        case '-':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::MINUS);

        case '/':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::DIVIDE);

        case '*':
            if (this->peek() == "**")
            {
                this->advance(2);
                return this->currentToken =  TokenFactory::build(Token::Type::POWER);
            }
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::MULTIPLY);

        case '%':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::MODULUS);


        // brackets
        case '(':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::L_PAREN);
        case ')':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::R_PAREN);
        case '[':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::L_BRACKET);
        case ']':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::R_BRACKET);
        case '{':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::L_BRACES);
        case '}':
            this->advance();
            return this->currentToken =  TokenFactory::build(Token::Type::R_BRACES);


        default:
            // keywords and identifire
            if (std::isdigit(this->input[this->currentPosition]))
                return this->currentToken =  this->readNumber();
            if (std::isalpha(this->input[this->currentPosition]) || this->input[this->currentPosition] == '_')
                return this->currentToken =  this->readID();
            if (this->input[this->currentPosition] == '\'' || this->input[this->currentPosition] == '"' || this->input[this->currentPosition] == '`')
                return this->currentToken =  this->readString(this->input[this->currentPosition]);
        }
    }
}

Token Lexer::readNumber() // reads no
{
    std::ostringstream oss;
    oss << this->input[this->currentPosition];
    this->advance();

    while (this->currentPosition < this->input.size() && std::isdigit(this->input[this->currentPosition]))
    {
        oss << this->input[this->currentPosition];
        this->advance();
    }

    // if we encounter a decimal
    if (this->currentPosition < this->input.size() && this->input[this->currentPosition] == '.')
    {
        oss << '.';
        this->advance();
        // we have something like 234.
        // and we want atleast one digit to make it 234.0
        if (this->currentPosition < this->input.size() && std::isdigit(this->input[this->currentPosition]))
        {
            while (this->currentPosition < this->input.size() && std::isdigit(this->input[this->currentPosition]))
            {
                oss << this->input[this->currentPosition];
                this->advance();
            }
        }
        else
        {
            // std::string error_message = std::string("expected a digit got a") + this->input[this->current_position];
            // throw Exception{error_message};
        }
    }

    return TokenFactory::build(Token::Type::NUMBER_CONST, oss.str());
}

Token Lexer::readString(char type) // reads string
{
    this->advance(); // reading starting quote
    std::ostringstream oss;
    while (this->currentPosition < this->input.size() && this->input[this->currentPosition] != type)
    {
        oss << this->input[this->currentPosition];
        this->advance();
    }
    this->advance(); // reading end quote
    return TokenFactory::build(Token::Type::STRING_CONST, oss.str());
}

Token Lexer::readID() // reads keywords and identifires
{
    std::ostringstream oss;
    while (this->currentPosition < this->input.size() && std::isalnum(this->input[this->currentPosition]))
    {
        oss << this->input[this->currentPosition];
        this->advance();
    }

    auto input = oss.str();

    // loop
    if (input == "for")
        return TokenFactory::build(Token::Type::FOR);
    if (input == "while")
        return TokenFactory::build(Token::Type::WHILE);
    if (input == "do")
        return TokenFactory::build(Token::Type::DO);

    // conditional
    if (input == "if")
        return TokenFactory::build(Token::Type::IF);
    if (input == "elif")
        return TokenFactory::build(Token::Type::ELIF);
    if (input == "else")
        return TokenFactory::build(Token::Type::ELSE);

    // user defined data type
    if (input == "class")
        return TokenFactory::build(Token::Type::CLASS);
    if (input == "interface")
        return TokenFactory::build(Token::Type::INTERFACE);
    if (input == "type")
        return TokenFactory::build(Token::Type::TYPE);

    // primitive data type
    if (input == "number")
        return TokenFactory::build(Token::Type::NUMBER);
    if (input == "string")
        return TokenFactory::build(Token::Type::STRING);
    if (input == "null")
        return TokenFactory::build(Token::Type::Null);
    if (input == "undefined")
        return TokenFactory::build(Token::Type::UNDEFINED);

    // collection data type
    if (input == "Array")
        return TokenFactory::build(Token::Type::ARRAY);
    if (input == "Object")
        return TokenFactory::build(Token::Type::OBJECT);

    // function data type
    if (input == "function")
        return TokenFactory::build(Token::Type::FUNCTION);

    // var decleration
    if (input == "let")
        return TokenFactory::build(Token::Type::LET);
    if (input == "const")
        return TokenFactory::build(Token::Type::CONST);
    
    // boolean const
    if(input == "true")
        return TokenFactory::build(Token::Type::TRUE);
    if(input == "false")
        return TokenFactory::build(Token::Type::FALSE);

    return TokenFactory::build(Token::Type::ID, input);

    // throw exception
}

Token Lexer::getCurrentToken(){
    return this->currentToken;
}