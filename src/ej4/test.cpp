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
    {CASE_DIR + "vsdd/vsdd.dat", CASE_DIR + "vsdd/vsdd.out"},
    {CASE_DIR + "nsccs/nsccs.dat", CASE_DIR + "nsccs/nsccs.out"}
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

// tests an instance with a directed circuit of size LTEST_MAX_A and LTEST_MAX_Q queries
// being the graph entirely strongly connected, all queries respnoses should be positive
void random_load_test() {
    size_t A = LTEST_MAX_A;
    size_t Q = LTEST_MAX_Q;

    adj_list g(A);
    vector<query> qs;
    qs.reserve(Q);

    for (size_t i = 0; i < A-1; ++i)
        g.at(i).push_back(i+1);
    g.at(A-1).push_back(0);


    unordered_set<pair<v_id, v_id>, pairhash> all_pairs;
    for (size_t i = 0; i < A-1; ++i) {
        for (size_t j = i+1; j < A; ++j) {
            qs.push_back({i,j});
            if (qs.size() >= Q) break;
        }
        if (qs.size() >= Q) break;
    }

    vector<bool> obtained = solve(g, qs);

    // all values in obtained should be true
    ASSERT(accumulate(obtained.cbegin(), obtained.cend(), true, [](bool a, bool b) {return a && b;}));
}

void run_unit_tests() {
    for (test_case_input& c : cases_filenames) {
        auto file_case = [&c] () {
            ifstream input_file(c.input_filename);
            ifstream expected_file(c.expected_filename);

            adj_list input_graph = read_graph(input_file);
            vector<query> input_queries = read_queries(input_file);

            vector<bool> obtained = solve(input_graph, input_queries);

            ASSERT(obtained == read_results(expected_file));
        };
        RUN_TEST(file_case);
    }

    RUN_TEST(random_load_test);
}
