//
//  Exception.cpp
//  calculate
//
//  Created by 苏丹 on 16/5/9.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#include "Exception.h"

const char* Exception::what() const throw()
{
    return message_.c_str();
}

const char* Exception::StackTrace() const throw()
{
    return stackTrace_.c_str();
}

void Exception::FillStackTrace()
{


}