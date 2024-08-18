#include <iostream>
#include <string>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

struct credentials {
    string name;
    int age, deposit, drinks;
    credentials *next;

    credentials() {
        name = "";
        age = -1;
        deposit = -1;
        drinks = -1;
        next = nullptr;
    }
    
    credentials(string name, int age, int deposit, int drinks) {
        this->name = name;
        this->age = age;
        this->deposit = deposit;
        this->drinks = drinks;
        next = nullptr;
    }
};

class guests {
private:
    credentials *head;
    credentials *tail;
public:
    guests() { 
        head = nullptr;
        tail = nullptr;
    }
    credentials *getHead() { return head;}
    credentials *getTail() { return tail;}
    int getSize(credentials*);
    void insertAtHead(credentials*);
    void insertAtPos(int, credentials*);
    void insertAtTail(credentials*);
    void sort(int);
    void removeHead();
    void removeTail();
    void removeName(guests&, string);
    void remove(guests&, int, int);
    void print(credentials*, ofstream&);
};

int guests::getSize(credentials* current) {
    if(current == nullptr) {
        return 0;
    }
    return getSize(current->next)+1;
}

void guests::insertAtHead(credentials* guest) {
    if(head == nullptr) {
        head = guest;
        return;
    }
    guest->next = head;
    head = guest;
}

void guests::insertAtPos(int pos, credentials* guest) {
    credentials *current = head;
    credentials *previous = nullptr;
    for(int i = 0; i < pos; i++) {
        previous = current;
        current = current->next;
    }

    previous->next = guest;
    guest->next = current;

}

void guests::insertAtTail(credentials* guest) {
    credentials *current = head;
    if(current == nullptr) {
        head = guest;
        tail = guest;
        return;
    }
    while(current->next != nullptr) {
        current = current->next;
    }

    current->next = guest;
    tail = guest;
}

void guests::sort(int attribute) {
    // for attribute: 1-name, 2-age, 3-deposit, 4-numDrinks
    if(head == nullptr || head->next == nullptr) {
        return;
    }
    bool isSorted = false;
    credentials *current = nullptr;
    while(!isSorted) {
        isSorted = true;
        current = head;
        switch(attribute) {
        case 1:
            while(current->next != nullptr) {
                if(current->name > current->next->name) {
                    int tempDrinks = current->drinks;
                    int tempDeposit = current->deposit;
                    int tempAge = current->age;
                    string tempName = current->name;

                    current->drinks = current->next->drinks;
                    current->next->drinks = tempDrinks;
                    current->deposit = current->next->deposit;
                    current->next->deposit = tempDeposit;
                    current->age = current->next->age;
                    current->next->age = tempAge;  
                    current->name = current->next->name;
                    current->next->name = tempName;
                    
                    isSorted = false;
                }
                current = current->next;
            }
            break;
        case 2:
            while(current->next != nullptr) {
                if(current->age > current->next->age) {
                    int tempDrinks = current->drinks;
                    int tempDeposit = current->deposit;
                    int tempAge = current->age;
                    string tempName = current->name;

                    current->drinks = current->next->drinks;
                    current->next->drinks = tempDrinks;
                    current->deposit = current->next->deposit;
                    current->next->deposit = tempDeposit;
                    current->age = current->next->age;
                    current->next->age = tempAge;  
                    current->name = current->next->name;
                    current->next->name = tempName;
                    
                    isSorted = false;
                }
                current = current->next;
            }
            break;
        case 3:
            while(current->next != nullptr) {
                if(current->deposit > current->next->deposit) {
                    int tempDrinks = current->drinks;
                    int tempDeposit = current->deposit;
                    int tempAge = current->age;
                    string tempName = current->name;

                    current->drinks = current->next->drinks;
                    current->next->drinks = tempDrinks;
                    current->deposit = current->next->deposit;
                    current->next->deposit = tempDeposit;
                    current->age = current->next->age;
                    current->next->age = tempAge;  
                    current->name = current->next->name;
                    current->next->name = tempName;
                    
                    isSorted = false;
                }
                current = current->next;
            }
            break;
        case 4:
            while(current->next != nullptr) {
                if(current->drinks > current->next->drinks) {
                    int tempDrinks = current->drinks;
                    int tempDeposit = current->deposit;
                    int tempAge = current->age;
                    string tempName = current->name;

                    current->drinks = current->next->drinks;
                    current->next->drinks = tempDrinks;
                    current->deposit = current->next->deposit;
                    current->next->deposit = tempDeposit;
                    current->age = current->next->age;
                    current->next->age = tempAge;  
                    current->name = current->next->name;
                    current->next->name = tempName;
                    
                    isSorted = false;
                }
                current = current->next;
            }
            break;
        }
    }
}

