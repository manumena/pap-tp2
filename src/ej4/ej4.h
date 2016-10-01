#ifndef PAP_TP2_EJ4_H
#define PAP_TP2_EJ4_H

#include "../main.h"
#include <utility>
#include <stack>
#include <algorithm>
#include <utility>

using namespace std;

/*
**  Exercise 4
*/

struct query {
    int origin, destination;
};

typedef vector<vector<int>> adj_list;


/* For DFS */
auto nobehavior = [](){};

template <class ClosingBehavior, class ForestingBehavior>
void dfs(adj_list&, ClosingBehavior, ForestingBehavior);

template <class ClosingBehavior>
void dfs_single_tree(adj_list& g, int root, vector<bool>& black, ClosingBehavior close);

/*************/

vector<size_t> kosaraju(adj_list& g);
vector<bool> solve(adj_list& g, vector<query>& qs);
void run_solver();

/*************/

/* For Input*/
adj_list read_graph();
vector<query> read_queries();

#endif // PAP_TP2_EJ4_H
