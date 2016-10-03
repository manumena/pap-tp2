#ifndef PAP_TP2_EJ4_H
#define PAP_TP2_EJ4_H

#include "../main.h"
#include <utility>
#include <stack>
#include <algorithm>
#include <utility>
#include <functional>
#include <unordered_set>
#include <numeric>

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
void dfs_single_tree(adj_list& g, v_id root, vector<bool>& black, ClosingBehavior close);

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

#define LTEST_MAX_A 10000
#define LTEST_MAX_P 100000
#define LTEST_MAX_Q 100000

struct test_case_input {
    string input_filename;
    string expected_filename;
};

struct pairhash {
public:
    template <typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

#endif // PAP_TP2_EJ4_H
