#include "interpreter.h"
#include <vector>
#include <ctype.h>
#include <stdio.h>

using namespace std;

Interpreter::Interpreter(istream& in){
    this->parse(in);
}

Interpreter::~Interpreter() {
	
	for(auto it = commandlist.begin(); it != commandlist.end(); ++it)
	{
		delete it->second;
	}
}

string Interpreter::type(Command* input){
	stringstream buffer;
	string name = input->format();
	string type;
	buffer << name;
	buffer >> type;
	return type;
}

string Interpreter::to_string(int input){
	stringstream buffer;
	string goal;
	buffer << input;
	buffer >> goal;
	return goal;
}

void Interpreter::run() {
	vector<size_t>::iterator it = linelist.begin();
	string line;
	while(it != linelist.end() && this->type(commandlist[*it]) != "END"){
		Command* curr_command = commandlist[*it];
		try{
			string command_type = this->type(curr_command);
			stringstream buffer;
			buffer << *it;
			buffer >> line;
			if(command_type == "LET"){
				set_value_command* object = static_cast<set_value_command*>(curr_command);
				if(prev_line > *it){
					NumericExpression* target = object->return_target();
					NumericExpression* value = object->return_value();
					string variable_name;
					if(target->is_array){
						ArrayVariable* object = static_cast<ArrayVariable*>(target);
						variable_name = object->print_value();
					}
					else{
						variable_name = target->format();
					}
					variable_map[variable_name] = value->get_value();

				}
				++it;
			}
			else if(command_type == "PRINT"){
				print_command* object = static_cast<print_command*>(curr_command);
				object->print();
				++it;
			}
			else if(command_type == "GOTO"){
				goto_command* object = static_cast<goto_command*>(curr_command);
				size_t goto_line = object->goto_line();
				string temp = to_string(goto_line);
				it = find(linelist.begin(),linelist.end(), goto_line);
				if(it == linelist.end()){
					throw string("Error in Line "+line+": GOTO to non-existent line " + temp);
				}
			}
			else if(command_type == "IF"){
				boolean_command* object = static_cast<boolean_command*>(curr_command);
				if(object->boolean_result()){
					size_t goto_line = object->boolean_line();
					string temp = to_string(goto_line);
					it = find(linelist.begin(),linelist.end(), goto_line);
					if(it == linelist.end()){
						throw string("Error in Line "+line+": IF jump to non-existent line " + temp);
					}
				}
				else{
					++it;
				}
			}
			else if(command_type == "GOSUB"){
				prev_line = *it;
				size_t old_line = *it;
				gosub_command* object = static_cast<gosub_command*>(curr_command);
				size_t goto_line = object->gosub_line();
				string temp = to_string(goto_line);
				it = find(linelist.begin(),linelist.end(), goto_line);
				if(it == linelist.end()){
					throw string("Error in Line "+line+": GOSUB to non-existent line " + temp);
				}
				else{
					jump_linelist.push(old_line);
				}
			}
			else if(command_type == "RETURN"){
				if(jump_linelist.empty()){
					throw string("Error in Line "+line+": No matching GOSUB for RETURN");
				}
				else{
					size_t goto_line = jump_linelist.top();
					it = find(linelist.begin(),linelist.end(), goto_line);
					++it;
					jump_linelist.pop();
				}
			}
		} 
		catch(string e){
			cerr << e << endl;
			return;
		}
		catch(exception& e){
			cerr << "Error in Line "+ line+e.what();
			return;
		}
	}
}

void Interpreter::parse(istream& in) {
    string line;
    while (getline(in, line)) {
    	size_t line_number;
        string line_command;
        stringstream stream(line);
        stream >> line_number;
        linelist.push_back(line_number);
        stream >> line_command >> ws;
        if(line_command == "PRINT"){
        	NumericExpression* target = parse_numeric(stream);
        	commandlist[line_number] = new print_command(target);
        }
        else if(line_command == "LET"){
        	NumericExpression* target = parse_numeric(stream);
        	stream>>ws;
        	NumericExpression* value = parse_numeric(stream);
        	string variable_name;
        	if(target->is_array){
        		ArrayVariable* object = static_cast<ArrayVariable*>(target);
        		variable_name = object->print_value();
        	}
        	else{
        		variable_name = target->format();
        	}
        	variable_map[variable_name] = value->get_value();
        	commandlist[line_number] = new set_value_command(target, value);
        }
        else if(line_command == "IF"){
        	stream >> ws;
        	BooleanExpression* target = parse_boolean(stream);
        	string then;
        	size_t LineNum;
        	stream >> then;
        	stream >> LineNum;
        	commandlist[line_number] = new boolean_command(target, LineNum);
        }
        else if(line_command == "GOTO"){
        	size_t LineNum;
        	stream >> LineNum;
        	commandlist[line_number] = new goto_command(LineNum);
        }
        else if(line_command == "GOSUB"){
        	size_t LineNum;
        	stream>>LineNum;
        	commandlist[line_number] = new gosub_command(LineNum);
        }
        else if(line_command == "RETURN"){
        	commandlist[line_number] = new return_command;
        }
        else if(line_command == "END"){
        	commandlist[line_number] = new end_command;
        }
    }
}

