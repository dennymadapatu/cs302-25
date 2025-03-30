// Challenge 02: Closest Numbers
// Name:  Dennis Madapatu
// Date: 1/25/2025

// Brief description: Taking all of the numbers

// This code solves yyyy based on the following idea/implementation...

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Main Execution

int main(int argc, char *argv[])
{
    int size;
    while (cin >> size) {
        vector<int> numbers(size);
        int number;
        for (int i = 0; i < size; i++) {
            cin >> number;
            numbers[i] = number;
        }
        sort(numbers.begin(), numbers.end());
        int bestDifference;
        vector<pair<int, int>> pairVector;
        for (int i = 1; i < size; i++) {
            int absDifference = abs(numbers[i - 1] - numbers[i]); // Calc (short for calculate) the absolute difference (I was coerced to put the calc thingy)
            if(i == 1) { // just to make sure a best difference is set
                bestDifference = absDifference;
                pair<int, int> newPair;
                newPair.first = numbers[i - 1];
                newPair.second = numbers[i];
                pairVector.push_back(newPair);
            }
            else if (absDifference < bestDifference) {  // If a better difference has been found, we need to get rid of all of the previous pairs, and set the best difference
                bestDifference = absDifference;
                pairVector.clear(); // Clear previous pairs
                pair<int, int> newPair; // Make new pair
                newPair.first = numbers[i - 1];
                newPair.second = numbers[i];
                pairVector.push_back(newPair); // Add new pair to the pairVector
            }
            else if (absDifference == bestDifference) { // if there are duplicates of the difference, make another pair and add it to the pairVector
                pair<int, int> newPair;
                newPair.first = numbers[i - 1];
                newPair.second = numbers[i];
                pairVector.push_back(newPair);
            }
        }

        for (size_t i = 0; i < pairVector.size(); i++) {
            if(i == 0) {
                cout << pairVector[i].first << " " << pairVector[i].second;
            }
            else { // This is just for formatting
                cout << " " << pairVector[i].first << " " << pairVector[i].second;
            }
        }
        cout << endl; // Starts the while loop again with a new line
    }
    return EXIT_SUCCESS;
}
