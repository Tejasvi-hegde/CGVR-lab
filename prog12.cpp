#include <GL/glut.h>

float v[8][3] = {{-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
                 {-1,1,1},   {1,1,1},   {1,-1,1}, {-1,-1,1}};
float c[8][3] = {{0,0,0}, {0,0,1}, {0,1,0}, {0,1,1},
                 {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}};
GLubyte faces[24] = {0,1,2,3,  0,6,7,1,  3,4,5,2,
                     0,3,4,7,  2,5,6,1,  7,4,5,6};
float theta[3] = {0, 0, 0};
int axis = 2;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, faces);
	glutSwapBuffers();
}

void spinCube() {
	theta[axis] += 0.5;
	if (theta[axis] > 360) theta[axis] -= 360;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if (state != GLUT_DOWN) return;
	if (button == GLUT_LEFT_BUTTON)   axis = 0;
	if (button == GLUT_MIDDLE_BUTTON) axis = 1;
	if (button == GLUT_RIGHT_BUTTON)  axis = 2;
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float a = (float)w / h;
	if (a >= 1) glOrtho(-2 * a, 2 * a, -2, 2, -10, 10);
	else        glOrtho(-2, 2, -2 / a, 2 / a, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Color Cube");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(spinCube);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v);
	glColorPointer(3, GL_FLOAT, 0, c);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
