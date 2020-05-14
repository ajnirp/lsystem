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
char g_active_fractal;
L_system g_fractal_tree;
L_system g_barnsley_fern;
L_system g_sierpinski_triangle;

void display() {
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    if (g_active_fractal == 'f') {
        g_draw_data = g_fractal_tree.contents;
        draw_fractal_tree();
    } else if (g_active_fractal == 'b') {
        g_draw_data = g_barnsley_fern.contents;
        draw_barnsley_fern();
    } else if (g_active_fractal == 's') {
        g_draw_data = g_sierpinski_triangle.contents;
        draw_sierpinski_triangle();
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
    } else if (key == 's' and g_active_fractal != 's') {
        g_active_fractal = 's';
        glutPostRedisplay();
    }
}

void init() {
    g_active_fractal = 'f';

    g_fractal_tree = fractal_tree();
    g_fractal_tree.iterate(8);

    g_barnsley_fern = barnsley_fern();
    g_barnsley_fern.iterate(6);

    g_sierpinski_triangle = sierpinski_triangle();
    g_sierpinski_triangle.iterate(7);
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