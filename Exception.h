//
//  Exception.hpp
//  calculate
//
//  Created by 苏丹 on 16/5/9.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    explicit Exception(const char* message) : message_(message)
    {
        FillStackTrace();
    }
    virtual ~Exception() throw() {}
    virtual const char* what() const throw();
    const char* StackTrace() const throw();
    
private:
    void FillStackTrace();
    std::string message_;
    std::string stackTrace_;
};


class SynatxError : public Exception
{
public:
    explicit SynatxError(const char* message) : Exception(message) {}
    virtual ~SynatxError() throw() {}
};

#endif /* Exception_hpp */
