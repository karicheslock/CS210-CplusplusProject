/*
 * Oviparous.cpp
 *
 *  Created on: Dec 10, 2020
 *      Author: Kari L. Cheslock
 */

//this file contains the definition of the Oviparous class default constructor and mutator/accessor methods
#include "Oviparous.h"
#include <iostream>

using namespace std;

//definition of default constructor for the Oviparous class
Oviparous::Oviparous() {
	m_numEggs = 0;
}

//definition of mutator/accessor methods for Oviparous class
void Oviparous::SetNumEggs(int numEggs) {
	m_numEggs = numEggs;
}

int Oviparous::GetNumEggs() const {
	return m_numEggs;
}




