#include "./ej4.h"

/*
**  Exercise 4
**  Problem solver
*/

void run_solver() {
    size_t a, p, q;
    int v1, v2, f, t;
    query qry;

    cin >> a >> p;
    vector<vector<int>> g(a); // adjacency list

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

    // cout << g << endl;
}
