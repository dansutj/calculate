//
//  Node.h
//  calculate
//
//  Created by 苏丹 on 16/5/7.
//  Copyright © 2016年 苏丹. All rights reserved.
//

#ifndef Node_h
#define Node_h
#include <vector>
#include <assert.h>
using namespace std;

class Storage;

class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable(){}
    
private:
    Noncopyable(const Noncopyable&);
    const Noncopyable& operator=(const Noncopyable&);
};

class Node : private Noncopyable
{
public:
    virtual double Calc() const = 0;
    virtual ~Node() {};
    virtual bool IsLvalue() const
    {
        return false;
    }
    
    virtual void Assign(double)
    {
        assert(!"Assign called incorrectlly");
    }
};

class NumberNode : public Node
{
public:
    NumberNode(double number) : number_(number) {}
    double Calc() const;
    
private:
    const double number_;
};

class BinaryNode : public Node
{
public:
    BinaryNode(auto_ptr<Node>& left, auto_ptr<Node>& right) : left_(left), right_(right) {}
    ~BinaryNode();
protected:
    auto_ptr<Node> left_;
    auto_ptr<Node> right_;
};

class UnaryNode : public Node
{
public:
    UnaryNode(auto_ptr<Node>& child) : child_(child) {}
    ~UnaryNode();
protected:
    auto_ptr<Node> child_;
};

class UMinusNode : public UnaryNode
{
public:
    UMinusNode(auto_ptr<Node> child) :
    UnaryNode(child) {}
    
    double Calc() const;
};

class MultipleNode : public Node
{
public:
    MultipleNode(auto_ptr<Node>& node)
    {
        AppendChild(node, true);
    }
    
    ~MultipleNode();
    
    void AppendChild(auto_ptr<Node>& node, bool positive)
    {
        childs_.push_back(node.release());
        positives_.push_back(positive);
    }
    
protected:
    vector<Node*> childs_;
    vector<bool> positives_;
};

class SumNode : public MultipleNode
{
public:
    SumNode(auto_ptr<Node>& node) : MultipleNode(node) {}
    double Calc() const;
};

class ProductNode : public MultipleNode
{
public:
    ProductNode(auto_ptr<Node>& node) : MultipleNode(node) {}
    double Calc() const;
};

class VariableNode : public Node
{
public:
    VariableNode(unsigned int id, Storage& storage)
    :  id_(id), storage_(storage) {}
    
    double Calc() const;
    bool IsLvalue() const;
    void Assign(double);
private:
    const unsigned int id_;
    Storage& storage_;
};

class AssignNode : public BinaryNode
{
public:
    AssignNode(auto_ptr<Node>& left, auto_ptr<Node>& right) :
    BinaryNode(left, right)
    {
        assert(left_->IsLvalue());
    }
    
    double Calc() const;
};

#endif /* Node_h */












