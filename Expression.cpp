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

CommandParseContext* BasicExpression::execute(CommandParseContext *command, VariablesTable &vars) const {
    auto proc = make_unique<RealProcess>(exec);
    for(const auto &i: args)
        proc->addArg(i);
    command->processes.push_back(std::move(proc));
    command->type = CommandType::new_pipeline;
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
    std::string ret = exec;
    for(const auto &i: args)
    {
        ret+=(" "+i);
    }
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

CommandParseContext* ReservedExpression::execute(CommandParseContext *command, VariablesTable &vars) const {
	switch(oper.getType())
	{
		case token::Token::Type::cd:
			command->type = CommandType::cd;
            vars.setActualPath(text);
			return command;
		case token::Token::Type::bg:
			command->type = CommandType::bg;
			return command;
		case token::Token::Type::fg:
			command->type = CommandType::fg;
			return command;
		case token::Token::Type::echo:
			command->type = CommandType::echo;
            std::cout<<std::endl<<text<<std::endl;
			return command;
		case token::Token::Type::pwd:
			command->type = CommandType::pwd;
            std::cout<<std::endl<<vars.getActualPath()<<std::endl;
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

CommandParseContext* ComplexExpression::execute(CommandParseContext *command, VariablesTable &vars) const {
    command = expr->execute(command, vars);
    switch (oper.getType())
    {
        case token::Token::Type::AppendOperator:
            command->hasAppend = true;
            command->outputFile = std::move(file.getMval());
            return command;
        case token::Token::Type::Redirect:
            command -> hasDirectOutput = true;
            command->outputFile = std::move(file.getMval());
            return command;
        case token::Token::Type::InputOperator:
            command ->hasInput = true;
            command->inputFile  = std::move(file.getMval());
            return command;
        case token::Token::Type::PipeOperator:
            if(this->rest)
                command = rest->execute(command, vars);
            return command;
        case token::Token::Type::bg:
            command->inBackground = true;
            return command;
    }       
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
ComplexExpression::ComplexExpression(std::unique_ptr<Expression> LeftSide, token::Token op, token::Token f)
        :expr(std::move(LeftSide))
{
    oper = op;
    file = f;
}

ComplexExpression::~ComplexExpression()
{

}
