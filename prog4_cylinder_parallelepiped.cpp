#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

int xc, yc, r;

void circle(int x, int y) {
	glBegin(GL_POINTS);
	for (float t = 0; t < 6.3; t += .01)
		glVertex2f(x + r * cos(t), y + r * sin(t));
	glEnd();
}

void rectangle(int x, int y) {       // square of side 2r
	glBegin(GL_LINE_LOOP);
	glVertex2i(x - r, y - r); glVertex2i(x + r, y - r);
	glVertex2i(x + r, y + r); glVertex2i(x - r, y + r);
	glEnd();
}

void cylinder() {                    // stack of circles
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	for (int i = 0; i < 100; i++) circle(xc, yc + i);
	glFlush();
}

void parallelepiped() {              // stack of shifted rectangles
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	for (int i = 0; i < 100; i++) rectangle(xc + i / 2, yc + i);
	glFlush();
}

void init() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
	cout << "Enter xc yc radius: ";
	cin >> xc >> yc >> r;
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);

	glutInitWindowPosition(50, 100);
	glutCreateWindow("Cylinder");
	glutDisplayFunc(cylinder);
	init();

	glutInitWindowPosition(600, 100);
	glutCreateWindow("Parallelepiped");
	glutDisplayFunc(parallelepiped);
	init();

	glutMainLoop();
}
