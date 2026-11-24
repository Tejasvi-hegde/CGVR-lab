#include <iostream>
#include <GL/glut.h>
using namespace std;

typedef float point[3];

int iter;
point tetra[4] = {{0,0,250}, {0,250,-250}, {250,-250,-250}, {-250,-250,-250}};

void triangle(point a, point b, point c) {
	glVertex3fv(a); glVertex3fv(b); glVertex3fv(c);
}

void tetrahedron(point a, point b, point c, point d) {
	glColor3f(1, 0, 0); triangle(a, b, c);
	glColor3f(0, 1, 0); triangle(a, b, d);
	glColor3f(0, 0, 1); triangle(a, c, d);
	glColor3f(1, 1, 0); triangle(b, c, d);
}

void divide(point a, point b, point c, point d, int k) {
	if (k == 0) { tetrahedron(a, b, c, d); return; }
	point ab, ac, ad, bc, bd, cd;       // midpoints of the 6 edges
	for (int j = 0; j < 3; j++) {
		ab[j] = (a[j] + b[j]) / 2;  ac[j] = (a[j] + c[j]) / 2;
		ad[j] = (a[j] + d[j]) / 2;  bc[j] = (b[j] + c[j]) / 2;
		bd[j] = (b[j] + d[j]) / 2;  cd[j] = (c[j] + d[j]) / 2;
	}
	divide(a, ab, ac, ad, k - 1);
	divide(ab, b, bc, bd, k - 1);
	divide(ac, bc, c, cd, k - 1);
	divide(ad, bd, cd, d, k - 1);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divide(tetra[0], tetra[1], tetra[2], tetra[3], iter);
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	cout << "Enter the number of subdivisions: ";
	cin >> iter;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Sierpinski Gasket");
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
	glOrtho(-250, 250, -250, 250, -250, 250);
	glutDisplayFunc(display);
	glutMainLoop();
}
