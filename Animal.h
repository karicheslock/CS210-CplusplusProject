/*
 * Animal.h
 *
 *  Created on: Dec 10, 2020
 *      Author: Kari L. Cheslock
 */


//this file contains the header information for the animal class

#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <iostream>
#include <string>

using namespace std;


//declaration of Animal class
class Animal {
//public declaration of Animal class and public mutator/accessor methods
public:
	Animal();
	void SetTrackingNumber(int trackNum);
	void SetName(string animalName);
	int GetTrackNumber() const;
	string GetName() const;
//declaration of Animal class private variables
private:
	int m_trackNum;
	string m_animalName;

};



#endif /* ANIMAL_H_ */
