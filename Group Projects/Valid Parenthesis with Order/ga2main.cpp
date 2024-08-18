#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include "ArgumentManager.h"
using namespace std;

bool validParenthesis(string s) {
  stack<char> st;
  int prev, value;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '{' || s[i] == '[' || s[i] == '(') {
      if (i == 0) {
        if (s[i] == '{')
          prev = 1;
        else if (s[i] == '[')
          prev = 2;
        else //(s[i] == '(')
          prev = 3;
        st.push(s[i]);
        continue;
      } else {
        if (s[i] == '{')
          value = 1;
        else if (s[i] == '[')
          value = 2;
        else //(s[i] == '(')
          value = 3;
      }
      if (prev > value) {
        return false;
      } else {
        st.push(s[i]);
        prev = value;
        
      }
    } else if (s[i] == '}' || s[i] == ']' || s[i] == ')') {
      if (st.empty()) {
        return false;
      } else {
        switch (s[i]) {
        case ')':
          if (st.top() == '(') {
            st.pop();
          } else {
            return false;
          }
          break;
        case ']':
          if (st.top() == '[') {
            st.pop();
          } else {
            return false;
          }
          break;
        case '}':
          if (st.top() == '{') {
            st.pop();
          } else {
            return false;
          }
          break;
        }
        prev = 0;
      }
    }
  }
  return (st.empty());
}
int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));
  queue<string> validQueue;
  queue<string> invalidQueue;
  // ifstream input("input4.txt");
  // ofstream output("output.txt");
  string inputLine;
  while (getline(input, inputLine)) {
      inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\n'), inputLine.end());
      inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\r'), inputLine.end());

    if (inputLine.empty()) {
      continue;
    }
    if (validParenthesis(inputLine)) {
      validQueue.push(inputLine);
    } else {
      invalidQueue.push(inputLine);
    }
  }
  if (!invalidQueue.empty()) {
    output << "Invalid" << endl;
    while (invalidQueue.size() != 0) {
      output << invalidQueue.front() << endl;
      invalidQueue.pop();
    }
  }
  if (!validQueue.empty()) {
    output << "Valid" << endl;
    while (validQueue.size() != 0) {
      output << validQueue.front() << endl;
      validQueue.pop();
    }
  }
}
