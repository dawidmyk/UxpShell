#ifndef SCANNER_HPP_INCLUDED
#define SCANNER_HPP_INCLUDED

#include <istream>
#include <ostream>
#include <stdexcept>
#include <iostream>
#include "Token.hpp"


class Scanner
{
public:
    Scanner(std::istream& in);
    Scanner(const Scanner&) = delete;
    const Scanner& operator=(const Scanner&) = delete;
    token::Token getToken();
    void readNextToken();
private:
    void ignoreWhitespace();
    void setToken();
    bool tryEof();
    bool tryKeyWord(std::string text);
    void throwOnStreamError();
    bool tryValue();
    bool tryVariable();
    bool tryIdentifier();
    bool tryOperator();
    bool tryString();
    void throwTokenTypeError();
    std::string getString();
    token::Token token;
    std::istream& in;
};

#endif // SCANNER_HPP_INCLUDED
