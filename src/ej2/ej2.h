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

int min_plots(const std::vector<std::vector<int>>& stock_value_matrix, const int stock_count, const int day_count);

#endif // PAP_TP2_EJ2_H
