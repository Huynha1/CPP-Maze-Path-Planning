#include <iostream>
#include <fstream>
#include <string>

void writeOut(char chararray[20][20]) {

    std::ofstream outFile;

    outFile.open("sample01-2.expout");
    
    for (int i = 0; i < 20 ; ++i) {
        for (int j = 0; j < 20 ; ++j) {
            outFile << chararray[i][j];
        }
        outFile << "\n";
    }

    outFile.close();
}

int main() {

    std::ifstream inFile;
    inFile.open("sample01.env");

    char chararray[20][20];
 
    for (int i = 0; i < 20 ; ++i) {
        for (int j = 0; j < 20 ; ++j) {
            inFile >> chararray[i][j];
        }
    }

    inFile.close();

    writeOut(chararray);

    return 0;
}