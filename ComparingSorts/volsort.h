// volsort.h

#ifndef VOLSORT_H
#define VOLSORT_H

#include <string>

struct Node {
    std::string string;
    int         number;
    Node       *next;
};

struct List {
    Node       *head;
    size_t      size;

    List(); 					// define in list.cpp
    ~List();					// define in list.cpp

    void push_front(const std::string &s){
    
      if(size > 0)
      {
        Node *i;
        i = new Node;
        i->string = s;
        i->number = std::stoi(s);
        i->next = head;
        head = i;
      }
      else
      {
        head->string = s;
        head->number = std::stoi(s);
      }
     


      //Add 1 to size to keep track of the size of the list
      size += 1;



    }	//define below
};


// Functions -------------------------------------------------------------------
// Got compare functions from
//http://anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml
int c_node_number_compare (const void * a, const void * b);

int c_node_string_compare (const void * a, const void * b);
//----------------------------------------------------------------------------------------------
bool node_number_compare(const Node *a, const Node *b);

bool node_string_compare(const Node *a, const Node *b);


void dump_node(Node *n);					// implement in this file (volsort.h) to make it easier for TAs to grade

void stl_sort(List &l, bool numeric);	// define in stl.cpp - sort using std::sort
void qsort_sort(List &l, bool numeric);	// define in qsort.cpp - sort using qsort from cstdlib
void merge_sort(List &l, bool numeric);	// define in merge.cpp - your implementation
void quick_sort(List &l, bool numeric);	// define in quick.cpp - your implementation

#endif
