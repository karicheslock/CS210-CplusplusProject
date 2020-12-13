//CS210 Project 3 Wildlife Zoo App
//Kari L. Cheslock
//12-13-2020

#include <iostream>
#include <jni.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Animal.h"
#include "Oviparous.h"
#include "Mammal.h"

using namespace std;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

void AddAnimal()
{
     //this method adds an animal to "zoodata.txt" via a vector

	//declaration of new Animal, Oviparous, and Mammal objects
	Animal newAnimal;
	Oviparous newOviparous;
	Mammal newMammal;

	//variable declarations
	int trackNumber;
	string animalName;
	string animalType;
	string animalSubType;
	int numAnimalEggs;
	int animalNursing;
	int i;

	//prompts for user inputs for animal info, mutator methods accessed where appropriate
	cout << "Track number: " << endl;
	cin >> trackNumber;
	newAnimal.SetTrackingNumber(trackNumber);
	cout << "Name: " << endl;
	cin >> animalName;
	newAnimal.SetName(animalName);
	cout << "Type: " << endl;
	cin >> animalType;
	cout << "Sub-type: " << endl;
	cin >> animalSubType;
	cout << "Eggs: " << endl;
	cin >> numAnimalEggs;
	newOviparous.SetNumEggs(numAnimalEggs);
	cout << "Nurse: " << endl;
	cin >> animalNursing;
	newMammal.SetIfNursing(animalNursing);

	//formatting of user inputs to match existing "zoodata.txt" format
	string stringTrackNumber = to_string(trackNumber);
	stringstream strTrackNumber;
	strTrackNumber << right << setfill('0') << setw(6) << stringTrackNumber;
	stringTrackNumber = strTrackNumber.str();

	stringstream strName;
	strName << left << setfill(' ') << setw(15) << animalName;
	animalName = strName.str();

	stringstream strType;
	strType << left << setfill(' ') << setw(15) << animalType;
	animalType = strType.str();

	stringstream strSubType;
	strSubType << left << setfill(' ') << setw(15) << animalSubType;
	animalSubType = strSubType.str();

	string stringEggs = to_string(numAnimalEggs);
	stringstream strNumEggs;
	strNumEggs << left << setfill(' ') << setw(2) << stringEggs;
	stringEggs = strNumEggs.str();

	string stringNursing = to_string(animalNursing);
	stringstream strNursing;
	strNursing << left << setfill(' ') << setw(2) << stringNursing;
	stringNursing = strNursing.str();


	//creating input stream for "zoodata.txt"
	ifstream inFS;

	//opening "zoodata.txt"
	inFS.open("zoodata.txt");

	//verifying that "zoodata.txt" could be opened, returning error message if unable to open
	if (!inFS.is_open()) {
		cout << "Could not open file zoodata.txt." << endl;
		return;
	}

	//creating vector for storing data in "zoodata.txt"
	string inputString;
	vector<string> data;

	//adding data from "zoodata.txt" to vector
	while(getline(inFS, inputString)) {
			data.push_back(inputString);
		}

	//validating user input via tracking number, checking that tracking number is unique
	for (i = 0; i < data.size(); ++i) {
		if (data.at(i).substr(0,6) == stringTrackNumber) {
			cout << "That tracking number already exists" << endl;
			break;
		}
		else {
			//if tracking number is unique, add new animal to end of vector
			string newInputString;
			newInputString = stringTrackNumber + animalName + animalType + animalSubType + stringEggs + stringNursing;
			data.push_back(newInputString);
		}
	}


	//close input file
	inFS.close();


	//ask user if they would like to save new data
	char saveInput;
	cout << "Would you like to save the data?  Enter y or n." << endl;
	cin >> saveInput;

	if (saveInput == 'y' || saveInput == 'Y') {
		//creating output stream to save new data to file "zoodata.txt"
		ofstream outFS;
		//opening output file
		outFS.open("zoodata.txt");

		//verifying output file can be opened or returning an error message if not
		if (!outFS.is_open()) {
		    cout << "Could not open file zoodata.txt." << endl;
		    return;
		   }

		//writing vector data to output file
		int i;
		for (i = 0; i < data.size(); ++i) {
			outFS << data[i] << endl;
		}

		//closing output file
		outFS.close();

		cout << "Save successfully completed." << endl;
	}


}


void RemoveAnimal()
{
    //this method deletes an animal from "zoodata.txt" via a vector
	//declaration/initialization of variables
	int userInputNum = 0;
	int i;

	//obtain user input for record to be deleted
	cout << "Enter the tracking number for the record to be deleted: " << endl;
	cin >> userInputNum;

	//format user input with leading 0s to match format in vector
	string stringTrackNumber = to_string(userInputNum);
	stringstream strTrackNumber;
	strTrackNumber << right << setfill('0') << setw(6) << stringTrackNumber;
	stringTrackNumber = strTrackNumber.str();

	//opening input stream for "zoodata.txt"
	ifstream inFS;

	inFS.open("zoodata.txt");

	//check to make sure "zoodata.txt" could be opened and return an error message if not
	if (!inFS.is_open()) {
		cout << "Could not open file zoodata.txt." << endl;
		return;
	}

	//creaing a vector to store data from "zoodata.txt"
	string inputString;
	vector<string> data;
	while(getline(inFS, inputString)) {
			data.push_back(inputString);
		}

	//check for vector entry matching the user-entered tracking number
	//substr() method used to only look at tracking number portion of record in vector
	//erase() method used to remove entry
	//user input validated to see if tracking number exists in order to remove it
	for (i = 0; i < data.size(); ++i) {
		if (data.at(i).substr(0,6) == stringTrackNumber) {
			data.erase(data.begin() + i);
		}
		else {
			cout << "There are no entries matching this tracking number." << endl;
			break;
		}
	}

	//input file stream closed
	inFS.close();

	//ask user if they would like to save the new data
	char saveInput;
	cout << "Would you like to save the data?  Enter y or n." << endl;
	cin >> saveInput;
	if (saveInput == 'y' || saveInput == 'Y') {
		//create output stream to save the vector to "zoodata.txt"
		ofstream outFS;
		//opening the output file
		outFS.open("zoodata.txt");

		//check to see if output file is able to be opened and return error message if not
		if (!outFS.is_open()) {
		    cout << "Could not open file zoodata.txt." << endl;
		    return;
		   }

		//write data from vector to "zoodata.txt"
		int i;
		for (i = 0; i < data.size(); ++i) {
			outFS << data[i] << endl;
		}

		//close output file
		outFS.close();

		cout << "Save successfully completed." << endl;
	}


}

