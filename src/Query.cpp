/*
 * Query.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#include "Query.h"

Query::Query() {
	// TODO Auto-generated ructor stub

}
Query::Query(string _targetName) {
	// TODO Auto-generated ructor stub
	setTargetName(_targetName);
}
Query::~Query() {
	// TODO Auto-generated destructor stub
}

string& Query::getQuery() {
	return query;
}

void Query::setQuery(string& query) {
	this->query = query;
}

int Query::getQueryLength() {
	return queryLength;
}

void Query::setQueryLength(int queryLength) {
	this->queryLength = queryLength;
}

string& Query::getTargetName() {
	return targetName;
}

void Query::setTargetName(string& targetName) {
	this->targetName = targetName;
}
int Query::loadQueryInfo(string queryLocation) {
	//open protein db file, read and store protein infomation
	string queryFile(queryLocation);
	queryFile += targetName;
	queryFile += ".fasta";
	//cout<<templateName<<endl;
	FILE* fptr = fopen((char*) queryFile.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << queryFile << " can't open" << endl;
		return -1;
	} else {
		int lineLength = 5000;
		char line[lineLength];
		fgets(line, lineLength, fptr);
		char _targetName[10];
		strstr(line, ">");
		sscanf(line + 1, "%s", _targetName);
		string str(_targetName);
		setTargetName(str);
		//cout<<getTargetName()<<endl;
		fgets(line, lineLength, fptr);
		int numberOfChars = 0;
		while (line[numberOfChars] != '\0') {

			numberOfChars++;
		}
		numberOfChars--;
		setQueryLength(numberOfChars);
		string _query(line);
		setQuery(_query);
		//cout<<getQueryLength()<<endl;
		//cout<<getQuery()<<endl;
		return 0;
	}

}
