//
//  Calc.cpp
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#include "Calc.h"

unsigned int Calc::FindSymbol(const string& str) const
{
    return symTbl_.Find(str);
}

unsigned int Calc::AddSymbol(const string& str)
{
    return symTbl_.Add(str);
}