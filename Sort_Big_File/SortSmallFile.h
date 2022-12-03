#pragma once

#include"Library.h"

struct Book {
	string id, context;
};


//function to parse line of file => data Book Info 
void parseData(string line);

//read Data of file
void readData(int lenghtFile);

//Quick sort
void qSort(int left, int right);


//write data into new file with name sorted
void writeData();



