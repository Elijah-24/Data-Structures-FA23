#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

struct node {
    int priority;
    string instruction;
    node *next;

    node(int priority, string instruction) {
        this->priority = priority;
        this->instruction = instruction;
        next = nullptr;
    }
};

class queue {
private:
    node *head;
public:
    queue() { head = nullptr;}
    node *getHead() { return head;}
    bool isempty();
    void insert(int,string);
    string pop();
    void sort(queue&);
    void print(ofstream&,node*);
};

bool queue::isempty() {
    if(head == nullptr) {
        return true;
    }
    return false;
}

void queue::insert(int priority, string direction) { // inserts at tail
    node *temp = new node(priority, direction);
    if(head == nullptr) {
        head = temp;
        return;
    }
    node *current = head;
    while(current->next != nullptr) {
        current = current->next;
    }
    current->next = temp;
}

string queue::pop() {
    if(head == nullptr) { return "";}

    node *temp = head;
    head = head->next;
    return temp->instruction;
}

void queue::sort(queue &q) {
    if(head == nullptr || head->next == nullptr) { return;}

    node *current = head;
    while(current->next != nullptr) {
        node *minimum = current;
        node *innerCurrent = current->next;

        while(innerCurrent != nullptr) {
            if(innerCurrent->priority < minimum->priority) {
                minimum = innerCurrent;
            }
            innerCurrent = innerCurrent->next;
        }

        if(minimum != current) {
            int tempPriority = minimum->priority;
            minimum->priority = current->priority;
            current->priority = tempPriority;

            string tempInstruction = minimum->instruction;
            minimum->instruction = current->instruction;
            current->instruction = tempInstruction;
        }
        current = current->next;
    }
}

void queue::print(ofstream &ofs, node *current) {
    if(head == nullptr) { return;}

    ofs << current->priority << " " << current->instruction << endl;
    print(ofs,current->next);
}

void doorState(string instruction, bool &closed, bool &unlocked) {
    if(instruction == "open the door") {
        if(closed) {
            if(unlocked) { closed = false;}
        }
    }
    else if(instruction == "close the door") {
        if(!closed) {
            if(unlocked) { closed = true;}
        }
    }
    else if(instruction == "lock the door") { unlocked = false;}
    else if(instruction == "unlock the door") { unlocked = true;}
}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc,argv);
    string input = am.get("input");
    string output = am.get("output");
    ifstream ifs(input);
    ofstream ofs(output);
    // ifstream ifs("input3.txt");
    // ofstream ofs("output.txt");
    string inputLine;
    string direction, priority;
    queue door;
    bool closed = true;
    bool unlocked = true;
    
    while(getline(ifs,inputLine)) {
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\n'), inputLine.end());
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\r'), inputLine.end());
        
        if(inputLine.length() < 17) {
            continue;
        }
        
        direction = inputLine.substr(0, inputLine.find('(')-1);
        //cout << direction << " ";
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), ')'), inputLine.end());
        priority = inputLine.substr(inputLine.find('(')+1, inputLine.find(')'));
        //cout << priority << endl;

        door.insert(stoi(priority),direction);
    }
    ifs.close();
    door.sort(door);

    while(!door.isempty()) {
        direction = door.pop();
        // ofs << direction << endl;
        doorState(direction,closed,unlocked);
    }

    if(closed) { ofs << "the door is closed\n";}
    else if(!closed) { ofs << "the door is open\n";}

    return 0;
}