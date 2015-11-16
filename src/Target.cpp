/*
 * Target.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#include "Target.h"

Target::Target() {
	// TODO Auto-generated ructor stub

}
Target::Target(string _targetName) {
	// TODO Auto-generated ructor stub
	setTargetName(_targetName);
}
Target::~Target() {
	// TODO Auto-generated destructor stub
}

int Target::getTargetLength() {
	return targetLength;
}

void Target::setTargetLength(int targetLength) {
	this->targetLength = targetLength;
}

string& Target::getTargetName() {
	return targetName;
}

void Target::setTargetName(string& targetName) {
	this->targetName = targetName;
}

string& Target::getTargetSequence() {
	return targetSequence;
}

void Target::setTargetSequence(string& targetSequence) {
	this->targetSequence = targetSequence;
}
