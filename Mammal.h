/*
 * Mammal.h
 *
 *  Created on: Dec 10, 2020
 *      Author: Kari L. Cheslock
 */


//this file contains the declaration of the Mammal class
#ifndef MAMMAL_H_
#define MAMMAL_H_

#include <iostream>
#include <string>

#include "Animal.h"

//declaration of the Mammal class extending the Animal class
class Mammal : public Animal {
//declaration of public Mammal class and mutator/accessor methods
public:
	Mammal();
	void SetIfNursing(int isNursing);
	int GetIfNursing() const;
//declration of private variable for Mammal class
private:
	int m_isNursing;
};



#endif /* MAMMAL_H_ */
