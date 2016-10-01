#include "./ej4.h"

/*
**  Exercise 4
**  Problem solver
*/

void run_solver() {
    adj_list g = read_graph(cin);
    vector<query> qs = read_queries(cin);

    vector<bool> result = solve(g, qs);

    for (bool a : result)
        if (a)
            cout << "S" << endl;
        else
            cout << "N" << endl;
}

vector<bool> solve(adj_list& g, vector<query>& qs) {
    vector<size_t> scc_ids = kosaraju(g); // scc_ids[v] = ID of SCC to which v belongs

    vector<bool> result(qs.size());
    auto query_evaluator = [&scc_ids] (query& q) { return scc_ids[q.origin] == scc_ids[q.destination]; };

    transform(qs.begin(), qs.end(), result.begin(), query_evaluator);

    return result;
}

vector<size_t> kosaraju(adj_list& g) {
    size_t n = g.size();

    /* Sequence vertices in decreasing finishing-time order */
    vector<int> scc_sequence(n);
    size_t i = n-1;
    dfs (
        g,
        [&g, &i, &scc_sequence] (int v) { scc_sequence[i--] = v; }, // add each vertex to front of scc_sequence at DFS closing time
        nobehavior // no special behavior for foresting
    );

    /* Transpose graph */
    adj_list g_t(n); // transpose of g
    dfs (
        g,
        [&g, &g_t] (int v) { for (int w : g[v]) g_t[w].push_back(v); }, // for each edge in g, add inverted edge to g_t
        nobehavior // no special behavior for foresting
    );

    /* Discover SCCs */
    vector<size_t> result(n);
    size_t scc_id = 0;
    dfs (
        g_t,
        [&result, &scc_id] (int v) { result[v] = scc_id; }, // assign vertex to current SCC being explored
        [&scc_id] () { scc_id++; } // increment ID for next SCC to be explored
    );

    return result;
}

/*******************************/
/*
    This implementation of DFS accepts callables through parameters "close" and "forest":
        - "close" is called each time a vertex is being closed;
        - "forest" is called each time a tree is begin closed.
*/

template <class ClosingCallable, class ForestingCallable>
void dfs(adj_list& g, ClosingCallable close, ForestingCallable forest) {
    vector<bool> black(g.size());
    for (size_t v = 0; v < black.size(); ++v) {
        if (!black[v]) {
            dfs_single_tree(g, v, black, close);
            forest();
        }
    }
}

template <class ClosingCallable>
void dfs_single_tree(adj_list& g, int root, vector<bool>& black, ClosingCallable close) {
    vector<bool> gray(g.size(), false);
    stack<int> s;

    adj_list g_t(g.size());

    gray[root] = true;
    s.push(root);

    while (!s.empty()) {
        int v = s.top();
        for (int w : g[v]) {
            if (!(gray[w] || black[w])) {
                gray[w] = true;
                s.push(w);
            }
        }
        if (s.top() == v) {
            black[v] = true;
            close(v);
            s.pop();
        }
    }
}

/*******************************/

/* Input processing */

adj_list read_graph(istream& is) {
    size_t a, p;
    int v1, v2;

    is >> a >> p;
    adj_list g(a); // adjacency list

    for (size_t i = 0; i < p; i++) {
        is >> v1 >> v2;
        g[v1-1].push_back(v2-1);
    }
    return g;
}

vector<query> read_queries(istream& is) {
    size_t q;
    int f, t;
    query qry;

    is >> q;

    vector<query> qs(q); // queries

    for (size_t i = 0; i < q; i++) {
        is >> f >> t;
        qry.origin = f-1;
        qry.destination = t-1;
        qs[i] = qry;
    }

    return qs;
}
