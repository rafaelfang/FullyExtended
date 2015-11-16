/*
 * Alignment.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#include "Alignment.h"

#include <stdlib.h>
#include <cstdio>
#include <cwchar>
#include <iostream>

#include "Point.h"

Alignment::Alignment() {
	// TODO Auto-generated ructor stub

}
Alignment::Alignment(Template _template) {
	// TODO Auto-generated ructor stub
	setTemplateName(_template.getTemplateName());
	setTemplateSequenceInfo(_template.getTemplateSequenceInfo());
	setTemplateSequenceLength(_template.getTemplateSequenceLength());
	setTemplateCAlphaCoords(_template.getTemplateCAlphaCoords());

}

Alignment::~Alignment() {
	// TODO Auto-generated destructor stub
}

int Alignment::getQueryEnd() {
	return queryEnd;
}

void Alignment::setQueryEnd(int queryEnd) {
	this->queryEnd = queryEnd;
}

string& Alignment::getQueryPart() {
	return queryPart;
}

void Alignment::setQueryPart(string& queryPart) {
	this->queryPart = queryPart;
}

int Alignment::getQueryStart() {
	return queryStart;
}

void Alignment::setQueryStart(int queryStart) {
	this->queryStart = queryStart;
}

int Alignment::getSubjectEnd() {
	return subjectEnd;
}

void Alignment::setSubjectEnd(int subjectEnd) {
	this->subjectEnd = subjectEnd;
}

string& Alignment::getSubjectPart() {
	return subjectPart;
}

void Alignment::setSubjectPart(string& subjectPart) {
	this->subjectPart = subjectPart;
}

int Alignment::getSubjectStart() {
	return subjectStart;
}

void Alignment::setSubjectStart(int subjectStart) {
	this->subjectStart = subjectStart;
}

Point* Alignment::fetchSubjectAlignedPart3DPointsForQuery() {

	int sizeOfAlignment = subjectPart.size();

	Point* subjectPoints = (Point*) malloc(sizeof(Point) * sizeOfAlignment);

	int numOfGapsInSubjectPart = 0;
	for (int i = 0; i < sizeOfAlignment; i++) {
		if (subjectPart[i] == '-') {
			Point bigNum(10000, 10000, 10000);
			subjectPoints[i] = bigNum;

			numOfGapsInSubjectPart++;
		} else {

			subjectPoints[i] = templateCAlphaCoords[subjectStart + i
					- numOfGapsInSubjectPart - 1];

		}

	}

	int numOfGapsInQueryPart = 0;
	for (int i = 0; i < queryPart.size(); i++) {
		if (queryPart[i] == '-') {
			numOfGapsInQueryPart++;
		}
	}

	int candidateQueryAlignedPartLength = queryEnd - queryStart + 1;
	Point* candidateQueryAlignedPart3DCoords = (Point*) malloc(
			sizeof(Point) * candidateQueryAlignedPartLength);

	int gapOffset = 0;
	for (int i = 0; i < queryPart.size(); i++) {
		if (queryPart[i] == '-') {
			gapOffset++;
		} else {
			candidateQueryAlignedPart3DCoords[i - gapOffset] = subjectPoints[i];
		}

	}

	return candidateQueryAlignedPart3DCoords;

}

int Alignment::fetchFullyExtendedStart() {
	string fullyExtendedSequence;
	int queryHeadDiff = queryStart - 1;
	int queryTailDiff = targetLength - queryEnd;

	int subjectHeadDiff = subjectStart - 1;
	int subjectTailDiff = templateSequenceLength - subjectEnd;
	//subject head more
	int subjectHeadMore;
	if (queryHeadDiff > subjectHeadDiff) {
		subjectHeadMore = subjectHeadDiff;
	} else {
		subjectHeadMore = queryHeadDiff;
	}
	return subjectStart - subjectHeadMore;
}
int Alignment::fetchFullyExtendedEnd() {
	string fullyExtendedSequence;
	int queryHeadDiff = queryStart - 1;
	int queryTailDiff = targetLength - queryEnd;

	int subjectHeadDiff = subjectStart - 1;
	int subjectTailDiff = templateSequenceLength - subjectEnd;
	//subject head more
	int subjectTailMore;
	if (queryTailDiff > subjectTailDiff) {
		subjectTailMore = subjectTailDiff;
	} else {
		subjectTailMore = queryTailDiff;
	}
	return subjectEnd + subjectTailMore;
}
string Alignment::fetchFullyExtendedSequence() {
	string fullyExtendedSequence;
	int queryHeadDiff = queryStart - 1;
	int queryTailDiff = targetLength - queryEnd;

	int subjectHeadDiff = subjectStart - 1;
	int subjectTailDiff = templateSequenceLength - subjectEnd;
	//subject head more
	int subjectHeadMore;
	if (queryHeadDiff > subjectHeadDiff) {
		subjectHeadMore = subjectHeadDiff;
	} else {
		subjectHeadMore = queryHeadDiff;
	}

	//subject tail more
	int subjectTailMore;
	if (queryTailDiff > subjectTailDiff) {
		subjectTailMore = subjectTailDiff;
	} else {
		subjectTailMore = queryTailDiff;
	}
	cout<<templateName<<endl;
	cout<<"headmore"<<endl;
	while (subjectHeadMore > 0) {

		char aminoAcid = (templateSequenceInfo[subjectStart - subjectHeadMore
				- 1]);
		fullyExtendedSequence += aminoAcid;
		cout<<aminoAcid;
		subjectHeadMore--;
	}
	cout<<endl;
	cout<<"middle"<<endl;
	for (int i = 0; i < subjectEnd - subjectStart + 1; i++) {

		char aminoAcid = (templateSequenceInfo[subjectStart + i - 1]);
		fullyExtendedSequence += aminoAcid;
		cout<<aminoAcid;

	}
	cout<<endl;
	cout<<"tailmore"<<endl;
	for (int i = 1; i <= subjectTailMore; i++) {

		char aminoAcid = (templateSequenceInfo[subjectEnd + i - 1]);
		fullyExtendedSequence += aminoAcid;
		cout<<aminoAcid;
	}
	cout<<endl;
	return fullyExtendedSequence;
}
Point* Alignment::fetchFullyExtendedSubjectAlignedPart3DPointsForQuery(
		string experimentLocation, string whichMethod, int id) {
	int queryHeadDiff = queryStart - 1;
	int queryTailDiff = targetLength - queryEnd;

	int subjectHeadDiff = subjectStart - 1;
	int subjectTailDiff = templateSequenceLength - subjectEnd;
	//subject head more
	int subjectHeadMore;
	if (queryHeadDiff > subjectHeadDiff) {
		subjectHeadMore = subjectHeadDiff;
	} else {
		subjectHeadMore = queryHeadDiff;
	}
	int fullyExtendedStart = queryStart - subjectHeadMore;

	//subject tail more
	int subjectTailMore;
	if (queryTailDiff > subjectTailDiff) {
		subjectTailMore = subjectTailDiff;
	} else {
		subjectTailMore = queryTailDiff;
	}
	int fullyExtendedEnd = queryEnd + subjectTailMore;

	string outputFile(experimentLocation);
	outputFile += targetName;
	outputFile += "/";
	mkdir(outputFile.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	outputFile += whichMethod;
	outputFile += "_";
	outputFile += targetName;
	outputFile += "_";
	char buffer[10];
	sprintf(buffer, "%d", id);
	outputFile += buffer;
	outputFile += "_";
	outputFile += templateName;
	outputFile += ".pdb";
	FILE *pFile = fopen((char*) outputFile.c_str(), "w");
	//return array allocation
	int totalSize = subjectHeadMore + subjectTailMore + queryEnd - queryStart
			+ 1;
	Point *fullyExtendedArray = (Point*) malloc(sizeof(Point) * totalSize);
	int index = 0; //index
	cout << templateName << endl;
	//fill in the subject head more points to return array
	cout << "\tHead More" << endl;
	while (subjectHeadMore > 0) {
		Point p = templateCAlphaCoords[subjectStart - subjectHeadMore - 1];
		fullyExtendedArray[index] = p;
		string aminoAcid(
				shortName2LongName(
						targetSequence[queryStart - subjectHeadMore - 1]));
		cout << "\t" << aminoAcid << "," << fullyExtendedArray[index].getX()
				<< "," << fullyExtendedArray[index].getY() << ","
				<< fullyExtendedArray[index].getZ() << endl;
		fprintf(pFile, "ATOM  %5d  CA  %3s  %4d    %8.3f%8.3f%8.3f\n",
				queryStart - subjectHeadMore, (char*) aminoAcid.c_str(),
				queryStart - subjectHeadMore, p.getX(), p.getY(), p.getZ());
		index++;
		subjectHeadMore--;
	}
	cout << "\tMiddle part" << endl;
	//middle part
	Point* alignPart = fetchSubjectAlignedPart3DPointsForQuery();
	for (int i = 0; i < queryEnd - queryStart + 1; i++) {

		fullyExtendedArray[index] = alignPart[i];
		string aminoAcid(
				shortName2LongName(targetSequence[queryStart + i - 1]));
		cout << "\t" << aminoAcid << "," << fullyExtendedArray[index].getX()
				<< "," << fullyExtendedArray[index].getY() << ","
				<< fullyExtendedArray[index].getZ() << endl;
		fprintf(pFile, "ATOM  %5d  CA  %3s  %4d    %8.3f%8.3f%8.3f\n",
				queryStart + i, (char*) aminoAcid.c_str(), queryStart + i,
				alignPart[i].getX(), alignPart[i].getY(), alignPart[i].getZ());
		index++;
	}
	cout << "\tTail More" << endl;
	//tail more
	for (int i = 1; i <= subjectTailMore; i++) {
		Point p = templateCAlphaCoords[subjectEnd + i - 1];
		fullyExtendedArray[index] = p;
		string aminoAcid(shortName2LongName(targetSequence[queryEnd + i - 1]));
		cout << "\t" << aminoAcid << "," << fullyExtendedArray[index].getX()
				<< "," << fullyExtendedArray[index].getY() << ","
				<< fullyExtendedArray[index].getZ() << endl;
		fprintf(pFile, "ATOM  %5d  CA  %3s  %4d    %8.3f%8.3f%8.3f\n",
				queryEnd + i, (char*) aminoAcid.c_str(), queryEnd + i, p.getX(),
				p.getY(), p.getZ());
		index++;

	}
	fprintf(pFile, "TER\n");
	fprintf(pFile, "END\n");
	fclose(pFile);
	return fullyExtendedArray;
}
string Alignment::shortName2LongName(char name) {
	if (name == 'A') {
		return "ALA";
	} else if (name == 'R') {
		return "ARG";
	} else if (name == 'N') {
		return "ASN";
	} else if (name == 'D') {
		return "ASP";
	} else if (name == 'C') {
		return "CYS";
	} else if (name == 'Q') {
		return "GLN";
	} else if (name == 'E') {
		return "GLU";
	} else if (name == 'G') {
		return "GLY";
	} else if (name == 'H') {
		return "HIS";
	} else if (name == 'I') {
		return "ILE";
	} else if (name == 'L') {
		return "LEU";
	} else if (name == 'K') {
		return "LYS";
	} else if (name == 'M') {
		return "MET";
	} else if (name == 'F') {
		return "PHE";
	} else if (name == 'P') {
		return "PRO";
	} else if (name == 'S') {
		return "SER";
	} else if (name == 'T') {
		return "THR";
	} else if (name == 'W') {
		return "TRP";
	} else if (name == 'Y') {
		return "TYR";
	} else if (name == 'V') {
		return "VAL";
	} else if (name == 'B') {
		return "ASX";
	} else if (name == 'Z') {
		return "GLX";
	}
}

