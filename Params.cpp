#include "Params.h"

Params::Params(): PORTNUM(8001) {}

void Params::setparams(char *config_file) {
	FILE *fp = fopen(config_file,"r");

	fscanf(fp,"MAX_NNB: %d", &MAX_NNB);
	fscanf(fp,"\nSINGLE_FAILURE: %d", &SINGLE_FAILURE);
	fscanf(fp,"\nDROP_MSG: %d", &DROP_MSG);
	fscanf(fp,"\nMSG_DROP_PROB: %lf", &MSG_DROP_PROB);

	EN_GPSZ = MAX_NNB;
	STEP_RATE=.25;
	MAX_MSG_SIZE = 4000;
	globaltime = 0;
	dropmsg = 0;
	allNodesJoined = 0;
	for ( unsigned int i = 0; i < EN_GPSZ; i++ ) {
		allNodesJoined += i;
	}
	fclose(fp);
	return;
}

int Params::getcurrtime(){
    return globaltime;
}
