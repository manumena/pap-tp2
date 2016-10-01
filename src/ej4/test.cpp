#include "./ej4.h"
#include "../mini_test.h"

/*
**  Exercise 4
**  Unit tests
*/

string CASE_DIR = "ej4/cases/";

vector<test_case_input> cases_filenames = {
    {CASE_DIR + "ssd/ssd.dat", CASE_DIR + "ssd/ssd.out"},
    {CASE_DIR + "sss/sss.dat", CASE_DIR + "sss/sss.out"},
    {CASE_DIR + "vsc/vsc.dat", CASE_DIR + "vsc/vsc.out"},
    {CASE_DIR + "vsdc/vsdc.dat", CASE_DIR + "vsdc/vsdc.out"},
    {CASE_DIR + "vsdd/vsdd.dat", CASE_DIR + "vsdd/vsdd.out"}
};

vector<bool> read_results(istream& is) {
    size_t n;
    string a;

    is >> n;

    vector<bool> result(n);
    for (size_t i = 0; i < n; ++i) {
        is >> a;
        result[i] = a == "S";
    }

    return result;
}

void run_unit_tests() {
    for (test_case_input& c : cases_filenames) {
        auto run_case = [&c] () {
            ifstream input_file(c.input_filename);
            ifstream expected_file(c.expected_filename);

            adj_list input_graph = read_graph(input_file);
            vector<query> input_queries = read_queries(input_file);

            vector<bool> obtained = solve(input_graph, input_queries);

            ASSERT(obtained == read_results(expected_file));
        };
        RUN_TEST (run_case);
    }
}
