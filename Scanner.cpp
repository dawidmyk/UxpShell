#include "Scanner.hpp"
#include <cctype>
#include <string>
#include <stdlib.h>

using namespace token;

Scanner::Scanner(std::istream& in_)
  : in(in_)
{
}


void Scanner::readNextToken()
{
    ignoreWhitespace();
    if(tryEof()) return;
    throwOnStreamError();
    if(tryIdentifier()||tryVariable()||tryOperator())
        return;
    throwTokenTypeError();
}

Token Scanner::getToken()
{
    return token;
}

void Scanner::ignoreWhitespace()
{
    while(in && std::isspace(in.peek()))
         in.get();
}

void Scanner::throwOnStreamError()
{
  if (!in)
    throw std::runtime_error("Error while reading from input");
  // TODO better error description
}

bool Scanner::tryEof()
{
    if(!in.eof())
        return false;
    token = Token();
    return true;
}

std::string Scanner::getString()
{
    std::string text="";
    while(in && (!std::isspace(in.peek()))&&(!std::ispunct(in.peek()))&&(std::isalnum(in.peek())))
        text+=in.get();
    if(in.peek()=='.')
    {
        text+=in.get();
        if(!std::isalnum(in.peek()))
            throwTokenTypeError();
        while(in && (!std::isspace(in.peek()))&&(!std::ispunct(in.peek()))&&(std::isalnum(in.peek())))
            text+=in.get();
    }
    return text;
}

bool Scanner::tryKeyWord(std::string text)
{
    for(const auto &key: RegisteredKeyWord)
    {
        if(text == key.first)
        {
            token=Token(key.second);
            return true;
        }
    }
    return false;
}

bool Scanner::tryVariable()
{
    if(in.peek()=='$')
    {
        in.get();
        token = Token(getString(), Token::Type::Variable);
        return true;
    }
    return false;
}

bool Scanner::tryOperator()
{
    for(const auto &o: Operators)
    {
        if(in.peek() == o.first)
        {
			if(in.peek()=='>')
			{
				in.get();
				token = in.peek()=='>' ? Token::Type::AppendOperator : Token::Type::Redirect;
				in.get();
			}
            token=Token(o.second);
            in.get();
            return true;
        }
    }
    return false;
}

bool Scanner::tryIdentifier()
{
    if(in &&!std::isalpha(in.peek()))
    {
        return false;
    }
    std::string text=getString();
    if(tryKeyWord(text))
        return true;
    token = Token(text, Token::Type::Identifier);
    return true;
}

void Scanner::throwTokenTypeError()
{
  const std::string msg = "Unknown token, starting with: ";
  throw std::runtime_error(msg + static_cast<char>(in.get()));
}

