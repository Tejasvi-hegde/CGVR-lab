#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

int choice;
int xc, yc, r;

void plot8(int x, int y) {   // plot the point in all 8 octants
	glVertex2i(xc + x, yc + y); glVertex2i(xc - x, yc + y);
	glVertex2i(xc + x, yc - y); glVertex2i(xc - x, yc - y);
	glVertex2i(xc + y, yc + x); glVertex2i(xc - y, yc + x);
	glVertex2i(xc + y, yc - x); glVertex2i(xc - y, yc - x);
}

void drawCircle() {
	int x = 0, y = r, d = 3 - 2 * r;
	glColor3f(0, 1, 0);
	glPointSize(3);
	glBegin(GL_POINTS);
	while (x <= y) {
		plot8(x, y);
		if (d < 0) d += 4 * x + 6;
		else { d += 4 * (x - y) + 10; y--; }
		x++;
	}
	glEnd();
	glFlush();
}

void mouse(int button, int state, int x, int y) {
	static bool second = false;
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;
	if (!second) { xc = x - 250; yc = 250 - y; }               // 1st click = centre
	else { r = hypot(x - 250 - xc, 250 - y - yc); drawCircle(); } // 2nd click = edge
	second = !second;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (choice == 1) drawCircle();
	glFlush();
}

int main(int argc, char** argv) {
	cout << "Enter 1 for keyboard, 2 for mouse: ";
	cin >> choice;
	if (choice == 1) {
		cout << "Enter xc yc r: ";
		cin >> xc >> yc >> r;
	}
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Bresenham Circle");
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-250, 250, -250, 250);

	glutDisplayFunc(display);
	if (choice == 2) glutMouseFunc(mouse);
	glutMainLoop();
}
