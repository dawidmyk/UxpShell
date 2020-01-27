#ifndef TOKEN_HPP_INCLUDED
#define TOKEN_HPP_INCLUDED

#include <string>
#include <ostream>
#include <iostream>
#include <map>


namespace token
{


    class Token
    {

    public:
        enum class Type
        {
            Eof,
            Variable,
            Identifier,
            PipeOperator,
            BackgroundOperator,
            bg,
            fg,
            jobs,
            pwd,
            echo,
            cd,
            Equals,
            Redirect,
            Dot,
            Slash,
            ParamOperator
        };
        Token();
        Token(std::string val, Type t);
        Token(Type t);
        Type getType() const;
        std::string getMval() const;
        const std::string& getStringValue() const;
        Token& operator=(const Token& other)
        {
            this-> mval=other.getMval();
            this-> type = other.getType();
            return *this;
        }


    private:
        std::string mval;
        Type type;
    };

    const std::map <const Token::Type, std::string> TypeName =
    {
        { Token::Type::Eof ,                "Eof"                   },
        { Token::Type::Variable ,           "Variable: "            },
        { Token::Type::Identifier ,         "Identifier: "          },
        { Token::Type::bg ,                 "KeyWord: bg"           },
        { Token::Type::fg ,                 "KeyWord: fg"           },
        { Token::Type::jobs ,               "KeyWord: jobs"         },
        { Token::Type::pwd ,                "KeyWord: pwd"          },
        { Token::Type::echo ,               "KeyWord: echo"         },
        { Token::Type::cd ,                 "KeyWord: cd"           },
        { Token::Type::Equals ,             "Equals: ="             },
        { Token::Type::Redirect ,           "Redirect: >"           },
        { Token::Type::Dot ,                "Dot: ."                },
        { Token::Type::Slash ,              "Slash: /"              },
        { Token::Type::PipeOperator ,       "PipeOperator: |"       },
        { Token::Type::BackgroundOperator , "BackgroundOperator: &" },
        { Token::Type::ParamOperator ,      "ParamOperator: -"      }
    };

    const std::map <const Token::Type, std::string> OperatorString =
    {
        { Token::Type::Redirect ,           ">"           },
        { Token::Type::PipeOperator ,       "|"       },
        { Token::Type::BackgroundOperator , "&" },
        { Token::Type::bg ,                 "bg"           },
        { Token::Type::fg ,                 "fg "           },
        { Token::Type::jobs ,               "jobs"         },
        { Token::Type::pwd ,                "pwd"          },
        { Token::Type::echo ,               "echo "         },
        { Token::Type::cd ,                 "cd "           },
        { Token::Type::Equals ,             "="             },
        { Token::Type::Redirect ,           ">"           },
        { Token::Type::Dot ,                "."                },
        { Token::Type::Slash ,              "/"              },
        { Token::Type::Identifier ,         "Identifier"              },
        { Token::Type::ParamOperator ,      "-"      }
    };

    const std::map <const char, const Token::Type> Operators =
    {
        { '=', Token::Type::Equals              },
        { '>', Token::Type::Redirect            },
        { '.', Token::Type::Dot                 },
        { '/', Token::Type::Slash               },
        { '-', Token::Type::ParamOperator       },
        { '&', Token::Type::BackgroundOperator  },
        { '|', Token::Type::PipeOperator        }
    };

    const std::map <const std::string, const Token::Type> RegisteredKeyWord =
    {
        { "bg",     Token::Type::bg   },
        { "fg",     Token::Type::fg   },
        { "jobs",   Token::Type::jobs },
        { "pwd",    Token::Type::pwd  },
        { "echo",   Token::Type::echo },
        { "cd",     Token::Type::cd   }
    };

    const std::map <const Token::Type, const bool> HasStringValue =
    {
        { Token::Type::Eof ,                false },
        { Token::Type::Variable ,           true  },
        { Token::Type::Identifier ,         true  },
        { Token::Type::PipeOperator ,       false },
        { Token::Type::BackgroundOperator , false },
        { Token::Type::bg ,                 false },
        { Token::Type::fg ,                 false },
        { Token::Type::jobs ,               false },
        { Token::Type::pwd ,                false },
        { Token::Type::echo ,               false },
        { Token::Type::cd ,                 false },
        { Token::Type::Equals ,             false },
        { Token::Type::Redirect ,           false },
        { Token::Type::Dot ,                false },
        { Token::Type::Slash ,              false },
        { Token::Type::ParamOperator ,      false }
    };

    const std::map <const Token::Type, const bool> IsKeyWord =
    {
        { Token::Type::Eof ,                false },
        { Token::Type::Variable ,           false  },
        { Token::Type::Identifier ,         false  },
        { Token::Type::PipeOperator ,       false },
        { Token::Type::BackgroundOperator , false },
        { Token::Type::bg ,                 true },
        { Token::Type::fg ,                 true },
        { Token::Type::jobs ,               true },
        { Token::Type::pwd ,                true },
        { Token::Type::echo ,               true },
        { Token::Type::cd ,                 true },
        { Token::Type::Equals ,             false },
        { Token::Type::Redirect ,           false },
        { Token::Type::Dot ,                false },
        { Token::Type::Slash ,              false },
        { Token::Type::ParamOperator ,      false }
    };
}

std::ostream& operator<<(std::ostream& out,  const token::Token& t);

#endif // TOKEN_HPP_INCLUDED
