#include "./ej3.h"
#include "../mini_test.h"

/*
**  Exercise 3
**  Unit tests
*/

extern vector<int> depth;
extern vector<int> low;
extern vector<bool> bridge;
extern vector<int> bridge_component_of_node;
extern vector<int> bridge_component_nodes;
extern int bridge_component_counter;

void solve_with_input(string file_name, vector<int>& query_solution) {
	ifstream input_file;
	input_file.open(file_name);

	//Graph input
	Graph graph = Graph();
	input_file >> graph;

	//Query input
	int Q;
	input_file >> Q;
	vector<Query> queries = vector<Query>(Q, Query());
	for (int i = 0; i < Q; ++i)
		input_file >> queries[i];

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
	for (int i = 0; i < Q; ++i) {
		int ans = 0;
		if (queries[i].type == A) {
			vector<bool> aux_visited = vector<bool>(graph.N, false);
			ans = bridges_between_nodes(queries[i].e1, queries[i].e2, queries[i].e1, graph, aux_visited);
		} else if (queries[i].type == B) {
			ans = bridge[queries[i].c] ? 1 : 0;
		} else if (queries[i].type == C) {
			ans = bridge_component_nodes[bridge_component_of_node[queries[i].e1]] - 1;
		}
		query_solution.push_back(ans);
	}

	input_file.close();
}

void test1(){
	vector<int> query_solution = vector<int>();
	solve_with_input("ej3/cases/example_1",query_solution);
	vector<int> solution = {3,0,0,1,2,0};
	ASSERT(compare_vectors(query_solution, solution));
}

void test2(){
	vector<int> query_solution = vector<int>();
	solve_with_input("ej3/cases/example_2",query_solution);
	vector<int> solution = {0, 2, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 4, 4, 4, 4, 4, 0};
	ASSERT(compare_vectors(query_solution, solution));
}

void test3(){
	vector<int> query_solution = vector<int>();
	solve_with_input("ej3/cases/example_3",query_solution);
	vector<int> solution = vector<int>(1000, 0);
	for (int i=0; i < 1000; ++i)
		solution[i]=i;
	ASSERT(compare_vectors(query_solution, solution));
}

void test4(){
	vector<int> query_solution = vector<int>();
	solve_with_input("ej3/cases/example_4",query_solution);
}

void run_unit_tests() {
	RUN_TEST(test1);
	RUN_TEST(test2);
	RUN_TEST(test3);
	RUN_TEST(test4);
}