void guests::removeHead() {
    credentials *current = head;
    if(current == nullptr) {
        return;
    }
    head = current->next;
    delete current;
}

void guests::removeTail() {
    credentials *current = head;
    credentials *previous = nullptr;
    if(current == nullptr) {
        return;
    }
    
    while(current->next != nullptr) {
        previous = current;
        current = current->next;
    }
    
    previous->next = nullptr;
    delete current;
}

void guests::removeName(guests &casino, string removeName) {
    credentials *current = head;
    credentials *previous = nullptr;
    if(current == nullptr) {
        return;
    }

    while(current->next != nullptr) {
        if(current->name == removeName) {
            // if it's the head
            if(current == head) {
                casino.removeHead();
            }
            else {
                credentials *temp = current;
                previous->next = current->next;
                delete temp;
            }
        }
        previous = current;
        current = current->next;
    }

    if(current->name == removeName) { // if it's the tail
        casino.removeTail();
    }
}

void guests::remove(guests &casino, int attribute, int value) {
    credentials *current = head;
    credentials *previous = nullptr;
    if(current == nullptr) {
        return;
    }
    
    switch(attribute) {
    case 2:
        while(current->next != nullptr) {
            if(current->age == value) {
                // if it's the head
                if(current == head) {
                    casino.removeHead();
                }
                else {
                    credentials *temp = current;
                    previous->next = current->next;
                    delete temp;
                }
            }
            previous = current;
            current = current->next;
        }
        if(current->age == value) { // if it's the tail
            casino.removeTail();
        }
        break;
    case 3:
        while(current->next != nullptr) {
            if(current->deposit == value) {
                // if it's the head
                if(current == head) {
                    casino.removeHead();
                }
                else {
                    credentials *temp = current;
                    previous->next = current->next;
                    delete temp;
                }
            }
            previous = current;
            current = current->next;
        }
        if(current->deposit == value) { // if it's the tail
            casino.removeTail();
        }
        break;
    case 4:
        while(current->next != nullptr) {
            if(current->drinks == value) {
                // if it's the head
                if(current == head) {
                    casino.removeHead();
                }
                else {
                    credentials *temp = current;
                    previous->next = current->next;
                    delete temp;
                }
            }
            previous = current;
            current = current->next;
        }
        if(current->drinks == value) { // if it's the tail
            casino.removeTail();
        }
        break;
    }

}

