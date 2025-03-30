// Name: Dennis Madapatu
// Date: 3/11/2025
// Description: Taking in DNA sequences, we find all of the repeated sequences found in that specific sequence
// Challenge 06: Repeated DNA sequences

#include <iostream>
#include <set>
#include <unordered_map>

using namespace std;

int main(int argc, char *argv[]) {
    string DNA;
    int strandLen = 9; // Default length of a DNA sequence???
    while(cin >> DNA) {
        if((int) DNA.length() < strandLen) { // An example in the input where the sequence is less than 9 chars (which ain't a DNA sequence!)
            cout << -1 << endl;
            continue;
        }
        unordered_map<string, int> DNAStrands;
        set<string> DNAKeys;
        for(size_t i = 0; i < DNA.length() - 8; i++) { // Keep every single 9 char sequence found
            string DNAsubstr = DNA.substr(i, strandLen);
            DNAKeys.insert(DNAsubstr);
            DNAStrands[DNAsubstr]++;
        }
        for(auto key : DNAKeys) { // Go through all 9 char sequences and print out the repeated sequences
            if(DNAStrands[key] > 1) {
                cout << key << endl;
            }
        }
        cout << -1 << endl; // Finished printing out all sequences, print -1 to signify the next DNA strand
    }
    return 0;
}


