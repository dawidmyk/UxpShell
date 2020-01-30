#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <string>
#include <memory>
#include <vector>
#include "Token.hpp"
#include "Command.hpp"
#include "VariablesTable.h"

class Expression
{
public:
    virtual ~Expression();
    virtual std::string toString() const = 0;
    virtual CommandParseContext* execute(CommandParseContext *command, VariablesTable &vars) const = 0;
};

class BasicExpression : public Expression
{
public:

    BasicExpression(std::string text);
    BasicExpression(std::string text, std::vector<std::string> params);
    BasicExpression(std::string text, token::Token t);
    CommandParseContext* execute(CommandParseContext *command, VariablesTable &vars) const;
    ~BasicExpression();
    std::string toString() const override;

private:
    std::string exec;
    std::vector<std::string> args;
};

class ReservedExpression : public Expression
{
public:
    ReservedExpression(token::Token t);
    ReservedExpression(std::string s ,token::Token t);
    CommandParseContext* execute(CommandParseContext *command, VariablesTable &vars) const;
    ~ReservedExpression();
    std::string toString() const override;
private:
    token::Token oper;
    std::string text;
};

class ComplexExpression : public Expression
{
public:

    ComplexExpression(std::unique_ptr<Expression> LeftSide, token::Token op, std::unique_ptr<Expression> RightSide);
    ComplexExpression(std::unique_ptr<Expression> LeftSide, token::Token op);
    ComplexExpression(std::unique_ptr<Expression> LeftSide, token::Token op, token::Token f);
    CommandParseContext* execute(CommandParseContext *command, VariablesTable &vars) const;
    ~ComplexExpression();
    std::string toString() const override;

private:
    token::Token oper;
    token::Token file;
    std::unique_ptr<Expression> expr;
    std::unique_ptr<Expression> rest;
};

#endif // EXPRESSION_HPP_INCLUDED
