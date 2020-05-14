#ifndef UTIL_H
#define UTIL_H

#include <vector>

#include "systems.h"

struct L_system_selector {
    int index = 0;
    std::vector<L_system*> L_systems;
    void next() { index = (index + 1) % L_systems.size(); }
    void prev() { index = index ? index - 1 : L_systems.size() - 1; }
    void add(L_system* l) { L_systems.push_back(l); }
    L_system* current() { return L_systems[index]; }
};

#endif