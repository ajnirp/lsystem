// Build: g++ barnsley.cpp -lGL -lGLU -lglut
// Run: ./lsystem
// Hit <esc> to exit. B and F to toggle between Barnsley fern and Fractal tree.

#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>

#include <GL/gl.h>
#include <GL/glut.h>

#define WINDOW_SIZE 1000

using namespace std;

typedef unsigned char uchar;

// Globals
int g_window;
string g_draw_data;

struct point {
    double x, y;
    void operator+=(const point& p) { x += p.x; y += p.y; }
};

struct L_system {
    char axiom;
    unordered_map<char, string> rules;
    string contents;

    void iterate(unsigned int n) {
        for (unsigned int i = 0; i < n; i++) {
            step();
        }
    }

    void step() {
        ostringstream buffer;
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

L_system fractal_tree() {
    unordered_map<char, string> rules = {
        {'1', "11"},
        {'0', "1[0]0"}
    };
    return {.axiom='0', .rules=rules, .contents="0"};
}

L_system barnsley_fern() {
    unordered_map<char, string> rules = {
        {'X', "F+[[X]-X]-F[-FX]+X"},
        {'F', "FF"}
    };
    return {.axiom='X', .rules=rules, .contents="X"};
}

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

    stack<pair<point, float>> state;

    for (auto c : g_draw_data) {
        if (c == '1' or c == '0') {
            const point dp = { cos(angle) * k_segment_len, sin(angle) * k_segment_len };
            glBegin(GL_LINES);
            glVertex2f(p.x, p.y);
            glVertex2f(p.x + dp.x, p.y + dp.y);
            glEnd();
            p += dp;
        } else if (c == '[') {
            state.push(make_pair(p, angle));
            angle -= k_delta_angle;
        } else if (c == ']') {
            p = get<0>(state.top());
            angle = get<1>(state.top()) + k_delta_angle;
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

    stack<pair<point, float>> state;

    for (auto c : g_draw_data) {
        if (c == 'F') {
            const point dp = { cos(angle) * k_segment_len, sin(angle) * k_segment_len };
            glBegin(GL_LINES);
            glVertex2f(p.x, p.y);
            glVertex2f(p.x + dp.x, p.y + dp.y);
            glEnd();
            p += dp;
        } else if (c == '[') {
            state.push(make_pair(p, angle));
        } else if (c == ']') {
            p = get<0>(state.top());
            angle = get<1>(state.top());
            state.pop();
        } else if (c == '+') {
            angle += k_delta_angle;
        } else if (c == '-') {
            angle -= k_delta_angle;
        }
    }
}

char g_active_fractal;
L_system g_fractal_t;
L_system g_barnsley;

void display() {
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    if (g_active_fractal == 'f') {
        g_draw_data = g_fractal_t.contents;
        draw_fractal_tree();
    } else if (g_active_fractal == 'b') {
        g_draw_data = g_barnsley.contents;
        draw_barnsley_fern();
    }
    glFlush();
}

void keyboard(uchar key, int x, int y) {
    if (key == 27) {
        glutDestroyWindow(g_window);
    } else if (key == 'b' and g_active_fractal != 'b') {
        g_active_fractal = 'b';
        glutPostRedisplay();
    } else if (key == 'f' and g_active_fractal != 'f') {
        g_active_fractal = 'f';
        glutPostRedisplay();
    }
}

void init() {
    g_active_fractal = 'f';

    g_fractal_t = fractal_tree();
    g_fractal_t.iterate(8);

    g_barnsley = barnsley_fern();
    g_barnsley.iterate(6);
}

int main(int argc, char** argv) {
    init();
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutInitWindowPosition(400, 0);
    g_window = glutCreateWindow("L-systems");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}