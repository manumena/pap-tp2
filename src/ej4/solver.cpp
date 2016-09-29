#include "./ej4.h"

/*
**  Exercise 4
**  Problem solver
*/

template <class ClosingBehavior>
void dfs_with_root(adj_list& g, int root, vector<bool>& black, ClosingBehavior close) {
    vector<bool> gray(g.size(), false);
    stack<int> s;

    adj_list g_t(g.size());

    gray[root] = true;
    s.push(root);

    while (!s.empty()) {
        int v = s.top();
        for (int w : g[v]) {
            if (!gray[w]) {
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

template <class ClosingBehavior>
void dfs(adj_list& g, ClosingBehavior close) {
    vector<bool> black(g.size());
    for (size_t v = 0; v < g.size(); ++v)
        if (!black[v])
            dfs_with_root(g, v, black, close);
}

// adj_list get_inverted(adj_list& g) {
//     adj_list g_t(g.size());
    // dfs_with_root(g, v, black, [&g, &i, &result] (int v) {for (int w : g[v]) {result[--i] = v;} });
// }

vector<size_t> kosaraju(adj_list& g) {
    vector<int> scc_sequence(g.size());
    size_t i = scc_sequence.size()-1;
    dfs(g, [&g, &i, &scc_sequence] (int v) { scc_sequence[i--] = v; }); // ordering by decreasing finishing time according to DFS

    adj_list g_t(g.size()); // transpose of g
    dfs(g, [&g, &g_t] (int v) { for (int w : g[v]) { g_t[w].push_back(v); } });

    cout << "Kosaraju sequence: " << scc_sequence << endl;
    for (auto& l : g_t) for (auto& u : l) u++;
    cout << "Grafo invertido: " << g_t << endl;
    return {};
}

void solve(adj_list& g, vector<query>& qs) {
    vector<size_t> scc_ids = kosaraju(g); // scc_ids[v] = ID of SCC to which v belongs
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
        qs.push_back(qry);
    }

    solve(g, qs);
}
