#ifndef MEMBER_H_
#define MEMBER_H_

#include "stdincludes.h"

class q_elt {
public:
	void *elt;
	int size;
	q_elt(void *elt, int size);
};

class Address {
public:
	char addr[6];
	Address() {}
	Address(const Address &anotherAddress);
	Address& operator =(const Address &anotherAddress);
	bool operator ==(const Address &anotherAddress);
	Address(string address) {
		size_t pos = address.find(":");
		int id = stoi(address.substr(0, pos));
		short port = (short)stoi(address.substr(pos + 1, address.size()-pos-1));
		memcpy(&addr[0], &id, sizeof(int));
		memcpy(&addr[4], &port, sizeof(short));
	}
	string getAddress() {
		int id = 0;
		short port;
		memcpy(&id, &addr[0], sizeof(int));
		memcpy(&port, &addr[4], sizeof(short));
		return to_string(id) + ":" + to_string(port);
	}
	void init() {
		memset(&addr, 0, sizeof(addr));
	}
};

class MemberListEntry {
public:
	int id;
	short port;
	long heartbeat;
	long timestamp;
	MemberListEntry(int id, short port, long heartbeat, long timestamp);
	MemberListEntry(int id, short port);
	MemberListEntry(): id(0), port(0), heartbeat(0), timestamp(0) {}
	MemberListEntry(const MemberListEntry &anotherMLE);
	MemberListEntry& operator =(const MemberListEntry &anotherMLE);
	int getid();
	short getport();
	long getheartbeat();
	long gettimestamp();
	void setid(int id);
	void setport(short port);
	void setheartbeat(long hearbeat);
	void settimestamp(long timestamp);
};

class Member {
public:
	Address addr;
	bool inited;
	bool inGroup;
	bool bFailed;
	int nnb;
	long heartbeat;
	int pingCounter;
	int timeOutCounter;
	vector<MemberListEntry> memberList;
	vector<MemberListEntry>::iterator myPos;
	queue<q_elt> mp1q;
	Member(): inited(false), inGroup(false), bFailed(false), nnb(0), heartbeat(0), pingCounter(0), timeOutCounter(0) {}
	Member(const Member &anotherMember);
	Member& operator =(const Member &anotherMember);
	virtual ~Member() {}
};

#endif
