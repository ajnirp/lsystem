#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <unordered_map>

#include "types.h"

struct l_system_selector {
    int index = 0;
    int num_fractals;
    void next() { index = (index + 1) % num_fractals; }
    void prev() { index = index ? index - 1 : num_fractals - 1; }
};

L_system fractal_tree() {
    std::unordered_map<char, std::string> rules = {
        {'1', "11"},
        {'0', "1[0]0"}
    };
    return {.axiom='0', .rules=rules, .contents="0"};
}

L_system barnsley_fern() {
    std::unordered_map<char, std::string> rules = {
        {'X', "F+[[X]-X]-F[-FX]+X"},
        {'F', "FF"}
    };
    return {.axiom='X', .rules=rules, .contents="X"};
}

L_system sierpinski_triangle() {
    std::unordered_map<char, std::string> rules = {
        {'A', "B-A-B"},
        {'B', "A+B+A"}
    };
    return {.axiom='A', .rules=rules, .contents="A"};
}

L_system hexagonal_gosper_curve() {
    std::unordered_map<char, std::string> rules = {
        {'A', "A+B++B-A--AA-B+"},
        {'B', "-A+BB++B+A--A-B"}
        // Notice how the two lines complement each other if you reverse one of them
    };
    return {.axiom='A', .rules=rules, .contents="A"};
}

#endif