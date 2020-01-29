#include "boolean.h"

using namespace std;

BooleanExpression::~BooleanExpression(){
	delete this->left;
	delete this->right;
}

BiggerCheck::BiggerCheck(NumericExpression* left, NumericExpression* right){
	this->left = left;
	this->right = right;
}

BiggerCheck::~BiggerCheck(){
}

SmallerCheck::SmallerCheck(NumericExpression* left, NumericExpression* right){
	this->left = left;
	this->right = right;
}

SmallerCheck::~SmallerCheck(){
}

EqualCheck::EqualCheck(NumericExpression* left, NumericExpression* right){
	this->left = left;
	this->right = right;
}

EqualCheck::~EqualCheck(){
}

string BiggerCheck::format() const {
	return "[" + right->format() + " < " + left->format() + "]";
}

string SmallerCheck::format() const{
	return "[" + left->format() + " < " + right->format() + "]";
}

string EqualCheck::format() const{
	return "[" + left->format() + " = " + right->format() + "]";
}

bool BiggerCheck::get_value() const{
	return left->get_value() > right->get_value();
}

bool SmallerCheck::get_value() const{
	return left->get_value() < right->get_value();
}

bool EqualCheck::get_value() const{
	return left->get_value() == right->get_value();
}
