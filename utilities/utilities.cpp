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

/**
 * Converts received string to int type, returns 0 if invalid
 * @param myString - string to attempt to convert to int type
 * @return int conversion of myString
 */
int stringToInt(const char *myString) {
	return atoi(myString);
}

/**
 * Converts received string to float type, returns 0 if invalid
 * @param myString - string to attempt to convert to Double type
 * @return float conversion of myString
 */
double stringToDouble(const char *myString) {
	return atof(myString);
}

/**
 * CompareName function is used for sorting algorithm; compares by alphabetical order of name
 * @param x - first studentData struct to compare
 * @param y - second studentData struct to compare
 * @return boolean
 */
bool compareName(const KP::studentData& x, const KP::studentData& y){
	return x.name<y.name;
}

/**
 * CompareName function is used for sorting algorithm; compares by final grade
 * @param x - first studentData struct to compare
 * @param y - second studentData struct to compare
 * @return boolean
 */
bool compareFinal(const KP::studentData& x, const KP::studentData& y){
	return x.finalgrade>y.finalgrade;
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
	allstudentData.clear(); // Had to clear before reading in or it would append data onto vector (vector was not empty for some reason)
	std::ifstream my_input_file; // Creates ifstream
	my_input_file.open(file.c_str(), std::ios::in); // Opens file
	if (!my_input_file.is_open()) { // File was not opened
		return KP::COULD_NOT_OPEN_FILE;
	}
	// Initialize tool variables for file read
	std::string line;
	std::stringstream lineStream;
	std::string item;
	KP::studentData myStudentData;

	while(!my_input_file.eof()) { // While not at end of file
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
		allstudentData.push_back(myStudentData); // add myStudentData to allstudentData vector
	}
	my_input_file.close(); // Don't forget to close the file genius
	return KP::SUCCESS;
}

/***
 * Iterates over all students in vector, and averages midterm1 and midterm2 to get the finalgrade
 * @param allstudentData
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
int calculateFinalGrade(std::vector<KP::studentData> &allstudentData) {
	if(allstudentData.empty()){
		return KP::VECTOR_CONTAINS_NO_STUDENTS;
	}
	for(int i=0;i<allstudentData.size();i++) {
		allstudentData[i].finalgrade = (allstudentData[i].midterm1 + allstudentData[i].midterm2)/2.0;
	}
	return KP::SUCCESS;
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
	if(allstudentData.empty()){
		return KP::VECTOR_CONTAINS_NO_STUDENTS;
	}
	std::ofstream my_output_file;
	my_output_file.open(file.c_str(), std::ios::out);
	if(!my_output_file.is_open()){
		return KP::COULD_NOT_OPEN_FILE;
	}
	for(int i=0;i<allstudentData.size();i++){
		if(i==0){ // If it is the first line we don't want a leading newline
			my_output_file<<allstudentData[i].name<<" "<<allstudentData[i].midterm1<<" "<<allstudentData[i].midterm2<<" "<<allstudentData[i].finalgrade;
		}
		else{ // Have leading newline on the rest so the last line doesn't have a trailing newline
			my_output_file<<"\n"<<allstudentData[i].name<<" "<<allstudentData[i].midterm1<<" "<<allstudentData[i].midterm2<<" "<<allstudentData[i].finalgrade;
		}
	}
	my_output_file.close();
	return KP::SUCCESS;
}

/***
 * Sorts studentdata based on SORT_TYPE
 * @param allstudentData - a vector that holds student data info that will be written to file
 * @param st - how to sort the vector
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
int sortStudentData(std::vector<KP::studentData> &allstudentData,KP::SORT_TYPE st) {
	if(allstudentData.empty()){
		return KP::VECTOR_CONTAINS_NO_STUDENTS;
	}
	switch (st){
	case KP::NAME:
		std::sort(allstudentData.begin(), allstudentData.end(), compareName); // give range of vector and sort by name (make compareName method)
		break;
	case KP::FINAL_GRADE:
		std::sort(allstudentData.begin(), allstudentData.end(), compareFinal); // give range of vector and sort by final grade (make compareFinal method)
	}
	return KP::SUCCESS;
}
