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
        int offset = numRotations % arraySize; // Starting to input from the offset calculated here
        vector<int> initialVector(arraySize); // Initializing a vector with a specified size
        vector<int> finalVector;
        for(int i = 0; i < arraySize; i++) { // Taking the numbers and putting then into the initial vector
            int num;
            cin >> num;
            initialVector[i] = num;
        }
        if(LorR == 'L') { // Left Rotation
            for(int i = offset; i < arraySize; i++) { // Start from the offset and go to the end of the vector
                finalVector.push_back(initialVector[i]);
            }
            for(int i = 0; i < offset; i++) { // Start fron the beginning and go to the offset to add everything from the vector
                finalVector.push_back(initialVector[i]);
            }
            for(int i = 0; i < arraySize; i++) { // This for loop is only for formatting purposes
                if(i == arraySize - 1) { 
                    cout << finalVector[i] << endl;
                }
                else {
                    cout << finalVector[i] << " ";
                }
            }
        }
        if(LorR == 'R') { // Right Rotation
            for(int i = arraySize - offset; i < arraySize; i++) {
                finalVector.push_back(initialVector[i]);
            }
            for(int i = 0; i < arraySize - offset; i++) {
                finalVector.push_back(initialVector[i]);
            }
            for(int i = 0; i < arraySize; i++) {
                if(i == arraySize - 1) {
                    cout << finalVector[i] << endl;
                }
                else {
                    cout << finalVector[i] << " ";
                }
            }
        }
    }

}

