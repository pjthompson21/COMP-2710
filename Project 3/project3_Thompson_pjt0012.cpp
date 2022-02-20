/** 
 * Parker Thompson
 * project3_Thompson_pjt0012.cpp
 * compilation instructions: g++ project3_Thompson_pjt0012.cpp
 *                           ./a.out
 * Program that merges numbers found within 2 seperate files
 * and combines them into a new 3rd file.
 * 
 * REFERENCES:
 * Utilized the hints provided by Dr. Li to help me complete this
 * project. 
 **/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std; 


//********************************************
//**************DECLARATIONS******************
//********************************************

//function declarations 
bool check_file(string);
vector<int> read_file(string);
void write_file(string, vector<int>);
vector<int> merge(vector<int>, vector<int>);
void to_string(string, vector<int>);



//********************************************
//******************MAIN**********************
//********************************************

int main() {
    string inputFile1;
    string inputFile2;
    string outputFile;
    vector<int> inputList1;
    vector<int> inputList2;
    vector<int> inputList3;

    do {
        cout << "*** Welcome to Thompson's sorting program ***" << endl;
        cout << "Enter the first input file name: ";
        cin >> inputFile1;

    } while (cin.fail() || !check_file(inputFile1));

    inputList1 = read_file(inputFile1);
    cout << "The list of " << inputList1.size()
         << " numbers in file " << inputFile1 << " is:" << endl;
    to_string(inputFile1, inputList1);
    


    do {
        cout << "Enter the second input file name: ";
        cin >> inputFile2;

    } while (cin.fail() || !check_file(inputFile2));

    inputList2 = read_file(inputFile2);
    cout << "The list of " << inputList2.size()
         << " numbers in file " << inputFile2 << " is:" << endl;
    to_string(inputFile2, inputList2);



    inputList3 = merge(inputList1, inputList2);
    cout << "The sorted list of " << inputList3.size()
         << " numbers is: ";

    for (int i = 0; i < inputList3.size(); i++) {
        cout << inputList3[i] << " ";
    }
    cout << endl;



    do {
        cout << "Enter the output file name: ";
        cin >> outputFile;

    } while (cin.fail());
        
    write_file(outputFile, inputList3);
    cout << "*** Please check the new file - "
         << outputFile << " ***" << endl; 
    cout << "*** Goodbye. ***";
}



//********************************************
//*************IMPLEMENTATIONS****************
//********************************************

bool check_file(string file) {
    ifstream stream;

    stream.open(file.c_str());
    if (stream.fail()) {
        cout << "Error: Unable to open file" << endl;
        return false; 
    }
    stream.close();
    return true;
}


vector<int> read_file(string file) {
    ifstream inStream; 
    vector<int> vecList;
    string line;    //individual line in file
    int i;          //variable to convert str to int 

    inStream.open(file.c_str());
    if (inStream.fail()) {
        cout << "Error: Unable to read file" << endl;
    }
    else {
        while (inStream >> line) {
            istringstream(line) >> i;   //converts str to int format
            vecList.push_back(i);
        }
    }
    inStream.close();
    return vecList;
}


void write_file(string file, vector<int> vecList) {
    ofstream outStream;
    
    outStream.open(file.c_str());
    if (outStream.fail()) {
        cout << "Error: Unable to write file" << endl;
    }
    else {
        for (int i = 0; i < vecList.size(); i++) {   //converts int back into str
            outStream << vecList[i] << endl;
        }
    }
    outStream.close();
}


vector<int> merge(vector<int> vecList1, vector<int> vecList2) {
    vector<int> vecList3;

    unsigned short i;
    unsigned short s;

    //Compare both vectors
    while (vecList1.size() > 0 && vecList2.size() > 0) {
        if (vecList1.at(0) < vecList2.at(0)) {
            vecList3.push_back(vecList1.at(0));
            vecList1.erase(vecList1.begin());
        }
        else {
            vecList3.push_back(vecList2.at(0));
            vecList2.erase(vecList2.begin());
        }
    }

    //Add any remaining values from vecList1
    if (vecList1.size() > 0) {
        s = vecList1.size();
        for (i = 0; i < s; i++) {
            vecList3.push_back(vecList1.at(0));
            vecList1.erase(vecList1.begin());
        }
    }

    //Add any remaining values from vecList2
    if (vecList2.size() > 0) {
        s = vecList2.size();
        for (i = 0; i < s; i++) {
            vecList3.push_back(vecList2.at(0));
            vecList2.erase(vecList2.begin());
        }
    }
    return vecList3;
}


void to_string(string file, vector<int> vecList) {
    ofstream stream;

    stream.open(file.c_str());
    if (stream.fail()) {
        cout << "Error: Unable to open file" << endl;
    }
    else {
        for (int i = 0; i < vecList.size(); i++) {
            cout << vecList[i] << endl;
        }
    }
    cout << endl;
}