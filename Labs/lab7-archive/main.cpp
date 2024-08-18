#include <iostream>
#include <fstream>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

struct vertex {
    int value;
    vertex* next;
    vertex() : value(-999), next(nullptr) {}
    vertex(int x) : value(x), next(nullptr) {}
};

bool hasCycleUtil(int v, vector<vertex*>& arr, vector<int>& visited, vector<int>& recursionStack) {
    visited[v] = 1;  // Mark as visited
    recursionStack[v] = 1;  // Add to recursion stack

    vertex* current = arr[v]->next;
    while (current != nullptr) {
        int neighbor = current->value;
        if (!visited[neighbor]) {
            if (hasCycleUtil(neighbor, arr, visited, recursionStack)) {
                return true;
            }
        } else if (recursionStack[neighbor]) {
            // If the neighbor is already in the recursion stack, then there is a cycle.
            return true;
        }
        current = current->next;
    }

    recursionStack[v] = 0;  // Remove from recursion stack
    return false;
}

bool hasCycle(vector<vertex*>& arr, int size) {
    vector<int> visited(size, 0);
    vector<int> recursionStack(size, 0);

    for (int i = 0; i < size; ++i) {
        if (!visited[i] && hasCycleUtil(i, arr, visited, recursionStack)) {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream output(am.get("output"));
    // ifstream input("input1.txt");
    // ofstream output("output.txt");
    int numVertices;
    int inputValue1, inputValue2;

    input >> numVertices;

    vector<vertex*> arr(numVertices, nullptr);

    for (int i = 0; i < numVertices; ++i) {
        arr[i] = new vertex(i);
    }

    while (input >> inputValue1 >> inputValue2) {
        if (arr[inputValue1]->value == -999) {
            arr[inputValue1]->value = inputValue1;
            arr[inputValue1]->next = new vertex(inputValue2);
        } else {
            vertex* current = arr[inputValue1];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new vertex(inputValue2);
        }
    }

    if (hasCycle(arr, numVertices)) {
        output << "TRUE" << endl;
    } else {
        output << "FALSE" << endl;
    }

    return 0;
}
