// qsort.cpp

#include "volsort.h"

#include <cstdlib>
#include <array>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int qComparisonInt(const void * a, const void * b) { // Changed out from Nodes to numbers, and reassigned the values
    const int * ia = (const int *) a;
    const int * ib = (const int *) b;

    return *ia - *ib; //  sorts in ascending order                                                                                         
}

int qComparisonStr(const void * a, const void * b) { // This function might need editting
    const Node * ia = *(const Node **) a;
    const Node * ib = *(const Node **) b;

    return strcmp(ia->string.c_str(),ib->string.c_str());
}

void qsort_sort(List &l, bool numeric) {
    if(numeric) { // If numbers are in the list
        int *intArray = new int[l.size];
        Node *current;
        current = l.head;
        for(size_t i = 0; i < l.size; i++) {
            intArray[i] = current->number;
            current = current->next;
        }
        qsort(intArray, l.size, sizeof(int), qComparisonInt); // Used Geeksforgeeks for syntax: https://www.geeksforgeeks.org/c-qsort-vs-c-sort/
        current = l.head;
        for(size_t i = 0; i < l.size; i++) { // Probably needs edits
            current->number = intArray[i];
            current = current->next;
        }
        delete[] intArray;
    }
    else { // Need to work on this
        Node *nodeArray = new Node [l.size];
        Node *current;
        current = l.head;
        for(size_t i = 0; i < l.size; i++) {
            nodeArray[i] = *current;
            current = current->next;
            cout << "nodeArray[i]: " << &nodeArray[i] << endl;
        }
        qsort(nodeArray, l.size, sizeof(Node *), qComparisonStr); // Used Geeksforgeeks for syntax: https://www.geeksforgeeks.org/c-qsort-vs-c-sort/
        current = l.head;
        for(size_t i = 0; i < l.size; i++) {
            current = &nodeArray[i];
            current = current->next;
        }
        delete[] nodeArray;
    }
}

