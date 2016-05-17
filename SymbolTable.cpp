//
//  SymbolTable.cpp
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#include "Exception.h"
#include "SymbolTable.h"

unsigned int SymbolTable::Add(const string& str)
{
    dictionary_[str] = curId_;
    return curId_++;
}

unsigned int SymbolTable::Find(const string& str) const
{
    map<const string, unsigned int>::const_iterator it;
    it = dictionary_.find(str);
    if(it != dictionary_.end())
        return it->second;
    
    return IDNOTFIND;
}

void SymbolTable::Clear()
{
    dictionary_.clear();
    curId_ = 0;
}

class IsEqualId
{
public:
    IsEqualId(unsigned int id) : id_(id) {}
    bool operator()(const pair<const string, unsigned int>& it) const
    {
        return it.second == id_;
    }
private:
    unsigned int id_;
};


string SymbolTable::GetSymbolName(unsigned int id) const
{
    map<const string, unsigned int>::const_iterator it;
    it = find_if(dictionary_.begin(), dictionary_.end(), IsEqualId(id));
    
    if(it == dictionary_.end()){
        throw Exception("Internal error : missing entry in symbol table");
    }
    return it->first;
}




