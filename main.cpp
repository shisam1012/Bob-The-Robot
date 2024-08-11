/*
This is my final project for the Computer Graphics course (20562)
"Bob the Robot" - created by me (Shiri Samoch)

I run this project by using Microsoft Visual Studio
I used the FreeGLUT library and the ImGui library, they are included in the "glandstuff.h" file.

Enjoy :)
*/
#include "robotAndMenu.h"

GLint winWidth = 800;
GLint winHeight = 800;

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Bob the robot");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardPressed);
    glutReshapeFunc(reshape);
     
    glutMainLoop();
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
    
    return 0;
}

