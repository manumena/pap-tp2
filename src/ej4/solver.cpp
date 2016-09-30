#include "./ej4.h"

/*
**  Exercise 4
**  Problem solver
*/

auto nobehavior = [](){};

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

// provides possibility of specifying behavior for each closing vertex and each discovered tree
template <class ClosingBehavior, class ForestingBehavior>
void dfs(adj_list& g, ClosingBehavior close, ForestingBehavior foresting, int root = 0) {
    vector<bool> black(g.size());

    int i = 0;
    vector<int> vertex_sequence(g.size());
    generate_n(vertex_sequence.begin(), g.size(), [&i] () {return i++;}); // create vertex range
    swap(vertex_sequence[0], vertex_sequence[root]); // place root at the beginning

    for (int v : vertex_sequence){
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
    // for (int root : scc_sequence) {
    //     dfs(g_t, [&g_t, &result, &scc_id] (int v) { result[v] = scc_id; }, [&scc_id] () { scc_id++; cout << "scc_id " << scc_id << endl;}, root);
    // }

    dfs(g_t, [&result, &scc_id] (int v) { cout << v << " <- " << scc_id << endl; result[v] = scc_id; }, [&scc_id] () { scc_id++; cout << "scc_id " << scc_id << endl;});

    return result;
}

void solve(adj_list& g, vector<query>& qs) {
    vector<size_t> scc_ids = kosaraju(g); // scc_ids[v] = ID of SCC to which v belongs
    cout << scc_ids << endl;
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
