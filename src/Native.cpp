/*
 * Native.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#include "Native.h"

Native::Native() {
	// TODO Auto-generated ructor stub

}
Native::Native(Query _query) {
	setTargetName(_query.getTargetName());
	setQuery(_query.getQuery());
	setQueryLength(_query.getQueryLength());

}
Native::~Native() {
	// TODO Auto-generated destructor stub
}

Point* Native::getCAlphaCoords() {
	return cAlphaCoords;
}

void Native::setCAlphaCoords(Point* _cAlphaCoords) {
	cAlphaCoords = _cAlphaCoords;
}
