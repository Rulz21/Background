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

void sideline(int x, int y,int h, int w) {
	glBegin(GL_POLYGON);
	glVertex2i(x ,y );
	glVertex2i(x + w, y + 4);
	glVertex2i(x + w, y + h +4);
	glVertex2i(x, y + h);
	glEnd();

}

void wallTexture(int x, int y, int h, int w) {
	glColor3ub(0, 0, 0);
	sideline(x, y, h, w);
	sideline(x + 20, y - 35, h + 300, w - 8);
}

void sidewall(int x,int y) {
	glColor3ub(70, 70, 70);
	glBegin(GL_POLYGON);
	glVertex2i(x , y);
	glVertex2i(0.42*SCREENWIDTH, SCREENHEIGHT);
	glVertex2i(0,SCREENHEIGHT);
	glEnd();

	
	wallTexture( x + 50, y + 60, 100, 10);
	wallTexture(x + 110, y + 80, 100, 10);
	wallTexture(x + 170, y + 100, 100, 10);
	wallTexture(x + 230, y + 125, 100, 10);
	

}

void window(int x, int y, int h, int w) {
	glColor3ub(0, 0, 0);
	rectangle(x, y, h, w);
	//inner rectangle
	glColor3ub(76, 78, 108);
	rectangle(x + 5, y + 5, h - 10, w - 10);

}

void door() {
	glColor3ub(40, 40, 40);
	int x = SCREENWIDTH / 3 + 260;
	int y = SCREENHEIGHT / 2 + 0.1 * SCREENHEIGHT;
	int h = SCREENHEIGHT / 2 - 250;
	int w = 200;
	rectangle(x , y,h , w);

	//back circle
	circle(x + w/2,y+h,w/2,100);
	//front rectangle
	glColor3ub(34, 34, 34);
	rectangle(x + 15,y + 10,h, w - 30 );
	//front circle
	circle(x + w/2, y + h, w/2 -15, 100);
	//handle
	glColor3ub(17, 17, 17);
	circle(x+w - 8, y+h/2 + 25 , 5, 20);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(4.0);
	//wall
	glColor3ub(70, 70, 70);
	rectangle(SCREENWIDTH / 3,  SCREENHEIGHT/2 + 0.1*SCREENHEIGHT, SCREENHEIGHT, SCREENWIDTH);
	glColor3ub(0, 0, 0);
	circle(SCREENWIDTH / 3 + 50,SCREENHEIGHT - 20, 5, 50);
	circle(SCREENWIDTH / 3 + 100, SCREENHEIGHT - 20, 5, 50);
	circle(SCREENWIDTH / 3 + 150, SCREENHEIGHT - 20, 5, 50);
	//sidewall
	sidewall(0, SCREENHEIGHT*0.78);
	//line
	glColor3ub(20, 20, 20);
	rectangle(SCREENWIDTH / 3, SCREENHEIGHT / 2 + 0.1 * SCREENHEIGHT, SCREENHEIGHT, 4);
	//door
	door();
	//window
	window(3 * SCREENWIDTH / 4, 4 * SCREENHEIGHT / 5, 60, 400);

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
