#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

struct node {
    node *left;
    int value;
    node *right;

    // node(int x) : value(x), right(nullptr), left(nullptr) {}
}*root;

class avl {
public:
    node *root;
    avl() { root = nullptr; }
    int getHeight(node*);
    int heightDiff(node*);
    node *ll(node*);
    node *rr(node*);
    node *lr(node*);
    node *rl(node*);
    node *balance(node*);
    node *insert(node*,int);
    void levelOrder(node*,ofstream&);
    node *remove(node*,int);
    node *findMin(node*);
};

int avl::getHeight(node *temp) {
    int height = 0;
    
    if(temp != nullptr) {
        int leftHeight = getHeight(temp->left);
        int rightHeight = getHeight(temp->right);
        int maxHeight = max(leftHeight, rightHeight);
        height = maxHeight + 1;
    }
    return height;
}

int avl::heightDiff(node *temp) {
    int leftHeight = getHeight(temp->left);
    int rightHeight = getHeight(temp->right);
    int balanceFactor = leftHeight - rightHeight;
    return balanceFactor;
}

node* avl::ll(node *parent) {
    node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

node* avl::rr(node *parent) {
    node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

node* avl::lr(node *parent) {
    node *temp;
    temp = parent->left;
    parent->left = rr(temp);
    return ll(parent);
}

node* avl::rl(node *parent) {
    node *temp;
    temp = parent->right;
    parent->right = ll(temp);
    return rr(parent);
}

node* avl::balance(node *temp) {
    int balanceFactor = heightDiff(temp);
    
    if(balanceFactor > 1) {
        if(heightDiff(temp->left) > 0) { temp = ll(temp); }
        else { temp = lr(temp); }
    }
    else if(balanceFactor < -1) {
        if(heightDiff(temp->right) > 0) { temp = rl(temp); }
        else { temp = rr(temp); }
    }
    return temp;
}

node* avl::insert(node *root, int x) {
    if(root == nullptr) {
        root = new node;
        root->value = x;
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }
    else if(x < root->value) {
        root->left = insert(root->left, x);
        root = balance(root);
    }
    else if(x > root->value) {
        root->right = insert(root->right, x);
        root = balance(root);
    }
    return root;
}

void avl::levelOrder(node *n, ofstream& output) {
    // if(n == nullptr) {
    //     output << "AVL tree is empty\n";
    //     return;
    // }

    queue<node*> q;
    q.push(n);
    while(!q.empty()) {
        int levelSize = q.size();
        for(int i = 0; i < levelSize; i++) {
            node *current = q.front();
            q.pop();
            output << current->value << " ";
            if(current->left != nullptr) { q.push(current->left);}
            if(current->right != nullptr) { q.push(current->right);}
        }
        output << endl;
    }
}

node* avl::remove(node* root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->value) {
        root->left = remove(root->left, key);
    } 
    else if (key > root->value) {
        root->right = remove(root->right, key);
    } 
    else {
        if (root->left == nullptr || root->right == nullptr) {
            node* temp = (root->left != nullptr) ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } 
            else {
                *root = *temp;
            }
            delete temp;
        } 
        else {
            node* temp = findMin(root->right);
            root->value = temp->value;
            root->right = remove(root->right, temp->value);
        }
    }

    if (root == nullptr) {
        return root;
    }

    root = balance(root);

    return root;
}

node* avl::findMin(node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}


int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream output(am.get("output"));
    // ifstream input("input1.txt");
    // ofstream output("output.txt");
    avl tree;
    string inputLine, temp;
    int num;

    while(getline(input, inputLine)) {
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\n'), inputLine.end());
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\r'), inputLine.end());

        if(inputLine.find("Insert") != string::npos) {
            num = stoi(inputLine.substr(inputLine.find('(')+1, inputLine.find(')')-inputLine.find('(')-1));
            root = tree.insert(root, num);
        }
        else if(inputLine.find("Remove") != string::npos) {
            num = stoi(inputLine.substr(inputLine.find('(')+1, inputLine.find(')')-inputLine.find('(')-1));
            root = tree.remove(root, num);
            // cout << "Remove " << num << endl;
        }
    }

    tree.levelOrder(root, output);

    return 0;
}