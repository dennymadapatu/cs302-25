// quick.cpp

#include "volsort.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Prototypes

Node *qsort(Node *head, bool numeric);
void  partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric);
Node *concatenate(Node *left, Node *right);

// Implementations

void quick_sort(List &l, bool numeric) { // Wrapper function, no recursion needed
    l.head = qsort(l.head, numeric);
}

Node *qsort(Node *head, bool numeric) {
    if(head->next == NULL) { // head->next being NULL means there is only one object left in the list
        return head;
    }
    Node *left = NULL;
    Node *right = NULL;
    Node *pivot = head;
    //cout << "pivot is " << pivot->number << endl;
    partition(head, pivot, left, right, numeric);
    if(left == NULL) {
        head = pivot;
    }
    else {
        left = qsort(left, numeric);
        head = concatenate(left, pivot);

    }
    if(right != NULL) {
        right = qsort(right, numeric);
        pivot->next = right;
        //head = concatenate(pivot, right);
    }
    else
    {pivot->next = NULL;}
   // else {
    //    head = left;
   // }
    
    // head = concatenate(left, right);
    
    return head;
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric) { // Want to use the original head as the pivot, and pivot as the comparing node
    Node *temp = head->next; // temp has all connections in this form
    Node *leftHead = NULL;
    Node *leftTail = NULL;
    Node *rightHead = NULL;
    Node *rightTail = NULL;
    while(temp != NULL) {
        //cout << "temp is " << temp->string << endl; 
        if(numeric) {
            if(node_number_compare(pivot, temp)) {
                if(leftTail == NULL) {
                    leftHead = temp;
                    leftTail = temp;
                }
                else {
                    leftTail->next = temp;
                    leftTail = leftTail->next;
                }
            }
            else {
                if(rightTail == NULL) {
                    rightHead = temp;
                    rightTail = temp;
                }
                else {
                    rightTail->next = temp;
                    rightTail = rightTail->next;
                }
            }
        }
        else {
            if(node_string_compare(pivot, temp)) {
                if(leftTail == NULL) {
                    leftHead = temp;
                    leftTail = temp;
                }
                else {
                    leftTail->next = temp;
                    leftTail = leftTail->next;
                }
            }
            else {
                if(rightTail == NULL) {
                    rightHead = temp;
                    rightTail = temp;
                }
                else {
                    rightTail->next = temp;
                    rightTail = rightTail->next;
                }
            }
        }
        temp = temp->next;
    }
    if(leftTail != NULL) {
        leftTail->next = NULL;
        //leftTail->next = pivot;
        //pivot->next = NULL;
    }
    // else {
    //     leftHead = pivot;
    //     leftTail = pivot;
    //     leftHead->next = NULL;
    // }
    if(rightTail != NULL) {
        rightTail->next = NULL;
    }
    left = leftHead;
    right = rightHead;
}

Node *concatenate(Node *left, Node *right) {
    Node *head = left;
    while(left->next != NULL) {
        left = left->next;
    }
    left->next = right;
    return head;
}

