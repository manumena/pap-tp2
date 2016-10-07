#include "./ej2.h"
#include "../mini_test.h"

using namespace std;

/*
**  Exercise 2
**  Unit tests
*/

void test_sample_input_1() {
	ifstream input_file;
	input_file.open("test_cases/input_1");

	int stock_count;
	int day_count;

	input_file >> stock_count;
	input_file >> day_count;

	vector<vector<int>> stock_value_matrix = vector<vector<int>>(stock_count, vector<int>(day_count, 0));

	for (int i = 0; i < stock_count; i++) {
		for (int j = 0; j < day_count; j++) {
			input_file >> stock_value_matrix[i][j];
		}
	}

	input_file.close();


	ASSERT_EQ(3, min_plots(stock_value_matrix, stock_count, day_count));
}

void test_sample_input_2() {
	ifstream input_file;
	input_file.open("test_cases/input_2");

	int stock_count;
	int day_count;

	input_file >> stock_count;
	input_file >> day_count;

	vector<vector<int>> stock_value_matrix = vector<vector<int>>(stock_count, vector<int>(day_count, 0));

	for (int i = 0; i < stock_count; i++) {
		for (int j = 0; j < day_count; j++) {
			input_file >> stock_value_matrix[i][j];
		}
	}

	input_file.close();


	ASSERT_EQ(2, min_plots(stock_value_matrix, stock_count, day_count));
}

void test_sample_input_3() {
	ifstream input_file;
	input_file.open("test_cases/input_3");

	int stock_count;
	int day_count;

	input_file >> stock_count;
	input_file >> day_count;

	vector<vector<int>> stock_value_matrix = vector<vector<int>>(stock_count, vector<int>(day_count, 0));

	for (int i = 0; i < stock_count; i++) {
		for (int j = 0; j < day_count; j++) {
			input_file >> stock_value_matrix[i][j];
		}
	}

	input_file.close();


	ASSERT_EQ(1, min_plots(stock_value_matrix, stock_count, day_count));
}

void test_sample_input_4() {
	ifstream input_file;
	input_file.open("test_cases/input_4");

	int stock_count;
	int day_count;

	input_file >> stock_count;
	input_file >> day_count;

	vector<vector<int>> stock_value_matrix = vector<vector<int>>(stock_count, vector<int>(day_count, 0));

	for (int i = 0; i < stock_count; i++) {
		for (int j = 0; j < day_count; j++) {
			input_file >> stock_value_matrix[i][j];
		}
	}

	input_file.close();


	ASSERT_EQ(5, min_plots(stock_value_matrix, stock_count, day_count));
}

void test_single_stock() {
	int stock_count = 1;
	int day_count = 5;

	vector<vector<int>> stock_value_matrix = vector<vector<int>>(1, {34, 23, 3, 342, 4});

	ASSERT_EQ(1, min_plots(stock_value_matrix, stock_count, day_count));
}

void test_no_overlapping_stocks() {
	int stock_count = 4;
	int day_count = 5;

	vector<vector<int>> stock_value_matrix =
		{
			{1, 1, 1, 1, 1},
			{3, 3, 3, 3, 3},
			{2, 2, 2, 2, 2},
			{0, 0, 0, 0, 0}
		};

	ASSERT_EQ(1, min_plots(stock_value_matrix, stock_count, day_count));
}

void test_one_overlapping_stock() {
	int stock_count = 4;
	int day_count = 5;

	vector<vector<int>> stock_value_matrix =
		{
			{1, 1, 1, 1, 1},
			{3, 3, 3, 3, 3},
			{2, 2, 2, 2, 2},
			{0, 1, 2, 3, 4}
		};

	ASSERT_EQ(2, min_plots(stock_value_matrix, stock_count, day_count));
}

void test_two_overlapping_stocks() {
	int stock_count = 4;
	int day_count = 5;

	vector<vector<int>> stock_value_matrix =
		{
			{1, 1, 1, 1, 1},
			{1, 1, 2, 2, 2},
			{3, 3, 3, 3, 3},
			{3, 3, 4, 4, 4}
		};

	ASSERT_EQ(2, min_plots(stock_value_matrix, stock_count, day_count));
}

void test_big_instance_no_overlapping_stocks() {
	int stock_count = 1000;
	int day_count = 100;

	vector<vector<int>> stock_value_matrix = vector<vector<int>>(stock_count, vector<int>(day_count, 0));

	int stock_val = 0;
	for (int i = 0; i < stock_count; i++) {
		for (int j = 0; j < day_count; j++) {
			stock_value_matrix[i][j] = stock_val;
		}
		stock_val++;
	}

	ASSERT_EQ(1, min_plots(stock_value_matrix, stock_count, day_count));
}

void test_big_instance_all_overlapping_stocks() {
	int stock_count = 1000;
	int day_count = 100;

	vector<vector<int>> stock_value_matrix = vector<vector<int>>(stock_count, vector<int>(day_count, 42));

	ASSERT_EQ(stock_count, min_plots(stock_value_matrix, stock_count, day_count));

}

void run_unit_tests() {
	RUN_TEST(test_sample_input_1);
	RUN_TEST(test_sample_input_2);
	RUN_TEST(test_sample_input_3);
	RUN_TEST(test_sample_input_4);
	RUN_TEST(test_single_stock);
	RUN_TEST(test_no_overlapping_stocks);
	RUN_TEST(test_one_overlapping_stock);
	RUN_TEST(test_two_overlapping_stocks);
	RUN_TEST(test_big_instance_no_overlapping_stocks);
	RUN_TEST(test_big_instance_all_overlapping_stocks);
}
