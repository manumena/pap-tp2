#ifndef PAP_TP2_MAIN_H
#define PAP_TP2_MAIN_H

#include <iostream>      // cout, cin, <<
#include <fstream>       // ifstream, ofstream
#include <iomanip>       // stoi
#include <unistd.h>      // getopt
#include <cstdlib>       // srand, rand
#include <vector>
#include <list>

// Imprimir ayuda por pantalla
void show_help(char* bin_path);

// Funciones principales
void run_solver();
void run_unit_tests();

// Compara dos vectores
template <typename T>
bool compare_vectors(const std::vector<T> v1, const std::vector<T> v2) {
    if (v1.size() != v2.size()) {
        return false;
    } else {
        for (unsigned int i = 0; i < v1.size(); i++) {
            if (v1[i] != v2[i]) {
                return false;
            }
        }
    }
    return true;
}

// Imprime una list
template <typename T>
std::ostream& operator <<(std::ostream& os, const std::list<T>& l) {
    os << "[";
    bool first = true;
    for (typename std::list<T>::const_iterator it = l.begin();
        it != l.end(); ++it)
    {
        if (! first) {
            os << ", ";
        } else {
            first = false;
        }
        os << *it;
    }
    os << "]";
    return os;
}

// Imprime un vector
template <typename T>
std::ostream& operator <<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    bool first = true;
    for (typename std::vector<T>::const_iterator it = v.begin();
        it != v.end(); ++it)
    {
        if (! first) {
            os << ", ";
        } else {
            first = false;
        }
        os << *it;
    }
    os << "]";
    return os;
}

#endif  // PAP_TP2_MAIN_H
