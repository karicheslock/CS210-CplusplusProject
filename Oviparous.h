/*
 * Oviparous.h
 *
 *  Created on: Dec 10, 2020
 *      Author: Kari L. Cheslock
 */

//this file contains the declaration of the Oviparous class
#ifndef OVIPAROUS_H_
#define OVIPAROUS_H_

#include <iostream>

#include "Animal.h"

using namespace std;


//declaration of Oviparous class extending the Animal class
class Oviparous : public Animal {
//declaration of Oviparous class and mutator/accessor methods
public:
	Oviparous();
	void SetNumEggs(int numEggs);
	int GetNumEggs() const;
//declaration of Oviparous class private variable
private:
	int m_numEggs;
};


#endif /* OVIPAROUS_H_ */
