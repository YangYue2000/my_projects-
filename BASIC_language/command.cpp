#include "command.h"

using namespace std;

Command::~Command(){

}

set_value_command::set_value_command(NumericExpression* target, NumericExpression* value) : target(target), value(value){

}

set_value_command::~set_value_command(){
    delete this->target;
	delete this->value;
}

print_command::print_command(NumericExpression* target) : target(target){

}

print_command::~print_command(){
	delete this->target;
}

boolean_command::boolean_command(BooleanExpression* target, size_t LineNum){
	this->target = target;
	std::stringstream s;
    s<<LineNum;
    s>>name;
    this->LineNum = LineNum;
}

boolean_command::~boolean_command(){
	if(this->target) delete this->target;
}

string set_value_command::format() const{
	return "LET " + target->format() + " " +value->format();
}

string print_command::format() const{
	return "PRINT " + target->format();
}

string goto_command::format() const{
	return "GOTO <" + name + '>';
}

string boolean_command::format() const{
	return "IF " + target->format() + " THEN " + "<" + name + ">";
}

string gosub_command::format() const{
	return "GOSUB <" +name + '>';
}

string return_command::format() const{
	return "RETURN";
}

string end_command::format() const{
	return "END";
}

void print_command::print() const{
	cout<<target->get_value()<<endl;
}

size_t goto_command::goto_line() const{
	return LineNum;
}

bool boolean_command::boolean_result() const{
	return target->get_value();
}

size_t boolean_command::boolean_line() const{
	return LineNum;
}

size_t gosub_command::gosub_line() const{
	return LineNum;
}

NumericExpression* set_value_command::return_target(){
	return target;
}

NumericExpression* set_value_command::return_value(){
	return value;
}
