//
//  Storage.cpp
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#include "Storage.h"
#include <cmath>
#include <cassert>
#include "SymbolTable.h"

Storage::Storage(SymbolTable& tbl) : size_(0)
{
    AddConstants(tbl);
}

void Storage::Clear()
{
    cells_.clear();
    inits_.clear();
}

bool Storage::IsInit(unsigned int id) const
{
    return id < cells_.size() && inits_[id];
}

void Storage::AddConstants(SymbolTable& tbl)
{
    unsigned int id = tbl.Add("e");
    AddValue(id, exp(1.0));
    
    id = tbl.Add("pi");
    AddValue(id, 2.0 * acos(0.0));
}

double Storage::GetValue(unsigned int id) const
{
    assert(id < cells_.size());
    return cells_[id];
}

void Storage::SetValue(unsigned int id, double val)
{
    assert(id <= cells_.size());
    
    if(id < cells_.size())
    {
        cells_[id] = val;
        inits_[id] = true;
    }
    else if(id == cells_.size())
    {
        AddValue(id, val);
    }
}

void Storage::AddValue(unsigned int id, double val)
{
    cells_.resize(id + 1);
    inits_.resize(id + 1);
    size_ = id + 1;
    
    cells_[id] = val;
    inits_[id] = true;
}

unsigned int Storage::GetSize() const
{
    return size_;
}

void  Storage::SetSize(unsigned int size)
{
    cells_.resize(size);
    inits_.resize(size);
    size_ = size;
}
