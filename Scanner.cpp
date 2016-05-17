//
//  Scanner.cpp
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#include "Scanner.h"
#include <string>
#include <stdlib.h>
#include <cctype>
using namespace std;

Scanner::Scanner(const string& buf) : buf_(buf), curPos_(0)
{
    Accept();
}

double Scanner::GetNumber() const
{
    return number_;
}

string Scanner::GetSymbol() const
{
    return symbol_;
}

EToken Scanner::Token() const
{
    return token_;
}

void Scanner::SikpWhite()
{
    while(isspace(buf_[curPos_]))
        curPos_++;
}


void Scanner::Accept()
{
    SikpWhite();
    switch (buf_[curPos_])
    {
        case '+':
            token_ = TOKEN_PLUS;
            ++curPos_;
            break;
            
        case '-':
            token_ = TOKEN_MINUS;
            ++curPos_;
            break;
            
        case '*':
            token_ = TOKEN_MULTIPLY;
            ++curPos_;
            break;
            
        case '/':
            token_ = TOKEN_DIVIDE;
            ++curPos_;
            break;
            
        case '(':
            token_ = TOKEN_LPARENTHESIS;
            ++curPos_;
            break;
            
        case '=':
            token_ = TOKEN_ASSGIN;
            ++curPos_;
            break;
            
        case ')':
            token_ = TOKEN_RPARENTHESIS;
            ++curPos_;
            break;
            
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case '.':
            token_ = TOKEN_NUMBER;
            char *p;
            number_ = strtod(&buf_[curPos_], &p);
            curPos_ = int(p - &buf_[0]);
            break;
            
        case '\n': case '\r': case EOF:
            token_ = TOKEN_END;
            
        default:
            if(isalpha(buf_[curPos_]) || buf_[curPos_] == '_')
            {
                token_ = TOKEN_IDENTIFIER;
                symbol_.erase();
                char ch = buf_[curPos_];
                do
                {
                    symbol_ += ch;
                    ch = buf_[++curPos_];
                }
                while(isalnum(ch) || ch == '-');
            }
            else token_ = TOKEN_ERROR;
            break;
    }
}

