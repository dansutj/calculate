//
//  Parser.cpp
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#include "Parser.h"
#include "Scanner.h"
#include "Node.h"
#include "Calc.h"
#include "Exception.h"
#include "SymbolTable.h"
#include "DebugNew.h"
#include <cassert>
#include <iostream>


Parser::Parser(Scanner& scanner, Calc& calc) : scanner_(scanner), calc_(calc), tree_(0) {}

Parser::~Parser()
{
    
}

void Parser::Parse()
{
    tree_ = Expr();
}

auto_ptr<Node> Parser::Expr()
{
    auto_ptr<Node> node = Term();
    EToken token = scanner_.Token();
    
    if(token == TOKEN_PLUS || token == TOKEN_MINUS)
    {
        auto_ptr<MultipleNode> multipleNode(new SumNode(node));
        do
        {
            scanner_.Accept();
            auto_ptr<Node> nextNode = Term();
            multipleNode->AppendChild(nextNode, token == TOKEN_PLUS);
            token = scanner_.Token();
        }
        while(token == TOKEN_PLUS || token == TOKEN_MINUS);
        node = multipleNode;
    }
    else if(token == TOKEN_ASSGIN)
    {
        scanner_.Accept();
        auto_ptr<Node> nodeRight = Expr();
        if(node->IsLvalue())
        {
            node = auto_ptr<Node>(new AssignNode(node, nodeRight));
        }
        else
        {
            status_ = STATUS_ERROR;
            throw SynatxError("The left-hand side of an assignment must be a variable");
        }
    }
    return node;
}

auto_ptr<Node> Parser::Term()
{
    auto_ptr<Node> node = Factor();
    EToken token = scanner_.Token();
    
    if(token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE)
    {
        auto_ptr<MultipleNode> multipleNode(new ProductNode(node));
        do
        {
            scanner_.Accept();
            auto_ptr<Node> nextNode = Factor();
            multipleNode->AppendChild(nextNode, token == TOKEN_MULTIPLY);
            token = scanner_.Token();
        }
        while(token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE);
        node = multipleNode;
    }
    return node;
}

auto_ptr<Node> Parser::Factor()
{
    auto_ptr<Node> node;
    EToken token = scanner_.Token();
    if(token == TOKEN_LPARENTHESIS)
    {
        scanner_.Accept();
        node = Expr();
        
        if(scanner_.Token() == TOKEN_RPARENTHESIS)
            scanner_.Accept();
        else
        {
            status_ = STATUS_ERROR;
            throw SynatxError("Missing parentthesis.");
        }
    }
    else if(token == TOKEN_NUMBER)
    {
        node = auto_ptr<Node>(new NumberNode(scanner_.GetNumber()));
        scanner_.Accept();
    }
    else if(token == TOKEN_IDENTIFIER)
    {
        string symbol = scanner_.GetSymbol();
        unsigned int id = calc_.FindSymbol(symbol);
        scanner_.Accept();
        
        if(id == SymbolTable::IDNOTFIND)
        {
            id = calc_.AddSymbol(symbol);
            if(id > calc_.GetStorage().GetSize())
                calc_.GetStorage().SetSize(id);
        }
        node = auto_ptr<Node>(new VariableNode(id, calc_.GetStorage()));
    }
    else if(token == TOKEN_MINUS)
    {
        scanner_.Accept();
        node = auto_ptr<Node>(new UMinusNode(Factor()));
    }
    else
    {
        status_ = STATUS_ERROR;
        throw SynatxError("not a valid expression");
    }
    return node;
}

double Parser::Calculate()
{
    assert(tree_.get() != NULL);
    return tree_->Calc();
}