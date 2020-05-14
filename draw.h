#ifndef DRAW_H
#define DRAW_H

#include <cmath>
#include <stack>
#include <utility>

#include <GL/gl.h>
#include <GL/glut.h>

#include "types.h"

typedef unsigned char uchar;

extern std::string g_draw_data;

// Coordinate system explanation: (0, 0) is the window centre. (1, 1) is the top right corner.
void draw_background_gradient(uchar r, uchar g, uchar b) {
    glBegin(GL_QUADS);
    glColor3ub(r, g, b);
    glVertex2f(-1.f, -1.f);
    glVertex2f( 1.f, -1.f);
    glColor3ub(255, 255, 255);
    glVertex2f( 1.f,  1.f);
    glVertex2f(-1.f,  1.f);
    glEnd();
}

void draw_fractal_tree() {
    draw_background_gradient(95, 196, 232);

    glColor3f(0.f, 0.f, 0.f);

    point p = { 0.f, -0.9 };
    const float k_delta_angle = M_PI / 4.0;
    float angle = M_PI / 2.0;
    const double k_segment_len = 0.0075;

    std::stack<std::pair<point, float>> state;

    for (auto c : g_draw_data) {
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

void draw_barnsley_fern() {
    draw_background_gradient(138, 237, 164);

    glColor3f(0.f, 0.f, 0.f);

    point p = { -0.7f, -0.9 };
    const float k_delta_angle = 25 * M_PI / 180.0;
    float angle = (M_PI / 2.0) - k_delta_angle;
    const double k_segment_len = 0.0125f;

    std::stack<std::pair<point, float>> state;

    for (auto c : g_draw_data) {
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

void draw_sierpinski_triangle() {
    draw_background_gradient(250, 149, 77);

    glColor3f(0.f, 0.f, 0.f);

    point p = { -0.95f, -0.9 };
    const float k_delta_angle = -M_PI / 3.0;
    float angle = 0;
    const double k_segment_len = 0.015f;

    for (auto c : g_draw_data) {
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

#endif