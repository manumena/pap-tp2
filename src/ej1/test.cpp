#include "./ej1.h"
#include "../mini_test.h"

/*
**  Exercise 1
**  Unit tests
*/

#define SOURCE 	0
#define SINK 	1

vector<list<int>> readInput(string path) {
	ifstream input_file;
	input_file.open(path);

	int n, m;
	input_file >> n >> m;

	vector<list<int>> network(2 * n + 2);

	for(int corner = 1; corner <= n; corner++) {
		int in = 2 * corner;
		int out = in + 1;

		char type;
		input_file >> type;

		switch(type) {
			case 'A':
				network[SOURCE].push_back(in);
				break;
			case 'E':
				network[out].push_back(SINK);
				break;
		}

		network[in].push_back(out);
	}

	for(int edges = 0; edges < m; edges++) {
		// The edges are indexed from 1
		int corner1, corner2;
		input_file >> corner1 >> corner2;

		int in1 = 2 * corner1;
		int in2 = 2 * corner2;
		int out1 = in1 + 1;
		int out2 = in2 + 1;

		network[out1].push_back(in2);
		network[out2].push_back(in1);
	}

	input_file.close();

	return network;
}

void test_simple_path() {
	ASSERT_EQ(1, maxFlow(readInput("ej1/test_cases/simple_path")));
}

void test_topknot() {
	ASSERT_EQ(1, maxFlow(readInput("ej1/test_cases/topknot")));
}

void test_double_path() {
	ASSERT_EQ(2, maxFlow(readInput("ej1/test_cases/double_path")));
}

void test_one_house() {
	ASSERT_EQ(1, maxFlow(readInput("ej1/test_cases/one_house")));
}

void test_one_school() {
	ASSERT_EQ(1, maxFlow(readInput("ej1/test_cases/one_school")));
}

void test_big() {
	ASSERT_EQ(2, maxFlow(readInput("ej1/test_cases/big")));
}

void test_big2() {
	ASSERT_EQ(3, maxFlow(readInput("ej1/test_cases/big2")));
}

void test_example1() {
	ASSERT_EQ(1, maxFlow(readInput("ej1/test_cases/example1")));
}

void test_example2() {
	ASSERT_EQ(1, maxFlow(readInput("ej1/test_cases/example2")));
}

void test_example3() {
	ASSERT_EQ(2, maxFlow(readInput("ej1/test_cases/example3")));
}

void test_example4() {
	ASSERT_EQ(1, maxFlow(readInput("ej1/test_cases/example4")));
}

void run_unit_tests() {
	RUN_TEST(test_simple_path);
	RUN_TEST(test_topknot);
	RUN_TEST(test_double_path);
	RUN_TEST(test_one_house);
	RUN_TEST(test_one_school);
	RUN_TEST(test_big);
	RUN_TEST(test_big2);
	RUN_TEST(test_example1);
	RUN_TEST(test_example2);
	RUN_TEST(test_example3);
	RUN_TEST(test_example4);
}