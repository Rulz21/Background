#include <windows.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define SCREENWIDTH 1280 
#define SCREENHEIGHT 900
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

void flower(int x, int y, int r) {
    const GLubyte colors[][3] = {
        {255, 0, 0},     // Red
        {255, 165, 0},   // Orange
        {255, 255, 0},   // Yellow
        {0, 128, 0},     // Green
        {0, 0, 255},     // Blue
        {128, 0, 128},   // Purple
        {255, 192, 203}  // Pink
    };

    int colorIndex = (x / 50 + y / 50) % 7;

    // Stem
    glColor3ub(34, 139, 34); // Forest green
    glBegin(GL_LINES);
    glVertex2i(x, y - 10);
    glVertex2i(x, y);
    glEnd();

    // Petals
    glColor3ubv(colors[colorIndex]);
    for (int i = 0; i < 6; i++) {
        double angle = i * PI / 3;
        int px = x + r * cos(angle);
        int py = y + r * sin(angle);
        nGon(px, py, r, 20);
    }

    // Center
    glColor3ub(255, 255, 255);
    nGon(x, y, r - 2, 20);

    glColor3ub(21, 54, 10);
    rectangle(x - 2, y - 40, 25, 4);
}

void floor() {
    int a = 76;
    int b = 76;
    int c = 112;
    glColor3ub(a, b, c);
    rectangle(0, SCREENHEIGHT / 3, 80, SCREENWIDTH - 400);

    glBegin(GL_POLYGON);
    glVertex2i(SCREENWIDTH - 400, SCREENHEIGHT / 3);
    glVertex2i(SCREENWIDTH - 200, 2 * SCREENHEIGHT / 3 - 50);
    glVertex2i(SCREENWIDTH - 200, 2 * SCREENHEIGHT / 3 + 5);
    glVertex2i(SCREENWIDTH - 400, SCREENHEIGHT / 3 + 80);
    glEnd();

    // DIRT base
    glColor3ub(110, 56, 23); // Base dirt color
    glBegin(GL_POLYGON);
    glVertex2i(0, SCREENHEIGHT / 3 + 80);
    glVertex2i(SCREENWIDTH - 400, SCREENHEIGHT / 3 + 80);
    glVertex2i(SCREENWIDTH - 200, 2 * SCREENHEIGHT / 3 + 5);
    glVertex2i(0, 2 * SCREENHEIGHT / 3 + 5);
    glEnd();

    // Simulated dirt texture using random patches
    int dirtStartY = SCREENHEIGHT / 3 + 80;
    int dirtEndY = 2 * SCREENHEIGHT / 3;
    int patchCount = 200;

    for (int i = 0; i < patchCount; i++) {
        int x = rand() % (SCREENWIDTH - 400);
        int y = dirtStartY + rand() % (dirtEndY - dirtStartY);
        int size = 3 + rand() % 3;

        // Randomly pick a light or dark shade for variation
        int r = 90 + rand() % 60;
        int g = 45 + rand() % 50;
        int b = 15 + rand() % 40;

        glColor3ub(r, g, b);
        glBegin(GL_POLYGON);
        glVertex2i(x, y);
        glVertex2i(x + size, y);
        glVertex2i(x + size, y + size);
        glVertex2i(x, y + size);
        glEnd();
    }

    // BLACK LINE
    glColor3ub(0, 0, 0);
    rectangle(SCREENWIDTH - 410, SCREENHEIGHT / 3, 80, 10);

    //back
    glColor3ub(a, b, c);
    rectangle(0, 2 * SCREENHEIGHT / 3 + 5, 4, SCREENWIDTH - 200);


    glColor3ub(0, 0, 0);
    rectangle(0, SCREENHEIGHT/3 + 75, 5, SCREENWIDTH - 400);

    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(SCREENWIDTH - 400, SCREENHEIGHT / 3);
    glVertex2i(SCREENWIDTH - 200, 2 * SCREENHEIGHT / 3);
    glVertex2i(SCREENWIDTH - 200, 2 * SCREENHEIGHT / 3 + 10);
    glVertex2i(SCREENWIDTH - 400, SCREENHEIGHT / 3 + 10);
    glEnd();

    rectangle(SCREENWIDTH - 205, 2 * SCREENHEIGHT / 3 - 60, 60, 5);
   
}

void window(int x, int y, int h, int w) {
    glColor3ub(0, 0, 0);
    rectangle(x - 50, y + 70, h, w);

    glColor3ub(173, 177, 255);
    rectangle(x - 48, y + 72, h - 4, w - 4);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(10.0);
    glLineWidth(4.0);

    // Wall
    glColor3ub(60, 60, 60);
    rectangle(0, SCREENHEIGHT / 2 + 0.25 * SCREENHEIGHT, SCREENHEIGHT, SCREENWIDTH);

    // Windows
    window(SCREENWIDTH / 4, 2 * SCREENHEIGHT / 3 +100, 80, 250);
    window(SCREENWIDTH / 2 + 100, 2 * SCREENHEIGHT / 3 + 100, 80, 250);

    floor();

    // Colorful flowers on dirt pile with rightward slant
    int flowerCount = 30;
    int flowersPerRow = 6; // Fewer flowers per row = more horizontal space
    int spacingX = 150;    // Wider horizontal spacing
    int spacingY = 40;     // More vertical spacing

    for (int i = 0; i < flowerCount; i++) {
        int row = i / flowersPerRow;
        int col = i % flowersPerRow;

        int slantOffset = row * 50; // Gradual rightward slant
        int xJitter = rand() % 10 - 5; // Horizontal variation
        int yJitter = rand() % 5;      // Vertical variation

        int x = 0 + col * spacingX + slantOffset + xJitter;
        int y = SCREENHEIGHT / 3 + 150 + row * spacingY + yJitter; // Adjusted to sit on dirt pile

        flower(x, y, 6 + rand() % 2); // Slightly bigger petals
    }



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
    glutCreateWindow("Scene 4");
    glutDisplayFunc(display);

    initGL();
    glutMainLoop();
}
