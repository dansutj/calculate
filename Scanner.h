//
//  Scanner.h
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#ifndef SCANNER_H_
#define SCANNER_H_
#include <string>
using namespace std;

enum EToken
{
    TOKEN_END,
    TOKEN_ERROR,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPARENTHESIS,
    TOKEN_RPARENTHESIS,
    TOKEN_IDENTIFIER,
    TOKEN_ASSGIN
};

class Scanner
{
public:
    explicit Scanner(const string& buf);
    void Accept();
    double GetNumber() const;
    string GetSymbol() const;
    EToken Token() const;
private:
    void SikpWhite();
    const string buf_;
    unsigned int curPos_;
    EToken token_;
    double number_;
    string symbol_;
};

#endif /* Scanner_h */
