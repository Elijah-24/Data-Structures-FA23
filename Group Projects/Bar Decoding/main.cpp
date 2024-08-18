#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h> 
#include <stdio.h>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

struct person { 
    string code;
    person *next;

    person(string code) {
        this->code = code;
        next = nullptr;
    }
};

class bar {
private:
    person *head;
public:
    bar() { head = nullptr;}
    person *getHead() { return head;}
    bool isEmpty() { return head;}
    void insertHead(person*);
    void print(person*,ofstream&);
    void remove(string);
    void sort();
};

void bar::insertHead(person *p) {
    if(head == nullptr) {
        head = p;
        return;
    }
    p->next = head;
    head = p;
}

void bar::print(person *current, ofstream &ofs) {
    if(current == nullptr) {
        return;
    }
    
    ofs << current->code << endl;
    print(current->next,ofs);
}

void bar::remove(string deleteCode) {
    person *current = head;
    person *previous = nullptr;

    while(current != nullptr) {
        if(current->code == deleteCode && current == head) {
            person *deletePerson = current;
            head = head->next;
            delete deletePerson;
            previous = current;
        }
        else if(current->code == deleteCode && current->next != nullptr) {
            person *deletePerson = current;
            previous->next = current->next;
            delete deletePerson;
        }
        else if(current->code == deleteCode && current->next == nullptr) {
            previous->next = nullptr;
            delete current;
        }
        else {
            previous = current;
        }
        current = current->next;
    }
}

void bar::sort() {
    if(head == nullptr || head->next == nullptr) {
        return;
    }
    bool swapped = false;
    person *current = nullptr;
    while(!swapped) {
        swapped = true;
        current = head;
        while(current->next != nullptr) {
            if(stoi(current->code) > stoi(current->next->code)) {
                string tempData = current->code;
                current->code = current->next->code;
                current->next->code = tempData;
                swapped = false;
            }
            current = current->next;
        }
    }
}

void parseInput(string& s, size_t start, size_t& end) {
    for (size_t i = start; i < s.length(); ++i) {
        if (s[i] == '(') {
            parseInput(s, i + 1, end);
            std::reverse(s.begin() + i, s.begin() + end + 1);
            i = end; // Skip past the processed section
        } else if (s[i] == ')') {
            end = i; // Update the end position
            return;
        }
    }
}

void compareBars(bar bar1, bar &bar2, bar &guilty, bar &innocent) {
    person *current = bar1.getHead();
    while(current != nullptr) {
        person *temp = new person(current->code);
        innocent.insertHead(temp);
        current = current->next;
    }
    current = bar2.getHead();
    while(current != nullptr) {
        person *temp = new person(current->code);
        innocent.insertHead(temp);
        current = current->next;
    }
    current = innocent.getHead();
    
    // innocent.print(innocent.getHead());
    innocent.sort();
    current = innocent.getHead();
    while(current->next != nullptr) {
        if(current->code == current->next->code) {
            person *temp = new person(current->code);
            guilty.insertHead(temp);
            innocent.remove(current->code);
        }
        current = current->next;
    }
    guilty.sort();
}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
    ifstream ifs(input);
    ofstream ofs(output);
    
    string inputLine, barNum;
    bar bar1,bar2;
    bar guilty,innocent;
    // ifstream ifs("input3.txt");
    // ofstream ofs("output1.txt");
    if(!ifs.is_open()) { cout<<"Could not open file.\n";}

    while(getline(ifs,inputLine)) {
        if(inputLine.empty()) {
            // cout << "empty\n";
            continue;
        }
        else if(inputLine == "Bar1" || inputLine == "Bar2") { 
            barNum = inputLine;
            getline(ifs,inputLine);
            if(inputLine.length() == 0) {
                getline(ifs,inputLine);
            }
        }
        size_t end = 0;
        parseInput(inputLine,0,end);
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '('), inputLine.end());
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), ')'), inputLine.end());
        person *temp = new person(inputLine);
        //cout << temp->code << endl;

        if(barNum == "Bar1") {
            bar1.insertHead(temp);
        }
        else if(barNum == "Bar2") {
            bar2.insertHead(temp);
        }
        
    }
    ifs.close();

    // bar1.print(bar1.getHead());
    // cout << endl;
    // bar2.print(bar2.getHead());
    // cout << endl;
    compareBars(bar1,bar2,guilty,innocent);

    if(guilty.isEmpty()) {
        ofs << "Guilty: " << endl;
        guilty.print(guilty.getHead(),ofs);
    }

    if(innocent.isEmpty()) {
        ofs << "Innocent: " << endl;
        innocent.print(innocent.getHead(),ofs);
    }

    ofs.close();

    return 0;
}