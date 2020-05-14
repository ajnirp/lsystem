#ifndef TYPES_H
#define TYPES_H

#include <sstream>
#include <string>
#include <unordered_map>

struct point {
    double x, y;
    void operator+=(const point& p) { x += p.x; y += p.y; }
};

struct L_system {
    char axiom;
    std::unordered_map<char, std::string> rules;
    std::string contents;

    void iterate(unsigned int n) {
        for (unsigned int i = 0; i < n; i++) {
            step();
        }
    }

    void step() {
        std::ostringstream buffer;
        for (auto c : contents) {
            auto itr = rules.find(c);
            if (itr != rules.end()) {
                buffer << itr->second;
            } else {
                buffer << c;
            }
        }
        contents = buffer.str();
    }
};

#endif