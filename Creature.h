

#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <iostream>

using namespace std;

class Creature{
	private:
		string name;
		string description;
		int lifePoints;
		int hitPoints;
	public:
		//constructor that will accept values from a file
		Creature(string n, string des, int lp, int hp){
			name = n;
			description = des;
			lifePoints = lp;
			hitPoints = hp;
		}
		//destructor
		~Creature();
		
		//accessor functions for the creature object
		string getName();
		string getDescription();
		int getLifePoints();
		int getHitPoints();
		
		//mutator functions for the creature object
		void setName(string);
		void setDes(string);
		void setLife(int);
		void setHP(int);
		
		//prints all attributes of the creature object
		void printCreature(Creature*);
};

string Creature::getName(){
	return name;
}

string Creature::getDescription(){
	return description;
}

int Creature::getLifePoints(){
	return lifePoints;
}

int Creature::getHitPoints(){
	return hitPoints;
}

void Creature::setName(string n){
	name = n;
}

void Creature::setDes(string d){
	description = d;
}

void Creature::setLife(int L){
	lifePoints = L;
}

void Creature::setHP(int hp){
	hitPoints = hp;
}

void Creature::printCreature(Creature* c){
	cout << "\n\n*******************************************\n";
	cout << "Name : " << c->getName() << endl;
	cout << "Description : \n";
	cout << c->getDescription() << endl;
	cout << "Life Points : " << c->getLifePoints() << endl;
	cout << "Hit Points : " << c->getHitPoints() << endl;
	cout << "********************************************\n\n";
}




#endif