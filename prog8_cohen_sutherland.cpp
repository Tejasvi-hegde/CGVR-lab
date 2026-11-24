#include <iostream>
#include <GL/glut.h>
using namespace std;

enum { TOP = 1, BOTTOM = 2, RIGHT = 4, LEFT = 8 };
float xmin, ymin, xmax, ymax;        // clipping window
float vxmin, vymin, vxmax, vymax;    // viewport
int n;
float L[20][4];                      // lines: x0 y0 x1 y1

int code(float x, float y) {
	int c = 0;
	if (y > ymax) c |= TOP;
	if (y < ymin) c |= BOTTOM;
	if (x > xmax) c |= RIGHT;
	if (x < xmin) c |= LEFT;
	return c;
}

void line(float x0, float y0, float x1, float y1) {
	glBegin(GL_LINES);
	glVertex2f(x0, y0); glVertex2f(x1, y1);
	glEnd();
}

void box(float a, float b, float c, float d) {
	glBegin(GL_LINE_LOOP);
	glVertex2f(a, b); glVertex2f(c, b); glVertex2f(c, d); glVertex2f(a, d);
	glEnd();
}

void clip(float x0, float y0, float x1, float y1) {
	int c0 = code(x0, y0), c1 = code(x1, y1);
	while (c0 | c1) {
		if (c0 & c1) return;                          // reject
		int c = c0 ? c0 : c1;                         // an outside end
		float x, y, dx = x1 - x0, dy = y1 - y0;
		if (c & TOP)         { x = x0 + dx * (ymax - y0) / dy; y = ymax; }
		else if (c & BOTTOM) { x = x0 + dx * (ymin - y0) / dy; y = ymin; }
		else if (c & RIGHT)  { y = y0 + dy * (xmax - x0) / dx; x = xmax; }
		else                 { y = y0 + dy * (xmin - x0) / dx; x = xmin; }
		if (c0) { x0 = x; y0 = y; c0 = code(x, y); }
		else    { x1 = x; y1 = y; c1 = code(x, y); }
	}
	float sx = (vxmax - vxmin) / (xmax - xmin);       // window -> viewport
	float sy = (vymax - vymin) / (ymax - ymin);
	glColor3f(0, 0, 1);
	line(vxmin + (x0 - xmin) * sx, vymin + (y0 - ymin) * sy,
	     vxmin + (x1 - xmin) * sx, vymin + (y1 - ymin) * sy);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 1, 0);
	box(xmin, ymin, xmax, ymax);
	box(vxmin, vymin, vxmax, vymax);
	for (int i = 0; i < n; i++) {
		glColor3f(1, 0, 0);
		line(L[i][0], L[i][1], L[i][2], L[i][3]);
		clip(L[i][0], L[i][1], L[i][2], L[i][3]);
	}
	glFlush();
}

int main(int argc, char** argv) {
	cout << "Window xmin ymin xmax ymax: ";
	cin >> xmin >> ymin >> xmax >> ymax;
	cout << "Viewport xmin ymin xmax ymax: ";
	cin >> vxmin >> vymin >> vxmax >> vymax;
	cout << "Number of lines: ";
	cin >> n;
	cout << "Enter x0 y0 x1 y1 for each line:\n";
	for (int i = 0; i < n; i++)
		cin >> L[i][0] >> L[i][1] >> L[i][2] >> L[i][3];

	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cohen Sutherland");
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
	glutDisplayFunc(display);
	glutMainLoop();
}
