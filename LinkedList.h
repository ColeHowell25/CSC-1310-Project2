/*****************************************************************
	Title:  	LinkedList.h - Class Specification File for 
				both the ListNode Class and LinkedList Class
	Date:  		2-8-2019
	Author: 	April Crockett, made Template by Cole Howell
	Purpose:	A Singly-Linked List implemented in a
				LinkedList class that contains a ListNode
				structure variable
******************************************************************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>
using namespace std;

/*****************************************************************
							LinkedList Class
******************************************************************/
template <typename var>
class LinkedList
{
	private:
		
		struct ListNode{	
			/*	notice the attributes are public so that the 
				LinkedList class can directly access them */
				
			var value;           // Node value
			struct ListNode *next; // Pointer to the next node
		};
	
		ListNode *head; // List head pointer
		ListNode *tail;	//List tail pointer

	public:
		// Constructor
		LinkedList()
		{ 
			head = NULL; 
			tail = NULL;
		}

		// Destructor
		~LinkedList();

		// Linked list operations
		void appendNode(var);	//inserts node at end of list
		void insertNode(var);	//inserts node in ascending value order
		void insertNode(int position, var); //insert node in given position
		
		var getNodeValue(int);
		void deleteNode(var);
		void displayList() const;
		bool isEmpty(){
			if(!head)
				return true;
			else
				return false;
		}
		int getLength(){
			
			int counter = 0;
			ListNode *nodePtr;
			
			nodePtr = head;
			
			while(nodePtr != tail)
			{
				counter++;
				nodePtr = nodePtr->next;
				if (nodePtr == tail)
					counter++;
			}
			return counter;
		}
};
template <typename var>
void LinkedList<var>::appendNode(var newValue)
{
	ListNode *newNode;  // To point to a new node
	ListNode *nodePtr;  // To move through the list

	// Allocate a new node and store newValue there.
	newNode = new ListNode;
	newNode->value = newValue;
	newNode->next = NULL;

	// If there are no nodes in the list make newNode the first node.
	if (!head) 
	{
		head = newNode;
		tail = newNode;
	}
	else  // Otherwise, insert newNode at end.
	{
		//set the current last node's next pointer to the new node
		tail->next = newNode;
		
		//now the tail is the new node
		tail = newNode;
	}
}

//returns the node value at a given integer position
template <typename var>
var LinkedList<var>::getNodeValue(int pos)
{
	ListNode *nodePtr;
	if(!head)
		return NULL;
	else
	{
		if(pos == 0)
			return head->value;
		nodePtr = head;
		int currentPos = 0;
		while(nodePtr != NULL && pos >= currentPos)
		{
			if(pos == currentPos)
				return nodePtr->value;
			currentPos++;
			nodePtr = nodePtr->next;				
		}
	}
	return NULL;
}

template <typename var>
void LinkedList<var>::displayList() const
{
	ListNode *nodePtr;  // To move through the list

	// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr points to a node, traverse the list.
	while (nodePtr)
	{
		// Display the value in this node.
		cout << nodePtr->value << endl;

		// Move to the next node.
		nodePtr = nodePtr->next;
	}
}

//insert a node in ascending order value
template <typename var>
void LinkedList<var>::insertNode(var newValue)
{
	ListNode *newNode;				// A new node
	ListNode *nodePtr;				// To traverse the list
	ListNode *previousNode = NULL; // The previous node

	// Allocate a new node and store newValue there.
	newNode = new ListNode;
	newNode->value = newValue;

	// If there are no nodes in the list make newNode the first node
	if (!head)
	{
		head = newNode;
		newNode->next = NULL;
	}
	else  // Otherwise, insert newNode
	{
		// Position nodePtr at the head of list.
		nodePtr = head;

		// Initialize previousNode to NULL.
		previousNode = NULL;

		// Skip all nodes whose value is less than newValue.
		while (nodePtr != NULL && nodePtr->value < newValue)
		{  
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If the new node is to be the 1st in the list, insert it before all other nodes.
		if (previousNode == NULL)
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else  // Otherwise insert after the previous node.
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
}

//insert a new node at the integer position passed to this function
template <typename var>
void LinkedList<var>::insertNode(int position, var x)
{
	ListNode *nodePtr;
	ListNode *newNode;
	
	newNode = new ListNode;
	newNode->value = x;
	
	if(!head)
	{
		if(position != 0)
		{
			//can't insert node at position (>0) if there is not already a node
			cout << "\n\nUnable to insert a node at position " << position << " because there are currently no nodes in the list.  I am going to insert this node at position 1.\n\n";
		}
		head = newNode;
		tail = newNode;
	}
	else
	{
		nodePtr = head;
		int nodeCount = 0;
		if(position == 0)
		{
			newNode->next = head->next;
			head = newNode;
		}
		while(nodePtr != tail && nodeCount < position)
		{
			nodeCount++;
			if(nodeCount == position)
				break;
			nodePtr = nodePtr->next;
		}
		
		//now nodePtr is positioned 1 node BEFORE the node we want to insert
		if(nodePtr->next == NULL) //we are appending this node to the end
			tail = newNode;
			
		newNode->next = nodePtr->next;
		nodePtr->next = newNode;
		
	}
	
}
template <typename var>
void LinkedList<var>::deleteNode(var searchValue)
{
	ListNode *nodePtr;       // To traverse the list
	ListNode *previousNode;  // To point to the previous node

	// If the list is empty, do nothing.
	if (!head)
		return;

	// Determine if the first node is the one.
	if (head->value == searchValue)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose value member is not equal to num.
		while (nodePtr != NULL && nodePtr->value != searchValue)
		{  
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If nodePtr is not at the end of the list, 
		// link the previous node to the node after
		// nodePtr, then delete nodePtr.
		if (nodePtr)
		{
			if(nodePtr == tail)
			{
				tail = previousNode;
			}
			previousNode->next = nodePtr->next;
			delete nodePtr;
		}
	}
}
template <typename var>
LinkedList<var>::~LinkedList(){
	ListNode *nodePtr;   // To traverse the list
	ListNode *nextNode;  // To point to the next node

	// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr is not at the end of the list...
	while (nodePtr != NULL)
	{
		// Save a pointer to the next node.
		nextNode = nodePtr->next;

		// Delete the current node.
		delete nodePtr;

		// Position nodePtr at the next node.
		nodePtr = nextNode;
	}
}

#endif