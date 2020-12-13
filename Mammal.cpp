/*
 * Mammal.cpp
 *
 *  Created on: Dec 10, 2020
 *      Author: Kari L. Cheslock
 */

//this file contains the definition of the default constructor and mutator/accessor methods for the Mammal class
#include <iostream>
#include "Mammal.h"

using namespace std;

//definition of default constructor for Mammal class
Mammal::Mammal() {
	m_isNursing = 0;
}
//definition of mutator and accessor methods for Mammal class
void Mammal::SetIfNursing(int isNursing) {
	m_isNursing = isNursing;
}

int Mammal::GetIfNursing() const {
	return m_isNursing;
}


