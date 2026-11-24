#include <iostream>
#include <algorithm>
#include <GL/glut.h>
using namespace std;

int n;
float x[100], y[100];

void scanFill() {
	glColor3f(0, 0, 1);
	for (int s = 0; s <= 500; s++) {            // for every scanline
		int xs[50], count = 0;
		for (int i = 0; i < n; i++) {           // find where each edge crosses it
			float x1 = x[i], y1 = y[i], x2 = x[(i+1) % n], y2 = y[(i+1) % n];
			if (y2 < y1) { swap(x1, x2); swap(y1, y2); }
			if (s > y1 && s < y2)
				xs[count++] = x1 + (s - y1) * (x2 - x1) / (y2 - y1);
		}
		sort(xs, xs + count);
		glBegin(GL_LINES);                       // fill between pairs
		for (int i = 0; i + 1 < count; i += 2) {
			glVertex2i(xs[i], s);
			glVertex2i(xs[i+1], s);
		}
		glEnd();
	}
	glFlush();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 1, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);                      // polygon outline
	for (int i = 0; i < n; i++) glVertex2f(x[i], y[i]);
	glEnd();
	scanFill();
}

int main(int argc, char** argv) {
	cout << "Enter the number of sides: ";
	cin >> n;
	cout << "Enter the vertices (x y):\n";
	for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Scanline Area Fill");
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
	glutDisplayFunc(display);
	glutMainLoop();
}
