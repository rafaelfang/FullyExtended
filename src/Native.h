/*
 * Native.h
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#ifndef NATIVE_H_
#define NATIVE_H_

#include "Query.h"

class Native: public Query {
public:
	Native();
	Native(Query);
	virtual ~Native();
	Point* getCAlphaCoords();
	void setCAlphaCoords(Point*);

private:
	Point* cAlphaCoords;
};

#endif /* NATIVE_H_ */
