#include "volsort.h"
#include<string.h>
#include<vector>
#include<iostream>


List::List() {
    head = new Node();
    head->next = nullptr;
    size = 0;
}

List::~List() {
    Node *i;
	i = head->next;
	Node *j;
	j = head-> next;
	while (j != nullptr){
		j = j->next;
		delete i;
		i = j;
	}
	delete head;
}

bool node_number_compare(const Node *a, const Node *b)
{
  if (a->number <= b->number){
    return true;
  }
  else{
    return false;
  }
};

bool node_string_compare(const Node *a, const Node *b)
{
  if (a->string <= b->string){
    return true;
  }
  else{
    return false;
  }
};	


int c_node_number_compare (const void * a, const void * b) {
    const int *ia = (const int *)a; // casting pointer types 
    const int *ib = (const int *)b;
    return *ia  - *ib; 

};

int c_node_string_compare (const void * a, const void * b) {
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);

};