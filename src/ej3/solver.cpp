#include "./ej3.h"

/*
**  Exercise 3
**  Problem solver
*/

// ---------------- Classes ---------------- 

class Graph {
public:
	Graph(int N, int M);
	~Graph() {}

	int N; // #nodes
	int M; // #edges
	vector< list<int> > edges;

	void addEdge(int n1, int n2);
};

Graph::Graph(int N, int M) {
	this->N = N;
	this->M = M;
	this->edges = vector< list<int> >(N, list<int>());
}

void Graph::addEdge(int n1, int n2) {
	edges[n1].push_back(n2);
	edges[n2].push_back(n1);
}

enum QueryType {A, B, C};
class Query {
public:
	Query() {}
	~Query() {}

	QueryType type;
	int c; // calle
	int e1, e2; // esquinas
};

istream& operator>>(istream& i, Query& q) {
	char t;
	i >> t;
	if (t == 'A') {
		i >> q.e1; i >> q.e2; q.type = A;
	} else if (t == 'B') {
		i >> q.c; q.type = B;
	} else if (t == 'C')  {
		i >> q.e1; q.type = C;
	}
	return i;
}

// ---------------- Code ---------------- 

void run_solver() {
	int N,M;
	cin >> N; cin >> M;
	Graph grafo = Graph(N, M);
	for (int i = 0; i < M; ++i) {
		int n1, n2;
		cin >> n1; cin >> n2;
		grafo.addEdge(n1, n2);
	}

	int Q;
	cin >> Q;
	vector<Query> queries = vector<Query>(Q, Query());
	for (int i = 0; i < Q; ++i)
		cin >> queries[i];

}