#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

class NumericExpression {
public:
    virtual ~NumericExpression();
    virtual string format() const = 0;
    virtual int get_value() const = 0;
    bool is_array = false;
};

class Variable : public NumericExpression{
public:
	virtual ~Variable();
	virtual string format() const = 0;
	virtual int get_value() const = 0;
protected:
	string name;
	map<string,int>* value_map;
};


class IntVariable : public Variable{
public:
	IntVariable(string name, map<string,int>* input_map);
	string format() const;
	int get_value() const;
};

class ArrayVariable : public Variable{
public:
	ArrayVariable(string name, NumericExpression* index, map<string,int>* input_map);
	~ArrayVariable();
	string format() const;
	int get_value() const;
	string print_value() const;
private:
	NumericExpression* index;
};


class ConstantVariable : public Variable{
public:
	ConstantVariable(int value);
	string format() const;
	int get_value() const;
};

class BinaryExpression : public NumericExpression {
public:
	virtual ~BinaryExpression();
	virtual string format() const = 0;
protected:
	NumericExpression* left;
	NumericExpression* right;
};

class AdditionExpression : public BinaryExpression{
public:
	AdditionExpression(NumericExpression* left, NumericExpression* right);
	~AdditionExpression();
	string format() const;
	int get_value() const;
};


class DeductionExpression : public BinaryExpression {
public:
    DeductionExpression(NumericExpression* left, NumericExpression* right);
    ~DeductionExpression();
    string format() const;
    int get_value() const;
};

class MultiplicationExpression : public BinaryExpression{
public:
	MultiplicationExpression(NumericExpression* left, NumericExpression* right);
	~MultiplicationExpression();
	string format() const;
	int get_value() const;
};

class DivisionExpression : public BinaryExpression{
public:
	DivisionExpression(NumericExpression* left, NumericExpression* right);
	~DivisionExpression();
	string format() const;
	int get_value() const;
};

#endif
