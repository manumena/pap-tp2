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
	if (t == 'A') {
		i >> q.e1; q.e1--;
		i >> q.e2; q.e2--;
		q.type = A;
	} else if (t == 'B') {
		i >> q.c; q.c--;
		q.type = B;
	} else if (t == 'C') {
		i >> q.e1; q.e1--;
		q.type = C;
	}
	return i;
}

// ---------------- Code ---------------- 

vector<int> depth;
vector<int> low;
vector<bool> articulation_point;
vector<bool> bridge;
vector<int> bridge_component_of_node;
vector<int> bridge_component_nodes;
int bridge_component_counter = 0;

void calculate_biconnected_components(Graph& grafo, int v, int d, int parent) {
	depth[v] = d;
	low[v] = d;
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
				if ((v != parent && low[w] >= depth[v]) || (v == parent && children > 1)) {
					articulation_point[v] = true;
				}
				if (low[w] >= depth[w]) {
					bridge[e] = true;
				}
			} else {
				low[v] = min(low[v], depth[w]);
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
				++bridge_component_counter;
				calculate_bridge_components(grafo, w, bridge_component_counter);
			} else {
				calculate_bridge_components(grafo, w, component);
			}
		}
	}
}

int bridges_between_nodes(int src, int dst, int current, Graph& grafo, vector<bool>& aux_visited) {
	aux_visited[current] = true;
	if (current == dst)
		return 0;
	int ans = -1;
	for (list< pair<int, int> >::iterator it = grafo.adjacency[current].begin(); it != grafo.adjacency[current].end(); ++it) {
		pair<int, int> c = *it;
		int e = c.first;
		int w = c.second;
		if (!aux_visited[w]) {
			int rec = bridges_between_nodes(src, dst, w, grafo, aux_visited);
			if (rec != -1) {
				ans = bridge[e] ? rec+1 : rec;
			}
		}
	}
	return ans;
}

void solve_query(Query& query, Graph& grafo) {
	int ans = 0;
	if (query.type == A) {
		vector<bool> aux_visited = vector<bool>(grafo.N, false);
		ans = bridges_between_nodes(query.e1, query.e2, query.e1, grafo, aux_visited);
	} else if (query.type == B) {
		ans = bridge[query.c] ? 1 : 0;
	} else if (query.type == C) {
		ans = bridge_component_nodes[bridge_component_of_node[query.e1]] - 1;
	}
	cout << ans << endl;
}

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

	//Initializers
	depth = vector<int>(grafo.N, -1);
	low = vector<int>(grafo.N, -1);
	articulation_point = vector<bool>(grafo.N, false);
	bridge = vector<bool>(grafo.M, false);
	bridge_component_of_node = vector<int>(grafo.N, -1);
	bridge_component_nodes = vector<int>(grafo.N, 0);

	//Main DFS
	calculate_biconnected_components(grafo, 0, 0, 0);
	calculate_bridge_components(grafo, 0, 0);

	//Handle queries
	for (int i = 0; i < Q; ++i)
		solve_query(queries[i], grafo);
}