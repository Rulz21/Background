#include <windows.h>
#include <stdlib.h>
#include <GL\gl.h>
#include <GL\glut.h>
#include <GL\glu.h>
#include <math.h>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 900
#define PI 3.1415926535897932384626433832795

void rectangle(int x, int y, int h, int w) {

	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y + h);
	glVertex2i(x, y + h);
	glEnd();
}

void circle(int n, int x, int y, int r) {
	double inc = 2 * PI / n;

	glBegin(GL_POLYGON);
	for (double theta = 0.0; theta <= 2 * PI; theta += inc) {
		glVertex2i(r * cos(theta) + x, r * sin(theta) + y);
	}
	glEnd();
}

void window(int x, int y, int h, int w) {
	glColor3ub(0, 0, 0);
	rectangle(x, y, h, w);

	glColor3ub(94, 94, 94);
	rectangle(x + 4, y + 4, h - 8, w - 8);
}

void door(int x, int y, int w) {
	int h = w;
	//main
	glColor3ub(100, 100, 100);
	rectangle(x, y, h, w);
	//small rectangle
	int innerW = w * 0.8;
	int innerH = h - 20;
	int innerX = x + (w - 15 * (w / 16));
	int innerY = y + (h / 16);

	//back circle
	glColor3ub(100, 100, 100);
	circle(100, x + w / 2, y+h, 75);

	glColor3ub(50, 50, 50);
	rectangle(innerX, innerY, innerH, innerW);
	//front circle
	glColor3ub(50, 50, 50);
	circle(100, x + w / 2 ,y+ h, 60);

	glColor3ub(173, 177, 255);
	circle(100,x+ w/2, y+h, 20);

	//handle
	glColor3ub(50, 50, 50);
	circle(100,x+w-5, y+h/2+10, 5);


}

void trapezium(int x, int y, int h, int w) {
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w - 10, y + h);
	glVertex2i(x + 10, y + h);
	glEnd();
}

void pot(int x, int y, int h, int w) {
	int a = x / 2 + x / 4;
	int M = w / 8;
	glColor3ub(120, 67, 21);
	glBegin(GL_POLYGON);
	glVertex2i(a, y);
	glVertex2i(a + w, y);
	glVertex2i(a + 7 * M, y + h);
	glVertex2i(a + M, y + h);
	glEnd();

	//inside
	glColor3ub(70, 30, 8);
	glBegin(GL_POLYGON);
	glVertex2i(a + 15, y);
	glVertex2i(a + w - 15, y);
	glVertex2i(a + 7 * M - 10, y + h - 10);
	glVertex2i(a+ M + 10, y + h -10);
	glEnd();

	//body
	glColor3ub(94, 53, 17);
	rectangle(a, y - 20, 20, w);
	glColor3ub;(94, 53, 17);
	glBegin(GL_POLYGON);
	glVertex2i(a + 20, y - 70);
	glVertex2i(a + 100, y - 70);
	glVertex2i(a + 110, y - 10);
	glVertex2i(a + 10, y - 10);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(4.0);

	

	glColor3ub(30, 30, 30);
	rectangle(0, 0, 500, SCREENWIDTH);

	pot(SCREENWIDTH, 400, 40, 120);

	window(3 * SCREENWIDTH / 4, 2 * SCREENHEIGHT / 3 , 200, 600);
	window(50, 3 * SCREENHEIGHT / 4 +15, 100, 450);

	//box
	glColor3ub(114, 50, 17);
	trapezium(SCREENWIDTH / 4, 520, 20, 80);
	glColor3ub(105, 40, 10);
	rectangle(SCREENWIDTH / 4, 470 , 50, 80);

	glColor3ub(114, 50, 17);
	trapezium(SCREENWIDTH / 4 - 200, 530, 20, 110);
	glColor3ub(105, 40, 10);
	rectangle(SCREENWIDTH / 4-200, 470, 60, 110);

	door(SCREENWIDTH / 2, 500, 150);



	glEnd();
	glFlush();
}

void initGL() {
	glClearColor(0.176, 0.180, 0.209, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREENWIDTH, 0, SCREENHEIGHT);

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	glutCreateWindow("Test Window");
	glutDisplayFunc(display);

	initGL();

	glutMainLoop();

}