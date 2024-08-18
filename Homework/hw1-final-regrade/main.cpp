#include <iostream>
#include <string>
#include <ctype.h>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;

string greatestToLeast(string &inputNumbers, int size) {
    if(size == 0) {
        return inputNumbers;
    }

    for(int i = 0; i < size; i++) {
        if(inputNumbers[size] > inputNumbers[i]) {
            swap(inputNumbers[i], inputNumbers[size]);
        }
    }

    return greatestToLeast(inputNumbers, size-1);
}

int main(int argc, char *argv[]) {

    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
    ifstream ifs(input);
    ofstream ofs(output);

    //ifstream ifs("input3.txt");
    string inputNumbers;
    string fromFile;

    if(!ifs.is_open()) {
        cout << "Cannot open input1.txt.\n";
    }

    getline(ifs, fromFile);

    for(int i = 0; i < fromFile.length(); i++) {
        if(isdigit(fromFile[i])) {
            inputNumbers += fromFile[i];
        }
    }
    ifs.close();

    //cout << inputNumbers << endl;

    ofs << greatestToLeast(inputNumbers, inputNumbers.length()-1) << endl;

    return 0;
}