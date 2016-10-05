#ifndef PAP_TP2_EJ3_H
#define PAP_TP2_EJ3_H

#include "../main.h"
#include <stack>
#include <algorithm>

using namespace std;

/*
**  Exercise 3
*/

// --------------- Classes ----------------

class Graph {
public:
	Graph() {}
	~Graph() {}

	int N; // #nodes
	int M; // #edges
	vector< list< pair<int, int> > > adjacency; //<edge number, neightbor>

	void addEdge(int i, int v, int w) {
		adjacency[v].push_back(make_pair(i, w));
		adjacency[w].push_back(make_pair(i, v));
	}

	friend istream& operator >>(istream& i, Graph& graph) {
		cin >> graph.N;
		cin >> graph.M;
		graph.adjacency = vector< list< pair<int, int> > >(graph.N, list< pair<int, int> >());
		for (int i = 0; i < graph.M; ++i) {
			int v, w;
			cin >> v; cin >> w;
			graph.addEdge(i, v-1, w-1);
		}
		return i;
	}
};

enum QueryType {A, B, C};

class Query {
public:
	Query() {}
	~Query() {}

	QueryType type;
	int c; // calle
	int e1, e2; // esquinas

	friend istream& operator >>(istream& i, Query& query) {
		char t;
		i >> t;
		if (t == 'A') {
			i >> query.e1; query.e1--;
			i >> query.e2; query.e2--;
			query.type = A;
		} else if (t == 'B') {
			i >> query.c; query.c--;
			query.type = B;
		} else if (t == 'C') {
			i >> query.e1; query.e1--;
			query.type = C;
		}
		return i;
	}
};

// --------------- Functions ----------------

void calculate_biconnected_components(Graph& graph, int v, int d, int parent);
void calculate_bridge_components(Graph& graph, int v, int component);
int bridges_between_nodes(int src, int dst, int current, Graph& graph, vector<bool>& aux_visited);
void solve_query(Query& query, Graph& graph);

#endif // PAP_TP2_EJ3_H