void Interpreter::write(ostream& out) {
	for(size_t i=0; i<linelist.size(); i++){
		cout<<linelist[i]<<" "<<commandlist[linelist[i]]->format()<<endl;
	}
}

string Interpreter::parse_name(stringstream& input){
	input>>ws;
	string name;
	char buffer;
	while(isalpha((char)input.peek())){
		input>>buffer;
		name += buffer;
	}
	return name;
}

ConstantVariable* Interpreter::parse_constant(stringstream& input){
	input>>ws;
	int constant;
	char buffer;
	string constant_buffer;
	bool isNegative = false;
	char garbage;
	if(input.peek()=='-'){
		isNegative = true;
		input>>garbage;
	}
	while(isdigit(input.peek())){
		input>>buffer;
		constant_buffer += buffer;
	}
	stringstream num(constant_buffer);
	num>>constant;
	if(isNegative){
		constant *= -1;
	}
	return new ConstantVariable(constant);
}

NumericExpression* Interpreter::parse_numeric(stringstream& input){
	char garbage;
	if(input.peek() == '-' || isdigit(input.peek())){
		return parse_constant(input);
	}
	else if(isalpha(input.peek())){
		string name = parse_name(input);
		input>>ws;//skip possible whitespace between array name and []
		map<string, int>::iterator it;
		if(input.peek() == '['){
			input>>garbage;//to get rid of'['
			input>>ws;//skip possible whitespace between [ and index
			NumericExpression* index = parse_numeric(input);
			input>>garbage;//to get rid of']'
			//the following block of codes transfer the value of the index into a string
			int buffer = index->get_value();
			string temp;
			stringstream s;
			s << buffer;
			s >> temp;
			    //the end of the block of code
			name = name+'['+temp+']';
			if(variable_map.empty()){
				variable_map.insert(pair<string,int>(name,0));
			}
			else{
				it = variable_map.find(name);
				if(it == variable_map.end()){
					variable_map.insert(pair<string,int>(name,0));
				}
			}
			return new ArrayVariable(name, index, &variable_map);
		}
		else{
			if(variable_map.empty()){
				variable_map.insert(pair<string,int>(name,0));
			}
			else{
				it = variable_map.find(name);
				if(it == variable_map.end()){
					variable_map.insert(pair<string,int>(name,0));
				}
			}
			return new IntVariable(name, &variable_map);
		}
	}
	else if(input.peek() == '('){
		input>>garbage;//to get rid of '('
		input>>ws;//skip possible whitespace between ( and NEXP;
		NumericExpression* left = parse_numeric(input);
		char binary; 
		input>>binary;
		input>>ws;
		NumericExpression* right = parse_numeric(input);
		input>>garbage;//to get rid of')'
		if(binary == '+'){
			return new AdditionExpression(left,right);
		}
		else if(binary == '-'){
			return new DeductionExpression(left,right);
		}
		else if(binary == '*'){
			return new MultiplicationExpression(left,right);
		}
		else if(binary == '/'){
			return new DivisionExpression(left,right);
		}
	}
	return 0;
}

BooleanExpression* Interpreter::parse_boolean(stringstream& input){
	NumericExpression* left = parse_numeric(input);
	input>>ws;
	char comparison;
	input >> comparison >> ws;
	NumericExpression* right = parse_numeric(input);
	if(comparison =='>'){
		return new BiggerCheck (left,right);
	}
	else if(comparison == '<'){
		return new SmallerCheck (left,right);
	}
	else if(comparison == '='){
		return new EqualCheck (left,right);

	}
	return 0;
}
