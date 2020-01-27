#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include <memory>
#include <iostream>
#include <vector>

#include "../Scanner/Scanner.hpp"
#include "Expression.hpp"

namespace parser
{

class Parser
{
public:
  Parser(std::unique_ptr<Scanner> scanner);
  ~Parser();

  std::unique_ptr<Expression> parse();

private:
  std::unique_ptr<Expression> basicCommand();
  std::unique_ptr<Expression> readCommand();
  std::unique_ptr<Expression> reservedCommand();
  std::unique_ptr<Expression> complexCommand();
  std::unique_ptr<Expression> assigmnemntOperation();
  std::string readDirectory();
  std::string readText();
  std::string readCall();
  std::vector<std::string> readParams();
  void basicCommand(const std::unique_ptr<Expression> previousCommand, token::Token t);

  void throwOnUnexpectedInput(token::Token::Type expected);
  token::Token requireToken(token::Token::Type expected);
  token::Token requireTokenAndAdvance(token::Token::Type expected);
  bool checkTokenType(token::Token::Type expected) const;
  token::Token readToken();
  token::Token getToken();
  void advance();

  std::unique_ptr<Scanner> scanner;
};

} // namespace parser



#endif // PARSER_HPP_INCLUDED
