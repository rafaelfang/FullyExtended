/*
 * Template.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#include "Template.h"

Template::Template() {
	// TODO Auto-generated ructor stub

}
Template::Template(Target t) {
	// TODO Auto-generated ructor stub
	setTargetName(t.getTargetName());
	setTargetSequence(t.getTargetSequence());
	setTargetLength(t.getTargetLength());
}

Template::~Template() {
	// TODO Auto-generated destructor stub
}
int Template::loadTemplateInfo(string proteinDatabaseLocation) {
	//open protein db file, read and store protein infomation
	string proteinFile(proteinDatabaseLocation);
	proteinFile += templateName;
	proteinFile += ".db";
	//cout<<templateName<<endl;
	FILE* fptr = fopen((char*) proteinFile.c_str(), "r");
	if (fptr == NULL) {
		//cout << "input file: " << proteinFile << " can't open" << endl;
		return -1;
	} else {
		int lineLength = 5000;
		char line[lineLength];
		while (fgets(line, lineLength, fptr) != NULL) {
			if ((strstr(line, ">Reference Sequence Info:") != NULL)) {

				fgets(line, lineLength, fptr);

				int numberOfChars = 0;
				while (line[numberOfChars] != '\0') {

					numberOfChars++;
				}
				numberOfChars--;

				string _realSequenceInfo(line);
				_realSequenceInfo = _realSequenceInfo.erase(
						_realSequenceInfo.find_last_not_of(" \n\r\t") + 1);
				setTemplateSequenceInfo(_realSequenceInfo);

				//cout << templateSequenceInfo << endl;
				setTemplateSequenceLength(numberOfChars);
				//cout << templateSequenceLength << endl;
			}
			if ((strstr(line, ">Ca XYZ:") != NULL)) {

				double Xs[templateSequenceLength];
				double Ys[templateSequenceLength];
				double Zs[templateSequenceLength];

				double temp;
				for (int i = 0; i < templateSequenceLength; i++) {
					fscanf(fptr, "%lf", &temp);
					Xs[i] = temp;
					//if (i % 10 == 0) {
					//	cout << endl;
					//}
					//cout << Xs[i] << " ";
				}
				//cout << endl;

				for (int i = 0; i < templateSequenceLength; i++) {
					fscanf(fptr, "%lf", &temp);
					Ys[i] = temp;
					//if (i % 10 == 0) {
					//cout << endl;
					//}
					//cout << Ys[i] << " ";
				}
				//cout << endl;
				for (int i = 0; i < templateSequenceLength; i++) {
					fscanf(fptr, "%lf", &temp);
					Zs[i] = temp;
					//if (i % 10 == 0) {
					//	cout << endl;
					//}
					//cout << Zs[i] << " ";
				}
				//cout << endl;

				templateCAlphaCoords = (Point*) malloc(
						sizeof(Point) * templateSequenceLength);

				for (int i = 0; i < templateSequenceLength; i++) {
					Point point(Xs[i], Ys[i], Zs[i]);
					templateCAlphaCoords[i] = point;
				}

			}
		}
	}
	return 0;

}
string& Template::getMethodUsed() {
	return methodUsed;
}

void Template::setMethodUsed(string& methodUsed) {
	this->methodUsed = methodUsed;
}

Point* Template::getTemplateCAlphaCoords() {
	return templateCAlphaCoords;
}

void Template::setTemplateCAlphaCoords(Point* templateCAlphaCoords) {
	this->templateCAlphaCoords = templateCAlphaCoords;
}

string& Template::getTemplateName() {
	return templateName;
}

void Template::setTemplateName(string& templateName) {
	this->templateName = templateName;
}

string& Template::getTemplateSequenceInfo() {
	return templateSequenceInfo;
}

void Template::setTemplateSequenceInfo(string& templateSequenceInfo) {
	this->templateSequenceInfo = templateSequenceInfo;
}

int Template::getTemplateSequenceLength() {
	return templateSequenceLength;
}

void Template::setTemplateSequenceLength(int templateSequenceLength) {
	this->templateSequenceLength = templateSequenceLength;
}
