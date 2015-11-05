/*
 * BlastAlignment.h
 *
 *  Created on: Oct 24, 2015
 *      Author: Chao
 */

#ifndef BLASTALIGNMENT_H_
#define BLASTALIGNMENT_H_

#include "Alignment.h"

class BlastAlignment: public Alignment {
public:
	BlastAlignment();
	virtual ~BlastAlignment();
	int getGaps();
	void setGaps(int gaps);
	int getPositives();
	void setPositives(int positives);

private:
	int positives;
	int gaps;
};

#endif /* BLASTALIGNMENT_H_ */
