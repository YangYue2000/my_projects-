#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "command.h"
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>


using namespace std;

class Interpreter {
public:
    Interpreter(istream& in);
    ~Interpreter();//

    void write(ostream& out);
    void run();

protected:
    void parse(istream& in);
    ConstantVariable* parse_constant(stringstream& input);
    string parse_name(stringstream& input);
    NumericExpression* parse_numeric(stringstream& input);
    BooleanExpression* parse_boolean(stringstream& input);
    vector<size_t> linelist;
    stack<size_t> jump_linelist;
    map<size_t, Command*> commandlist;
    map<string, int> variable_map;
    string type(Command* input);
    string to_string(int input);
    size_t prev_line = 0;
};

#endif
