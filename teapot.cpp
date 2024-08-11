#include "glandstuff.h"

void drawTeapot() {
    GLfloat mat_ambient[] = { 0.25, 0.25, 0.25, 1.0 };
    GLfloat mat_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat mat_specular[] = { 0.774597, 0.774597, 0.774597, 1.0 };
    GLfloat mat_shininess[] = { 76.8 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();

    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(-5.0, -1.5, -17.0);
    glutSolidTeapot(0.5);   //thanks to opengl to make this easy :)

    glPopMatrix();
}
