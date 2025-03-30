// merge.cpp

#include "volsort.h"

#include <iostream>
#include <string.h>

// Prototypes

Node *msort(Node *head, bool numeric);
void  split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);

// Implementations

void merge_sort(List &l, bool numeric) {
    Node * head = l.head;
    l.head = msort(head, numeric);
}


Node *msort(Node *head, bool numeric) {
    if(head->next == NULL || head == NULL){ //base case
        return head;
    }
    Node* left = head;
    Node* right = head;
    split(head, left, right);
    left = msort(left, numeric);
    right = msort(right, numeric);
    head = merge(left, right, numeric);
    return head;
}

void split(Node *head, Node *&left, Node *&right){
    //use a fast node to go through two nodes every time the slow goes one, so when the fast is at the end, the slow is in the middle.
    if(head->next == NULL){
        return;
    }
    Node * fast = head;
    Node * slow = head;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        if(fast != NULL){
            slow = slow->next;
        }
    }
    right = slow->next;
    slow->next = NULL;
    left = head;
}

Node *merge(Node *left, Node *right, bool numeric) { //have to do this iteratively instead of recursively or else you get stack overflow
    //ITERATIVE MERGE, ABANONDED BECAUSE OF MEMORY LEAKS
    /*Node * head = NULL;
    Node * prev = NULL;
    Node * current = NULL;
    while (left != NULL || right != NULL){
        current = new Node;
        if(left == NULL) { //handles base cases
            current = right;
            right = right->next;
        } else if (right == NULL){
            current = left;
            left = left->next;
        }
        else if (numeric){
            if (left->number <= right->number){ //make the head the left or right, depending on which is smaller
                current = left;
                left = left->next;
            } else {
                current = right;
                right = right->next;
            }
        } else {
            const char * left_string = left->string.c_str();
            const char * right_string  = right->string.c_str();
            int result = strcmp(left_string, right_string);
            if(result <= 0){
                current->string = left->string;
                left = left->next;
            } else {
                current->string = right->string;
                right = right->next;
            }
        }
        current->next = NULL;
        if(head == NULL){ //means head has not been modified yet
            head = current;
        } else {
            prev->next = current;
        }
        prev = current;
    } 
    return head;*/
    
    //RECURSIVE CODE
    if(left == NULL){ //base cases
        return right;
    } else if (right == NULL){
        return left;
    }
    if(numeric){
        //cheng helped me with this logic
        if(left->number <= right->number){
            left->next = merge(left->next, right, numeric);
            return left;
        } else if (left->number > right->number){
            right->next = merge(left, right->next, numeric);
            return right;
        } 
    } else {
        //strcmp only uses c strings so we need to convert them.
        const char * left_string = left->string.c_str();
        const char * right_string  = right->string.c_str();
        int result = strcmp(left_string, right_string);
        if(result < 0){
            left->next = merge(left->next, right, numeric);
            return left;
        } else {
            right->next = merge(left, right->next, numeric);
            return right;
        }
    }
    return left;
    
}
