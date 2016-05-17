//
//  Storage.hpp
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#ifndef STORAGE_H_
#define STORAGE_H_
#include <vector>
using namespace std;

class SymbolTable;

class Storage
{
public:
    Storage(SymbolTable& tbl);
    void Clear();
    bool IsInit(unsigned int id) const;
    void AddConstants(SymbolTable& tbl);
    double GetValue(unsigned int id) const;
    unsigned int GetSize() const;
    void SetSize(unsigned int);
    void SetValue(unsigned int id, double val);
    void AddValue(unsigned int id, double val);

private:
    unsigned size_;
    vector<double> cells_;
    vector<bool> inits_;
};

#endif /* Storage_hpp */
