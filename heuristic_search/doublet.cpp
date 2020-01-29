#include<string>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<map>
#include<fstream>
#include "heap.h"

using namespace std;

//have a map that matches words and their nth orders;

//a map that matches words and their g value;

int get_h(string word, string target);

int main(int argc, char* argv[]){
	if(argc != 4){
		cerr << "please provide two words and a file name";
		return 1;
	}
	ifstream input(argv[3]);
	string start = argv[1];
	string end = argv[2];
	transform(start.begin(), start.end(), start.begin(), ::toupper);
	transform(end.begin(), end.end(), end.begin(), ::toupper);
	map<string, vector<string>> word_map;
	vector<string> word_list;
	int n = start.length();//n is the length of word
	string line;
	string word;
	int total;//total number of words in the file
	getline(input,line);
	stringstream N(line);
	N >> total;
	while(getline(input,line)){
		stringstream buffer(line);
		buffer >> word;
		transform(word.begin(), word.end(), word.begin(), ::toupper);
		//capitalize all the words;
		word_list.push_back(word);
		word_map.insert(pair<string,vector<string>>(word,vector<string>()));
		
	}
	for(int i=0; i<total; i++){
	//iterate through all the words
		word = word_list[i];
		if(word.length() == start.length()){
			for(unsigned int i=0; i<word.length(); i++){
			//all possible words differ by one letter: n
				char target = word[i];
				string sub1 = word.substr(0,i);
				string sub2 = word.substr(i+1);
				char x = 'A';
				for( int i=0; i<26; i++){
				//all possible words differ by one letter: n*25
					if(target!=x){
						string edge = sub1 + x + sub2;
						vector<string>::iterator IT;
						IT = find(word_list.begin(), word_list.end(), edge);
						if(IT != word_list.end()){
							word_map[word].push_back(edge);
						}
					}
					x++;//x iterates from A to Z
				}
			}
		}
	}
    int expansion = 0;
    bool found = false;
	MinHeap<string> heap(2);
	map<string,int> g;//store all words'g-value;
	map<string, int> p;//store all words' priority;
	map<string, int> nth;//store all words' nth value;
	int priority = get_h(start,end)*(n+2);
	//f(n+1)+h=(g+h)(n+1)+h=h(n+1)+h=h(n+2)
	g.insert(pair<string,int>(start,0));
	p.insert(pair<string,int>(start, priority));
	nth.insert(pair<string,int>(start,heap.add(start,priority)));
	while(!heap.isEmpty()){
		string top = heap.peek();
		int old_g = g[top];
		if(top == end){
			//this is the case when the start word and the end word is the same
			found = true;
			break;
		}
		heap.remove();
		expansion++;
		vector<string> edges = word_map[top];
		for(unsigned int i=0; i<edges.size(); i++){
			//for all outgoing edges of this node
			//check if has been visited
			string new_word = edges[i];
			int new_g = old_g+1;
			int h = get_h(new_word,end);
			priority = (h+new_g)*(n+1)+h;
			if(g.find(new_word) == g.end()){
				//the new word has not been visited
				int order = heap.add(new_word,priority);
				g.insert(pair<string,int>(new_word,new_g));
				p.insert(pair<string,int>(new_word,priority));
				nth.insert(pair<string,int>(new_word,order));
			}
			else{
				//the new word has been visited
				int index = nth[new_word];
				if(p[new_word] > priority){
					p[new_word] = priority;
					heap.update(index,priority);
					g[new_word] = new_g;
				}
			}
		}
	}
	if(found){
		cout<<get_h(start,end)<<endl;
		cout<<expansion<<endl;
	}
	else{
		cout<<"No transformation"<<endl;
		cout<<expansion<<endl;
	}
	return 0;
}

int get_h(string word, string target){
	int h = 0;
	for(unsigned int i=0; i<word.length(); i++){
		if(word[i]!=target[i]){
			h++;
		}
	}
	return h;
}
