#include "Parser.hpp"

using namespace parser;
using namespace token;

Parser::Parser(std::unique_ptr<Scanner> scanner_)
  : scanner(std::move(scanner_))
{
}

Parser::~Parser()
{
}

std::unique_ptr<Expression> Parser::parse()
{
    advance();
    return readCommand();
}

std::unique_ptr<Expression> Parser::readCommand()
{
    auto t = getToken();

    if(IsKeyWord.at(t.getType()))
        return reservedCommand();
    else
        return complexCommand();
}

std::unique_ptr<Expression> Parser::reservedCommand()
{
    const auto t = getToken();
    switch(t.getType())
    {
    case Token::Type::bg: case Token::Type::jobs:
    case Token::Type::pwd:
        return std::make_unique<ReservedExpression>(t);
    case Token::Type::cd:
        {
            const auto dir = readDirectory();
            return std::make_unique<ReservedExpression>(dir, t);
        }
    case Token::Type::fg: case Token::Type::echo:
        const auto expr = readText();
        return std::make_unique<ReservedExpression>(expr, t);
    }
}

std::unique_ptr<Expression> Parser::basicCommand()
{
    const auto prog   = readCall();
    const auto params = readParams();
    return std::make_unique<BasicExpression>(prog, params);
}

std::unique_ptr<Expression> Parser::complexCommand()
{
    auto expr = basicCommand();
    auto t = readToken();
    if(t.getType() == Token::Type::PipeOperator)
        return std::make_unique<ComplexExpression>(std::move(expr), t, complexCommand());
    if(t.getType() == Token::Type::BackgroundOperator)
        return std::make_unique<ComplexExpression>(std::move(expr), t);
    requireToken(Token::Type::Eof);
    return std::move(expr);
}

std::string Parser::readDirectory()
{
    std::string ret="";
    while(checkTokenType(Token::Type::Slash))
    {
        advance();
        ret += "/"+requireTokenAndAdvance(Token::Type::Identifier).getStringValue();
    }
    return ret;
}

std::string Parser::readCall()
{
    std::string ret = "";
    if(checkTokenType(Token::Type::Dot))
    {
        advance();
        requireTokenAndAdvance(Token::Type::Slash);
        ret += "./"+readToken().getStringValue();
        return ret+=readDirectory();
    }
    if(checkTokenType(Token::Type::Slash))
        return ret+=readDirectory();
    else
        ret += requireTokenAndAdvance(Token::Type::Identifier).getStringValue();
    std::cout<<ret<<std::endl;
    return ret;
}

std::vector<std::string> Parser::readParams()
{
    std::vector<std::string> param;
    while(checkTokenType(Token::Type::ParamOperator)||checkTokenType(Token::Type::Identifier))
    {
        if(checkTokenType(Token::Type::ParamOperator))
        {
            advance();
            param.push_back("-"+requireTokenAndAdvance(Token::Type::Identifier).getStringValue());
        }
        else
            param.push_back(requireTokenAndAdvance(Token::Type::Identifier).getStringValue());
    }
    for(const auto &i: param)
        std::cout<<i<<std::endl;
    return param;
}

std::string Parser::readText()
{

}

Token Parser::readToken()
{
    const auto t = scanner->getToken();
    advance();
    return t;
}
Token Parser::getToken()
{
    return scanner->getToken();
}

void Parser::throwOnUnexpectedInput(Token::Type expected)
{
    throw std::runtime_error("Unexpected token: " + scanner->getToken().getStringValue()
                            + ", expecting: " + OperatorString.at(expected));
}

Token Parser::requireToken(Token::Type expected)
{
    auto token = scanner->getToken();
    if (token.getType() != expected)
        throwOnUnexpectedInput(expected);
    return token;
}

Token Parser::requireTokenAndAdvance(Token::Type expected)
{
    auto token = scanner->getToken();
    if (token.getType() != expected)
        throwOnUnexpectedInput(expected);
    advance();
    return token;
}


bool Parser::checkTokenType(Token::Type expected) const
{
    return scanner->getToken().getType() == expected;
}

void Parser::advance()
{
    scanner->readNextToken();
    std::cout<<scanner->getToken()<<std::endl;
}

