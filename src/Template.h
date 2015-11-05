/*
 * Template.h
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include "Query.h"

class Template: public Query {
public:
	Template();
	Template(Query);
	virtual ~Template();
	string& getMethodUsed();
	void setMethodUsed(string& methodUsed);
	Point* getTemplateCAlphaCoords();
	void setTemplateCAlphaCoords(Point* templateCAlphaCoords);
	string& getTemplateName();
	void setTemplateName(string& templateName);
	int loadTemplateInfo(string);
	string& getTemplateSequenceInfo();
	void setTemplateSequenceInfo(string& templateSequenceInfo);
	int getTemplateSequenceLength();
	void setTemplateSequenceLength(int templateSequenceLength);

protected:
	string templateName;
	string templateSequenceInfo;
	int templateSequenceLength;
	string methodUsed;
	Point* templateCAlphaCoords;
};

#endif /* TEMPLATE_H_ */
