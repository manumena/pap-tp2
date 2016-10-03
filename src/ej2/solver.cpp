#include "./ej2.h"

using namespace std;

/*
**  Exercise 2
**  Problem solver
*/

bool is_bounded(const vector<vector<int>>& stock_value_matrix, const int day_count, const int i, const int j) {
	bool bounded = true;

	int d = 0;
	while (bounded && d < day_count) {
		if (stock_value_matrix[i][d] >= stock_value_matrix[j][d]) {
			bounded = false;
		}
		d++;
	}

	return bounded;
}

vector<vector<network_edge>> build_network(const vector<vector<int>>& stock_value_matrix,
		const int stock_count, const int day_count) {
	// build flow network
	vector<vector<network_edge>> network_graph(2*stock_count + 1, vector<network_edge>());

	for (int i = 0; i < stock_count; i++) {
		// add edge from source to node
		network_graph[2*stock_count].push_back(network_edge(2*stock_count, i, 1));
		// add edge between node and those which bound its stock
		for (int j = 0; j < stock_count; j++) {
			if (j != i && is_bounded(stock_value_matrix, day_count, i, j)) {
				network_graph[i].push_back(network_edge(i, j + stock_count, 1));
			}
		}
		// add edge from node to sink
		network_graph[i + stock_count].push_back(network_edge(i + stock_count, 2*stock_count + 1, 1));
	}

	return network_graph;
}

int find_max_flow(vector<vector<network_edge>> network_graph, const int stock_count) {
	bool sink_reachable = true;
	int max_flow = 0;
	stack<int> nodes_to_visit;
	vector<pair<int, int>> flow(2*stock_count + 2, pair<int, int>());
	int current_node;

	// as long as there is an augmented path from source to sink
	while (sink_reachable) {
		sink_reachable = false;
		// start from the source
		nodes_to_visit.push(2*stock_count);
		while (!nodes_to_visit.empty()) {
			current_node = nodes_to_visit.top();
			if (current_node == 2*stock_count + 1) {
				// if we've reached the sink, update residual network
				sink_reachable = true;
				pair<int, int> flow_edge = flow[2*stock_count + 1];
				while (flow_edge.first != 2*stock_count) {
					network_graph[flow_edge.first][flow_edge.second].capacity = 0;
					flow_edge = flow[flow_edge.first];
				}
				network_graph[flow_edge.first][flow_edge.second].capacity = 0;
				max_flow++;
				nodes_to_visit = stack<int>();
			}
			else {
				// otherwise, we continue searching for a path to the sink
				nodes_to_visit.pop();
				for (unsigned int i = 0; i < network_graph[current_node].size(); i++) {
					if (network_graph[current_node][i].capacity > 0) {
						flow[network_graph[current_node][i].dst] = make_pair(current_node, i);
						nodes_to_visit.push(network_graph[current_node][i].dst);
					}
				}
			}
		}
	}
	return max_flow;
}

int min_plots(const vector<vector<int>>& stock_value_matrix, const int stock_count, const int day_count) {
	return stock_count - find_max_flow(build_network(stock_value_matrix, stock_count, day_count), stock_count);
}

void run_solver() {
	int stock_count;
	int day_count;

	// read input

	cin >> stock_count;
	cin >> day_count;

	vector<vector<int>> stock_value_matrix = vector<vector<int>>(stock_count, vector<int>(day_count, 0));

	for (int i = 0; i < stock_count; i++) {
		for (int j = 0; j < day_count; j++) {
			cin >> stock_value_matrix[i][j];
		}
	}

	// write solution

	cout << min_plots(stock_value_matrix, stock_count, day_count);
}
