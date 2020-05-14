#ifndef TYPES_H
#define TYPES_H

#include <cmath>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>

#include <GL/gl.h>
#include <GL/glut.h>

// TODO: figure out where to put this
// Coordinate system explanation: (0, 0) is the window centre. (1, 1) is the top right corner.
void draw_background_gradient(unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_QUADS);
    glColor3ub(r, g, b);
    glVertex2f(-1.f, -1.f);
    glVertex2f( 1.f, -1.f);
    glColor3ub(255, 255, 255);
    glVertex2f( 1.f,  1.f);
    glVertex2f(-1.f,  1.f);
    glEnd();
}

struct point {
    double x, y;
    void operator+=(const point& p) { x += p.x; y += p.y; }
};

struct L_system {
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

    virtual void draw() = 0;
};

struct fractal_tree : public L_system {
    fractal_tree(unsigned int n) {
        rules = {
            {'1', "11"},
            {'0', "1[0]0"}
        };
        contents = "0";
        iterate(n);
    }

    void draw() override {
        draw_background_gradient(95, 196, 232);

        glColor3f(0.f, 0.f, 0.f);

        point p = { 0.0, -0.9 };
        const float k_delta_angle = M_PI / 4.0;
        float angle = M_PI / 2.0;
        const double k_segment_len = 0.0075;

        std::stack<std::pair<point, float>> state;

        for (auto c : contents) {
            if (c == '1' or c == '0') {
                const point dp = { cos(angle) * k_segment_len, sin(angle) * k_segment_len };
                glBegin(GL_LINES);
                glVertex2f(p.x, p.y);
                glVertex2f(p.x + dp.x, p.y + dp.y);
                glEnd();
                p += dp;
            } else if (c == '[') {
                state.push(std::make_pair(p, angle));
                angle -= k_delta_angle;
            } else if (c == ']') {
                p = std::get<0>(state.top());
                angle = std::get<1>(state.top()) + k_delta_angle;
                state.pop();
            }
        }
    }
};

struct barnsley_fern : public L_system {
    barnsley_fern(unsigned int n) {
        rules = {
            {'X', "F+[[X]-X]-F[-FX]+X"},
            {'F', "FF"}
        };
        contents = "X";
        iterate(n);
    }

    void draw() override {
        draw_background_gradient(138, 237, 164);

        glColor3f(0.f, 0.f, 0.f);

        point p = { -0.7, -0.9 };
        const float k_delta_angle = 25 * M_PI / 180.0;
        float angle = (M_PI / 2.0) - k_delta_angle;
        const double k_segment_len = 0.0125f;

        std::stack<std::pair<point, float>> state;

        for (auto c : contents) {
            if (c == 'F') {
                const point dp = { cos(angle) * k_segment_len, sin(angle) * k_segment_len };
                glBegin(GL_LINES);
                glVertex2f(p.x, p.y);
                glVertex2f(p.x + dp.x, p.y + dp.y);
                glEnd();
                p += dp;
            } else if (c == '[') {
                state.push(std::make_pair(p, angle));
            } else if (c == ']') {
                p = std::get<0>(state.top());
                angle = std::get<1>(state.top());
                state.pop();
            } else if (c == '+') {
                angle += k_delta_angle;
            } else if (c == '-') {
                angle -= k_delta_angle;
            }
        }
    }
};

struct sierpinski_triangle : public L_system {
    sierpinski_triangle(unsigned int n) {
        rules = {
            {'A', "B-A-B"},
            {'B', "A+B+A"}
        };
        contents = "A";
        iterate(n);
    }

    void draw() override {
        draw_background_gradient(250, 149, 77);

        glColor3f(0.f, 0.f, 0.f);

        point p = { -0.95, -0.9 };
        const float k_delta_angle = -M_PI / 3.0;
        float angle = 0;
        const double k_segment_len = 0.015f;

        for (auto c : contents) {
            if (c == 'A' or c == 'B') {
                const point dp = { cos(angle) * k_segment_len, sin(angle) * k_segment_len };
                glBegin(GL_LINES);
                glVertex2f(p.x, p.y);
                glVertex2f(p.x + dp.x, p.y + dp.y);
                glEnd();
                p += dp;
            } else if (c == '+') {
                angle += k_delta_angle;
            } else if (c == '-') {
                angle -= k_delta_angle;
            }
        }
    }
};

struct hexagonal_gosper_curve : public L_system {
    hexagonal_gosper_curve(unsigned int n) {
        rules = {
            {'A', "A+B++B-A--AA-B+"},
            {'B', "-A+BB++B+A--A-B"}
            // Notice how the two lines complement each other if you reverse one of them
        };
        contents = "A";
        iterate(n);
    }

    void draw() override {
        draw_background_gradient(201, 131, 242);

        glColor3f(0.f, 0.f, 0.f);

        point p = { 0.3, 0.7 };
        const float k_delta_angle = -M_PI / 3.0;
        float angle = 0;
        const double k_segment_len = 0.03f;

        for (auto c : contents) {
            if (c == 'A' or c == 'B') {
                const point dp = { cos(angle) * k_segment_len, sin(angle) * k_segment_len };
                glBegin(GL_LINES);
                glVertex2f(p.x, p.y);
                glVertex2f(p.x + dp.x, p.y + dp.y);
                glEnd();
                p += dp;
            } else if (c == '+') {
                angle += k_delta_angle;
            } else if (c == '-') {
                angle -= k_delta_angle;
            }
        }
    }
};

#endif