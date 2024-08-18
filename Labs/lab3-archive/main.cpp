#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <bits/stdc++.h>
#include <cmath>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

struct node {
    double value;
    string operation;
    node *next;
    node(double x) {
        this->value = x;
        this->operation = '\0';
        next = nullptr;
    }
    node(string o) {
        this->value = -1;
        this->operation = o;
        next = nullptr;
    }
};

class expression {
private:
    node *head;
public:
    expression() { head = nullptr;}
    node *getHead() { return head;}
    bool isEmpty() { return head;}
    void push(node*);
    node *pop();
    void print(node*);
    void printOperation(node*);
};

void expression::push(node *n) {
    if(head == nullptr) { 
        head = n;    
        return;
    }

    n->next = head;
    head = n;
}

node *expression::pop() {
    if(head == nullptr) { return head;}
    node *temp = head;
    head = head->next;
    return temp;
}

void expression::print(node* current) {
    if(current == nullptr) { return;}
    if(current->value == -1) {
        cout << current->operation << " ";
    }
    else{
        cout << current->value << " ";
    }
    print(current->next);
}

double operation(char symbol, double x, double y) {
    if(symbol == '+') {
        return (x+y);
    }
    else if(symbol == '-') {
        return (x-y);
    }
    else if(symbol == '*') {
        return (x*y);
    }
    else if(symbol == '/') {
        return (x/y);
    }
    else if(symbol == '^') {
        return (pow(x,y));
    }
    else {
        return -1;
    }
}

double operation(string symbol, double x, double y) {
    if(symbol == "+") {
        return (x+y);
    }
    else if(symbol == "-") {
        return (x-y);
    }
    else if(symbol == "*") {
        return (x*y);
    }
    else if(symbol == "/") {
        return (x/y);
    }
    else if(symbol == "^") {
        return (pow(x,y));
    }
    else {
        return -1;
    }
}

int precedence(char c) {
    switch (c) {
    case '+': case '-':
        return 1;
    case '*': case '/':
        return 2;
    case '^':
        return 3;
    default:
        return -1;
    }
}

int main(int argc, char *argv[]) {

    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
    ifstream ifs(input);
    ofstream ofs(output);

    // ifstream ifs("input3.txt");
    // ofstream ofs("output.txt");
    expression stack, tempStack;
    double x,y; 
    string typeOfExp, exp, op;
    
    if(!ifs.is_open()) { cout << "Could not open file.\n";}    
    
    ifs >> typeOfExp;
    
    if(typeOfExp == "postfix") { //if postfix expression
        while(ifs >> exp) {
            if(all_of(exp.begin(), exp.end(), ::isdigit)) {
                node *temp = new node(stod(exp));
                stack.push(temp);
            }
            else {
                y = stack.pop()->value;
                x = stack.pop()->value;
                node *temp = new node(operation(exp[0],x,y));
                stack.push(temp);
            }
        }
        ofs << fixed << setprecision(2) << stack.getHead()->value << endl;
    }
    else if (typeOfExp == "prefix") {
        while(ifs >> exp) {
            if(all_of(exp.begin(), exp.end(), ::isdigit)) {
                node *temp = new node(stod(exp));
                stack.push(temp);
            }
            else {
                node *temp = new node(exp);
                stack.push(temp);
            }
        }
        
        while(stack.isEmpty()) {
            if(stack.getHead()->value != -1) {
                x = stack.pop()->value;
                node *temp = new node(x);
                tempStack.push(temp);
            }
            else {
                op = stack.pop()->operation;
                x = tempStack.pop()->value;
                y = tempStack.pop()->value;
                node *temp = new node(operation(op,x,y));
                tempStack.push(temp);
            }
        }
        ofs << fixed << setprecision(2) << tempStack.getHead()->value << endl;;
    }
    else if(typeOfExp == "infix") { 
        while(ifs >> exp) {
            if(all_of(exp.begin(),exp.end(),::isdigit)) {
                node *temp = new node(stod(exp));
                stack.push(temp);
            }
            else if(exp == "(") {
                node *temp = new node(exp);
                tempStack.push(temp);
            }
            else if(exp == ")") {
                while(tempStack.getHead()->operation !="(") {
                    node *temp = new node(tempStack.pop()->operation);
                    stack.push(temp);
                }
                tempStack.pop();
            }
            else {
                node *temp = new node(exp);
                tempStack.push(temp);
            }
        }
        while(tempStack.getHead() != nullptr) {
            node *temp = new node(tempStack.pop()->operation);
            stack.push(temp);
        }
        while(stack.isEmpty()) {
            if(stack.getHead()->value != -1) {
                node *temp = new node(stack.pop()->value);
                tempStack.push(temp);
            }
            else {
                node *temp = new node(stack.pop()->operation);
                tempStack.push(temp);
            }
        }
        while(tempStack.isEmpty()) {
            if(tempStack.getHead()->value != -1) {
                x = tempStack.pop()->value;
                node *temp = new node(x);
                stack.push(temp);
            }
            else {
                op = tempStack.pop()->operation;
                y = stack.pop()->value;
                x = stack.pop()->value;
                node *temp = new node(operation(op,x,y));
                stack.push(temp);
            }
        }
        ofs << fixed << setprecision(2) << stack.getHead()->value << endl;
    }
    ifs.close();
    ofs.close();
    return 0;
}