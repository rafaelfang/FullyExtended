/*
 * Alignment.h
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#ifndef ALIGNMENT_H_
#define ALIGNMENT_H_

#include <string>
#include <sys/stat.h>
#include "Template.h"

using namespace std;
class Alignment: public Template {
public:
	Alignment();
	Alignment(Template);

	virtual ~Alignment();

	int getQueryEnd();
	void setQueryEnd(int queryEnd);
	string& getQueryPart();
	void setQueryPart(string& queryPart);
	int getQueryStart();
	void setQueryStart(int queryStart);
	int getSubjectEnd();
	void setSubjectEnd(int subjectEnd);
	string& getSubjectPart();
	void setSubjectPart(string& subjectPart);
	int getSubjectStart();
	void setSubjectStart(int subjectStart);
	Point* fetchSubjectAlignedPart3DPointsForQuery();
	string fetchFullyExtendedSequence();
	Point* fetchFullyExtendedSubjectAlignedPart3DPointsForQuery(string, string,
			int);
	string shortName2LongName(char name);
	int fetchFullyExtendedStart();
	int fetchFullyExtendedEnd();

private:
	int queryStart;
	string queryPart;
	int queryEnd;

	int subjectStart;
	string subjectPart;
	int subjectEnd;



};

#endif /* ALIGNMENT_H_ */
