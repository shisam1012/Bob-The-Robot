#include "glandstuff.h"
#include "floorAndWalls.h"

const float FLOOR_TILE_SIZE = 2;
const float NUM_TILES_ROW = 8;
const float NUM_TILES_COL = 10;
float FLOOR_LEFT_EDGE = -8;
float FLOOR_BOTTOM_EDGE = -12;
float FLOOR_LEVEL = -5;


void drawWalls() {

    glBegin(GL_QUADS);
    glColor3f(0.482, 0.702, 0.91);
    //left wall
    glVertex3f(FLOOR_LEFT_EDGE, FLOOR_LEVEL, FLOOR_BOTTOM_EDGE - 20);
    glVertex3f(FLOOR_LEFT_EDGE, FLOOR_LEVEL, FLOOR_BOTTOM_EDGE);
    glVertex3f(FLOOR_LEFT_EDGE, FLOOR_LEVEL + 12, FLOOR_BOTTOM_EDGE);
    glVertex3f(FLOOR_LEFT_EDGE, FLOOR_LEVEL + 12, FLOOR_BOTTOM_EDGE - 20);
    //right wall
    glVertex3f(FLOOR_LEFT_EDGE + 16, FLOOR_LEVEL, FLOOR_BOTTOM_EDGE - 20);
    glVertex3f(FLOOR_LEFT_EDGE + 16, FLOOR_LEVEL, FLOOR_BOTTOM_EDGE);
    glVertex3f(FLOOR_LEFT_EDGE + 16, FLOOR_LEVEL + 12, FLOOR_BOTTOM_EDGE);
    glVertex3f(FLOOR_LEFT_EDGE + 16, FLOOR_LEVEL + 12, FLOOR_BOTTOM_EDGE - 20);
    //back wall
    glColor3f(0.62, 0.486, 0.486);
    glVertex3f(FLOOR_LEFT_EDGE + 16, FLOOR_LEVEL + 12, FLOOR_BOTTOM_EDGE - 20);
    glVertex3f(FLOOR_LEFT_EDGE + 16, FLOOR_LEVEL, FLOOR_BOTTOM_EDGE - 20);
    glVertex3f(FLOOR_LEFT_EDGE, FLOOR_LEVEL, FLOOR_BOTTOM_EDGE - 20);
    glVertex3f(FLOOR_LEFT_EDGE, FLOOR_LEVEL + 12, FLOOR_BOTTOM_EDGE - 20);

    glEnd();
}

void drawFloor() {
    drawWalls();
    //   GLfloat mat_ambient[] = { 0.25, 0.25, 0.25, 1.0 };
    //   GLfloat mat_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };

    //   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    //   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    int startY = -5.0;
    for (int i = 0; i < NUM_TILES_COL; i++) {
        for (int j = 0; j < NUM_TILES_ROW; j++) {
            if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) {
                glColor3f(0.482, 0.702, 0.91);  // Color for odd-even pattern
            }
            else {
                glColor3f(0.122, 0.455, 0.769);  // Color for even-even or odd-odd pattern
            }
            glBegin(GL_QUADS);
            glVertex3f(FLOOR_LEFT_EDGE, startY, FLOOR_BOTTOM_EDGE - FLOOR_TILE_SIZE);
            glVertex3f(FLOOR_LEFT_EDGE, startY, FLOOR_BOTTOM_EDGE);
            glVertex3f(FLOOR_LEFT_EDGE + FLOOR_TILE_SIZE, startY, FLOOR_BOTTOM_EDGE);
            glVertex3f(FLOOR_LEFT_EDGE + FLOOR_TILE_SIZE, startY, FLOOR_BOTTOM_EDGE - FLOOR_TILE_SIZE);
            glEnd();

            FLOOR_LEFT_EDGE += FLOOR_TILE_SIZE;
        }
        FLOOR_LEFT_EDGE = -8;
        FLOOR_BOTTOM_EDGE -= FLOOR_TILE_SIZE;
    }

    FLOOR_LEFT_EDGE = -8;
    FLOOR_BOTTOM_EDGE = -12;
}
