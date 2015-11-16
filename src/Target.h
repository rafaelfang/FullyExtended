/*
 * Target.h
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#ifndef TARGET_H_
#define TARGET_H_
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "Point.h"
using namespace std;
class Target {
public:
	Target();
	Target(string);
	virtual ~Target();
	int getTargetLength();
	void setTargetLength(int targetLength);
	string& getTargetName();
	void setTargetName(string& targetName);
	string& getTargetSequence();
	void setTargetSequence(string& targetSequence);

protected:
	string targetName;
	string targetSequence;
	int targetLength;
};

#endif /* TARGET_H_ */
