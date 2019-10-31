#include <iostream>
#include <fstream>
using namespace std;

void readEntry( int& entry, ifstream& in);

int main() {
    ifstream inFile;
    ofstream outFile;

    inFile.open("input.txt");
    outFile.open("output.txt");

    if (!inFile.is_open()) {
        cout << "Could not open file \n";
        return 1;
    }
        // read table dimensions and allocate 2D array
        int nRows, nCols;
        cout << "Enter the number of rows and columns: ";
        inFile >> nRows >> nCols;
        int **table = new int *[nRows];
        for (int i = 0; i < nRows; i++) {
            table[i] = new int[nCols];
        }

        // read table data
        cout << "Enter your numbers: ";
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                try {
                    readEntry((table[i][j]), inFile);
                }
                catch (int x) {
                    outFile << "Entry " << i << "," << j << " not an integer, was set to " << x << ", now setting it to 0"
                         << endl;
                    table[i][j] = 0;
                    inFile.clear();
                    string tmp;
                    inFile >> tmp;
                }
                inFile.clear();
            }
        }


        // write table data to the screen in transposed order
        outFile << nCols << " " << nRows << endl;
        for (int i = 0; i < nCols; i++) {
            for (int j = 0; j < nRows; j++) {
                outFile << table[j][i] << " ";
            }
            outFile << endl;
        }


        // free memory
        for (int i = 0; i < nRows; i++) {
            delete[] table[i];
        }
        delete[] table;

        inFile.close();
        outFile.close();


}

void readEntry( int& entry, ifstream& in) {
    in >> entry;
    if(in.fail()) {
        throw entry;
    }
}