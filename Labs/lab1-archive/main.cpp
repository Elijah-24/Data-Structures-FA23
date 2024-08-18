#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

string reverseString(string phrase, int begOfWord, int endOfWord) {
    string reversedPhrase = phrase;
    if(begOfWord == endOfWord) {
        return reversedPhrase;
    }
    
    swap(reversedPhrase[begOfWord], reversedPhrase[endOfWord]);
    reverseString(reversedPhrase, begOfWord+1, endOfWord-1);
}


int main(int argc, char *argv[]) {
    
    string phrase;
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
     
    /*ifstream ifs("input1.txt");
    if(!ifs.is_open()) {
        cout << "Could not open file." << endl;
        return -1;
    }*/

    ifstream ifs(input);
    if(!ifs.is_open()) {
        cout << "Could not open file." << endl;
        return -1;
    }

    getline(ifs, phrase);
    for(int i = 0; i < phrase.length(); i++) {
        phrase[i] = tolower(phrase[i]);
        
        if(isalnum(phrase[i]) == false) {
            phrase[i] = '\0';
        }
    }

    ifs.close();

    ofstream ofs(output);

    if(phrase == "") {
        ofs << "true\n";
    }

    if(reverseString(phrase, 0, phrase.length()-1) == phrase) {
        ofs << "true\n";
    }
    else {
        ofs << "false\n";
    }

    ofs.close();

    return 0;
}