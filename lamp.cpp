#include "glandstuff.h"
#include "lamp.h"

float light1Z = -22;
void drawLamp() {
    GLfloat mat_ambient[] = { 0.25, 0.25, 0.25, 1.0 };
    GLfloat mat_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat mat_specular[] = { 0.774597, 0.774597, 0.774597, 1.0 };
    GLfloat mat_shininess[] = { 76.8 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColor3f(1, 0.953, 0);

    glPushMatrix();
    glTranslatef(-8, 3, light1Z); // Position the cone
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotate to make the tip point left

    GLUquadricObj* quadObj = gluNewQuadric();
    gluCylinder(quadObj, 0.1, 0.5, 1.5, 32, 32);

    gluDeleteQuadric(quadObj);
    glPopMatrix();
}
