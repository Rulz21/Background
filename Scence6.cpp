#include <windows.h>
#include <stdlib.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>
#include <math.h>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 900
#define PI 3.1415926535897932384626433832795

void circle(int x, int y, int r, int n) {
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
	glVertex2i(SCREENWIDTH, 2*SCREENHEIGHT/3 );
	glVertex2i(x + 100, 2*SCREENHEIGHT / 3);
	glEnd();
	//pole
	glColor3ub(62, 40, 38);
	rectangle(x + 30, 0, SCREENHEIGHT - (SCREENHEIGHT - y), 25);

	glColor3ub(36,20,20);
	rectangle(x, y - 20, 20, SCREENWIDTH - x);
	
}

void pot(int x, int y, int h, int w) {
	//body
	glColor3ub(115, 64, 20);
	glBegin(GL_POLYGON);
	glVertex2i(x + 16, y - 60);
	glVertex2i(x + w, y - 60);
	glVertex2i(x + w + 8, y + h - 15);
	glVertex2i(x + w + 10, y + h);
	glVertex2i(x+8, y);
	glEnd();


	glColor3ub(79,44, 14);
	glBegin(GL_POLYGON);
	glVertex2i(x, y-15);
	glVertex2i(x + w, y-15);
	glVertex2i(x + w + 10, y + h-15);
	glVertex2i(x + w + 10, y + h);
	glVertex2i(x, y);
	glEnd();
	
	//INSIDE
	glColor3ub(115, 64, 20);
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w + 10, y + h);
	glVertex2i(x + 10, y + h);
	glEnd();

	//dirt inside
	glColor3ub(71, 40, 12);
	glBegin(GL_POLYGON);
	glVertex2i(x + 12, y);
	glVertex2i(x + w - 2, y);
	glVertex2i(x + w + 6, y + h - 12);
	glVertex2i(x + 20, y +h - 12);
	glEnd();

	
}

void plant(int x,int y) {
	glColor3ub(55, 125, 34);
	rectangle(x, y, 60, 8);
}

void door(int x, int y, int w) {
	int h = w;
	//main
	glColor3ub(100, 100, 100);
	rectangle(x, y, h, w);
	//front circle
	circle(x + w / 2, y + h, w/2, 100);
	//small rectangle
	glColor3ub(63, 63, 63);
	rectangle(x + 10, y, h,w-20);
	//back circle
	circle(x + w / 2, y + h, w/2 -10, 100);
	//handle
	glColor3ub(0, 0, 0);
	circle(x + w -6, y + h / 2 + 13, 5, 20);
	//window
	glColor3ub(158, 161, 232);
	circle(x + w / 2, y + h, 20, 100);
}

void box(int x, int y,int h, int w) {
	glColor3ub(110, 49, 45);
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w + 8, y + 10);
	glVertex2i(x + 8, y + 10);
	glEnd();

	glColor3ub(74, 33, 30);
	rectangle(x, y - h, h, w);
	//side box
	glBegin(GL_POLYGON);
	glVertex2i(x + w, y - h);
	glVertex2i(x + w + 8, y - h + 10);
	glVertex2i(x + w + 8, y + 10);
	glVertex2i(x + w, y );
	glEnd();
}

void window(int x, int y, int h, int w) {
	glColor3ub(0, 0, 0);
	rectangle(x, y, h, w);

	glColor3ub(130, 133, 191);
	rectangle(x + 5, y + 5, h - 10, w - 10);
}

void wall() {
	//window
	window(2 * SCREENWIDTH / 3, 7 * SCREENHEIGHT / 8, 50, 300);

	int a = SCREENWIDTH / 8 - 50;
	int b = SCREENHEIGHT - 100;
	int c = 50;
	int d = 400;
	glColor3ub(0, 0, 0);
	rectangle(a,b, c, d);
	//front
	glColor3ub(70, 70, 70);
	rectangle(a + 5, b + 5, c - 10, d - 10);
	//lower rectangle
	glColor3ub(45, 45, 45);
	rectangle(a, b - 60, c, d);
	
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(4.0);
	//wall
	glColor3ub(70, 70, 70);
	rectangle(0, SCREENHEIGHT / 2 + 0.25 * SCREENHEIGHT, SCREENHEIGHT, SCREENWIDTH);
	wall();
	//table
	glColor3ub(62, 40, 38);
	table(SCREENWIDTH - 450, SCREENHEIGHT/8 + 100);
	//door
	door(SCREENWIDTH/2, SCREENHEIGHT / 2 + 0.25 * SCREENHEIGHT, 140);
	//pot
	pot(SCREENWIDTH - 300, SCREENHEIGHT/8 + 250, 60, 100);
	pot(SCREENWIDTH - 240, 2 * SCREENHEIGHT / 3 - 90, 55, 90);
	//plant
	plant(SCREENWIDTH - 250, SCREENHEIGHT / 8 + 265);
	plant(SCREENWIDTH - 200, 2* SCREENHEIGHT / 3 - 75);
	//BOX
	box(SCREENWIDTH / 3, SCREENHEIGHT / 2 + 0.25 * SCREENHEIGHT + 20, 50, 70);
	box(SCREENWIDTH / 3 - 120, SCREENHEIGHT / 2 + 0.25 * SCREENHEIGHT + 10, 30, 50);

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
