#include "Expression.hpp"

Expression::~Expression()
{

}

BasicExpression::~BasicExpression()
{

}

BasicExpression::BasicExpression(std::string text): exec(std::move(text))
{
}

BasicExpression::BasicExpression(std::string text, token::Token t): exec(std::move(text))
{

}

BasicExpression::BasicExpression(std::string text,
                                 std::vector<std::string> params)
                                 : exec(std::move(text))
{
    args = params;
}

std::string BasicExpression::toString() const
{
    std::cout<<"tostring()\n";
    std::string ret = exec;
    for(const auto &i: args)
        ret+=(" "+i);
    return ret;
}

ReservedExpression::~ReservedExpression()
{

}

ReservedExpression::ReservedExpression(token::Token t)
{
    oper = t;
}

ReservedExpression::ReservedExpression(std::string s ,token::Token t): text(std::move(s))
{
    oper = t;
}

std::string ReservedExpression::toString() const
{
    if(oper.getType()==token::Token::Type::cd || oper.getType()==token::Token::Type::echo
       || oper.getType()==token::Token::Type::bg)
        return token::OperatorString.at(oper.getType())+text;
    return token::OperatorString.at(oper.getType());
}

std::string ComplexExpression::toString() const
{
    if(rest)
        return expr->toString() +" "+ token::OperatorString.at(oper.getType()) +" "+ rest->toString();
    else
        return expr->toString() +" "+ token::OperatorString.at(oper.getType());
}

ComplexExpression::ComplexExpression(std::unique_ptr<Expression> LeftSide,
                                     token::Token op, std::unique_ptr<Expression> RightSide)
                                     : expr(std::move(LeftSide)), rest(std::move(RightSide))
                                     {
                                         oper = op;
                                     }
ComplexExpression::ComplexExpression(std::unique_ptr<Expression> LeftSide, token::Token op)
        :expr(std::move(LeftSide))
{
    oper = op;
}

ComplexExpression::~ComplexExpression()
{

}
