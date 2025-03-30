// Challenge 03: Palindrome Permutation
#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>

using namespace std;

bool is_palindrome(string phrase) { // Self explanatory name
  unordered_map<char, int> letters;
  for(size_t i = 0; i < phrase.length(); i++) {
    char letter = tolower(phrase[i]); // tolower because capital letters don't matter either
    if(letter < 97 || letter > 122) { // Don't care about characters that are not letters
      continue;
    }
    else { 
      letters[letter]++;
    }
  }
  int oddCounter = 0;
  // If there is more than one character that has an odd value, then that means it is not a palindrome permutation
  for(size_t i = 0; i < phrase.length(); i++) {
    char letter = tolower(phrase[i]);
    if(letters[letter] % 2 != 0) {   // letters[letter] % 2 != 0
      oddCounter++;
    }
    if(oddCounter > 1) {
      return false;
    }
  }
  return true;
}
int main(int argc, char *argv[]) {
  string phrase;
  while(getline(cin, phrase)) {
    if(is_palindrome(phrase)) {
      cout << '"' << phrase << '"' << " is a palindrome permutation" << endl;
    }
    else {
      cout << '"' << phrase << '"' << " is not a palindrome permutation" << endl;
    }
  }
  return (0);
}

