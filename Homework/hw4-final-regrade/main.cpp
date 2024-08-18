#include <iostream>
#include <fstream>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

class hashTable {
public:
    int* table;
    int tableSize;
    hashTable(int);
    ~hashTable();
    int hash1(int);
    void linearProbing(int);
    void quadraticProbing(int);
    void heapify(int);
    void print(ofstream&);
    void search(int,ofstream&);
};

hashTable::hashTable(int tableSize) {
    table = new int[tableSize];
    this->tableSize = tableSize;

    for(int i = 0; i < tableSize; i++) {
        table[i] = -1;
    }
}

hashTable::~hashTable() {
    delete[] table;
    tableSize = 0;
}

int hashTable::hash1(int x) {
    return x % tableSize;
}

void hashTable::linearProbing(int x) {
    for(int i = 0; i < tableSize; i++) {
        int index = (hash1(x) + i) % tableSize;
        if(table[index] == -1) {
            table[index] = x;
            return;
        }
    }
}

void hashTable::quadraticProbing(int x) {
    for(int i = 0; i < tableSize; i++) {
        int index = (hash1(x) + (3*i + 5*i)) % tableSize;
        if(table[index] == -1) {
            table[index] = x;
            return;
        }
    }
}

void hashTable::heapify(int i) {
    int largest = i;
    int left_child_index = 2 * i + 1;
    int right_child_index = 2 * i + 2;

    if(left_child_index < tableSize && table[left_child_index] < table[largest]) {
        largest = left_child_index;
    }
    if(right_child_index < tableSize && table[right_child_index] < table[largest]) {
        largest = right_child_index;
    }

    if(largest != i) {
        swap(table[largest], table[i]);
        heapify(largest);
    }
}

void hashTable::print(ofstream &output) {
    int i = 0;
    while(i < tableSize-1) {
        output << table[i] << ",";
        i++;
    }
    output << table[i] << endl;
}

void hashTable::search(int searchVal, ofstream &output) {
    for(int i = 0; i < tableSize; i++) {
        if(table[i] == searchVal) {
            output << searchVal << " is found at index " << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    ArgumentManager am(argc,argv);
    ifstream input(am.get("input"));
    ofstream output(am.get("output"));
    // ifstream input("input2.txt");
    // ofstream output("output.txt");
    
    string inputLine, probingType;
    int inputValue, tableSize;
    int initializeVal = -1;

    getline(input, inputLine);
    // cout << tableSize << endl;
    tableSize = stoi(inputLine);
    hashTable hash(tableSize);
    // print(table, tableSize);

    getline(input, probingType);
    // cout << probingType << endl;

    if(probingType == "Linear probing") {
        while(getline(input, inputLine, ',')) {
            // cout << inputLine << endl;
            hash.linearProbing(stoi(inputLine));
        }
    }
    else if(probingType == "Quadratic probing") {
        while(getline(input, inputLine, ',')) {
            // cout << inputLine << endl;
            hash.quadraticProbing(stoi(inputLine));
        }
    }

    hash.print(output); // print hash table

    for(int i = (tableSize / 2) - 1; i >= 0; i--) {
        hash.heapify(i);
    }

    hash.print(output); // print min heap of hash table

    return 0;
}