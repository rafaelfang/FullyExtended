/*
 * CNFSearchParser.cpp
 *
 *  Created on: Oct 26, 2015
 *      Author: Chao
 */

#include "CNFSearchParser.h"

CNFSearchParser::CNFSearchParser() {
	// TODO Auto-generated constructor stub

}
CNFSearchParser::CNFSearchParser(string _rootName) {
	// TODO Auto-generated constructor stub
	setRootName(_rootName);

}
void CNFSearchParser::storeFullyExtendedPDBFiles(string targetName,string queryLocation,string proteinDatabaseLocation,string experimentLocation){
	string whichMethod("cnfSearch");
	for (int i = 0; i < cnfSearchRecords.size(); i++) {
		cnfSearchRecords[i].setTargetName(targetName);
		cnfSearchRecords[i].loadQueryInfo(queryLocation);
		cnfSearchRecords[i].loadTemplateInfo(proteinDatabaseLocation);
		cnfSearchRecords[i].fullyExtended(experimentLocation,whichMethod);
	}
}
void CNFSearchParser::storeRecords(string resultPosition) {
	ofstream myfile;
	string outputFile(resultPosition);
	outputFile += rootName;
	outputFile += "_cnfSearch.json";
	myfile.open((char*) outputFile.c_str());
	myfile << "{\"" << rootName << "\":[" << endl;
	for (int i = 0; i < cnfSearchRecords.size(); i++) {
		myfile << "\t{" << endl;
		myfile << "\t\"hitName\":\"" << cnfSearchRecords[i].getTemplateName()
				<< "\"," << endl;

		myfile << "\t\"queryStart\":\"" << cnfSearchRecords[i].getQueryStart()
				<< "\"," << endl;
		myfile << "\t\"queryPart\":\"" << cnfSearchRecords[i].getQueryPart()
				<< "\"," << endl;
		;
		myfile << "\t\"queryEnd\":\"" << cnfSearchRecords[i].getQueryEnd()
				<< "\"," << endl;
		myfile << "\t\"subjectStart\":\""
				<< cnfSearchRecords[i].getSubjectStart() << "\"," << endl;
		;
		myfile << "\t\"subjectPart\":\"" << cnfSearchRecords[i].getSubjectPart()
				<< "\"," << endl;
		;
		myfile << "\t\"subjectEnd\":\"" << cnfSearchRecords[i].getSubjectEnd()
				<< "\"}";
		if (i == cnfSearchRecords.size() - 1) {
			myfile << endl;
		} else {
			myfile << "," << endl;
		}
	}
	myfile << "]}" << endl;
	myfile.close();
}

void CNFSearchParser::storeCoordinates(string experimentLocation,
		string proteinDatabaseLocation,string queryLocation) {
	ofstream myfile;
	string outputFile(experimentLocation);
	outputFile += rootName;
	outputFile += "_coords_cnfSearch.txt";
	myfile.open((char*) outputFile.c_str());

	for (int i = 0; i < cnfSearchRecords.size(); i++) {

		int queryStart = cnfSearchRecords[i].getQueryStart();
		int queryEnd = cnfSearchRecords[i].getQueryEnd();
		cnfSearchRecords[i].loadQueryInfo(queryLocation);
		int flag = cnfSearchRecords[i].loadTemplateInfo(
				proteinDatabaseLocation);
		if (flag == 0) {
			int queryPointsArrSize = queryEnd - queryStart + 1;
			Point *queryPoints = (Point*) malloc(
					sizeof(Point) * queryPointsArrSize);
			queryPoints =
					cnfSearchRecords[i].fetchSubjectAlignedPart3DPointsForQuery();
			myfile << "Hit" << i << endl;
			for (int j = 0; j < queryPointsArrSize; j++) {
				myfile << "\t" << queryPoints[j].getX() << ","
						<< queryPoints[j].getY() << "," << queryPoints[j].getZ()
						<< endl;
			}
			free(queryPoints);
		} else {
			//unsucessful load template file due to lack of the db file
			myfile << "Hit" << i << endl;
			myfile << "\t" << "lack db file"
					<< cnfSearchRecords[i].getTemplateName() << endl;
		}

	}
	myfile.close();
}

