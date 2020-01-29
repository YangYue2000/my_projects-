#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


int main(int argc, char* argv[]){
	if (argc < 2) {
        cout << "Please provide an input and output file!" << endl;
        return 1;
    } 
    ifstream input(argv[1]);
    int size;
    string line;
    string buffer;
    getline(input,buffer);
    getline(input,line);
    stringstream s(buffer);
    s>>size;
    for(int i=0; i<size; i++){
    	cout<<line.at(size-1-i);
    }
    return 0;
}
