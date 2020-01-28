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

CommandParseContext* BasicExpression::execute(CommandParseContext *command){
    command->processes.push_back(std::make_unique<Process>(this->toString()));
    return command;
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

CommandParseContext* ReservedExpression::execute(CommandParseContext *command){
	switch(oper.getType())
	{
		case token::Token::Type::cd:
			command->type = CommandType::cd;
			return command;
		case token::Token::Type::bg:
			command->type = CommandType::bg;
			return command;
		case token::Token::Type::fg:
			command->type = CommandType::fg;
			return command;
		case token::Token::Type::echo:
			command->type = CommandType::echo;
			return command;
		case token::Token::Type::pwd:
			command->type = CommandType::pwd;
			return command;
		case token::Token::Type::jobs:
			command->type = CommandType::jobs;
			return command;
	}
}

std::string ComplexExpression::toString() const
{
    if(rest)
        return expr->toString() +" "+ token::OperatorString.at(oper.getType()) +" "+ rest->toString();
    else
        return expr->toString() +" "+ token::OperatorString.at(oper.getType());
}

CommandParseContext* ComplexExpression::execute(CommandParseContext *command){
    command = expr->execute(command);
    if(this->rest)
    {
        switch (oper.getType())
        {
        case token::Token::Type::AppendOperator:
            command->hasAppend = true;
            return rest->execute(command);
        case token::Token::Type::Redirect:
            command -> hasDirectOutput = true;
            return rest->execute(command);
        case token::Token::Type::InputOperator:
            command -> hasInput = true;
            return rest->execute(command);
        }
    }   
    else
        command->inBackground = true;
    
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
