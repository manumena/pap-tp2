#include "./ej4.h"

/*
**  Exercise 4
**  Problem solver
*/

template <class ClosingBehavior>
void dfs_single_tree(adj_list& g, int root, vector<bool>& black, ClosingBehavior close) {
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

// provides possibility of specifying behavior for each closing vertex and each discovered tree
template <class ClosingBehavior, class ForestingBehavior>
void dfs(adj_list& g, ClosingBehavior close, ForestingBehavior foresting) {
    vector<bool> black(g.size());

    for (size_t v = 0; v < black.size(); ++v) {
        if (!black[v]) {
            dfs_single_tree(g, v, black, close);
            foresting();
        }
    }
}


vector<size_t> kosaraju(adj_list& g) {
    size_t n = g.size();

    vector<int> scc_sequence(n);
    size_t i = n-1;
    dfs(g, [&g, &i, &scc_sequence] (int v) { scc_sequence[i--] = v; }, nobehavior); // ordering by decreasing finishing time according to DFS

    adj_list g_t(n); // transpose of g
    dfs(g, [&g, &g_t] (int v) { for (int w : g[v]) { g_t[w].push_back(v); } }, nobehavior);

    vector<size_t> result(n);
    size_t scc_id = 0;
    dfs(g_t, [&result, &scc_id] (int v) { result[v] = scc_id; }, [&scc_id] () { scc_id++; });

    return result;
}

void solve(adj_list& g, vector<query>& qs) {
    vector<size_t> scc_ids = kosaraju(g); // scc_ids[v] = ID of SCC to which v belongs

    for (query q : qs)
        if (scc_ids[q.origin] == scc_ids[q.destination])
            cout << "S" << endl;
        else
            cout << "N" << endl;
}

void run_solver() {
    size_t a, p, q;
    int v1, v2, f, t;
    query qry;

    cin >> a >> p;
    adj_list g(a); // adjacency list

    for (size_t i = 0; i < p; i++) {
        cin >> v1 >> v2;
        g[v1-1].push_back(v2-1);
    }

    cin >> q;
    vector<query> qs(q); // queries

    for (size_t i = 0; i < q; i++) {
        cin >> f >> t;
        qry.origin = f-1;
        qry.destination = t-1;
        qs[i] = qry;
    }

    solve(g, qs);
}
