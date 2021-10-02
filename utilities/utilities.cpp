#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

#include "../includes/constants.h"
#include "../includes/utilities.h"

//if you are debugging the file must be in the project parent directory
std::string DoubleToString(double Number) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

//if myString does not contain a string rep of number returns 0
//if int not large enough has undefined behaviour, 
//this is a very fragile function
//ex. string a="3";
//    int i = stringToInt(a.c_str()); //i contains 3
//    a="s";
//    i = stringToInt(a.c_str()); //i receives 0
int stringToInt(const char *myString) {
	return atoi(myString);
}

//if myString does not contain a string rep of number returns 0
//this is a very fragile function
//ex. string b="4.5";
//    double d = stringToDouble(b.c_str()); //d receives 4.5
double stringToDouble(const char *myString) {
	return atof(myString);
}

/***
* Clears allStudentData, Opens file, For each line; parses name, midterm1,midterm2 and an
* optional finalgrade (if present in file)from that line. Puts this info into a studentData struct,
* adds this struct to allstudentData vector.
* NOTE:
* Ignore empty lines
* Non empty lines will contain 4 or 5 values to be parsed.
* the default param separator_char is defined in the header file declaration of readFile ONLY, it is not in the readFile definition.
* @param file - where student data is stored
* @param allstudentData - a vector that holds the student data info after it has been read from file
* @param separator_char - the character that separates each bit of data in a line of student data
* @return COULD_NOT_OPEN_FILE
*         SUCCESS
*/
int readFile(std::string &file, std::vector<KP::studentData> &allstudentData, char separator_char){
	std::ifstream my_input_file; // Creates ifstream
	my_input_file.open(file.c_str(), std::ios::in); // Opens file
	if (!my_input_file.is_open()) { // File was not opened
		return KP::COULD_NOT_OPEN_FILE;
	}
	// Read Contents of file and *Print to console*
	std::string line;
	std::stringstream lineStream;
	std::string item;
	KP::studentData myStudentData;

	while(!my_input_file.eof()) {
		std::getline(my_input_file, line);
		lineStream.clear();  // Clears stringstream of old data
		myStudentData.clear(); // Clears myStudentData of old values
		lineStream.str(line);
		//get the name
		std::getline(lineStream, myStudentData.name, separator_char);
		//get the midterm1 grade
		std::getline(lineStream, item, separator_char);
		myStudentData.midterm1 = stringToDouble(item.c_str());
		//get the midterm2 grade
		std::getline(lineStream, item, separator_char);
		myStudentData.midterm2 = stringToDouble(item.c_str());
		//get the final grade if it exists
		if (std::getline(lineStream, item, separator_char)) {
			myStudentData.finalgrade = stringToDouble(item.c_str());
		}
		allstudentData.push_back(myStudentData);
	}
//Code below is previously used methods
//	while(std::getline(my_input_file, line)) {
//		lineStream.clear();
//		lineStream.str(line); //Line in file
//		while(std::getline(lineStream, item, separator_char)) { //item is each item in the line (items split from line by delimiter)
//			std::cout<<"Item in line: "<<item<<std::endl;
//		}
//	}
//	while(!my_input_file.eof()) {
//		getline(my_input_file, line);
//		std::cout<<line<<std::endl;
//	}
	my_input_file.close();
	return KP::SUCCESS;
}

/***
 * Iterates over all students in vector, and averages midterm1 and midterm2 to get the finalgrade
 * @param allstudentData
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
int calculateFinalGrade(std::vector<KP::studentData> &allstudentData) {
	return 0;
}

/***
 * Opens file, serializes data from allstudentData to file, closes file
 * the default param seperator_char is defined in the header file ONLY
 * @param file - where student data is stored
 * @param allstudentData - a vector that holds student data info that will be written to file
 * @param separator_char - the character that separates each bit of data in a line of student data
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         COULD_NOT_OPEN_FILE
 *         SUCCESS
 */
int writeFile(std::string &file, std::vector<KP::studentData> &allstudentData, char separator_char) {
	return 0;
}

/***
 * Sorts studentdata based on SORT_TYPE
 * @param allstudentData - a vector that holds student data info that will be written to file
 * @param st - how to sort the vector
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
int sortStudentData(std::vector<KP::studentData> &allstudentData,KP::SORT_TYPE st) {
	return 0;
}
