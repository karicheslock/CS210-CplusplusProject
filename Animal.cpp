/*
 * Animal.cpp
 *
 *  Created on: Dec 10, 2020
 *      Author: Kari L. Cheslock
 */

//this file includes the default constructor and mutator/accessor methods for the Animal class

#include <iostream>
#include <string>
#include "Animal.h"

using namespace std;


//default constructor for Animal class
Animal::Animal() {
	m_trackNum = 0;
	m_animalName = "";
}

//definition of mutator and accessor methods for Animal class
void Animal::SetTrackingNumber(int trackNum) {
	m_trackNum = trackNum;
}

void Animal::SetName(string animalName) {
	m_animalName = animalName;
}

int Animal::GetTrackNumber() const {
	return m_trackNum;
}

string Animal::GetName() const {
	return m_animalName;
}


