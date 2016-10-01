#include "./ej4.h"
#include "../mini_test.h"

/*
**  Exercise 4
**  Unit tests
*/

struct test_case_input {
    string input_filename;
    string expected_filename;
};

vector<test_case_input> cases_filenames = {
    {"ej4/cases/ssd/ssd.dat", "ej4/cases/ssd/ssd.out"},
    {"ej4/cases/sss/sss.dat", "ej4/cases/sss/sss.out"},
    {"ej4/cases/vsc/vsc.dat", "ej4/cases/vsc/vsc.out"},
    {"ej4/cases/vsdc/vsdc.dat", "ej4/cases/vsdc/vsdc.out"},
    {"ej4/cases/vsdd/vsdd.dat", "ej4/cases/vsdd/vsdd.out"}
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
