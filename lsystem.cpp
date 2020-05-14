// Build: g++ barnsley.cpp -lGL -lGLU -lglut
// Run: ./lsystem
// Hit <esc> to exit. B and F to toggle between Barnsley fern and Fractal tree.

#include <cmath>
#include <iostream>
#include <string>

#include <GL/gl.h>
#include <GL/glut.h>

#include "draw.h"
#include "types.h"
#include "util.h"

#define WINDOW_SIZE 1000

typedef unsigned char uchar;

// Globals
int g_window;
std::string g_draw_data;
l_system_selector g_l_system_selector;
L_system g_fractal_tree;
L_system g_barnsley_fern;
L_system g_sierpinski_triangle;
L_system g_hexagonal_gosper_curve;

void display() {
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    if (g_l_system_selector.index == 0) {
        g_draw_data = g_fractal_tree.contents;
        draw_fractal_tree();
    } else if (g_l_system_selector.index == 1) {
        g_draw_data = g_barnsley_fern.contents;
        draw_barnsley_fern();
    } else if (g_l_system_selector.index == 2) {
        g_draw_data = g_sierpinski_triangle.contents;
        draw_sierpinski_triangle();
    } else if (g_l_system_selector.index == 3) {
        g_draw_data = g_hexagonal_gosper_curve.contents;
        draw_hexagonal_gosper_curve();
    }
    glFlush();
}

void keyboard(uchar key, int x, int y) {
    if (key == 27) {
        glutDestroyWindow(g_window);
    }
}

void special_input(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) {
        g_l_system_selector.next();
        glutPostRedisplay();
    } else if (key == GLUT_KEY_LEFT) {
        g_l_system_selector.prev();
        glutPostRedisplay();
    }
}

void init() {
    g_l_system_selector.num_fractals = 4;

    g_fractal_tree = fractal_tree();
    g_fractal_tree.iterate(8);

    g_barnsley_fern = barnsley_fern();
    g_barnsley_fern.iterate(6);

    g_sierpinski_triangle = sierpinski_triangle();
    g_sierpinski_triangle.iterate(7);

    g_hexagonal_gosper_curve = hexagonal_gosper_curve();
    g_hexagonal_gosper_curve.iterate(4);
}

int main(int argc, char** argv) {
    init();
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutInitWindowPosition(400, 0);
    g_window = glutCreateWindow("L-systems");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_input);
    glutMainLoop();

    return 0;
}