#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctype.h> 
#include <stdio.h> 
#include "ArgumentManager.h"
using namespace std;

struct node {
    int value;
    node *next;
    node *previous;

    node(int value) {
        this->value = value;
        next = nullptr;
        previous = nullptr;
    }
};

class numbers {
private:
    node *head;
public:
    numbers() { head = nullptr;}
    bool isEmpty() { return head;}
    node *getHead() { return head;}
    void insert(int);
    void print(ofstream&);
    void selectionSort(ofstream&,numbers&);
    void insertionSort(ofstream&,numbers&);
    void swap(node*,node*);
};

void numbers::insert(int value) {
    node *temp = new node(value);
    if(head == nullptr) {
        head = temp;
        return;
    }
    node *current = head;
    while(current->next != nullptr) {
        current = current->next;
    }
    current->next = temp;
    temp->previous = current;
}

void numbers::print(ofstream &ofs) {
    node *current = head;
    ofs << "[";
    while(current->next != nullptr) {
        ofs << current->value << ",";
        current = current->next;
    }
    ofs << current->value << "]\n";
}

void numbers::swap(node* node1, node* node2) {
    node *previous1 = node1->previous;
    node *previous2 = node2->previous;

    if(previous1 == nullptr) {
        head = node2;
    }
    else {
        previous1->next = node2;
    }
    if(previous2 == nullptr) {
        head = node1;
    }
    else {
        previous2->next = node1;
    }

    node *temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;
    temp = node1->previous;
    node1->previous = node2->previous;
    node2->previous = temp;

    if(node1->next != nullptr) {
        node1->next->previous = node1;
    }
    if(node2->next != nullptr) {
        node2->next->previous = node2;
    }
}

void numbers::selectionSort(ofstream &ofs, numbers &list) {
    if(head == nullptr || head->next == nullptr) { return;}
    
    node *current = head;
    while(current->next != nullptr) {
        node *minimum = current;
        node *innerCurrent = current->next;

        while(innerCurrent != nullptr) {
            if(innerCurrent->value < minimum->value) {
                minimum = innerCurrent;
            }
            innerCurrent = innerCurrent->next;
        }

        if(minimum != current) {
            swap(current,minimum);
            list.print(ofs);
            continue;     
        }
        else {
            list.print(ofs);
        }

        current = current->next;
    }
}

void numbers::insertionSort(ofstream &ofs,numbers &list) {
    if(head == nullptr || head->next == nullptr) { return;}

    node *key = head->next;
    node *current;  
    node *keyNext = key->next;
    node *temp;
    while(key != nullptr) {
        current = key;
        while(current->previous != nullptr && current->previous->value > key->value) {
            current = current->previous;
        }
        if(current == key) {
            temp = head;
            list.print(ofs);
            key = keyNext;
            if(keyNext != nullptr) {
                keyNext = keyNext->next;
            }
        }
        else {
            if(current->previous == nullptr) {
                head = key;
                key->next = current;
                current->previous = key;
                key->previous->next = keyNext;
                if(key->next != nullptr) {
                    keyNext->previous = key->previous;
                }
                key->previous = nullptr;
                temp = head;
                list.print(ofs);
                key = keyNext;
                if(keyNext != nullptr) {
                    keyNext = keyNext->next;
                }
            }
            else {
                current->previous->next = key;
                key->previous->next = keyNext;
                if(keyNext != nullptr) {
                    keyNext->previous = key->previous;
                }
                key->previous = current->previous;
                key->next = current;
                current->previous = key;
                temp = head;
                list.print(ofs);
                key = keyNext;
                if(keyNext != nullptr) {
                    keyNext = keyNext->next;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
    ifstream ifs(input);
    ofstream ofs(output);
    // ifstream ifs("input1.txt");
    // ofstream ofs("output1.txt");
    if(!ifs.is_open() || !ofs.is_open()) {  // check if files opened
        cout << "Could not open file\n";
        return -1;
    }
    string inputLine, numberToAdd;
    numbers list;
 
    getline(ifs,inputLine); // check if first line is valid
    if(isdigit(inputLine[0])) {
        stringstream ss(inputLine);
        while(ss>>numberToAdd) {
            list.insert(stoi(numberToAdd));
        }
    }
    else {
        ofs << "Input is invalid.";
        return 0;
    }

    getline(ifs,inputLine); // check if second line is valid
    if(inputLine == "Selection") {
        list.selectionSort(ofs,list);
        // list.print(ofs);
        // selection sort
    }
    else if(inputLine == "Insertion") {
        list.insertionSort(ofs,list);
        // list.print(ofs);
        // insertion sort
    }
    else {
        ofs << "Input is invalid.";
        return 0;
    }

    ifs.close();
    ofs.close();

    return 0;
}