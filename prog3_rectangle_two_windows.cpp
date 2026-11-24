#include <iostream>
#include <GL/glut.h>
using namespace std;

float w, h, spin = 0;
int win2;

void rect() {
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0); glVertex2f(-w / 2, -h / 2);
	glColor3f(0, 1, 0); glVertex2f( w / 2, -h / 2);
	glColor3f(0, 0, 1); glVertex2f( w / 2,  h / 2);
	glColor3f(1, 1, 0); glVertex2f(-w / 2,  h / 2);
	glEnd();
}

void display1() {                    // window 1: still rectangle
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	rect();
	glutSwapBuffers();
}

void display2() {                    // window 2: spinning rectangle
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(spin, 0, 0, 1);
	rect();
	glutSwapBuffers();
}

void spinDisplay() {
	spin += 0.5;
	glutSetWindow(win2);
	glutPostRedisplay();
}

void init() {
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-250, 250, -250, 250);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	cout << "Enter width and height: ";
	cin >> w >> h;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);

	glutInitWindowPosition(50, 100);
	glutCreateWindow("Window 1");
	glutDisplayFunc(display1);
	init();

	glutInitWindowPosition(600, 100);
	win2 = glutCreateWindow("Window 2");
	glutDisplayFunc(display2);
	init();

	glutIdleFunc(spinDisplay);
	glutMainLoop();
}
