#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"

using namespace std;

int getRow(char rank) {     // returns row index of respective rank 
    if(rank >= '2' && rank <= '9') {
        return ((rank -'0') - 1);
    }
    else if(rank == 'K') {
        return 12;
    }
    else if(rank == 'Q') {
        return 11;
    }
    else if(rank == 'J') {
        return 10;
    }
    else if(rank == '1') {
        return 0;
    }

    return -1; // invalid rank
}

int getCol(char suit) {     // returns column index of respective suit
    if(suit == 'S') {
        return 0;
    }
    else if(suit == 'H') {
        return 1;
    }
    else if(suit == 'C') {
        return 2;
    }
    else if(suit == 'D') {
        return 3;
    }
    
    return -1; // invalid suit
}



int main(int argc, char *argv[]) {

    ArgumentManager am(argc, argv);

    //string fileName = "";
   
    string input = am.get("input");
    string output = am.get("output");
    string inputLine = "";
    int array[13][4] = {0};
    int row, col;

    //cout << "Please enter input file name: " << endl;
    //cin >> fileName;

    ifstream ifs(input);

    if(!ifs.is_open()) {
        cout << "Could not open desired input file." << input << endl;
        return -1;
    }

    getline(ifs, inputLine);
    ifs.close();

    for(int i = 0; i < inputLine.length(); i++) {
        if(inputLine[i] == ',' || inputLine[i] == ' ') {
            inputLine[i] = '\0';
        }
    }

    for(int i = 0; i < inputLine.length(); i++) {

        if(inputLine[i] == '0' && inputLine[i-1] == '1') {
            continue;
        }

        if(inputLine[i] == '1' && inputLine[i+1] == '0') {
            row = 9;
            col = getCol(inputLine[i+2]);
            array[row][col] = 1; 
            continue;
        }

        row = getRow(inputLine[i]);
        col = getCol(inputLine[i+1]);

        if(row == -1 || col == -1) {
            continue;
        }
        
        array[row][col] = 1;

    }

    ofstream ofs(output);
    
    if (!ofs.is_open()) {
        cout << "Failed to open output file." << endl;
        return -1;
    }    

    for(int i = 0; i < 13; i++) {
        for(int j = 0; j < 4; j++) {
            ofs << array[i][j];
        }
        
        ofs << endl;
    }

    ofs.close();

    return 0;
}
