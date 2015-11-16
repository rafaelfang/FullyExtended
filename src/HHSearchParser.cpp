/*
 * HHSearchParser.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: Chao
 */

#include "HHSearchParser.h"

HHSearchParser::HHSearchParser() {
	// TODO Auto-generated constructor stub

}
HHSearchParser::HHSearchParser(string _rootName) {
	// TODO Auto-generated constructor stub
	setRootName(_rootName);
}
void HHSearchParser::storeFullyExtendedPDB(string resultPosition) {
	string whichMethod("hhsearch");
	for (int i = 0; i < hhsearchRecords.size(); i++) {
		Point*P =
				hhsearchRecords[i].fetchFullyExtendedSubjectAlignedPart3DPointsForQuery(
						resultPosition, whichMethod, i);

	}
}
void HHSearchParser::storeRecords(string resultPosition) {
	ofstream myfile;
	string outputFile(resultPosition);
	outputFile += rootName;
	outputFile += "_hhsearch.json";
	myfile.open((char*) outputFile.c_str());

	myfile << "{\"" << rootName << "\":[" << endl;
	for (int i = 0; i < hhsearchRecords.size(); i++) {
		myfile << "\t{" << endl;
		myfile << "\t\"targetName\":\"" << hhsearchRecords[i].getTargetName()
				<< "\"," << endl;
		myfile << "\t\"targetFullSequence\":\""
				<< hhsearchRecords[i].getTargetSequence() << "\"," << endl;
		myfile << "\t\"targetLength\":\""
				<< hhsearchRecords[i].getTargetLength() << "\"," << endl;
		myfile << "\t\"templateName\":\""
				<< hhsearchRecords[i].getTemplateName() << "\"," << endl;
		myfile << "\t\"templateSequenceInfo\":\""
				<< hhsearchRecords[i].getTemplateSequenceInfo() << "\","
				<< endl;
		myfile << "\t\"templateSequenceLength\":\""
				<< hhsearchRecords[i].getTemplateSequenceLength() << "\","
				<< endl;

		myfile << "\t\"probab\":\"" << hhsearchRecords[i].getProbab() << "\","
				<< endl;
		myfile << "\t\"expect\":\"" << hhsearchRecords[i].getExpect() << "\","
				<< endl;
		myfile << "\t\"score\":\"" << hhsearchRecords[i].getScore() << "\","
				<< endl;
		myfile << "\t\"Aligned Columns\":\""
				<< hhsearchRecords[i].getAlignedColumns() << "\"," << endl;
		myfile << "\t\"identities\":\"" << hhsearchRecords[i].getIdentities()
				<< "%\"," << endl;
		myfile << "\t\"queryStart\":\"" << hhsearchRecords[i].getQueryStart()
				<< "\"," << endl;
		myfile << "\t\"queryPart\":\"" << hhsearchRecords[i].getQueryPart()
				<< "\"," << endl;
		;
		myfile << "\t\"queryEnd\":\"" << hhsearchRecords[i].getQueryEnd()
				<< "\"," << endl;
		myfile << "\t\"subjectStart\":\""
				<< hhsearchRecords[i].getSubjectStart() << "\"," << endl;
		;
		myfile << "\t\"subjectPart\":\"" << hhsearchRecords[i].getSubjectPart()
				<< "\"," << endl;
		;
		myfile << "\t\"subjectEnd\":\"" << hhsearchRecords[i].getSubjectEnd()
				<< "\"," << endl;
		myfile << "\t\"fullyEntendedStart\":\""
				<< hhsearchRecords[i].fetchFullyExtendedStart() << "\","
				<< endl;
		myfile << "\t\"fullyEntendedEnd\":\""
				<< hhsearchRecords[i].fetchFullyExtendedEnd() << "\"," << endl;
		myfile << "\t\"FullyExtendedPart\":\""
				<< hhsearchRecords[i].fetchFullyExtendedSequence() << "\"}";
		if (i == hhsearchRecords.size() - 1) {
			myfile << endl;
		} else {
			myfile << "," << endl;
		}
	}
	myfile << "]}" << endl;
	myfile.close();
}

