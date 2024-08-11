#include "glandstuff.h"
void drawLeg() {

    GLfloat mat_diffuse_reg_t[] = { 0.329, 0.212, 0.212, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_reg_t);
    //glColor3f(0.329, 0.212, 0.212);
    glBegin(GL_QUADS);
    //front
    glVertex3f(0.0, 3.0, 0.0); //a
    glVertex3f(0.0,0.0,0.0); //c
    glVertex3f(0.5,0.0,0.0); //d
    glVertex3f(0.5,3.0,0.0); //b
    //back
    glVertex3f(0.5,3.0,-0.5); //h
    glVertex3f(0.5,0.0,-0.5); //g 
    glVertex3f(0.0,0.0,-0.5); //f
    glVertex3f(0.0,3.0,-0.5); //e
    //right
    glVertex3f(0.5, 3.0, -0.5);
    glVertex3f(0.5, 3.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.5, 0.0, -0.5);
    //left
    glVertex3f(0.0, 3.0, -0.5);
    glVertex3f(0.0, 0.0, -0.5);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 3.0, 0.0);
    //top
    glVertex3f(0.0, 3.0, -0.5);
    glVertex3f(0.0, 3.0, 0.0);
    glVertex3f(0.5, 3.0, 0.0);
    glVertex3f(0.5, 3.0, -0.5);
    //bottom
    glVertex3f(0.0, 0.0, -0.5);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.5, 0.0, -0.5);

    glEnd();

}

void drawTable() {

    GLfloat mat_diffuse_reg_t[] = { 0.329, 0.212, 0.212, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_reg_t);
    glBegin(GL_QUADS);



    //top
    glColor3f(0.329, 0.212, 0.212);
    glVertex3f(-6.0,-2.0,-15.0);
    glVertex3f(-4.0,-2.0,-15.0);
    glVertex3f(-4.0,-2.0,-20.0);
    glVertex3f(-6.0,-2.0,-20.0);
    
    glEnd();


    glPushMatrix();
    glTranslatef(-6.0, -5.0, -15.0);
    drawLeg();  //1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5, -5.0, -15.0);
    drawLeg();  //2
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.0, -5.0, -19.5);
    drawLeg();  //3
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5, -5.0, -19.5);
    drawLeg();  //4
    glPopMatrix();





}


