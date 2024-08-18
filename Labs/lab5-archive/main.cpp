#include <iostream>
#include <fstream>
#include <map>
#include "ArgumentManager.h"
using namespace std;


int main(int argc, char *argv[]) {
    ArgumentManager am(argc,argv);
    ifstream input(am.get("input"));
    ofstream output(am.get("output"));
    
    // ifstream input("input1.txt");
    // ofstream output("output1.txt");
    int num;
    string word;
    map<string, int> mapping;
    
    input >> num;

    for(int i = 0; i < num; i++) {
        input >> word;

        if(mapping[word] == -1) {
            mapping[word] = 1;
        }
        else {
            mapping[word]++;
        }
    }

    for(auto word: mapping) {
        output << word.first << ": " << word.second << endl;
    }

    return 0;
}