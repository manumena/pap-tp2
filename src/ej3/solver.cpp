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
	vector< list< pair<int, int> > > adjacency; //<edge number, neightbor>

	void addEdge(int i, int v, int w);
};

Graph::Graph(int N, int M) {
	this->N = N;
	this->M = M;
	this->adjacency = vector< list< pair<int, int> > >(N, list< pair<int, int> >());
}

void Graph::addEdge(int i, int v, int w) {
	adjacency[v].push_back(make_pair(i, w));
	adjacency[w].push_back(make_pair(i, v));
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
	switch (t) {
		case 'A':
			i >> q.e1; q.e1--;
			i >> q.e2; q.e2--;
			q.type = A;
			break;
		case 'B':
			i >> q.c; q.c--;
			q.type = B;
			break;
		case 'C':
			i >> q.e1;  q.e1--;
			q.type = C;
			break;
	}
	return i;
}

// ---------------- Code ---------------- 

typedef pair<int, int> Edge;

vector<int> depth;
vector<int> low;
vector<bool> articulation_point;
vector<bool> bridge;
vector<int> bridge_component_of_node;
vector<int> bridge_component_nodes;
stack<Edge> pila;

void extract_biconnected_component(int v, int w) {
	while (pila.top() != Edge(v, w) && pila.top() != Edge(w, v)) {
		cout << pila.top().first << "-" << pila.top().second << ", ";
		pila.pop();
	}
	cout << pila.top().first << "-" << pila.top().second << endl;
	pila.pop();
}

void calculate_biconnected_components(Graph& grafo, int v, int d, int parent) {
	depth[v] = d;
	low[v] = d;
	if (v != parent) {
		pila.push(Edge(parent, v));
	}
	int children = 0;
	for (list< pair<int, int> >::iterator it = grafo.adjacency[v].begin(); it != grafo.adjacency[v].end(); ++it) {
		pair<int, int> c = *it;
		int e = c.first;
		int w = c.second;
		if (w != parent) {
			if (depth[w] == -1) {
				++children;
				calculate_biconnected_components(grafo, w, d+1, v);
				low[v] = min(low[v], low[w]);
				if (low[w] >= depth[v]) {
					extract_biconnected_component(v, w);
				}
				if ((v != parent && low[w] >= depth[v]) || (v == parent && children > 1)) {
					articulation_point[v] = true;
				}
				if (low[w] >= depth[w]) {
					bridge[e] = true;
				}
			} else {
				if (depth[w] < low[v]) {
					pila.push(Edge(w, v));
					low[v] = depth[w];
				}
			}
		}
	}
}

void calculate_bridge_components(Graph& grafo, int v, int component) {
	bridge_component_of_node[v] = component;
	++bridge_component_nodes[component];
	for (list< pair<int, int> >::iterator it = grafo.adjacency[v].begin(); it != grafo.adjacency[v].end(); ++it) {
		pair<int, int> c = *it;
		int e = c.first;
		int w = c.second;
		if (bridge_component_of_node[w] == -1) {
			if (bridge[e]) {
				calculate_bridge_components(grafo, w, component+1);
			} else {
				calculate_bridge_components(grafo, w, component);
			}
		}
	}
}

// void solve_query(int i) {
// 	Query query = queries[i];
// 	switch (query.type) {
// 		case A:

// 			break;
// 		case B:
// 			cout << bridge[i] << endl;
// 			break;
// 		case C:

// 			break;
// 	}
// }

void run_solver() {
	//Graph input
	int N,M;
	cin >> N; cin >> M;
	Graph grafo = Graph(N, M);
	for (int i = 0; i < M; ++i) {
		int v, w;
		cin >> v; cin >> w;
		grafo.addEdge(i, v-1, w-1);
	}

	//Query input
	int Q;
	cin >> Q;
	vector<Query> queries = vector<Query>(Q, Query());
	for (int i = 0; i < Q; ++i)
		cin >> queries[i];

	//Main DFS
	depth = vector<int>(grafo.N, -1);
	low = vector<int>(grafo.N, -1);
	articulation_point = vector<bool>(grafo.N, false);
	bridge = vector<bool>(grafo.M, false);
	bridge_component_of_node = vector<int>(grafo.N, -1);
	bridge_component_nodes = vector<int>(grafo.N, 0);
	pila = stack<Edge>();
	calculate_biconnected_components(grafo, 0, 0, 0);
	calculate_bridge_components(grafo, 0, 0);

	// cout << endl;
	// cout << depth << endl;
	// cout << low << endl;
	// cout << articulation_point << endl;
	// cout << bridge << endl;

	cout << endl << "[";
	for (int i = 0; i < N; ++i) {
		cout << bridge_component_nodes[bridge_component_of_node[i]] << ", ";
	}
	cout << "]" << endl;

	//Handle queries
	// for (int i = 0; i < Q; ++i)
	// 	solve_query(i);
}