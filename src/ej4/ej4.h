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

typedef size_t scc_id;
typedef size_t v_id;

struct query {
    v_id origin, destination;
};

typedef vector<vector<v_id>> adj_list;


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
adj_list read_graph(istream&);
vector<query> read_queries(istream&);
vector<bool> read_results(istream&);
/*************/

/* For Testing */

struct test_case_input {
    string input_filename;
    string expected_filename;
};

#endif // PAP_TP2_EJ4_H
