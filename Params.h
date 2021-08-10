#ifndef _PARAMS_H_
#define _PARAMS_H_

#include "stdincludes.h"
#include "Params.h"
#include "Member.h"

enum testTYPE { CREATE_TEST, READ_TEST, UPDATE_TEST, DELETE_TEST };

class Params{
public:
	int MAX_NNB;
	int SINGLE_FAILURE;	
	double MSG_DROP_PROB;
	double STEP_RATE;
	int EN_GPSZ;
	int MAX_MSG_SIZE;
	int DROP_MSG;
	int dropmsg;
	int globaltime;
	int allNodesJoined;
	short PORTNUM;
	Params();
	void setparams(char *);
	int getcurrtime();
};

#endif
