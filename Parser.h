//
//  Parser.hpp
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <memory>
using namespace std;

class Node;
class Scanner;
class Calc;

enum STATUS
{
    STATUS_OK,
    STATUS_QUIT,
    STATUS_ERROR
};

class Parser
{
public:
    Parser(Scanner& scanner, Calc& calc);
    ~Parser();
    void Parse();
    auto_ptr<Node> Expr();
    auto_ptr<Node> Term();
    auto_ptr<Node> Factor();
    double Calculate();
    
private:
    Scanner& scanner_;
    auto_ptr<Node> tree_;
    STATUS status_;
    Calc& calc_;
};

#endif /* Parser_hpp */
