/**********************************************************************
	Title:  	LinkedList.h - Class Specification File for           *
				both the ListNode Class and LinkedList Class          *
	Date:  		2-16-2019											  *
	Author: 	Cole Howell										      *
	Purpose:	Game Driver file for Creature Fight, includes list of *
				creatures from file									  *
***********************************************************************/

#include "LinkedList.h"
#include "Creature.h"
#include <fstream>
#include <cctype>
#include "Random.h"

//function prototypes
int binarySearchRecur(LinkedList<Creature*>*, int first, int last, string); //recursively searches a linked list
void mergeSort(LinkedList<Creature*>*, int first, int last); //sorts linked list recursively
void Merge(LinkedList<Creature*>* l, int beg, int mid, int end); //used in mergesort

int main(){
	//define a linked list of type Creature
	LinkedList<Creature*>* list;
	
	ifstream inFile;
	inFile.open("creatureFile.txt");
	
	if (!inFile.good()){
		cout << "The correct creature files are not in this directory.\n";
		cout << "Have a nice day.";
		return 0;
	}
	
	while (!inFile.eof()){
		string n; //temporary variable for the name of a Creature
		string d; //temp variable for description
		int lp; //temp variable for life points
		int hp; //temp variable for the hit points
		
		
		getline(inFile, n);
		inFile.ignore();
		getline(inFile, d);
		inFile.ignore();
		inFile >> lp;
		inFile >> hp;
		
		if (binarySearchRecur(list, 0, (list->getLength())-1, n) == -1){ //binary search is messed up, likely going infinite
			cout << n << " was not found in the list.\n";
			Creature* temp = new Creature(n, d, lp, hp);
			list->appendNode(temp);
			mergeSort(list, 0, list->getLength()); //sorts list
			cout << n << " has been added to the list.";
		}
		else{
			cout << n << " was already in the list. Skipping.\n";
		}
		
	}
	inFile.close();
	
	char choice2;
	do{//game actually starts
		string name1, name2;
		cout << "Player 1 enter your name : ";
		cin.ignore();
		getline(cin, name1);
		cout << "Player 2 enter your name : ";
		cin.ignore();
		getline(cin, name2);
		
		char choice;
		int P1choiceCreature, P2choiceCreature;
		cout << "Would either player like detailed information on the creatures? (y/n): ";
		cin >> choice;
		while (toupper(choice) != 'Y' || toupper(choice) != 'N'){
			cout << "Invalid input, choose y or n : ";
			cin >> choice;
		}
		
		if (toupper(choice) == 'Y'){
			//print all information for all creatures
			for (int i = 0; i<list->getLength(); i++){
				Creature* temp = list->getNodeValue(i);
				temp->printCreature(temp);
			}
		}
		
		cout << name1 << " enter the creature you would like to use to fight\n";
		cout << "\n\n";
		//print all names for the creatures with numbers assigned to them
		for (int i; i<list->getLength(); i++){
			cout << i << ". " << list->getNodeValue(i)->getName() << endl;
		}
		cin >> P1choiceCreature;
		Creature* P1 = list->getNodeValue(P1choiceCreature);
		
		cout << name2 << " enter the creature you would like to use to fight\n";
		cout << "\n\n";
		//print all names for the creatures with numbers assigned to them
		for (int i; i<list->getLength(); i++){
			cout << i << ". " << list->getNodeValue(i)->getName() << endl;
		}
		cin >> P2choiceCreature;
		Creature* P2 = list->getNodeValue(P2choiceCreature);
		int round = 1;
		
		
		do{
			seedRandom();
			cout << name1 << " hit enter to roll a die to determine damage.";
			cin.ignore();
			int damage1 = (getRandomInt(1,6)) * (P1->getHitPoints());
			P2->setLife((P2->getLifePoints())-damage1);
			
			if(P2->getLifePoints() <= 0){
				cout << name1 << " wins!\n";
				break;
			}
			
			cout << name2 << " hit enter to roll a die to determine damage";
			cin.ignore();
			int damage2 = (getRandomInt(1,6)) * (P2->getHitPoints());
			P1->setLife((P1->getLifePoints())-damage2);
			
			if(P1->getLifePoints() <= 0){
				cout << name2 << " wins!\n";
				break;
			}
			
			round++;
			
		}while (round > 3);
		
		if (round == 3){
			if(P1->getLifePoints() > P2->getLifePoints()){
				cout << name1 << " wins!\n";
			}
			else{
				cout << name2 << " wins!\n";
			}
		}
		
		
		
		cout << "Would you like to play again? (y/n)";
		cin >> choice2;
		
		while (toupper(choice2) != 'Y' || toupper(choice2) != 'N'){
			cout << "Invalid input, choose y or n : ";
			cin >> choice2;
		}
	
	}while(choice2 == 'Y');
	
	return 0;
}

int binarySearchRecur(LinkedList<Creature*>* l, int first, int last, string name){ //this function somehow going infinite
	
	if (first > last){
		return -1;
	}
	
	if (l->getNodeValue(first) == NULL){
		return -1;
	}
	
	int middle = (first + last)/2;
	Creature* search = l->getNodeValue(middle);
	
	if (search->getName() == name){
		return 0;
	}	
	else if (search->getName() < name){
		return binarySearchRecur(l, middle+1, last, name);
	}
	else if(search->getName() > name){
		return binarySearchRecur(l, first, middle-1, name); 
	}
}

void mergeSort(LinkedList<Creature*>* l, int beg, int end) {
   int mid = 0;
   
   if (beg < end) {
      mid = (beg + end) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      mergeSort(l, beg, mid);
      mergeSort(l, mid + 1, end);
      
      // Merge left and right partition in sorted order
      Merge(l, beg, mid, end);
   }
}

void Merge(LinkedList<Creature*>* l, int beg, int mid, int end) {
   int mergedSize = end - beg + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   
   leftPos = beg;                               // Initialize left partition position
   rightPos = mid + 1;                          // Initialize right partition position
   
   // Add smallest element from left or right partition to list
   while (leftPos <= mid && rightPos <= end) {
	   Creature* c1 = l->getNodeValue(leftPos); //creates temp variable for the node at left pos
	   Creature* c2 = l->getNodeValue(rightPos); //does same for node at right pos
      if (c1->getName() < c2->getName()) {
        l->deleteNode(c1); //deletes the original node
		l->insertNode(mergePos, c1); //replacing the value at the correct position
        ++leftPos;
      }
      else { //same outline but for the other case
		l->deleteNode(c2); 
        l->insertNode(mergePos, c2);
        ++rightPos; 
      }
      ++mergePos; //increment the mergepos
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   /*while (leftPos <= mid) {
      mergedNumbers[mergePos] = arr[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= end) {
      mergedNumbers[mergePos] = arr[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to arr
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      arr[beg + mergePos] = mergedNumbers[mergePos];
   }*/
}

