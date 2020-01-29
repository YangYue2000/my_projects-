#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

#include "arithmetic.h"
#include <string>
using namespace std;

class BooleanExpression{
public:

	virtual ~BooleanExpression();
	virtual string format() const = 0;
	virtual bool get_value() const = 0;
protected:
	NumericExpression* left;
	NumericExpression* right;
};

class BiggerCheck : public BooleanExpression{
public:
	string format() const; 
	bool get_value() const;
	BiggerCheck(NumericExpression* left, NumericExpression* right);
	~BiggerCheck();
};

class SmallerCheck : public BooleanExpression{
public:
	string format() const;
	bool get_value() const;
	SmallerCheck(NumericExpression* left, NumericExpression* right);
	~SmallerCheck();
};

class EqualCheck : public BooleanExpression{
public:
	string format() const;
	bool get_value() const;
	EqualCheck(NumericExpression* left, NumericExpression* right);
	~EqualCheck();
};

#endif
