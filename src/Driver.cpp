//============================================================================
// Name        : AlignmentOOD.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Query.h"
#include "Native.h"
#include "Point.h"
#include "Template.h"
#include "BlastParser.h"
#include "HHSearchParser.h"
#include "CNFSearchParser.h"
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]) {

	/*if (argc != 3) {
	 cout << "the input should like this:" << endl;
	 cout << "<excutable> <type> <rootName>" << endl;
	 return 0;
	 }*/
	string querySeqLocation("/home/cf797/test/Proteins/");
	string alignmentResultLocation("/home/cf797/test/testAlignment/");
	string experimentLocation("/home/cf797/test/FullyExtendedOutputFolder/");
	string proteinDatabaseLocation("/home/lihongb/DATABASE/DBInfo/");
	string queryLocation("/home/cf797/test/Proteins/");

	if (strcmp(argv[1], "-blaPDB") == 0) {

		BlastParser blastParser(argv[2]);
		blastParser.parseFile(alignmentResultLocation);
		blastParser.storeFullyExtendedPDBFiles(argv[2],queryLocation,
				proteinDatabaseLocation, experimentLocation);
	}
	if (strcmp(argv[1], "-hhsearch") == 0) {

		HHSearchParser hhsearchParser(argv[2]);
		hhsearchParser.parseFile(alignmentResultLocation);
		hhsearchParser.storeFullyExtendedPDBFiles(argv[2],queryLocation,
				proteinDatabaseLocation, experimentLocation);
	}

	if (strcmp(argv[1], "-cnfSearch") == 0) {

		CNFSearchParser cnfSearchParser(argv[2]);
		cnfSearchParser.parseFile(alignmentResultLocation);
		cnfSearchParser.storeFullyExtendedPDBFiles(argv[2],queryLocation,
				proteinDatabaseLocation, experimentLocation);

	}

	return 0;
}
