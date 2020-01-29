#include <iostream>
#include <fstream>
#include <string>
#include<sstream>

using namespace std; 

double backtracking(double max, double load, int index, int last, double limit, double* w, double* l);

int main(int argc, char* argv[]){
	if(argc != 2){
		cerr << "please provide an input file" << endl;
		return 1;
	}
	ifstream input(argv[1]);
	string line;
	getline(input,line);
	stringstream s(line);
	int num;
	double limit;
	s >> num >> limit;
	double* w = new double[num];
	double* l = new double[num];
	string classes;
	for(int i=0; i<num; i++){
		getline(input,line);
		stringstream ss(line);
		ss>> classes >> w[i] >> l[i];
	}
	double result = backtracking(0, 0, 0, num, limit, w, l);
	cout<<result;
	return 0;
}

double backtracking(double max, double load, int index, int last, double limit, double* w, double* l){
		double local_max = 0;
		for(int i=index; i<last; i++){
			if(load+w[i] <= limit){
				double temp = backtracking(max+l[i], load+w[i], i+1, last, limit, w, l);
				if(temp > local_max){
					local_max = temp;
				}
			}
			else{
				if(max > local_max){
					local_max = max;
				}
			}
		}
		if(index == last){
			return max;
		}
		else{
			return local_max;
		}
}
