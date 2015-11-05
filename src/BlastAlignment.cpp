/*
 * BlastAlignment.cpp
 *
 *  Created on: Oct 24, 2015
 *      Author: Chao
 */

#include "BlastAlignment.h"

BlastAlignment::BlastAlignment() {
	// TODO Auto-generated ructor stub

}

BlastAlignment::~BlastAlignment() {
	// TODO Auto-generated destructor stub
}

int BlastAlignment::getGaps() {
	return gaps;
}

void BlastAlignment::setGaps(int gaps) {
	this->gaps = gaps;
}

int BlastAlignment::getPositives() {
	return positives;
}

void BlastAlignment::setPositives(int positives) {
	this->positives = positives;
}
