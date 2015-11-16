/*
 * Template.h
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include "Target.h"

class Template: public Target {
public:
	Template();
	Template(Target);
	virtual ~Template();
	string& getMethodUsed();
	void setMethodUsed(string& methodUsed);
	Point* getTemplateCAlphaCoords();
	void setTemplateCAlphaCoords(Point* templateCAlphaCoords);
	string& getTemplateName();
	void setTemplateName(string& templateName);
	string& getTemplateSequenceInfo();
	void setTemplateSequenceInfo(string& templateSequenceInfo);
	int getTemplateSequenceLength();
	void setTemplateSequenceLength(int templateSequenceLength);
	int loadTemplateInfo(string);
protected:
	string templateName;
	string templateSequenceInfo;
	int templateSequenceLength;
	string methodUsed;
	Point* templateCAlphaCoords;
};

#endif /* TEMPLATE_H_ */
