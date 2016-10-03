#ifndef PAP_TP2_EJ2_H
#define PAP_TP2_EJ2_H

#include "../main.h"
#include <stack>
#include <utility>

/*
**  Exercise 2
*/

// Here go declarations of functions which are exported by the problem solver,
// global variables, etc.

struct network_edge {
	int src;
	int dst;
	int capacity;
	network_edge(int src, int dst, int capacity) {
		this->src = src;
		this->dst = dst;
		this->capacity = capacity;
	}
};

#endif // PAP_TP2_EJ2_H
