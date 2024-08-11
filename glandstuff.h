#pragma once
#ifdef _WIN32
#include <windows.h>
#include <imgui.h>
#include <imgui_impl_glut.h>
#include <imgui_impl_opengl2.h>
//#include <glut.h>
#include "GL/freeglut.h" 
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
//#include <glut.h>
#endif

struct Point3D {
    GLfloat x, y, z;
};