void HHSearchParser::loadAlignmentsInfo(string targetLocation,
		string hhsearchResultFileLocation, string proteinDatabaseLocation) {
	//************************************************************************
	//target information
	int _targetSequenceLength;
	string _targetSequence;
	string _targetName(rootName);

	string fastaFile(targetLocation);
	fastaFile += rootName;
	fastaFile += ".fasta";
	FILE* f = fopen((char*) fastaFile.c_str(), "r");
	if (f == NULL) {
		cout << "fasta file: " << fastaFile << " can't open" << endl;
	} else {

		int lineLength = 5000;
		char line[lineLength];
		fgets(line, lineLength, f);
		fgets(line, lineLength, f);
		string s(line);
		_targetSequence = s.erase(s.find_last_not_of(" \n\r\t") + 1);

		int numberOfChars = 0;
		while (line[numberOfChars] != '\0') {

			numberOfChars++;
		}
		numberOfChars--;
		_targetSequenceLength = numberOfChars;
	}
	fclose(f);
	//************************************************************************
	//Alignments information

	string hhsearchResultFile(hhsearchResultFileLocation);
	hhsearchResultFile += rootName;
	hhsearchResultFile += "/QueryInfo/query.hhr";
	cout << hhsearchResultFile << endl;
	FILE* fptr = fopen((char*) hhsearchResultFile.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << hhsearchResultFile << " can't open" << endl;
	} else {
		int lineLength = 5000;
		char line[lineLength];

		HHSearchAlignment hhsearchRecord;
		char prevState = 'N';
		char currentState = 'N';

		while (fgets(line, lineLength, fptr) != NULL) {

			if (strstr(line, ">") != NULL) {
				currentState = 'A';
			} else if (strstr(line, "Probab=") != NULL) {
				currentState = 'B';
			} else if (strstr(line, "Q ") != NULL && prevState == 'B') {
				currentState = 'C';
			} else if ((strstr(line, "Q ") != NULL && prevState == 'C')
					|| (strstr(line, "Q ") != NULL && prevState == 'D')) {
				currentState = 'D';
			} else {
				continue;
			}

			if ((prevState == 'D' && currentState == 'B')
					|| (prevState == 'C' && currentState == 'B')
					|| (prevState == 'D' && currentState == 'A')
					|| (prevState == 'C' && currentState == 'A')) {

				hhsearchRecords.push_back(hhsearchRecord);
				//hhsearchRecord.displayRecordInfo();
				string emptyString("");
				hhsearchRecord.setQueryPart(emptyString);
				hhsearchRecord.setSubjectPart(emptyString);
			}

			if (currentState == 'A') {
				string nameLine(line);
				string hitName = nameLine.substr(1, 6);
				//cout << "hitName is " << hitName << endl;
				hhsearchRecord.setTargetName(_targetName);
				hhsearchRecord.setTargetLength(_targetSequenceLength);
				hhsearchRecord.setTargetSequence(_targetSequence);
				hhsearchRecord.setTemplateName(hitName);
				//**********load template information here*****************
				hhsearchRecord.loadTemplateInfo(proteinDatabaseLocation);

			} else if (currentState == 'B') {

				char* pch = strstr(line, "=");
				double probab;
				sscanf(pch + 1, "%lf", &probab);

				char* pch2 = strstr(pch + 1, "=");
				double expect;
				sscanf(pch2 + 1, "%lf", &expect);

				char* pch3 = strstr(pch2 + 1, "=");
				double score;
				sscanf(pch3 + 1, "%lf", &score);

				char* pch4 = strstr(pch3 + 1, "=");
				int alignedColumns;
				sscanf(pch4 + 1, "%d", &alignedColumns);

				char* pch5 = strstr(pch4 + 1, "=");
				int identities;
				sscanf(pch5 + 1, "%d", &identities);

				hhsearchRecord.setProbab(probab);
				hhsearchRecord.setExpect(expect);
				hhsearchRecord.setScore(score);
				hhsearchRecord.setAlignedColumns(alignedColumns);
				hhsearchRecord.setIdentities(identities);
/*
				cout << "probab: " << probab << endl;
				cout << "expect: " << expect << endl;
				cout << "score: " << score << endl;
				cout << "aligned columns: " << alignedColumns << endl;
				cout << "identities: " << identities << endl;
*/
			} else if (currentState == 'C') {
				//current locate at Q ss_pred
				fgets(line, lineLength, fptr);	//skip Q ss_conf
				fgets(line, lineLength, fptr);	//get Q pdb info
				char queryPart[200];
				int queryStart, queryEnd;

				sscanf(line, "%*s %*s %d %s %d", &queryStart, queryPart,
						&queryEnd);
				//cout << line << endl;
				string _queryPart(queryPart);
				//cout << "=====" << queryStart << queryPart << queryEnd << endl;
				fgets(line, lineLength, fptr); //skip q consensus
				fgets(line, lineLength, fptr); //skip alignment
				fgets(line, lineLength, fptr); //skip T Consensus
				fgets(line, lineLength, fptr); //get T info

				char subjectPart[200];
				int subjectStart, subjectEnd;

				sscanf(line, "%*s %*s %d %s %d", &subjectStart, subjectPart,
						&subjectEnd);

				string _subjectPart(subjectPart);

				hhsearchRecord.setQueryStart(queryStart);
				hhsearchRecord.setQueryPart(_queryPart);
				hhsearchRecord.setQueryEnd(queryEnd);

				hhsearchRecord.setSubjectStart(subjectStart);
				hhsearchRecord.setSubjectPart(_subjectPart);
				hhsearchRecord.setSubjectEnd(subjectEnd);
				/*
				 cout << "query info: " << queryStart << queryPart << queryEnd
				 << endl;
				 cout << "subject info: " << subjectStart << subjectPart
				 << subjectEnd << endl;*/

			} else if (currentState == 'D') {
				//current locate at Q ss_pred
				fgets(line, lineLength, fptr); //skip Q ss_conf
				fgets(line, lineLength, fptr); //get Q pdb info
				char queryPart[200];
				int queryStart, queryEnd;

				sscanf(line, "%*s %*s %d %s %d", &queryStart, queryPart,
						&queryEnd);
				string _queryPart(queryPart);
				fgets(line, lineLength, fptr); //skip q consensus
				fgets(line, lineLength, fptr); //skip alignment
				fgets(line, lineLength, fptr); //skip T Consensus
				fgets(line, lineLength, fptr); //get T info

				char subjectPart[200];
				int subjectStart, subjectEnd;

				sscanf(line, "%*s %*s %d %s %d", &subjectStart, subjectPart,
						&subjectEnd);
				string _subjectPart(subjectPart);

				string oldQueryPart = hhsearchRecord.getQueryPart();
				oldQueryPart += _queryPart;
				hhsearchRecord.setQueryPart(oldQueryPart);

				hhsearchRecord.setQueryEnd(queryEnd);

				string oldSubjectPart = hhsearchRecord.getSubjectPart();
				oldSubjectPart += _subjectPart;
				hhsearchRecord.setSubjectPart(oldSubjectPart);

				hhsearchRecord.setSubjectEnd(subjectEnd);
				/*
				 cout << "query info: " << hhsearchRecord.getQueryStart()
				 << hhsearchRecord.getQueryPart()
				 << hhsearchRecord.getQueryEnd() << endl;
				 cout << "subject info: " << hhsearchRecord.getSubjectStart()
				 << hhsearchRecord.getSubjectPart()
				 << hhsearchRecord.getSubjectEnd() << endl;
				 */
			}
			prevState = currentState;
		}
		hhsearchRecords.push_back(hhsearchRecord);
	}

}
HHSearchParser::~HHSearchParser() {
// TODO Auto-generated destructor stub
}
