#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "boolean.h"
#include <string>
using namespace std;

class Command {
public:
    virtual string format() const = 0;
    virtual ~Command();
};

class set_value_command : public Command {
public:
	set_value_command(NumericExpression* target, NumericExpression* value);
	~set_value_command();
	string format() const;
	NumericExpression* return_target();
	NumericExpression* return_value();
private:
	NumericExpression* target;
	NumericExpression* value;
};

class print_command : public Command {
public:
	print_command(NumericExpression* target);
	~print_command();
	string format() const;
	void print() const;
private:
	NumericExpression* target;
};

class goto_command : public Command{
public:
	goto_command(size_t LineNum){
		this->LineNum = LineNum;
		stringstream s;
		s<<LineNum;
		s>>name;
		this->LineNum = LineNum;
	};
	string format() const;
    size_t goto_line() const;
private:
	size_t LineNum;
	string name;
};

class boolean_command : public Command{
public:
	boolean_command(BooleanExpression* target, size_t LineNum);
	~boolean_command();
	string format() const;
	bool boolean_result() const; 
	size_t boolean_line() const;
private:
	BooleanExpression* target;
	size_t LineNum;
	string name;
};

class gosub_command : public Command{
public:
	gosub_command(size_t LineNum){
		stringstream s;
		s<<LineNum;
		s>>name;
		this->LineNum = LineNum;
	};
	string format() const;
	size_t gosub_line() const;
private:
	size_t LineNum;
	string name;
};

class return_command : public Command{
public:
	string format() const;
};

class end_command : public Command{
public:
	string format() const;
};

#endif
