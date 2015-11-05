/*
 * CNFSearchParser.h
 *
 *  Created on: Oct 26, 2015
 *      Author: Chao
 */

#ifndef CNFSEARCHPARSER_H_
#define CNFSEARCHPARSER_H_
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Parser.h"
#include "CNFSearchAlignment.h"
class CNFSearchParser: public Parser {
public:
	CNFSearchParser();
	CNFSearchParser(string);
	virtual ~CNFSearchParser();
	void parseFile(string);
	void storeFullyExtendedPDBFiles(string,string ,string,string);
	void storeCoordinates(string, string,string);

	void storeRecords(string);
private:

	vector<CNFSearchAlignment> cnfSearchRecords;
};

#endif /* CNFSEARCHPARSER_H_ */
