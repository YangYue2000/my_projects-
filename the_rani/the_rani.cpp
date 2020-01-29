#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <math.h>//////include this to extrasct fraction part in function MOVE
#include<exception>
#include<cstdlib>

using namespace std;

class TheRani {
public:

    TheRani(char* input_path, char* output_path);
    ~TheRani();

    // Call execute and handles exceptions
    void main();

private:


    string** subject_history;   // And for each subject, their history
    int line_count = 0;
    int subject_pool_count;
    bool started = false;             //////
    int experiment_count;       // You will need to track the number of experiments
    int* subject_counts;        // For each, the number of subjects
    

    ifstream input;             // Input file stream
    ofstream output;            // Output file stream

    // Called in the main method
    void execute(const string& line);

    // Possible helper: deallocate all current members
    void destroy();//////// deallocated memories when a new Start is called or when the program ends.
    void move(int x, int y, int n, int m);
};

TheRani::TheRani(char* input_path, char* output_path) : input(input_path), output(output_path) , experiment_count(0){

}

TheRani::~TheRani() {
    destroy();
}

void TheRani::destroy(){/////
    if(experiment_count > 0){
        for(int i=0; i<experiment_count; i++){
            delete[] subject_history[i];
        }
        delete[] subject_history;

        delete[] subject_counts;
    }
}

void TheRani::move(int x, int y, int n, int m){//create new subject_history array and new subject_count array
    
    stringstream s;
    s<<y;
    string EXP2;
    s>>EXP2;

    string* buffer = new string[m-n+1];
    for(int i=0; i<m-n+1; i++){
        buffer[i] = subject_history[x][n+i];
    }

    for(int i=0; i<subject_pool_count-1-m; i++){
        subject_history[x][n+i] = subject_history[x][m+1+i];
    }

    subject_counts[x] -= m-n+1;

    for(int i=0; i<m-n+1; i++){
        subject_history[y][subject_counts[y]+i] = buffer[i]+EXP2+" ";
    }

    subject_counts[y] += m-n+1;
    delete [] buffer;
}

// Possible helper: read an integer argument from a stream

void TheRani::main() {
    string line;
    while (getline(input, line)) {
        try {
            this->execute(line);
        } catch(exception& e) {
            // If you use exceptions, make sure the line number is printed here
            this->output << "Error on line "<<line_count<<": " << e.what() << endl;
        }
    }
}

