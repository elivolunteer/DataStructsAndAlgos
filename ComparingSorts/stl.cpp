// stl.cpp
//Dev: Gabriel Stowe
//Decription: This sorts the linked list by the standard sort algo.

#include "volsort.h"

#include <algorithm> 
#include <iostream>
#include <vector>
void stl_sort(List &l, bool numeric)
 {
    

    std::vector<int> tmp;
    std::vector<std::string> tmpStr;

   
    //store list elements into vector
    for (Node * curr = l.head; curr != NULL; curr = curr->next) 
    {
       tmp.push_back(curr->number);
       tmpStr.push_back(curr->string);
    }

    if(numeric)
    {
        std::sort(tmp.begin(),tmp.end());    
        Node * curr;
        curr = l.head;
        //Replace all values in list with sorted vector. 
        for(unsigned int i = 0; i < tmp.size(); i++)
        {
            curr->number = tmp[i];
            curr->string = std::to_string(tmp[i]);
            curr = curr->next;   
        }
    }
    else
    {
        std::sort(tmpStr.begin(),tmpStr.end());    
        Node * curr;
        curr = l.head;
        //Replace all values in list with sorted vector. 
        for(unsigned int i = 0; i < tmpStr.size(); i++)
        {
            curr->number = std::stoi(tmpStr[i]);
            curr->string = tmpStr[i];
            curr = curr->next;   
        }
    }
    
      
    



}





