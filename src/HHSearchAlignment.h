/*
 * HHSearchAlignment.h
 *
 *  Created on: Oct 24, 2015
 *      Author: Chao
 */

#ifndef HHSEARCHALIGNMENT_H_
#define HHSEARCHALIGNMENT_H_

#include "Alignment.h"

class HHSearchAlignment: public Alignment {
public:
	HHSearchAlignment();
	virtual ~HHSearchAlignment();
	int getAlignedColumns();
	void setAlignedColumns(int alignedColumns);
	double getProbab();
	void setProbab(double probab);

private:
	double probab;
	int alignedColumns;
};

#endif /* HHSEARCHALIGNMENT_H_ */
