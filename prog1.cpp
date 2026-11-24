#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

int choice;
int xa, ya, xb, yb;   // line from (xa,ya) to (xb,yb)

void drawLine() {
	int dx = abs(xb - xa), dy = abs(yb - ya);
	int sx = xa <= xb ? 1 : -1;
	int sy = ya <= yb ? 1 : -1;
	int x = xa, y = ya;

	glColor3f(0, 0, 1);
	glPointSize(5);
	glBegin(GL_POINTS);
	if (dx > dy) {                      // gentle slope: step in x
		int p = 2 * dy - dx;
		for (int i = 0; i <= dx; i++) {
			glVertex2i(x, y);
			if (p > 0) { y += sy; p += 2 * (dy - dx); }
			else p += 2 * dy;
			x += sx;
		}
	} else {                            // steep slope: step in y
		int p = 2 * dx - dy;
		for (int i = 0; i <= dy; i++) {
			glVertex2i(x, y);
			if (p > 0) { x += sx; p += 2 * (dx - dy); }
			else p += 2 * dx;
			y += sy;
		}
	}
	glEnd();
	glFlush();
}

void mouse(int button, int state, int x, int y) {
	static bool second = false;
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;
	if (!second) { xa = x - 250; ya = 250 - y; }
	else         { xb = x - 250; yb = 250 - y; drawLine(); }
	second = !second;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (choice == 1) drawLine();
	glFlush();
}

int main(int argc, char** argv) {
	cout << "Enter 1 for keyboard, 2 for mouse: ";
	cin >> choice;
	if (choice == 1) {
		cout << "Enter x1 y1 x2 y2: ";
		cin >> xa >> ya >> xb >> yb;
	}
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Bresenham Line");
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-250, 250, -250, 250);

	glutDisplayFunc(display);
	if (choice == 2) glutMouseFunc(mouse);
	glutMainLoop();
}
