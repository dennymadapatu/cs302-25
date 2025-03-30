// stl.cpp

#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void stl_sort(List &l, bool numeric) {
    if(numeric) { // If numbers are in the list
        vector<int> intList;
        Node *current;
        current = l.head;
        for(size_t i = 0; i < l.size; i++) {
            intList.push_back(current->number);
            current = current->next;
        }
        sort(intList.begin(), intList.end());
        current = l.head;
        for(size_t i = 0; i < l.size; i++) { // Probably needs edits
            current->number = intList[i];
            current = current->next;
        }
    }
    else { // If numbers aren't in the list
        vector<string> strList;
        Node *current;
        current = l.head;
        for(size_t i = 0; i < l.size; i++) {
            strList.push_back(current->string);
            current = current->next;
        }
        sort(strList.begin(), strList.end());
        current = l.head;
        for(size_t i = 0; i < l.size; i++) { // Editting the data in each node and moving to the next
            current->string = strList[i];
            current = current->next;
        }
    }
}

