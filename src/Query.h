/*
 * Query.h
 *
 *  Created on: Oct 20, 2015
 *      Author: Chao
 */

#ifndef QUERY_H_
#define QUERY_H_
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "Point.h"
using namespace std;
class Query {
public:
	Query();
	Query(string );
	virtual ~Query();
	string& getQuery();
	void setQuery(string& query);
	int getQueryLength();
	void setQueryLength(int queryLength);
	string& getTargetName();
	void setTargetName(string& targetName);
	int loadQueryInfo(string);


protected:
	string targetName;
	string query;
	int queryLength;
};

#endif /* QUERY_H_ */
