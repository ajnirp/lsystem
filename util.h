#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <unordered_map>

#include "types.h"

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

#endif