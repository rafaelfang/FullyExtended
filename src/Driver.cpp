//============================================================================
// Name        : AlignmentOOD.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Point.h"
#include "Template.h"
#include "BlastParser.h"
#include "HHSearchParser.h"

#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]) {

	/*if (argc != 3) {
	 cout << "the input should like this:" << endl;
	 cout << "<excutable> <type> <rootName>" << endl;
	 return 0;
	 }*/
	string targetLocation("/home/cf797/test/Proteins/");
	string alignmentResultLocation("/home/spnf2f/dataset/alignment/casp10/");
	string experimentLocation("/home/cf797/test/FullyExtendedOutputFolder/");
	string proteinDatabaseLocation("/home/lihongb/DATABASE/DBInfo/");


	if (strcmp(argv[1], "-blaPDB") == 0) {

		BlastParser blastParser(argv[2]);
		blastParser.loadAlignmentsInfo(targetLocation,alignmentResultLocation,proteinDatabaseLocation);
		blastParser.storeRecords(experimentLocation);
		blastParser.storeFullyExtendedPDB(experimentLocation);

	}
	if (strcmp(argv[1], "-hhsearch") == 0) {

		HHSearchParser hhsearchParser(argv[2]);
		hhsearchParser.loadAlignmentsInfo(targetLocation,alignmentResultLocation,proteinDatabaseLocation);
		hhsearchParser.storeRecords(experimentLocation);
		hhsearchParser.storeFullyExtendedPDB(experimentLocation);

	}



	return 0;
}
