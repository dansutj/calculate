//
//  SymbolTable.hpp
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#include <map>
#include <string>
using namespace std;

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

class SymbolTable
{
public:
    enum { IDNOTFIND = 0xffffffff };
    SymbolTable() : curId_(0) {}
    unsigned int Add(const string& str);
    unsigned int Find(const string& str) const;
    void Clear();
    string GetSymbolName(unsigned int id) const;
    
private:
    map<const string, unsigned int> dictionary_;
    unsigned int curId_;
};

#endif /* SymbolTable_hpp */
