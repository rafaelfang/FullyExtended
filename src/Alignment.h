/*
 * Alignment.h
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#ifndef ALIGNMENT_H_
#define ALIGNMENT_H_

#include "Template.h"
#include <sys/stat.h>
class Alignment: public Template {
public:
	Alignment();
	Alignment(Template);
	void fullyExtended(string experimentLocation,string whichMethod);
	Point* fetchSubjectAlignedPart3DPointsForQuery();
	string changeName(char name);

	virtual ~Alignment();
	double getExpectedValue();
	void setExpectedValue(double expectedValue);
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

	int getIdentities();
	void setIdentities(int identities);

	double getScore();
	void setScore(double score);

private:
	int queryStart;
	string queryPart;
	int queryEnd;
	int subjectStart;
	string subjectPart;
	int subjectEnd;
	double expectedValue;
	double score;
	int identities;


};

#endif /* ALIGNMENT_H_ */
