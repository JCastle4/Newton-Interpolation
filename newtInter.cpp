//#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
//#include <chrono>
//using namespace std::chrono;
using std::cout, std::vector, std::string, std::cin, std::ifstream, std::endl, std::istringstream;

void Coeff(vector<double> xs, vector<double> ys, vector<double> &cs);
double EvalNewton(vector<double> xs, vector<double> cs, double z);
void fillVec(vector<double> &xs, vector<double> &ys, ifstream & infile);

int main(int argc, char* argv[]){

    vector<double> xvec;
    vector<double> yvec; 
    vector<double> cs;

    string file = "";
    if(argc == 2){file = argv[1];}

    std::ifstream MyFile(file);
    if (!MyFile.is_open()) {
        std::cout << "File Not Found." << std::endl;
    }
    else {
        fillVec(xvec,yvec, MyFile);
        Coeff(xvec, yvec, cs);
        MyFile.close();

        cout<< "Enter a value to evaluate or q to quit: " << endl;
        string input;
        cin >> input;
        while(input != "q"){
            bool flag = true;
            for (char const &ch : input) {
                if (!isdigit(ch)) 
                    flag = false;
            }

            if(!flag){cout << "Must be a number " << endl;}
            else{
                double x = stod(input);

                //auto start = high_resolution_clock::now();

                cout << EvalNewton(xvec, cs, x) << endl;

                //auto stop = high_resolution_clock::now();
                //auto duration = duration_cast<microseconds>(stop - start);
                //cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
            }
            cout<< "Enter a value to evaluate or q to quit: " << endl;
            cin >> input;
        }
    }

    return 0;
}

void Coeff(vector<double> xs, vector<double> ys, vector<double> &cs){

    for(int i = 0; i< ys.size();i++){
        cs.push_back(ys[i]);
    }

    for(int j = 1; j < ys.size(); j++){
        for(int i = ys.size(); i >= j; i--){
            cs[i] = (cs[i] - cs[i-1]) / (xs[i] - xs[i-j]);
        }
    }
}

double EvalNewton(vector<double> xs, vector<double> cs, double z){
    double result = cs[cs.size()-1];

    for(int i = cs.size()-2; i >= 0; i-- ){
        result = result * (z-xs[i]) + cs[i];
    }

    return result;
}

void fillVec(vector<double> &xs, vector<double> &ys, ifstream & infile){
    string line;

    getline(infile, line);
    istringstream ss(line);
    double num;
    while(ss >> num){
        xs.push_back(num);
    }

    getline(infile, line);
    istringstream ss2(line);
    while(ss2 >> num){
        ys.push_back(num);
    }
}