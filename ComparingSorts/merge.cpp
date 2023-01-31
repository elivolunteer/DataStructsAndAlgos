// merge.cpp

#include "volsort.h"

#include <iostream>

using namespace std; //TAKE THIS OUT
// Prototypes

Node *msort(Node *head, bool numeric);
void  split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);

// Implementations

void merge_sort(List &l, bool numeric) {

	l.head = msort(l.head, numeric); // calls recursive function

}

Node *msort(Node *head, bool numeric) {

	Node *left;
	Node *right;

	if(head->next == nullptr)
	{
		// the list is empty/already sorted
		return head;
	}
	else
	{
		split(head, left, right); // call split to start recursion
    }	

		
		head = merge(msort(left, numeric), msort(right, numeric), numeric); // then call merge

		return head;
}



void split(Node *head, Node *&left, Node *&right) {
	
	Node *slow;
	Node *fast;

	slow = head;
	fast = head->next;

	while(fast != nullptr)
	{
		if(fast->next != nullptr)
		{
			// slow moves once
			slow = slow->next;
		}

		// fast moves twice
		fast = fast->next;
		if(fast != nullptr)
		{
			fast = fast->next;
		}
	}

	// split the list
	left = head;
	right = slow->next;
	slow->next = nullptr;
	// slow is now the head of the right list, head is still head of the left list

}

Node *merge(Node *left, Node *right, bool numeric) {

	Node *n;
	Node *t;

	// both if statements performed the same way
	if(numeric)
	{
		// check the first case to set a "head"
		if(left->number <= right->number)
		{
			n = left;
			left = left->next;
		}
		else 
		{	
			n = right;
			right = right->next;
		}

		t = n; // t is a travel node that connects head (n) to create its list

		while((left != nullptr) || (right != nullptr))
		{
		
			if((left == nullptr) && (right != nullptr))
			{
				while(right != nullptr)
				{
					t->next = right;
					t = t->next;
					right = right->next;
				}
			}
			else if((left != nullptr) && (right == nullptr))
			{
				while(left != nullptr)
				{
					t->next = left;
					t = t->next;
					left = left->next;
				}

			}
			else // if neither are nullptr, then compare them
			{

				if(left->number <= right->number)
				{
					t->next = left;
					t = t->next;
					left = left->next;
				}
				else
				{
					t->next = right;
					t = t->next;
					right = right->next;
				}
			}

		}
	}


	else
	{
		if(left->string <= right->string)
		{
			n = left;
			left = left->next;
		}
		else 
		{	
			n = right;
			right = right->next;
		}

		t = n;

		while((left != nullptr) || (right != nullptr))
		{
			if((left == nullptr) && (right != nullptr))
			{
				while(right != nullptr)
				{	
					t->next = right;
					t = t->next;
					right = right->next;
				}
				
			}
			else if((left != nullptr) && (right == nullptr))
			{
				while(left != nullptr)
				{
					t->next = left;
					t = t->next;
					left = left->next;
				}

			}
			else
			{
				if(left->string <= right->string)
				{
					t->next = left;
					t = t->next;
					left = left->next;
				}
				else
				{	
					t->next = right;
					t = t->next;
					right = right->next;
				}
			}

		}
	}

	return n; // return the "head" node that t built on

}