void guests::print(credentials* current, ofstream &ofs) {
    if(current == nullptr) {
        return;
    }

    ofs << "[name: " << current->name << "; age: " << current->age;
    ofs << "; deposit: " << current->deposit << "; number of drinks: " << current->drinks << "]\n";

    print(current->next, ofs);
}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string command = am.get("command");
    string output = am.get("output");
    ifstream ifs(input);
    ifstream cfs(command);
    ofstream ofs(output);
    
    // string input = "input1.txt";
    // string command = "command1.txt";    
    // string output = "output1.txt";
    // ifstream ifs(input);
    // ifstream cfs(command);
    // ofstream ofs(output);

    // variables
    string inputLine;
    string name;
    guests casino;
    int age, numDrinks, deposit;

    int i = 0;
    while(getline(ifs,inputLine)) {
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\n'), inputLine.end());
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\r'), inputLine.end());

        name = inputLine.substr(7, inputLine.find(';')-7);
        // cout << name << endl;
        
        inputLine = inputLine.substr(inputLine.find(';')+2);
        // cout << "now input line is " << inputLine << endl;
        age = stoi(inputLine.substr(5, inputLine.find(';')-5));
        // cout << age << endl;

        inputLine = inputLine.substr(inputLine.find(';')+2);
        deposit = stoi(inputLine.substr(9, inputLine.find(';')-9));
        // cout << deposit << endl;

        inputLine = inputLine.substr(inputLine.find(';')+2);
        numDrinks = stoi(inputLine.substr(18, inputLine.find(']')-18));
        //cout << numDrinks << endl;
        
        credentials *temp = new credentials(name, age, deposit, numDrinks);

        if(i == 0) {
            casino.insertAtHead(temp);
        }
        else {
            casino.insertAtTail(temp);
        }
        i++;
    }

    ifs.close();

    while(getline(cfs,inputLine)) {
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\n'), inputLine.end());
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\r'), inputLine.end());

        if(inputLine.find("Add") == 0) { // add function
            int index = stoi(inputLine.substr(inputLine.find('(')+1,inputLine.find(')')));
            name = inputLine.substr(inputLine.find(':')+2,inputLine.find(';')-15);
            inputLine = inputLine.substr(inputLine.find(';')+2);
            age = stoi(inputLine.substr(5, inputLine.find(';')-5));
            inputLine = inputLine.substr(inputLine.find(';')+2);
            deposit = stoi(inputLine.substr(9, inputLine.find(';')-9));
            inputLine = inputLine.substr(inputLine.find(';')+2);
            numDrinks = stoi(inputLine.substr(18, inputLine.find(']')-18));
            credentials *temp = new credentials(name, age, deposit, numDrinks);
            //cout << temp->name << temp->age << temp->deposit << temp->drinks << endl;
            if(index >= casino.getSize(casino.getHead())) {
                casino.insertAtTail(temp);
            }
            else if(index == 0) {
                casino.insertAtHead(temp);
            }
            else {
                casino.insertAtPos(index, temp);
            }
        }


        if(inputLine.find("Remove") == 0) { // remove function
            if(inputLine.find("name") == 8) {
                inputLine.erase(remove(inputLine.begin(), inputLine.end(), ')'), inputLine.end());
                string removeName = inputLine.substr(inputLine.find(':')+2);
                casino.removeName(casino, removeName);
            }
            else if(inputLine.find("age") == 8) {
                inputLine.erase(remove(inputLine.begin(), inputLine.end(), ')'), inputLine.end());
                int removeAge = stoi(inputLine.substr(inputLine.find(':')+2));
                casino.remove(casino, 2, removeAge);
            }
            else if(inputLine.find("deposit") == 8) {
                inputLine.erase(remove(inputLine.begin(), inputLine.end(), ')'), inputLine.end());
                int removeDeposit = stoi(inputLine.substr(inputLine.find(':')+2));
                casino.remove(casino, 3, removeDeposit);
            }
            else if(inputLine.find("number of drinks") == 8) {
                inputLine.erase(remove(inputLine.begin(), inputLine.end(), ')'), inputLine.end());
                int removeDrink = stoi(inputLine.substr(inputLine.find(':')+2));
                casino.remove(casino, 4, removeDrink);
            }
        }

        if(inputLine.find("Sort") == 0) { // sort function
            if(inputLine.find("name") == 6) {
                casino.sort(1);
            }
            else if(inputLine.find("age") == 6) {
                casino.sort(2);
            }
            else if(inputLine.find("deposit") == 6) {
                casino.sort(3);
            }
            else if(inputLine.find("number of drinks") == 6) {
                casino.sort(4);
            }
        }
    }
    
    cfs.close();
    casino.print(casino.getHead(),ofs);
    ofs.close();

    return 0;
}