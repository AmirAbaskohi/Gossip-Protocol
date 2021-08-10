#ifndef QUEUE_H_
#define QUEUE_H_

#include "stdincludes.h"
#include "Member.h"

class Queue {
public:
	Queue() {}
	virtual ~Queue() {}
	static bool enqueue(queue<q_elt> *queue, void *buffer, int size) {
		q_elt element(buffer, size);
		queue->emplace(element);
		return true;
	}
};

#endif
