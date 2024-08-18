#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <queue>
#include "ArgumentManager.h"
using namespace std;

void formatInput(string &inputLine) {
    inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\n'), inputLine.end());
    inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\r'), inputLine.end());
}

struct node {
    node *left;
    int value;
    node *right;

    node(int x) : value(x), left(nullptr), right(nullptr) {}
};

class BST {
private:
    node *root;
public:
    BST() { root = nullptr; }
    node* getRoot() { return root; }
    bool isempty(node*) { return root == nullptr; }
    void insert(int,node*);
    void levelOrder(node*);
    void inorder(node*,string&);
    void preorder(node*,string&);
    void postorder(node*,string&);
    node* remove(int,node*);
    node* minValueNode(node*);
};

void BST::insert(int x, node* current) {
    if(root == nullptr) {
        root = new node(x);
        return;
    }
    else if(x < current->value) {
        if(current->left != nullptr) {
            insert(x, current->left);
        }
        else {
            current->left = new node(x);
        }
    }
    else if(x > current->value) {
        if(current->right != nullptr) {
            insert(x, current->right);
        }
        else {
            current->right = new node(x);
        }
    }
    else {
        return;
    }
}

void BST::levelOrder(node *n) {
    if(n == nullptr) {
        cout << "BST is empty\n";
        return;
    }

    queue<node*> q;
    q.push(n);
    while(!q.empty()) {
        int levelSize = q.size();
        for(int i = 0; i < levelSize; i++) {
            node *current = q.front();
            q.pop();
            cout << current->value << " ";
            if(current->left != nullptr) { q.push(current->left);}
            if(current->right != nullptr) { q.push(current->right);}
        }
        cout << endl;
    }
}

void BST::inorder(node *n, string &result) {
    if(n == nullptr) {
        return;
    }

    inorder(n->left, result);
    result += to_string(n->value) + " ";
    inorder(n->right, result);
}

void BST::preorder(node *n, string &result) {
    if(n == nullptr) {
        return;
    }

    result += to_string(n->value) + " ";
    preorder(n->left, result);
    preorder(n->right, result);
}

void BST::postorder(node *n, string &result) {
    if(n == nullptr) {
        return;
    }

    postorder(n->left, result);
    postorder(n->right, result);
    result += to_string(n->value) + " ";
}

node* BST::remove(int x, node* n) {
    if (n == nullptr) {
        return nullptr; // No need to remove anything, return nullptr.
    }

    // Recursive call to find the node to be deleted
    if (x < n->value) {
        n->left = remove(x, n->left);
    } else if (x > n->value) {
        n->right = remove(x, n->right);
    } else {
        // Node found, proceed to delete

        // Case 1: Node with only one child or no child
        if (n->left == nullptr) {
            node* temp = n->right;
            delete n;

            // Update the root after removal
            if (n == root) {
                root = temp;
            }

            return temp;
        } else if (n->right == nullptr) {
            node* temp = n->left;
            delete n;

            // Update the root after removal
            if (n == root) {
                root = temp;
            }

            return temp;
        }

        // Case 3: Node with two children
        // Get the inorder successor (smallest in the right subtree)
        node* temp = minValueNode(n->right);

        // Copy the inorder successor's content to this node
        n->value = temp->value;

        // Delete the inorder successor
        n->right = remove(temp->value, n->right);
    }

    return n;
}



node* BST::minValueNode(node* n) {
    node* current = n;

    while (current->left != nullptr) {
        current = current->left;
    }

    return current;
}

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream output(am.get("output"));
    // ifstream input("input2.txt");
    // ofstream output("output.txt");
    
    string inputLine;
    string preorder = "";
    string postorder = "";
    string inorder = "";
    int inputValue, successor, predecessor, replacement;
    BST tree;

    while(getline(input,inputLine)) {
        formatInput(inputLine);
        if(inputLine == "Insert") {
            getline(input,inputLine);
            formatInput(inputLine);
            stringstream ss(inputLine);
            while(ss >> inputValue) {
                // cout << "Insert: " << inputValue << endl;
                tree.insert(inputValue, tree.getRoot());
            }
        }
        else if(inputLine == "Remove") {
            getline(input,inputLine);
            formatInput(inputLine);
            stringstream ss(inputLine);
            while(ss >> inputValue) {
                tree.remove(inputValue, tree.getRoot());
                // cout << tree.getRoot()->value << endl;
            }
        }
        else if(inputLine == "Traverse") {
            getline(input,inputLine);
            formatInput(inputLine);

            tree.inorder(tree.getRoot(), inorder);
            tree.preorder(tree.getRoot(), preorder);
            tree.postorder(tree.getRoot(), postorder);

            inorder.pop_back();
            preorder.pop_back();
            postorder.pop_back();

            // cout << preorder.length() << endl;
            // cout << inputLine.length() << endl;

            if(inorder == inputLine) { output << "Inorder" << endl; }
            if(preorder == inputLine) { output << "Preorder" << endl; }
            if(postorder == inputLine) { output << "Postorder" << endl; }
            
            if(inorder != inputLine && preorder != inputLine && postorder != inputLine) { output << "False" << endl; }

            inorder = "";
            preorder = "";
            postorder = "";
        }
    }

    return 0;
}