void LoadDataFromFile()
{
    //this method loads the data from "zoodata.txt" into a vector
	//input stream created and "zoodata.txt" opened
	ifstream inFS;
	inFS.open("zoodata.txt");

	//check if "zoodata.txt" can be opened and return an error message if not
	if (!inFS.is_open()) {
		cout << "Could not open file zoodata.txt." << endl;
		return;
	}

	//create a vector to hold the data from "zoodata.txt"
	string inputString;
	vector<string> data;
	//writing data to vector
	while(getline(inFS, inputString)) {
			data.push_back(inputString);
		}


	cout << "Load complete." << endl;
	//closing input file
	inFS.close();



}
void SaveDataToFile()
{

	//this method saves data to an output file

	//creating input stream and opening "zoodata.txt"
	ifstream inFS;
	inFS.open("zoodata.txt");

	//check to see if "zoodata.txt" can be opened and return an error message if not
	if (!inFS.is_open()) {
		cout << "Could not open file zoodata.txt." << endl;
		return;
	}

	//create a vector to write data from "zoodata.txt"
	string inputString;
	vector<string> data;
	//write data to vector
	while(getline(inFS, inputString)) {
			data.push_back(inputString);
		}

	//close input file
	inFS.close();


	//create output stream and open "zoodata.txt"
	ofstream outFS;
	outFS.open("zoodata.txt");

	//check if output file can be opened and return an error message if not
	if (!outFS.is_open()) {
	    cout << "Could not open file zoodata.txt." << endl;
	    return;
	   }

	//write data from vector to output file
	int i;
	for (i = 0; i < data.size(); ++i) {
		outFS << data[i] << endl;
	}

	//close output file
	outFS.close();

	cout << "Save successfully completed." << endl;




}

void DisplayMenu()
{
    //this method creates the menu to be displayed to the user

	//variable to accept user input
	int userChoice;

	cout << "Please choose from the following options: " << endl;
	cout << "1. Load Animal Data" << endl;
	cout << "2. Generate Data" << endl;
	cout << "3. Display Animal Data" << endl;
	cout << "4. Add Record" << endl;
	cout << "5. Delete Record" << endl;
	cout << "6. Save Animal Data" << endl;
	cout << "Enter the number for your choice: " << endl;
	cin >> userChoice;


	//option 1 calls the LoadDataFromFile() method
	if (userChoice == 1) {
		LoadDataFromFile();
	}
	//option 2 calls the GenerateData() method
	if (userChoice == 2) {
		GenerateData();
	}
	//option 3 displays data from "zoodata.txt" in tabular format
	if (userChoice == 3){
		//creating input stream and opening "zoodata.txt"
		ifstream inFS;
		inFS.open("zoodata.txt");

		//check to see if "zoodata.txt" can be opened and return an error message if not
		if (!inFS.is_open()) {
			cout << "Could not open file zoodata.txt." << endl;
			return;
		}

		//creating vector to load data
		string inputString;
		vector<string> data;

		//loading data into vector
		while(getline(inFS, inputString)) {
			data.push_back(inputString);
		}


		//formatting table header information
		cout << setw(10) << left << "Track #" << "|";
		cout << setw(20) << left << "Name" << "|";
		cout << setw(20) << left << "Type" << "|";
		cout << setw(20) << left << "Sub-type" << "|";
		cout << setw(10) << left << "Eggs" << "|";
		cout << setw(10) << left << "Nurse" << "|" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;

		//printing data from vector line-by-line
		//each line sliced into substrings and formatted into a table
		int i;
		for (i = 0; i < data.size(); ++i) {
			cout << data.at(i).substr(0,6) << "    |" << data.at(i).substr(6,15) << "     |" << data.at(i).substr(21,15) << "     |" << data.at(i).substr(36,15) << "     |" << data.at(i).substr(51,2) << "        |" << data.at(i).substr(53,2) << "         |" << endl;
		}

		//closing input file
		inFS.close();

	}
	//user choice 4 calls the AddAnimal() method
	if (userChoice == 4) {
		AddAnimal();
	}
	//user choice 5 calls the RemoveAnimal() method
	if (userChoice == 5) {
		RemoveAnimal();
	}
	//user choice 6 calls the SaveDataToFile() method
	if (userChoice == 6) {
		SaveDataToFile();
	}
}



int main()
{
	//DisplayMenu() method called in main()
	DisplayMenu();
	return 1;
}
