#pragma once
#include "glandstuff.h"

extern GLint winWidth;
extern GLint winHeight;

void display();
void init();
void keyboardPressed(unsigned char key, int x, int y);
void reshape(GLsizei width, GLsizei height);
