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
    vector<scc_id> scc_ids = kosaraju(g); // scc_ids[v] = ID of SCC to which v belongs

    vector<bool> result(qs.size());
    auto query_evaluator = [&scc_ids] (query& q) { return scc_ids[q.origin] == scc_ids[q.destination]; };

    transform(qs.begin(), qs.end(), result.begin(), query_evaluator);

    return result;
}

vector<scc_id> kosaraju(adj_list& g) {
    size_t n = g.size();

    /* Sequence vertices in decreasing finishing-time order */
    vector<v_id> kos_sequence(n);
    size_t i = n-1;
    dfs (
        g,
        [&g, &i, &kos_sequence] (v_id v) { kos_sequence[i--] = v; }, // add each vertex to front of kos_sequence at DFS closing time
        nobehavior // no special behavior for foresting
    );

    /* Transpose graph */
    adj_list g_t(n); // transpose of g
    dfs (
        g,
        [&g, &g_t] (v_id v) { for (v_id w : g[v]) g_t[w].push_back(v); }, // for each edge in g, add inverted edge to g_t
        nobehavior // no special behavior for foresting
    );

    /* Discover SCCs */
    vector<scc_id> result(n);
    scc_id id = 0;
    dfs (
        g_t,
        [&result, &id] (v_id v) { result[v] = id; }, // assign vertex to current SCC being explored
        [&id] () { id++; } // increment ID for next SCC to be explored
    );

    return result;
}

/*******************************/
/*
    This implementation of DFS accepts callables through parameters "close_vertex" and "close_tree":
        - "close_vertex" is called each time a vertex is being closed;
        - "close_tree" is called each time a tree is begin closed.
*/

template <class VertexClosingCallable, class TreeClosingCallable>
void dfs(adj_list& g, VertexClosingCallable close_vertex, TreeClosingCallable close_tree) {
    vector<bool> black(g.size());
    for (v_id v = 0; v < black.size(); ++v) {
        if (!black[v]) {
            dfs_single_tree(g, v, black, close_vertex);
            close_tree();
        }
    }
}

template <class VertexClosingCallable>
void dfs_single_tree(adj_list& g, v_id root, vector<bool>& black, VertexClosingCallable close_vertex) {
    vector<bool> gray(g.size(), false);
    stack<v_id> s;

    gray[root] = true;
    s.push(root);

    while (!s.empty()) {
        v_id v = s.top();
        for (v_id w : g[v]) {
            if (!(gray[w] || black[w])) {
                gray[w] = true;
                s.push(w);
            }
        }
        if (s.top() == v) {
            black[v] = true;
            close_vertex(v);
            s.pop();
        }
    }
}

/*******************************/

/* Input processing */

adj_list read_graph(istream& is) {
    size_t a, p;
    v_id v1, v2;

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
    v_id f, t;
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

// MAIN

enum mode {solver, test};

int main (int argc, char* argv[]) {
    // Configuración de la ejecución
    mode exec_mode = solver;

    // Parsea las opciones recibidas
    char opt;
    while ((opt = getopt(argc, argv, "ht")) != -1) {
        switch (opt) {
            case 'h': { // mostrar ayuda
                show_help(argv[0]);
                exit(0);
                break;
            }
            case 't': { // correr tests unitarios
                exec_mode = test;
                break;
            }
            default: { // si las opciones son inválidas
                show_help(argv[0]);
                exit(1);
                break;
            }
        }
    }

    if (exec_mode == solver) {
        run_solver();
    }
    else if (exec_mode == test) {
        run_unit_tests();
    }
}

// Imprime por pantalla un texto de ayuda
void show_help(char* bin_path) {
    cout << "  Modo de uso: " << setw(12) << bin_path << endl;
    cout << endl;
    cout << "  Los parámetros se reciben a través de la entrada estándar." << endl;
    cout << endl;
    cout << "  Opciones:" << endl;
    cout << "    -h          Muestra este texto de ayuda" << endl;
    cout << "    -t          Ejecuta los tests unitarios provistos para el algoritmo" << endl;
}
