/*
 * HHSearchParser.h
 *
 *  Created on: Nov 14, 2015
 *      Author: Chao
 */

#ifndef HHSEARCHPARSER_H_
#define HHSEARCHPARSER_H_
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HHSearchAlignment.h"
#include "Parser.h"

class HHSearchParser: public Parser {
public:
	HHSearchParser();
	HHSearchParser(string);
	virtual ~HHSearchParser();

	void loadAlignmentsInfo(string, string, string);

	void storeFullyExtendedPDB(string);
	void storeRecords(string);
private:
	vector<HHSearchAlignment> hhsearchRecords;
};
#endif /* HHSEARCHPARSER_H_ */
