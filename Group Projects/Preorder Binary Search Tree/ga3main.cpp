#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;

struct node {
  node *left;
  int val;
  node *right;
  node(int v, node *l = nullptr, node *r = nullptr) {
    val = v;
    left = l;
    right = r;
  }
};
class tree {
private:
  node *root;

public:
  tree() { root = nullptr; }
  node *getRoot() { return root; }
  node *insert(node *cur, int val) {
    if (cur == nullptr) {
      return new node(val);
    }
    if (val == cur->val)
      return cur;
    if (val < cur->val)
      cur->left = insert(cur->left, val);
    else if (val > cur->val)
      cur->right = insert(cur->right, val);
    return cur;
  }

  string search(node *cur, int val) {
    string location;
    if (cur == nullptr || val == cur->val)
      return location;
    if (val < cur->val) {
      location += 'l';
      location += search(cur->left, val);
    }
    if (val > cur->val) {
      location += 'r';
      location += search(cur->right, val);
    }
    return location;
  }
  string preorder(node* cur){
    if(cur != nullptr){
      string result;
      result += to_string(cur->val) + " ";
      result += preorder(cur->left);
      result += preorder(cur->right);
      return result;
    }
    return "";
  }
};

int main(int argc, char *argv[]){
  // ifstream input("input1.txt");
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));
  tree bst;
  int num;
  string preorder, location;
  node* r = bst.getRoot();
  while(input >> num){
    r = bst.insert(r,num);
  }
  preorder = bst.preorder(r);
  stringstream ss(preorder);
  while(ss >> num){
    output << "[x" << bst.search(r,num) << "] " << num << endl;
  }
    
}