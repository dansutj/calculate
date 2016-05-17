//
//  Calc.hpp
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#ifndef CALC_H_
#define CALC_H_
#include "SymbolTable.h"
#include "Storage.h"

class Parser;

class Calc
{
    friend class Parser;
public:
    Calc() : storage_(symTbl_) {}
private:
    Storage& GetStorage()
    {
        return storage_;
    }
    unsigned int AddSymbol(const string &str);
    unsigned int FindSymbol(const string &str) const;
    SymbolTable symTbl_;
    Storage storage_;
};

#endif /* Calc_hpp */
