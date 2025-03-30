// Name: Dennis Madapatu
// Date: 1/19/2025
// Challenge 01: Rotating Arrays; null solution
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    int arraySize;
    int numRotations;
    char LorR;
    while(cin >> arraySize >> numRotations >> LorR) { // While loop used to take in the first 3 variables
        int num;
        int offset = numRotations % arraySize; // Starting to input from the offset calculated here
        vector<int> finalVector(arraySize);
        if(LorR == 'L') {
            for(int i = arraySize - offset; i < arraySize; i++) { // Store starting from the left rotation offset
                cin >> num;
                finalVector[i] = num;
            }
            for(int i = 0; i < arraySize - offset; i++) { // Store the rest of the numbers
                cin >> num;
                finalVector[i] = num;
            }
        }
        else if(LorR =='R') {
            for(int i = offset; i < arraySize; i++) { // Store starting from the right rotation offset
                cin >> num;
                finalVector[i] = num;
            }
            for(int i = 0; i < offset; i++) { // Store the rest of the numbers
                cin >> num;
                finalVector[i] = num;
            }
        }
        for(int i = 0; i < arraySize; i++) { // Print out all of the numbers with correct formatting
            if(i == arraySize - 1) {
                cout << finalVector[i] << endl;
            }
            else {
                cout << finalVector[i] << " ";
            }
        }
    }
}