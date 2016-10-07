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

void update_network_edge(vector<vector<network_edge>>& network_graph, const int src, const int dst) {
	// use full capacity
	network_graph[src][dst].capacity = 0;

	// add capacity to edge going in opposite direction
	unsigned int i = 0;
	while (i < network_graph[dst].size() &&
			network_graph[dst][i].dst != src) {
		i++;
	}

	if (i == network_graph[dst].size()) {
		network_graph[dst].push_back(network_edge(dst, src, 1));
	}
	else {
		network_graph[dst][i].capacity = 1;
	}
}

int find_max_flow(vector<vector<network_edge>> network_graph, const int stock_count) {
	bool sink_reachable = true;
	int max_flow = 0;
	stack<int> nodes_to_visit;
	vector<pair<int, int>> flow(2*stock_count + 2, pair<int, int>());
	vector<bool> visited(2*stock_count + 2, false);
	int current_node;

	// as long as there is an augmented path from source to sink
	while (sink_reachable) {
		sink_reachable = false;
		// start from the source
		nodes_to_visit.push(2*stock_count);
		visited[2*stock_count] = true;
		while (!nodes_to_visit.empty()) {
			current_node = nodes_to_visit.top();
			if (current_node == 2*stock_count + 1) {
				// if we've reached the sink, update residual network
				sink_reachable = true;
				pair<int, int> flow_edge = flow[2*stock_count + 1];
				while (flow_edge.first != 2*stock_count) {
					update_network_edge(network_graph, flow_edge.first, flow_edge.second);
					flow_edge = flow[flow_edge.first];
				}
				update_network_edge(network_graph, flow_edge.first, flow_edge.second);

				max_flow++;
				// reset depth first search variables
				nodes_to_visit = stack<int>();
				visited = vector<bool>(2*stock_count + 2, false);
			}
			else {
				// otherwise, we continue searching for a path to the sink
				nodes_to_visit.pop();
				for (unsigned int i = 0; i < network_graph[current_node].size(); i++) {
					if (network_graph[current_node][i].capacity > 0 && !visited[network_graph[current_node][i].dst]) {
						// if the edge has capacity and dst hasn't been visited
						visited[network_graph[current_node][i].dst] = true;
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
