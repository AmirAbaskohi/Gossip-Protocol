#include "Application.h"

void handler(int sig) {
	void *array[10];
	size_t size;

	size = backtrace(array, 10);

	fprintf(stderr, "Error: signal %d:\n", sig);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}

int main(int argc, char *argv[]) {
	if ( argc != ARGS_COUNT ) {
		cout<<"Configuration (i.e., *.conf) file File Required"<<endl;
		return FAILURE;
	}

	Application *app = new Application(argv[1]);

	app->run();

	delete(app);

	return SUCCESS;
}

Application::Application(char *infile) {
	int i;
	par = new Params();
	srand (time(NULL));
	par->setparams(infile);
	log = new Log(par);
	en = new EmulNet(par);
	mp1 = (MP1Node **) malloc(par->EN_GPSZ * sizeof(MP1Node *));

	for( i = 0; i < par->EN_GPSZ; i++ ) {
		Member *memberNode = new Member;
		memberNode->inited = false;
		Address *addressOfMemberNode = new Address();
		Address joinaddr;
		joinaddr = getjoinaddr();
		addressOfMemberNode = (Address *) en->ENinit(addressOfMemberNode, par->PORTNUM);
		mp1[i] = new MP1Node(memberNode, par, en, log, addressOfMemberNode);
		log->LOG(&(mp1[i]->getMemberNode()->addr), "APP");
		delete addressOfMemberNode;
	}
}

Application::~Application() {
	delete log;
	delete en;
	for ( int i = 0; i < par->EN_GPSZ; i++ ) {
		delete mp1[i];
	}
	free(mp1);
	delete par;
}

int Application::run()
{
	int i;
	int timeWhenAllNodesHaveJoined = 0;

	bool allNodesJoined = false;
	srand(time(NULL));

	for( par->globaltime = 0; par->globaltime < TOTAL_RUNNING_TIME; ++par->globaltime ) {
		mp1Run();
		fail();
	}

	en->ENcleanup();

	for(i=0;i<=par->EN_GPSZ-1;i++) {
		 mp1[i]->finishUpThisNode();
	}

	return SUCCESS;
}

void Application::mp1Run() {
	int i;

	for( i = 0; i <= par->EN_GPSZ-1; i++) {

		if( par->getcurrtime() > (int)(par->STEP_RATE*i) && !(mp1[i]->getMemberNode()->bFailed) ) {
			mp1[i]->recvLoop();
		}

	}

	for( i = par->EN_GPSZ - 1; i >= 0; i-- ) {

		if( par->getcurrtime() == (int)(par->STEP_RATE*i) ) {
			mp1[i]->nodeStart(JOINADDR, par->PORTNUM);
			cout<<i<<"-th introduced node is assigned with the address: "<<mp1[i]->getMemberNode()->addr.getAddress() << endl;
			nodeCount += i;
		}

		else if( par->getcurrtime() > (int)(par->STEP_RATE*i) && !(mp1[i]->getMemberNode()->bFailed) ) {
			mp1[i]->nodeLoop();
			#ifdef DEBUGLOG
			if( (i == 0) && (par->globaltime % 500 == 0) ) {
				log->LOG(&mp1[i]->getMemberNode()->addr, "@@time=%d", par->getcurrtime());
			}
			#endif
		}

	}
}

void Application::fail() {
	int i, removed;

	if( par->DROP_MSG && par->getcurrtime() == 50 ) {
		par->dropmsg = 1;
	}

	if( par->SINGLE_FAILURE && par->getcurrtime() == 100 ) {
		removed = (rand() % par->EN_GPSZ);
		#ifdef DEBUGLOG
		log->LOG(&mp1[removed]->getMemberNode()->addr, "Node failed at time=%d", par->getcurrtime());
		#endif
		mp1[removed]->getMemberNode()->bFailed = true;
	}
	else if( par->getcurrtime() == 100 ) {
		removed = rand() % par->EN_GPSZ/2;
		for ( i = removed; i < removed + par->EN_GPSZ/2; i++ ) {
			#ifdef DEBUGLOG
			log->LOG(&mp1[i]->getMemberNode()->addr, "Node failed at time = %d", par->getcurrtime());
			#endif
			mp1[i]->getMemberNode()->bFailed = true;
		}
	}

	if( par->DROP_MSG && par->getcurrtime() == 300) {
		par->dropmsg=0;
	}

}

Address Application::getjoinaddr(void){
    Address joinaddr;
    joinaddr.init();
    *(int *)(&(joinaddr.addr))=1;
    *(short *)(&(joinaddr.addr[4]))=0;
    return joinaddr;
}
