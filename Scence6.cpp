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

void table(int x, int y) {
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(SCREENWIDTH, y);
	glVertex2i(SCREENWIDTH, SCREENHEIGHT/2 );
	glVertex2i(x + 40, SCREENHEIGHT / 2);
	glEnd();
	//pole
	glColor3ub(62, 40, 38);
	rectangle(x + 10, 0, SCREENHEIGHT - (SCREENHEIGHT - y), 17);

	glColor3ub(36,20,20);
	rectangle(x, y - 10, 10, SCREENWIDTH - x);
	
}

void pot(int x, int y, int h, int w) {
	//body
	glColor3ub(115, 64, 20);
	glBegin(GL_POLYGON);
	glVertex2i(x +8, y - 30);
	glVertex2i(x + w, y - 30);
	glVertex2i(x + w + 8, y + h - 5);
	glVertex2i(x + w + 8, y + h);
	glVertex2i(x+2, y);
	glEnd();

	glColor3ub(79,44, 14);
	glBegin(GL_POLYGON);
	glVertex2i(x, y-5);
	glVertex2i(x + w, y-5);
	glVertex2i(x + w + 8, y + h-5);
	glVertex2i(x + w + 8, y + h);
	glVertex2i(x, y);
	glEnd();

	glColor3ub(115, 64, 20);
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w + 8, y + h);
	glVertex2i(x + 8, y + h);
	glEnd();
	
}

void plant(int x,int y) {
	glColor3ub(55, 125, 34);
	rectangle(x, y, 30, 5);
}
void door(int x, int y, int w) {
	int h = 1.5 * w;
	//main
	glColor3ub(100, 100, 100);
	rectangle(x, y, h, w);
	//small rectangle
	int innerW = w * 0.8;
	int innerH = h / 2.5;
	int innerX = x + (w / 8);;
	int innerY = y + (h / 16);
	glColor3ub(50, 50, 50);
	rectangle(innerX, innerY, innerH, innerW);
	//uppper small rectangel
	glColor3ub(50, 50, 50);
	rectangle(innerX, innerY + innerH + (innerY - y), innerH, innerW);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(4.0);
	//wall
	glColor3ub(70, 70, 70);
	rectangle(0, SCREENHEIGHT / 2 + 0.25 * SCREENHEIGHT, SCREENHEIGHT, SCREENWIDTH);
	//table
	glColor3ub(62, 40, 38);
	table(SCREENWIDTH/2 + 60, 60);
	//door
	door(SCREENWIDTH/2, SCREENHEIGHT / 2 + 0.25 * SCREENHEIGHT, 60);
	//pot
	pot(SCREENWIDTH - 110, 120, 40, 50);
	pot(SCREENWIDTH - 90, 220, 40, 50);
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