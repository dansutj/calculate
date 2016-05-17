//
//  Node.cpp
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//
#include <iostream>
#include <cmath>
#include <cassert>
#include "Storage.h"
#include "DebugNew.h"
#include "Node.h"

double NumberNode::Calc() const
{
    return number_;
}

BinaryNode::~BinaryNode()
{
    
}

UnaryNode::~UnaryNode()
{
}

double UMinusNode::Calc() const
{
    return -(child_->Calc());
}

MultipleNode::~MultipleNode()
{
    vector<Node*>::const_iterator it;
    for(it = childs_.begin(); it != childs_.end(); ++it){
        delete *it;
    }
}

double SumNode::Calc() const
{
    double result = 0.0;
    vector<Node*>::const_iterator childIt = childs_.begin();
    vector<bool>::const_iterator positiveIt = positives_.begin();
    
    for(; childIt != childs_.end(); ++childIt, ++positiveIt)
    {
        assert(positiveIt != positives_.end());
        double val = (*childIt)->Calc();
        if(*positiveIt) result += val;
        else result -= val;
    }
    assert(positiveIt == positives_.end());
    return result;
}

double ProductNode::Calc() const
{
    double result = 1.0;
    vector<Node*>::const_iterator childIt = childs_.begin();
    vector<bool>::const_iterator positiveIt = positives_.begin();
    
    for(; childIt != childs_.end(); ++childIt, ++positiveIt)
    {
        assert(positiveIt != positives_.end());
        double val = (*childIt)->Calc();
        
        if(*positiveIt)
            result *= val;
        else if(val != 0.0)
            result /= val;
        else
        {
            cout << "Divsion by zero" << endl;
            return HUGE_VAL;
        }
            
    }
    assert(positiveIt == positives_.end());
    return result;
}

double VariableNode::Calc() const
{
    double x = 0.0;
    if(storage_.IsInit(id_))
        x = storage_.GetValue(id_);
    else
    {
        cout << "Usage of uninitalize variable" << endl;
    }
    return x;
}

bool VariableNode::IsLvalue() const
{
    return true;
}

void VariableNode::Assign(double val)
{
    storage_.SetValue(id_, val);
}

double AssignNode::Calc() const
{
    double x = 0.0;
    x = right_->Calc();
    left_->Assign(x);
    return x;
}

