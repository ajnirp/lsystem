// Build: g++ barnsley.cpp -lGL -lGLU -lglut
// Run: ./lsystem
// Hit <esc> to exit. B and F to toggle between Barnsley fern and Fractal tree.

#include <GL/gl.h>
#include <GL/glut.h>

#include "systems.h"
#include "util.h"

#define WINDOW_SIZE 1000

// Globals
int g_window;
L_system_selector g_L_system_selector;

void display() {
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    g_L_system_selector.current()->draw();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        glutDestroyWindow(g_window);
    }
}

void special_input(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) {
        g_L_system_selector.next();
        glutPostRedisplay();
    } else if (key == GLUT_KEY_LEFT) {
        g_L_system_selector.prev();
        glutPostRedisplay();
    }
}

void init() {
    g_L_system_selector.add(new fractal_tree(8));
    g_L_system_selector.add(new barnsley_fern(6));
    g_L_system_selector.add(new sierpinski_triangle(7));
    g_L_system_selector.add(new hexagonal_gosper_curve(4));
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