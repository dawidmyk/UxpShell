#include "Token.hpp"

using namespace token;

Token::Token():type(Type::Eof), mval(std::move(""))
{
}
Token::Token(std::string val, Type t): mval(std::move(val))
{
    type=t;
}

Token::Token(Type t)
{
    type=t;
}

Token::Type Token::getType() const
{
    return type;
}

std::string Token::getMval() const
{
    return mval;
}

 const std::string& Token::getStringValue() const
{
    if(type==Token::Type::Identifier)
        return mval;
    return OperatorString.at(type);
}

std::ostream& operator<<(std::ostream& out, const Token& t)
{
    std::string ret;
    ret = TypeName.at(t.getType());
    ret += HasStringValue.at(t.getType()) ? t.getStringValue() : "";
    return out<< ret;
}
