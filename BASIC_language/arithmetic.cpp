#include "arithmetic.h"

using namespace std;

NumericExpression::~NumericExpression(){
    
}

Variable::~Variable(){

}

BinaryExpression::~BinaryExpression(){
    delete this->left;
    delete this->right;
}

IntVariable::IntVariable(string name, map<string,int>* input_map){
    this->name = name;
    this->value_map = input_map;
}

ArrayVariable::ArrayVariable(string name, NumericExpression* index, map<string,int>* input_map){
    this->name = name;
    this->index = index;
    this->value_map = input_map;
    is_array = true;
}

ConstantVariable::ConstantVariable(int value){
    stringstream s;
    string buffer;
    s<<value;
    s>>buffer;
    this->name = buffer;
}

ArrayVariable::~ArrayVariable(){
	delete this->index;
}

AdditionExpression::AdditionExpression(NumericExpression* left, NumericExpression* right){
    this->left = left;
    this->right = right;
}

DeductionExpression::DeductionExpression(NumericExpression* left, NumericExpression* right){
    this->left = left;
    this->right = right;
}

MultiplicationExpression::MultiplicationExpression(NumericExpression* left, NumericExpression* right){
    this->left = left;
    this->right = right;
}

DivisionExpression::DivisionExpression(NumericExpression* left, NumericExpression* right){
    this->left = left;
    this->right = right;
}

AdditionExpression::~AdditionExpression(){
}

DeductionExpression::~DeductionExpression(){
}

MultiplicationExpression::~MultiplicationExpression(){
}

DivisionExpression::~DivisionExpression(){
}

string IntVariable::format() const{
	return this->name;
}

string ArrayVariable::format() const{
	return this->name + '[' + this->index->format() + ']';
}

string ArrayVariable::print_value() const{
    stringstream buffer;
    string position;
    buffer << this->index->get_value();
    buffer >> position;
    return this->name+'['+position+']';
}

string ConstantVariable::format() const{
	return this->name;
}

string AdditionExpression::format() const{
    return "(" + left->format() + " + " + right->format() + ")";
}

string DeductionExpression::format() const{
	return "(" + left->format() + " - " + right->format() + ")";
}

string MultiplicationExpression::format() const{
	return "(" + left->format() + " * " + right->format() + ")";
}

string DivisionExpression::format() const{
	return "(" + left->format() + " / " + right->format() + ")";
}

int IntVariable::get_value() const{
    return (*value_map)[this->name];
}


int ArrayVariable::get_value() const{
    string variable_name = this->print_value();
    return (*value_map)[variable_name];
}

int ConstantVariable::get_value() const{
    stringstream buffer;
    int value;
    buffer << this->name;
    buffer >> value;
    return value;
}

int AdditionExpression::get_value() const{
    return left->get_value() + right->get_value();
}

int DeductionExpression::get_value() const{
    return left->get_value() - right->get_value();
}

int MultiplicationExpression::get_value() const{
    return left->get_value()*right->get_value();
}

int DivisionExpression::get_value() const{
    if(right->get_value() == 0){
        string a = left->format();
        string b = right->format();
        stringstream buffer;
        string temp;
        buffer << left->get_value();
        buffer >> temp;
        throw logic_error(": Division by 0: "+a+" = "+temp+" , "+b+" = "+'0');
        return 0;
    }
    return left->get_value()/right->get_value();
}
