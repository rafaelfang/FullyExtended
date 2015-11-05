/*
 * HHSearchAlignment.cpp
 *
 *  Created on: Oct 24, 2015
 *      Author: Chao
 */

#include "HHSearchAlignment.h"

HHSearchAlignment::HHSearchAlignment() {
	// TODO Auto-generated ructor stub

}

HHSearchAlignment::~HHSearchAlignment() {
	// TODO Auto-generated destructor stub
}

int HHSearchAlignment::getAlignedColumns() {
	return alignedColumns;
}

void HHSearchAlignment::setAlignedColumns(int alignedColumns) {
	this->alignedColumns = alignedColumns;
}

double HHSearchAlignment::getProbab() {
	return probab;
}

void HHSearchAlignment::setProbab(double probab) {
	this->probab = probab;
}
