#include <windows.h>
#include <stdlib.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>
#include <math.h>

#define SCREENWIDTH 500
#define SCREENHEIGHT 500
#define PI 3.1415926535897932384626433832795

void nGon(int x, int y, int r, int n) {
	double inc = (2 * PI) / (double)n;
	glBegin(GL_POLYGON);
	for (double theta = 0.0; theta <= 2 * PI; theta += inc) {
		glVertex2d(x + r * cos(theta), y + r * sin(theta));
	}
	glEnd();
}

void rectangle(int x, int y, int h, int w) {

	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y + h);
	glVertex2i(x, y + h);
	glEnd();
}

void floor() {
	int a = 76;
	int b = 76;
	int c = 112;
	glColor3ub(a, b, c);
	rectangle(0, 30, 50, SCREENWIDTH - 100);

	glBegin(GL_POLYGON);
	glVertex2i(SCREENWIDTH - 100, 30);
	glVertex2i(SCREENWIDTH, 2 * SCREENHEIGHT /3);
	glVertex2i(SCREENWIDTH, 2 * SCREENHEIGHT / 3 + 20);
	glVertex2i(SCREENWIDTH - 100, 80);
	glEnd();

	//DIRT
	glColor3ub(110, 56, 23);
	glBegin(GL_POLYGON);
	glVertex2i(0, 80);
	glVertex2i(SCREENWIDTH-100, 80);
	glVertex2i(SCREENWIDTH, 2*SCREENHEIGHT/3 + 20);
	glVertex2i(0, 2*SCREENHEIGHT/3 + 20);
	glEnd();

	glColor3ub(0, 0, 0);
	rectangle(SCREENWIDTH - 110, 30, 50, 10);

	glColor3ub(a, b, c);
	rectangle(0, 2 * SCREENHEIGHT / 3 + 16, 4, SCREENWIDTH);

	glColor3ub(0, 0, 0);
	rectangle(0, 80, 4, SCREENWIDTH - 100);

	glColor3ub(0,0,0);
	glBegin(GL_POLYGON);
	glVertex2i(SCREENWIDTH - 100, 80);
	glVertex2i(SCREENWIDTH, 2 * SCREENHEIGHT / 3 + 20);
	glVertex2i(SCREENWIDTH, 2 * SCREENHEIGHT / 3 + 28);
	glVertex2i(SCREENWIDTH -100, 88);
	glEnd();
}

void window(int x, int y, int  h, int w) {
	glColor3ub(0, 0, 0);
	rectangle(x - 50, y + 70, h,w);

	glColor3ub(173, 177, 255);
	rectangle(x- 48,y+ 72, h-4, w-4);
}

void plant(int x, int y) {
	glColor3ub(55, 125, 34);
	rectangle(x, y, 30, 5);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(4.0);
	//wall
	glColor3ub(60,60,60);
	rectangle(0, SCREENHEIGHT / 2 + 0.25 * SCREENHEIGHT, SCREENHEIGHT, SCREENWIDTH);
	//window
	window(SCREENWIDTH / 4, 2 * SCREENHEIGHT / 3, 80, 140);
	window(SCREENWIDTH / 2 + 80, 2 * SCREENHEIGHT / 3, 80, 140);

	floor();
	//plant
	plant(SCREENWIDTH - 85, 138);
	plant(SCREENWIDTH - 65, 238);
	glEnd();
	glFlush();
}

void initGL() {
	glClearColor(0.2, 0.2, 0.2, .00);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREENWIDTH, 0, SCREENHEIGHT);

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	glutCreateWindow("Scence 4");
	glutDisplayFunc(display);

	initGL();

	glutMainLoop();

}