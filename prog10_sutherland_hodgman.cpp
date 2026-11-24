#include <iostream>
#include <GL/glut.h>
using namespace std;

enum { LEFT, TOP, RIGHT, BOTTOM };
struct Point { float x, y; };

float xmin, ymin, xmax, ymax;
int n;
Point poly[50], clipped[50];

bool inside(Point p, int e) {
	if (e == LEFT)  return p.x >= xmin;
	if (e == RIGHT) return p.x <= xmax;
	if (e == TOP)   return p.y <= ymax;
	return p.y >= ymin;
}

Point cut(Point s, Point p, int e) {         // edge s-p meets boundary e
	float m = (p.y - s.y) / (p.x - s.x);
	if (e == LEFT)  return { xmin, s.y + (xmin - s.x) * m };
	if (e == RIGHT) return { xmax, s.y + (xmax - s.x) * m };
	if (e == TOP)   return { s.x + (ymax - s.y) / m, ymax };
	return { s.x + (ymin - s.y) / m, ymin };
}

void clip() {
	Point in[50], out[50];
	int k = n;
	for (int i = 0; i < k; i++) in[i] = poly[i];
	for (int e = 0; e < 4; e++) {
		int m = 0;
		Point s = in[k - 1];
		for (int i = 0; i < k; i++) {
			Point p = in[i];
			if (inside(p, e)) {
				if (!inside(s, e)) out[m++] = cut(s, p, e);
				out[m++] = p;
			} else if (inside(s, e))
				out[m++] = cut(s, p, e);
			s = p;
		}
		for (int i = 0; i < m; i++) in[i] = out[i];
		k = m;
	}
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < k; i++) glVertex2f(in[i].x, in[i].y);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 1, 0);
	glRectf(xmin, ymin, xmax, ymax);
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++) glVertex2f(poly[i].x, poly[i].y);
	glEnd();
	clip();
	glFlush();
}

int main(int argc, char** argv) {
	cout << "Window xmin ymin xmax ymax: ";
	cin >> xmin >> ymin >> xmax >> ymax;
	cout << "Number of vertices: ";
	cin >> n;
	cout << "Enter the vertices (x y):\n";
	for (int i = 0; i < n; i++) cin >> poly[i].x >> poly[i].y;

	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Sutherland Hodgman");
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(3);
	glutDisplayFunc(display);
	glutMainLoop();
}
