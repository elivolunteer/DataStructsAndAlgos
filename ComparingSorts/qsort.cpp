// qsort.cpp
// Dev: Gabriel Stowe
// Date: 9/14/2021
//Description: 
// This code uses the qsort funtion from the standard libary. This sorts the single linked list that has been created

#include "volsort.h"
#include <algorithm>
#include <string>
#include <cstring>
#include<iostream>

void qsort_sort(List &l, bool numeric) {
    char * tmpStrs[l.size]; 
    int tmpInts[l.size];





    //store list elements into arrays
    int counter = 0;
    for (Node * curr = l.head; curr != NULL; curr = curr->next) 
    {
        tmpInts[counter] = curr->number;
        tmpStrs[counter] = strdup( curr->string.c_str() );
        counter++;
    }

    if(numeric)
    {
        //sort using c_node_number_compare
        std::qsort(&tmpInts[0],l.size,sizeof(int),c_node_number_compare);
        Node * curr;
        curr = l.head;
        //place sorted list into linked list
        for(unsigned int i = 0; i < l.size; i++)
        {
            curr->number = tmpInts[i];
            curr->string = std::to_string(tmpInts[i]);
            curr = curr->next;   
        }
      

    }
    else
    {
       
        //sort using c_node_string_compare
        std::qsort(&tmpStrs[0],l.size,sizeof(&tmpStrs[0]),c_node_string_compare);
        Node * curr;
        curr = l.head;
        //Replace all values in list with sorted vector. 
        for(unsigned int i = 0; i < l.size; i++)
        {
            curr->number = std::stoi(tmpStrs[i]);
            curr->string = tmpStrs[i];
            curr = curr->next;
        }

    }

    //free upmemory because of strdup
    for(size_t i = 0; i < l.size; i++)
    {
        free(tmpStrs[i]);
    }

   

}

