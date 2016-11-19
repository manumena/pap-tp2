#include "./ej2.h"

using namespace std;

/*
**  Exercise 2
**  Problem solver
*/

#define SOURCE  0
#define SINK    1

list<int> from_path(const vector<int> &previous, const int initial_node, const int final_node) {
	list<int> path;

	int current = final_node;
	while (current != initial_node) {
		path.push_front(current);
		current = previous[current];
	}
	path.push_front(initial_node);

	return path;
}

list<int> bfs(const vector<list<int>> &graph, const int initial_node, const int final_node) {
	int n = graph.size();
	vector<int> previous(n);
	bool valid = false;

	vector<bool> visited(n, false);
	visited[initial_node] = true;

	queue<int> pending;
	pending.push(initial_node);

	int current;
	while (!pending.empty()) {

		current = pending.front();
		pending.pop();

		if(current == final_node)
			valid = true;

		for (list<int>::const_iterator it = graph[current].begin(); it != graph[current].end(); it++) {
			if(!visited[*it]){
				visited[*it] = true;
				pending.push(*it);
				previous[*it] = current;
			}
		}
	}

	if(valid)
		return from_path(previous, initial_node, final_node);
	else
		return list<int>();
}

void augment_path(vector<list<int>> &network, const list<int> path) {
	list<int>::const_iterator it_current = path.begin();
	list<int>::const_iterator it_next = path.begin();
	it_next++;
	while (it_next != path.end()) {
		int from = *it_current;
		int to = *it_next;

		// This can be done only because all capacities are 1
		network[from].remove(to);
		network[to].push_back(from);

		it_current++;
		it_next++;
	}
}

int max_flow(vector<list<int>> network) {
	list<int> path = bfs(network, SOURCE, SINK);
	int flow = 0;
	while (!path.empty()) {
		augment_path(network, path);
		path = bfs(network, SOURCE, SINK);
		flow++;
	}
	return flow;
}

// is 'i' bounded by 'j'
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

vector<list<int>> build_network(const vector<vector<int>>& stock_value_matrix,
		const int stock_count, const int day_count) {
	// build flow network
	vector<list<int>> network_graph(2 * stock_count + 2);

	// first two nodes are SOURCE and SINK
	int first_partition_offset = 2;
	int second_partition_offset = stock_count + 2;

	for (int i = 0; i < stock_count; i++) {
		// add edge from source to node
		network_graph[SOURCE].push_back(i + first_partition_offset);
		// add edge between node and those which bound its stock
		for (int j = 0; j < stock_count; j++) {
			if (j != i && is_bounded(stock_value_matrix, day_count, i, j)) {
				network_graph[i + 2].push_back(j + second_partition_offset);
			}
		}
		// add edge from node to sink
		network_graph[i + second_partition_offset].push_back(SINK);
	}

	return network_graph;
}

int min_plots(const vector<vector<int>>& stock_value_matrix, const int stock_count, const int day_count) {
	return stock_count - max_flow(build_network(stock_value_matrix, stock_count, day_count));
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
