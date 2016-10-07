#include "./ej3.h"

/*
**  Exercise 3
**  Problem solver
*/

// --------------- Global Variables ----------------

vector<int> depth;
vector<int> low;
vector<bool> bridge;
vector<int> bridge_component_of_node;
vector<int> bridge_component_nodes;
int bridge_component_counter;

// -------------------- Code -----------------------

void run_solver() {
	//Graph input
	Graph graph = Graph();
	cin >> graph;

	//Query input
	int Q;
	cin >> Q;
	vector<Query> queries = vector<Query>(Q, Query());
	for (int i = 0; i < Q; ++i)
		cin >> queries[i];

	//Global variable initializers
	depth = vector<int>(graph.N, -1);
	low = vector<int>(graph.N, -1);
	bridge = vector<bool>(graph.M, false);
	bridge_component_of_node = vector<int>(graph.N, -1);
	bridge_component_nodes = vector<int>(graph.N, 0);
	bridge_component_counter = 0;

	//Main DFS
	calculate_bridges(graph, 0, 0, 0);
	calculate_bridge_components(graph, 0, 0);

	//Handle queries
	for (int i = 0; i < Q; ++i)
		solve_query(queries[i], graph);
}

void calculate_bridges(Graph& graph, int v, int d, int parent) {
	depth[v] = d;
	low[v] = d;
	for (list< pair<int, int> >::iterator it = graph.adjacency[v].begin(); it != graph.adjacency[v].end(); ++it) {
		pair<int, int> c = *it;
		int e = c.first;
		int w = c.second;
		if (w != parent) {
			if (depth[w] == -1) {
				calculate_bridges(graph, w, d+1, v);
				low[v] = min(low[v], low[w]);
				if (low[w] >= depth[w]) {
					bridge[e] = true;
				}
			} else {
				low[v] = min(low[v], depth[w]);
			}
		}
	}
}

void calculate_bridge_components(Graph& graph, int v, int component) {
	bridge_component_of_node[v] = component;
	++bridge_component_nodes[component];
	for (list< pair<int, int> >::iterator it = graph.adjacency[v].begin(); it != graph.adjacency[v].end(); ++it) {
		pair<int, int> c = *it;
		int e = c.first;
		int w = c.second;
		if (bridge_component_of_node[w] == -1) {
			if (bridge[e]) {
				++bridge_component_counter;
				calculate_bridge_components(graph, w, bridge_component_counter);
			} else {
				calculate_bridge_components(graph, w, component);
			}
		}
	}
}

int bridges_between_nodes(int src, int dst, int current, Graph& graph, vector<bool>& aux_visited) {
	aux_visited[current] = true;
	if (current == dst)
		return 0;
	int ans = -1;
	for (list< pair<int, int> >::iterator it = graph.adjacency[current].begin(); it != graph.adjacency[current].end(); ++it) {
		pair<int, int> c = *it;
		int e = c.first;
		int w = c.second;
		if (!aux_visited[w]) {
			int rec = bridges_between_nodes(src, dst, w, graph, aux_visited);
			if (rec != -1) {
				ans = bridge[e] ? rec+1 : rec;
			}
		}
	}
	return ans;
}

void solve_query(Query& query, Graph& graph) {
	int ans = 0;
	if (query.type == A) {
		vector<bool> aux_visited = vector<bool>(graph.N, false);
		ans = bridges_between_nodes(query.e1, query.e2, query.e1, graph, aux_visited);
	} else if (query.type == B) {
		ans = bridge[query.c] ? 1 : 0;
	} else if (query.type == C) {
		ans = bridge_component_nodes[bridge_component_of_node[query.e1]] - 1;
	}
	cout << ans << endl;
}