void TheRani::execute(const string& line) {
    line_count++;
    string command;
    stringstream stream(line);  // Initialize the stream with the line
    stream >> command;          // Read the first word, which is the command

    //cerr << "Before executing command: " << line << endl;
    //print_history();
    
    if (command!="START")
    {
        if(command!="ADD"&&command!="MOVE"&&command!="QUERY"){
            throw logic_error("command does not exist");
        }
        else if((line_count==0)||(line_count>0&&started==false)){
            throw logic_error("no subjects yet");
        }
        else{
            if(command == "ADD"){
                experiment_count++;

                string** new_history = new string*[experiment_count];
            //plus two because 1 for the subjecgt pool and 1 for the new experiment
            //create a new array that's larger than the old on 

                for(int i=0; i<experiment_count; i++){
                    new_history[i] = new string[subject_pool_count];
                }

                for(int i=0; i<experiment_count-1;i++){
                    for(int j=0; j<subject_pool_count; j++){

                        cerr<<subject_history[i][j];
                        new_history[i][j] = subject_history[i][j];

                    }
                }
            //copy the values from old array into the new array
                int* new_count = new int[experiment_count];
            //same reason for new_history
                for(int i=0; i<experiment_count-1; i++){
                    new_count[i] = subject_counts[i];
                }
                new_count[experiment_count-1] = 0;
            //copy values into new count array. 

                experiment_count--;
                destroy();
                experiment_count++;
                subject_history = new_history;
                subject_counts = new_count;
            //after extracting the values from old arrays, 
            //delete them, and then reassign them with new arrays

            //update the number of experiments
            }
            

            else if(command == "MOVE"){

        //the following block of code reads in the arguments and check for excpetions
                int exp1, exp2, range1, range2, intpart;
                double temp;
                string buffer;
                bool not_integer = false;
                bool negative = false;
                int num_count=0;
                while(stream>>buffer){////read in arguments parameters and count numbers
                    num_count++;
                    if(num_count>4){
                        break;
                    }
                    stringstream ss;
                    ss<<buffer;
                    ss>>temp;//convert the parsed_out strings into doubles
                    
                    if(ss.fail()){
                        not_integer = true;//check if the input is garbage value
                    }
                    else if(temp<0){
                        negative = true;
                    //a negative double also implies a negative integer
                    }

                    if(temp==0){
                        intpart = temp;
                    }
                    else{
                        intpart = (int)temp;
                    }


                    if((temp-intpart)!=0){
                        not_integer = true;
                    //shows the input parameter is a double, not an integer
                    }
                    else{
                        if(num_count==1)
                        {
                            exp1 = intpart;
                        }
                        else if (num_count==2)
                        {
                            exp2 = intpart;
                        }
                        else if (num_count==3)
                        {
                            range1 = intpart;
                        }
                        else if (num_count==4)
                        {
                            range2 = intpart;
                        }
                    }
                }

                //clear errors
                if(num_count<4){
                    throw logic_error("too few arguments");
                }
                else if(not_integer){
                    throw logic_error("expected integer argument");
                }
                else if((exp1<0||(exp1>experiment_count))||
                    (exp2<0||(exp2>experiment_count))||
                    (range1<0||range1>=subject_counts[exp1])||
                    (range2<0||range2>=subject_counts[exp1])||
                    negative)
                {
                    throw logic_error("argument out of range");
                }
                else if(range1>range2){
                    throw logic_error("invalid range of subjects to move");
                }
                else{
                    move(exp1, exp2, range1, range2);
                }
            }

            else if (command=="QUERY")
            {
                

                int x, n, intpart;

                double temp;
                string buffer;
                bool not_integer = false;
                bool negative = false;
                int num_count=0;
                while(stream>>buffer){////read in arguments parameters and count numbers
                    num_count++;
                    if(num_count>2){
                        break;
                    }
                    stringstream ss;
                    ss<<buffer;
                    ss>>temp;//convert the parsed_out strings into doubles
                    
                    if(ss.fail()){
                        not_integer = true;//check if the input is garbage value
                    }
                    else if(temp<0){
                        negative = true;
                    //a negative double also implies a negative integer
                    }

                    if(temp==0){
                        intpart = temp;
                    }
                    else{
                        intpart = (int)temp;
                    }


                    if((temp-intpart)!=0){
                        not_integer = true;
                    //shows the input parameter is a double, not an integer
                    }
                    else{
                        if(num_count==1)
                        {
                            x = intpart;
                        }
                        else if (num_count==2)
                        {
                            n = intpart;
                        }
                    }
                }

                //clear errors
                if(num_count<2){
                    throw logic_error("too few arguments");
                }
                else if(not_integer){
                    throw logic_error("expected integer argument");
                }
                else if((x<0||(x>experiment_count))||
                    (n<0||n>=subject_counts[x])||
                    negative)
                {
                    throw logic_error("argument out of range");
                }


                output<<subject_history[x][n] << endl;
            }
        }
    }

    else{//start function begings here
        int intpart;
        double temp;
        string buffer;
        bool not_integer = false;
        bool negative = false;
        int num_count=0;
        while(stream>>buffer){
            num_count++;
            if(num_count>1){
                break;
            }
            stringstream ss;
            ss<<buffer;
            ss>>temp;//convert the parsed_out strings into doubles

            if(ss.fail()){
                not_integer = true;
            }
            else if(temp<0){
                negative = true;
                    //a negative double also implies a negative integer
            }

            if(temp==0){
                intpart = temp;
            }
            else{
                intpart = (int)temp;
            }


            if((temp-intpart)!=0){
                not_integer = true;
                    //shows the input parameter is a double, not an integer
            }
            else{
                if(num_count==1)
                {
                    subject_pool_count = intpart;
                }
            }
        }

                //clear errors
        if(num_count<1){
            throw logic_error("too few arguments");
        }
        else if(not_integer){
            throw logic_error("expected integer argument");
        }
        else if(negative)
        {
            throw logic_error("argument out of range");
        }

        else{
            if(started){//if previous experiments exist, destroy them first
                //cout<<"asdasfa";
                destroy();
            }
            experiment_count = 1;
            subject_counts = new int[1];
            subject_counts[0] = subject_pool_count;

            subject_history = new string*[1];
            subject_history[0] = new string[subject_pool_count];
            for(int i=0; i<experiment_count; i++){
                for(int j=0; j<subject_pool_count; j++){
                    subject_history[i][j] = "";
                }
            }
            started = true;
        }
    }
    //cerr << "After executing command: " << line << endl;
    //print_history();
}





int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Please provide an input and output file!" << endl;
        return 1;
    }


    TheRani tr(argv[1], argv[2]);   
    tr.main();
    return 0;
}
