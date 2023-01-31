// quick.cpp

#include "volsort.h"

#include <iostream>

// Prototypes

Node *qsort(Node *head, bool numeric);
void  partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric);
Node *concatenate(Node *left, Node *right);

// Implementations

void quick_sort(List &l, bool numeric) {
    l.head = qsort(l.head, numeric);
}

Node *qsort(Node *head, bool numeric) {
    //base case
    if (head->next == nullptr){
        return head;
    }
    //going down the recursive calls
    Node *left = nullptr;
    Node *right = nullptr;
    partition(head, head, left, right, numeric);
    //disconnect head
    head->next = nullptr;

    //if the left side is null, only recurse right side, and only concat certain side
    if (left == nullptr){
        right = qsort(right, numeric);
        concatenate(head,right);
        return head;
    }
    //if the left side is null, only recurse right side, and only concat certain side
    else if (right == nullptr){
        left = qsort(left, numeric);
        concatenate(left,head);
        return left;
    }
    //otherwise recurse both and concat both
    else{
        left = qsort(left, numeric);
        right = qsort(right, numeric);
        concatenate(concatenate(left,head),right);
        return left;
    }
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric) {
    //traverse the rest of the list after the pivot(head) and depending on how we compare, 
    //add to the greater than or less than list
    Node *travel = pivot->next;
    Node *l_travel = left;
    Node *r_travel = right;
    //disconnect pivot
    pivot->next = nullptr;

    while(travel != nullptr){
        if (numeric){
            //if travel is greater
            if (node_number_compare(pivot, travel)){
                //if right doesn't have value, give it this. if it does, use r_travel to add
                if (right == nullptr){
                    right = travel;
                    r_travel = right;
                }
                else{
                    r_travel->next = travel;
                    r_travel = r_travel->next;
                }
                //move travel one then disconnect that node from original list
                travel = travel->next;
                r_travel->next = nullptr;
            }
            else{
                //if left doesn't have value, give it this. if it does, use l_travel to add
                if (left == nullptr){
                    left = travel;
                    l_travel = left;
                }
                else{
                    l_travel->next = travel;
                    l_travel = l_travel->next;
                }
                //move travel one then disconnect that node from original list
                travel = travel->next;
                l_travel->next = nullptr;
            }
        }
        else{
            //if travel is greater
            if (node_string_compare(pivot, travel)){
                //if right doesn't have value, give it this. if it does, use r_travel to add
                if (right == nullptr){
                    right = travel;
                    r_travel = right;
                }
                else{
                    r_travel->next = travel;
                    r_travel = r_travel->next;
                }
                //move travel one then disconnect that node from original list
                travel = travel->next;
                r_travel->next = nullptr;
            }
            else{
                //if left doesn't have value, give it this. if it does, use l_travel to add
                if (left == nullptr){
                    left = travel;
                    l_travel = left;
                }
                else{
                    l_travel->next = travel;
                    l_travel = l_travel->next;
                }
                //move travel one then disconnect that node from original list
                travel = travel->next;
                l_travel->next = nullptr;
            }
        }
    }
}

Node *concatenate(Node *left, Node *right) {
    //travel to the end of left and have it point to right
    Node *travel = left;
    while (travel->next != nullptr){
        travel = travel->next;
    }
    travel->next = right;
    //return concatinated head which is left with how we combined
    return left;
}

