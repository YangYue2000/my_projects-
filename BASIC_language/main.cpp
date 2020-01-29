#include <iostream>
#include <fstream>
#include "interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "File "<<argv[1]<<" cannot be opened." << endl;
        return 1;
    }
    ifstream input(argv[1]);
    Interpreter interpreter(input);
    interpreter.run();
    return 0;
}