void CNFSearchParser::parseFile(string cnfResultFileLocation) {
	string cnfResultFile(cnfResultFileLocation);
	cnfResultFile += rootName;
	cnfResultFile += "/query.rank";
	FILE* fptr = fopen((char*) cnfResultFile.c_str(), "r");

	if (fptr == NULL) {
		cout << "input file: " << cnfResultFile << " can't open" << endl;
	} else {
		int lineLength = 5000;
		char line[lineLength];
		CNFSearchAlignment cnfSearchRecord;
		char prevState = 'N';
		char currentState = 'N';
		while (fgets(line, lineLength, fptr) != NULL) {

			if (strstr(line, ">") != NULL) {
				currentState = 'A';
			} else if (strstr(line, "T sse_real") != NULL && prevState == 'A') {
				currentState = 'B';
			} else if ((strstr(line, "T sse_real") != NULL && prevState == 'B')
					|| (strstr(line, "T sse_real") != NULL && prevState == 'C')) {
				currentState = 'C';
			} else {
				continue;
			}

			if ((prevState == 'B' && currentState == 'A')
					|| (prevState == 'C' && currentState == 'A')) {

				cnfSearchRecords.push_back(cnfSearchRecord);
				//blastRecord.displayRecordInfo();
				string emptyString("");
				cnfSearchRecord.setQueryPart(emptyString);
				cnfSearchRecord.setSubjectPart(emptyString);
			}

			if (currentState == 'A') {
				string nameLine(line);
				string hitName = nameLine.substr(1, 6);

				for (int i = 0; i < hitName.length(); i++) {
					hitName[i] = toupper(hitName[i]);
				}
				hitName.insert(hitName.begin() + 4, '_');
				hitName.erase(hitName.find_last_not_of(" \n\r\t") + 1);
				cnfSearchRecord.setTemplateName(hitName);

			} else if (currentState == 'B') {
				//pay attention the rank file list subject first and then query
				//which is different sequence than blast and hhsearch
				fgets(line, lineLength, fptr); //skip subject acc_real
				fgets(line, lineLength, fptr); //get subject info

				char subjectPart[200];
				int subjectStart, subjectEnd;
				sscanf(line, "%*s %*s %d %s %d", &subjectStart, subjectPart,
						&subjectEnd);
				string _subjectPart(subjectPart);

				fgets(line, lineLength, fptr); //skip middle alignment
				fgets(line, lineLength, fptr); //get query info

				char queryPart[200];
				int queryStart, queryEnd;
				sscanf(line, "%*s %*s %d %s %d", &queryStart, queryPart,
						&queryEnd);
				string _queryPart(queryPart);

				cnfSearchRecord.setSubjectStart(subjectStart);
				cnfSearchRecord.setSubjectPart(_subjectPart);
				cnfSearchRecord.setSubjectEnd(subjectEnd);

				cnfSearchRecord.setQueryStart(queryStart);
				cnfSearchRecord.setQueryPart(_queryPart);
				cnfSearchRecord.setQueryEnd(queryEnd);

			} else if (currentState == 'C') {
				fgets(line, lineLength, fptr); //skip T acc_real
				fgets(line, lineLength, fptr); //get subject info

				char subjectPart[200];
				int subjectStart, subjectEnd;
				sscanf(line, "%*s %*s %d %s %d", &subjectStart, subjectPart,
						&subjectEnd);
				string _subjectPart(subjectPart);

				fgets(line, lineLength, fptr); //skip middle alignment
				fgets(line, lineLength, fptr); //get query info

				char queryPart[200];
				int queryStart, queryEnd;

				sscanf(line, "%*s %*s %d %s %d", &queryStart, queryPart,
						&queryEnd);
				string _queryPart(queryPart);


				string oldQueryPart = cnfSearchRecord.getQueryPart();
				oldQueryPart += _queryPart;
				cnfSearchRecord.setQueryPart(oldQueryPart);

				cnfSearchRecord.setQueryEnd(queryEnd);

				string oldSubjectPart = cnfSearchRecord.getSubjectPart();
				oldSubjectPart += _subjectPart;
				cnfSearchRecord.setSubjectPart(oldSubjectPart);

				cnfSearchRecord.setSubjectEnd(subjectEnd);
				/*cout << "query info: " << cnfSearchRecord.getQueryStart()
				 << cnfSearchRecord.getQueryPart()
				 << cnfSearchRecord.getQueryEnd() << endl;
				 cout << "subject info: " << cnfSearchRecord.getSubjectStart()
				 << cnfSearchRecord.getSubjectPart()
				 << cnfSearchRecord.getSubjectEnd() << endl;*/
			}
			prevState = currentState;

		}
		cnfSearchRecords.push_back(cnfSearchRecord);
	}
}
CNFSearchParser::~CNFSearchParser() {
// TODO Auto-generated destructor stub
}

