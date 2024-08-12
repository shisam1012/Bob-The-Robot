#include "glandstuff.h"


void drawDrawersBase() {

    glPushMatrix();
    glTranslatef(4.9, -5.0, -30.0);
    glColor3f(0.4, 0.396, 0.365);
    glBegin(GL_QUADS);
    //front  
    glVertex3f(-3, 1, 2); //1
    glVertex3f(-3, 0, 2); //2
    glVertex3f(3, 0, 2);  //3
    glVertex3f(3, 1, 2); //4
    //back
    glVertex3f(3, 1, -2); //8
    glVertex3f(3, 0, -2); //7
    glVertex3f(-3, 0, -2); //6
    glVertex3f(-3, 1, -2); //5
    //right
    glVertex3f(3, 1, -2);
    glVertex3f(3, 1, 2);
    glVertex3f(3, 0, 2);
    glVertex3f(3, 0, -2);
    //left
    glVertex3f(-3, 1, -2);
    glVertex3f(-3, 0, -2);
    glVertex3f(-3, 0, 2);
    glVertex3f(-3, 1, 2);
    //top
    glVertex3f(-3, 1, -2);
    glVertex3f(-3, 1, 2);
    glVertex3f(3, 1, 2);
    glVertex3f(3, 1, -2);
    //bottom
    glVertex3f(-3, 0, -2);
    glVertex3f(-3, 0, 2);
    glVertex3f(3, 0, 2);
    glVertex3f(3, 0, -2);

    glEnd();

    glPopMatrix();
}

void drawDrawer() {

    glBegin(GL_QUADS);
    //front
    glColor3f(0.8, 0.647, 0.451);
    glVertex3f(-1.5, 2, 2); //1
    glVertex3f(-1.5, 0, 2); //2
    glVertex3f(1.5, 0, 2);  //3
    glVertex3f(1.5, 2, 2); //4
    //back
    glVertex3f(1.5, 2, -2); //8
    glVertex3f(1.5, 0, -2); //7
    glVertex3f(-1.5, 0, -2); //6
    glVertex3f(-1.5, 2, -2); //5
    //right
    glVertex3f(1.5, 2, -2);
    glVertex3f(1.5, 2, 2);
    glVertex3f(1.5, 0, 2);
    glVertex3f(1.5, 0, -2);
    //left
    glVertex3f(-1.5, 2, -2);
    glVertex3f(-1.5, 0, -2);
    glVertex3f(-1.5, 0, 2);
    glVertex3f(-1.5, 2, 2);
    //top
    glVertex3f(-1.5, 2, -2);
    glVertex3f(-1.5, 2, 2);
    glVertex3f(1.5, 2, 2);
    glVertex3f(1.5, 2, -2);
    //bottom
    glVertex3f(-1.5, 0, -2);
    glVertex3f(-1.5, 0, 2);
    glVertex3f(1.5, 0, 2);
    glVertex3f(1.5, 0, -2);

    glEnd();

    glLineWidth(4.0f);
    glColor3f(0.91, 0.902, 0.741);
    //draw a line with a different color on every edge of the drawer
    glBegin(GL_LINES);

    glVertex3f(-1.5, 2, 2); //1
    glVertex3f(-1.5, 0, 2); //2

    glVertex3f(-1.5, 2, -2); //5
    glVertex3f(-1.5, 2, 2); //1

    glVertex3f(-1.5, 2, 2); //1
    glVertex3f(1.5, 2, 2); //4

    glVertex3f(1.5, 0, 2);  //3
    glVertex3f(1.5, 2, 2); //4

    glVertex3f(1.5, 0, 2);  //3
    glVertex3f(-1.5, 0, 2); //2

    glVertex3f(1.5, 2, -2); //8
    glVertex3f(1.5, 0, 2);  //3

    glVertex3f(-1.5, 0, -2); //6
    glVertex3f(-1.5, 2, -2); //5

    glVertex3f(-1.5, 2, -2); //5
    glVertex3f(1.5, 2, -2); //8

    glVertex3f(1.5, 2, -2); //8
    glVertex3f(1.5, 2, 2); //4

    glVertex3f(-1.5, 0, -2); //6
    glVertex3f(1.5, 0, -2); //7

    glVertex3f(1.5, 0, -2); //7
    glVertex3f(1.5, 0, 2);  //3

    glVertex3f(1.5, 0, -2); //7
    glVertex3f(1.5, 2, -2); //8
    glEnd();

    //handle
    glColor3f(0.4,0.396,0.365);
    glLineWidth(1.5f);

    glBegin(GL_LINES);

    glVertex3f(-1, 1.25, 2.1);
    glVertex3f(-0.5, 1.25, 2.1);

    glVertex3f(0.5, 1.25, 2.1);
    glVertex3f(1, 1.25, 2.1);

    glVertex3f(-0.75, 0.75, 2.1);
    glVertex3f(0.75, 0.75, 2.1);

    glVertex3f(-0.75, 1.25, 2.1);
    glVertex3f(-0.75, 0.75, 2.1);

    glVertex3f(0.75, 1.25, 2.1);
    glVertex3f(0.75, 0.75, 2.1);

    glEnd();
}

void drawDrawers() {

    drawDrawersBase();

    //drawing 4 legs, each one at a different position
    glPushMatrix();
    glTranslatef(6.4, -4.0, -30.0);
    drawDrawer();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.4, -4.0, -30.0);
    drawDrawer();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.4, -2.0, -30.0);
    drawDrawer();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.4, -2.0, -30.0);
    drawDrawer();
    glPopMatrix();
}
