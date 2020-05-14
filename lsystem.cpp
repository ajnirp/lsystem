// Build: g++ barnsley.cpp -lGL -lGLU -lglut
// Run: ./lsystem
// hit <esc> to exit

#include <cmath>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>

#include <GL/gl.h>
#include <GL/glut.h>

#define WINDOW_SIZE 900
#define SEGMENT_LEN 0.005

using namespace std;

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
void draw_fractal_tree(const string& draw_data) {
    glColor3f(0.f, 0.f, 0.f);

    point p = { 0.f, -0.9 };
    float angle = M_PI / 2.0;

    stack<pair<point, float>> s;

    for (auto c : draw_data) {
        if (c == '1' or c == '0') {
            const point dp = { cos(angle) * SEGMENT_LEN, sin(angle) * SEGMENT_LEN };
            glBegin(GL_LINES);
            glVertex2f(p.x, p.y);
            glVertex2f(p.x + dp.x, p.y + dp.y);
            glEnd();
            p += dp;
        } else if (c == '[') {
            s.push(make_pair(p, angle));
            angle -= M_PI / 4.0;
        } else if (c == ']') {
            p = get<0>(s.top());
            angle = get<1>(s.top()) + (M_PI / 4.0);
            s.pop();
        }
    }
}

// TODO
void draw_barnsley_fern() {}

void display() {
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_fractal_tree(g_draw_data);
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        glutDestroyWindow(g_window);
    }
}

int main(int argc, char** argv) {
    L_system fractal_t = fractal_tree();
    fractal_t.iterate(8);
    g_draw_data = fractal_t.contents;

    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutInitWindowPosition(400, 0);
    g_window = glutCreateWindow("Barnsley");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}