#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "table.h"
#include "floorAndWalls.h"
#include "teapot.h"
#include "drawers.h"
#include "lamp.h"
#include "transformations.h"
#include "robotAndMenu.h"

// Flag to control whether the menu is shown or not
void display_menu();
static bool show_menu = true;


// Robot arm joint angles
int DEG_SHO = 0;
int DEG_ELB = 0;
int DEG_PALM = 0;

const int MAX_ELB_DEG = 100;    // Maximum elbow rotation angle
const int MIN_ELB_DEG = -100;   // Minimum elbow rotation angle

// Robot head rotation angles
float DEG_HEAD_RL = 0;          // right-left head's rotation angle
float DEG_HEAD_UD = 0;          // up-down head's rotation angle

const float MIN_UP_HEAD = -90;  // Minimum head upward angle
const float MAX_DOWN_HEAD = 65; // Maximum head downward angle

// Robot body and movement variables
float DEG_ROB = 0;              // Robot rotation
float ROB_X = 0, ROB_Z = 0;     // Robot position

// Camera control variables
bool viewCamera = true;
int light1enable = false;
int light2enable = false;

// Camera rotation and translation variables
float vDeg = 0;
float vX = 0;
float vY = 0;
float vZ = 0;

// Light 1 properties
float light1X = -8;
float light1Y = 1;
float light1Amb = 0.25;
float light1Dif = 0.1;
float light1Spec = 0.1;

// Light 2 (spotlight) properties
float light2X = 0;
float light2Z = -22;
float light2Y = 10;
float spotlight2_cutoff = 30;
float spotlight2_exponent = 10.0;
float light2Amb = 0.2;
float light2Dif = 1.0;
float light2Spec = 1.0;
//----------------------------------------------//

// This function is setting up the lights of the scene
// There is one point light and one spotlight (except of the amibient light of the scene)
void lightning() {

    GLfloat light1_position[] = { light1X, light1Y, light1Z, 1.0f };
    GLfloat light1_ambient[] = { light1Amb, light1Amb, light1Amb, 1.0f };
    GLfloat light1_diffuse[] = { light1Dif, light1Dif, light1Dif, 1.0f };
    GLfloat light1_specular[] = { light1Spec, light1Spec, light1Spec, 1.0f };

    // Attenuation factors
    GLfloat light1_constant_attenuation = 0.6f;
    GLfloat light1_linear_attenuation = 0.5f;
    GLfloat light1_quadratic_attenuation = 0.1f;

    // Set light properties
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

    // Set attenuation parameters
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, light1_constant_attenuation);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, light1_linear_attenuation);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, light1_quadratic_attenuation);

    // Define the spotlight position
    GLfloat spotlight_position[] = { light2X, light2Y, light2Z, 1.0f };

    // Define the spotlight's ambient, diffuse, and specular components
    GLfloat spotlight_ambient[] = { light2Amb, light2Amb, light2Amb, 1.0f };
    GLfloat spotlight_diffuse[] = { light2Dif, light2Dif, light2Dif, light2Dif }; // Bright white light
    GLfloat spotlight_specular[] = { light2Spec, light2Spec, light2Spec, light2Spec }; // Bright white specular

    // Define the spotlight direction
    GLfloat spotlight_direction[] = { 0.0f, -1.0f, 0.0f }; // Points downward

    // Define the spotlight's cutoff angle and exponent
    GLfloat spotlight_cutoff = spotlight2_cutoff; // Angle in degrees
    GLfloat spotlight_exponent = spotlight2_exponent; // Focus of the spotlight

    // Set spotlight properties
    glLightfv(GL_LIGHT2, GL_POSITION, spotlight_position);
    glLightfv(GL_LIGHT2, GL_AMBIENT, spotlight_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, spotlight_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spotlight_specular);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotlight_direction);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotlight_cutoff);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotlight_exponent);
}

// Function to initialize OpenGL settings
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  //white
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Initialize ImGui for the menu (thanks to Rania)
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();

    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    
    // Initialize light 0 (ambient lighting)
    GLfloat light0_position[] = { 1.0f, 1.0f, 1.0f, 0.0f }; // Directional light
    GLfloat light0_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat light0_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    glEnable(GL_LIGHT0);
}

//set up the camera
void setCamera() {
    if (viewCamera) {
        //main camera view
        glLoadIdentity();
        //starting points before rotations and translations
        Point3D center_camera_point_v = { 0.0 , 0.0, 0.0 };
        Point3D look_at_point_v = { 0.0, 0.0, -1.0 };
        Point3D right_camera_point_v = { 1.0, 0.0, 0.0 };
        //rotate the camera based on vDeg
        look_at_point_v = rYTrans(look_at_point_v, vDeg);
        right_camera_point_v = rYTrans(right_camera_point_v, vDeg);

        gluLookAt(
            center_camera_point_v.x + vX, center_camera_point_v.y + vY, center_camera_point_v.z + vZ,
            look_at_point_v.x + vX, look_at_point_v.y + vY, look_at_point_v.z + vZ, //look-at point
            0.0, 1.0, 0.0);//up_point.x, up_point.y, up_point.z);
    }

    else {
        glLoadIdentity();
        //robot's view
        //starting points before rotations and translations
        Point3D center_camera_point_r = { 0.4 , 0.25, -25 };
        Point3D look_at_point_r = { 0.4, 0.0, -20.0 };
        Point3D right_camera_point_r = { 20.0, 0.0, 0.4 };

        //apply transformations to simulate the robot's head movement
        center_camera_point_r = tTrans(center_camera_point_r, 0, 1.0, 25.5);
        center_camera_point_r = rXTrans(center_camera_point_r, DEG_HEAD_UD);
        center_camera_point_r = tTrans(center_camera_point_r, 0, -1.0, -25.5);

        look_at_point_r = tTrans(look_at_point_r, 0, 1, 25.5);
        look_at_point_r = rXTrans(look_at_point_r, DEG_HEAD_UD);
        look_at_point_r = tTrans(look_at_point_r, 0, -1.0, -25.5);

        right_camera_point_r = tTrans(right_camera_point_r, 0, 1, 25.5);
        right_camera_point_r = rXTrans(right_camera_point_r, DEG_HEAD_UD);
        right_camera_point_r = tTrans(right_camera_point_r, 0, -1.0, -25.5);

        look_at_point_r = tTrans(look_at_point_r, -0.4, -0.25, 24.99);
        look_at_point_r = rYTrans(look_at_point_r, DEG_HEAD_RL + DEG_ROB);
        look_at_point_r = tTrans(look_at_point_r, 0.4, 0.25, -25);

        center_camera_point_r = tTrans(center_camera_point_r, 0, 0, 25.5);
        center_camera_point_r = rYTrans(center_camera_point_r, DEG_HEAD_RL + DEG_ROB);
        center_camera_point_r = tTrans(center_camera_point_r, 0, 0, -25.5);

        right_camera_point_r = tTrans(right_camera_point_r, -0.4, -0.25, 24.99);
        right_camera_point_r = rYTrans(right_camera_point_r, DEG_HEAD_RL + DEG_ROB);
        right_camera_point_r = tTrans(right_camera_point_r, 0.4, 0.25, -25);

        gluLookAt(
            //0.4 + ROB_X, 0.25, -24.99 + ROB_Z,
            center_camera_point_r.x + ROB_X, center_camera_point_r.y, center_camera_point_r.z + ROB_Z,
            //  front_head_point[0] + ROB_X, front_head_point[1], front_head_point[2] + ROB_Z,  //look-at point
            look_at_point_r.x + ROB_X, look_at_point_r.y, look_at_point_r.z + ROB_Z, //look-at point
            //up_head_vec[0], up_head_vec[1], up_head_vec[2]);  //up vector
            0.0, 1.0, 0.0);//up_point.x, up_point.y, up_point.z);
    }
}

// drawing the robot's head
void drawHead() {
    glPushMatrix();
    glTranslatef(ROB_X, -1.0, -25.5 + ROB_Z);
    glRotatef(DEG_HEAD_RL + DEG_ROB, 0.0, 1.0, 0.0);
    glRotatef(DEG_HEAD_UD, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 1.0, 25.5);

    glBegin(GL_QUADS);
    //eyes
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.2, 0.0, -24.99); //so they will stay in front of the face
    glVertex3f(0.6, 0.0, -24.99);
    glVertex3f(0.6, 0.5, -24.99);
    glVertex3f(0.2, 0.5, -24.99);

    glVertex3f(-0.6, 0.0, -24.99);
    glVertex3f(-0.2, 0.0, -24.99);
    glVertex3f(-0.2, 0.5, -24.99);
    glVertex3f(-0.6, 0.5, -24.99);

    //front
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, 1.0, -25.0);
    glVertex3f(-1.0, -1.0, -25.0);
    glVertex3f(1.0, -1.0, -25.0);
    glVertex3f(1.0, 1.0, -25.0);
    //back
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, -26.0);
    glVertex3f(1.0, -1.0, -26.0);
    glVertex3f(-1.0, -1.0, -26.0);
    glVertex3f(-1.0, 1.0, -26.0);
    //right
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, 1.0, -25.0);
    glVertex3f(1.0, -1.0, -25.0);
    glVertex3f(1.0, -1.0, -26.0);
    glVertex3f(1.0, 1.0, -26.0);
    //left
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, 1.0, -26.0);
    glVertex3f(-1.0, -1.0, -26.0);
    glVertex3f(-1.0, -1.0, -25.0);
    glVertex3f(-1.0, 1.0, -25.0);
    //top
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -26.0);
    glVertex3f(-1.0, 1.0, -25.0);
    glVertex3f(1.0, 1.0, -25.0);
    glVertex3f(1.0, 1.0, -26.0);
    //bottom
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(-1.0, -1.0, -26.0);
    glVertex3f(-1.0, -1.0, -25.0);
    glVertex3f(1.0, -1.0, -25.0);
    glVertex3f(1.0, -1.0, -26.0);

    glEnd();
    glPopMatrix();
}

// drawing the robot's body
void drawBody() {

    glPushMatrix();
    glTranslatef(ROB_X, -5.0, ROB_Z - 25.5);
    glRotatef(DEG_ROB, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 5.0, 25.5);

    glBegin(GL_QUADS);
    //front
    glColor3f(0.129, 0.161, 0.18);
    glVertex3f(-1.25, -1.5, -24.0);
    glVertex3f(-1.25, -5.0, -24.0);
    glVertex3f(1.25, -5.0, -24.0);
    glVertex3f(1.25, -1.5, -24.0);
    //back
    glVertex3f(1.25, -1.5, -27.0);
    glVertex3f(1.25, -5.0, -27.0);
    glVertex3f(-1.25, -5.0, -27.0);
    glVertex3f(-1.25, -1.5, -27.0);
    //right
    glVertex3f(1.25, -1.5, -24.0);
    glVertex3f(1.25, -5.0, -24.0);
    glVertex3f(1.25, -5.0, -27.0);
    glVertex3f(1.25, -1.5, -27.0);
    //left
    glVertex3f(-1.25, -1.5, -27.0);
    glVertex3f(-1.25, -5.0, -27.0);
    glVertex3f(-1.25, -5.0, -24.0);
    glVertex3f(-1.25, -1.5, -24.0);
    //top
    glVertex3f(-1.25, -1.5, -27.0);
    glVertex3f(-1.25, -1.5, -24.0);
    glVertex3f(1.25, -1.5, -24.0);
    glVertex3f(1.25, -1.5, -27.0);
    //bottom
    glVertex3f(-1.25, -5.0, -27.0);
    glVertex3f(-1.25, -5.0, -24.0);
    glVertex3f(1.25, -5.0, -24.0);
    glVertex3f(1.25, -5.0, -27.0);

    glEnd();
    glPopMatrix();
}

// drawing the robot's neck
void drawNeck() {
    glPushMatrix();
    glTranslatef(ROB_X, -1.5, ROB_Z - 25.5);
    glRotatef(DEG_ROB, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 1.5, 0.0);

    glBegin(GL_QUADS);
    //front
    glColor3f(0.129, 0.161, 0.18);
    glVertex3f(-0.5, -1.0, 0.5);
    glVertex3f(-0.5, -1.5, 0.5);
    glVertex3f(0.5, -1.5, 0.5);
    glVertex3f(0.5, -1.0, 0.5);

    //back
    glVertex3f(0.5, -1, -0.5);
    glVertex3f(0.5, -1.5, -0.5);
    glVertex3f(-0.5, -1.5, -0.5);
    glVertex3f(-0.5, -1.0, -0.5);

    //right
    glVertex3f(0.5, -1.0, 0.5);
    glVertex3f(0.5, -1.5, 0.5);
    glVertex3f(0.5, -1.5, -0.5);
    glVertex3f(0.5, -1, -0.5);
    //left
    glVertex3f(-0.5, -1.0, -0.5);
    glVertex3f(-0.5, -1.5, -0.5);
    glVertex3f(-0.5, -1.5, 0.5);
    glVertex3f(-0.5, -1.0, 0.5);
    //top
    glVertex3f(-0.5, -1.0, -0.5);
    glVertex3f(-0.5, -1.0, 0.5);
    glVertex3f(0.5, -1.0, 0.5);
    glVertex3f(0.5, -1, -0.5);
    //bottom
    glVertex3f(-0.5, -1.5, -0.5);
    glVertex3f(-0.5, -1.5, 0.5);
    glVertex3f(0.5, -1.5, 0.5);
    glVertex3f(0.5, -1.5, -0.5);
    glEnd();
    glPopMatrix();


}

// drawing the robot's shoulder
void drawShoulder() {
    glPushMatrix();

    glTranslatef(-1.25, -1.75, -25.5);
    glTranslatef(ROB_X, 0.0, ROB_Z);
    glTranslatef(1.25, 1.75, 0.0);
    glRotatef(DEG_ROB, 0.0, 1.0, 0.0);

    glTranslatef(-1.25, -1.75, 0.0);
    glRotatef(DEG_SHO, 1.0, 0.0, 0.0);
    glTranslatef(1.25, 1.75, 25.5);

    glBegin(GL_QUADS);
    //front
    glColor3f(0.129, 0.161, 0.18);
    glVertex3f(-2.0, -1.5, -25.25);  //1
    glVertex3f(-2.0, -2.0, -25.25);  //2
    glVertex3f(-1.25, -2.0, -25.25);  //3 
    glVertex3f(-1.25, -1.5, -25.25);  //4
    //back
    glVertex3f(-1.25, -1.5, -25.75);  //8
    glVertex3f(-1.25, -2.0, -25.75);  //7
    glVertex3f(-2.0, -2.0, -25.75);  //6
    glVertex3f(-2.0, -1.5, -25.75);  //5
    //right
    glVertex3f(-1.25, -1.5, -25.25);
    glVertex3f(-1.25, -2.0, -25.25);
    glVertex3f(-1.25, -2.0, -25.75);
    glVertex3f(-1.25, -1.5, -25.75);
    //left
    glVertex3f(-2.0, -1.5, -25.75);
    glVertex3f(-2.0, -2.0, -25.75);
    glVertex3f(-2.0, -2.0, -25.25);
    glVertex3f(-2.0, -1.5, -25.25);
    //top
    glVertex3f(-2.0, -1.5, -25.75);
    glVertex3f(-2.0, -1.5, -25.25);
    glVertex3f(-1.25, -1.5, -25.25);
    glVertex3f(-1.25, -1.5, -25.75);
    //bottom
    glVertex3f(-2.0, -2.0, -25.75);
    glVertex3f(-1.25, -2.0, -25.25);
    glVertex3f(-2.0, -2.0, -25.25);
    glVertex3f(-1.25, -2.0, -25.75);

    glEnd();
    glPopMatrix();
}

// drawing the robot's "elbow"
void drawElbow() {
    glPushMatrix();

    glTranslatef(-2.0, -1.75, -25.5);
    glTranslatef(ROB_X, 0.0, ROB_Z);

    glTranslatef(2.0, 1.75, 0.0);
    glRotatef(DEG_ROB, 0.0, 1.0, 0.0);
    glTranslatef(-2.0, -1.75, 0.0);

    glRotatef(DEG_SHO, 1.0, 0.0, 0.0);

    glRotatef(DEG_ELB, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 1.75, 25.5);

    glBegin(GL_QUADS);
    //front
    glColor3f(0.129, 0.161, 0.18);
    glVertex3f(-4.0, -2.0, -25.25);
    glVertex3f(-4.0, -2.5, -25.25);
    glVertex3f(-2.0, -2.0, -25.25);
    glVertex3f(-2.0, -1.5, -25.25);
    //back
    glVertex3f(-2.0, -1.5, -25.75);
    glVertex3f(-2.0, -2.0, -25.75);
    glVertex3f(-4.0, -2.5, -25.75);
    glVertex3f(-4.0, -2.0, -25.75);
    //right
    glVertex3f(-2.0, -1.5, -25.75); //5
    glVertex3f(-2.0, -2.0, -25.75); //6
    glVertex3f(-2.0, -2.0, -25.25); //2
    glVertex3f(-2.0, -1.5, -25.25); //1
    //left
    glVertex3f(-4.0, -2.0, -25.75); //12
    glVertex3f(-4.0, -2.5, -25.75); //11
    glVertex3f(-4.0, -2.5, -25.25); //10
    glVertex3f(-4.0, -2.0, -25.25); //9
    //top
    glVertex3f(-4.0, -2.0, -25.75);
    glVertex3f(-4.0, -2.0, -25.25);
    glVertex3f(-2.0, -1.5, -25.25);
    glVertex3f(-2.0, -1.5, -25.75);
    //bottom
    glVertex3f(-4.0, -2.5, -25.75);
    glVertex3f(-4.0, -2.5, -25.25);
    glVertex3f(-2.0, -2.0, -25.25);
    glVertex3f(-2.0, -2.0, -25.75);

    glEnd();
    glPopMatrix();
}

// drawing the robot's "palm"
void drawPalm() {

    glPushMatrix();

    glTranslatef(-2.0, -1.75, -25.5);
    glTranslatef(ROB_X, 0.0, ROB_Z);

    glTranslatef(2.0, 1.75, 0.0);
    glRotatef(DEG_ROB, 0.0, 1.0, 0.0);
    glTranslatef(-2.0, -1.75, 0.0);

    glRotatef(DEG_SHO, 1.0, 0.0, 0.0);

    glRotatef(DEG_ELB, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 1.75, 25.5);

    glTranslatef(-4.0, -2.25, -25.5);
    glRotatef(DEG_PALM, 1.0, 0.0, 0.0);
    glTranslatef(4.0, 2.25, 25.5);

    glBegin(GL_QUADS);
    //front
    glColor3f(0.129, 0.161, 0.18);
    glVertex3f(-4.3, -2.1, -25.35); //1
    glVertex3f(-4.3, -2.4, -25.35); //2
    glVertex3f(-4, -2.4, -25.35);  //4
    glVertex3f(-4, -2.1, -25.35); //3
    //back
    glVertex3f(-4, -2.1, -25.65); //8
    glVertex3f(-4, -2.4, -25.65); //7
    glVertex3f(-4.3, -2.4, -25.65); //6
    glVertex3f(-4.3, -2.1, -25.65); //5
    //right
    glVertex3f(-4, -2.1, -25.35);
    glVertex3f(-4, -2.4, -25.35);
    glVertex3f(-4, -2.4, -25.65);
    glVertex3f(-4, -2.1, -25.65);
    //left
    glVertex3f(-4.3, -2.1, -25.65);
    glVertex3f(-4.3, -2.4, -25.65);
    glVertex3f(-4.3, -2.4, -25.35);
    glVertex3f(-4.3, -2.1, -25.35);
    //top
    glVertex3f(-4.3, -2.1, -25.65);
    glVertex3f(-4.3, -2.1, -25.35);
    glVertex3f(-4, -2.1, -25.35);
    glVertex3f(-4, -2.1, -25.65);
    //bottom
    glVertex3f(-4.3, -2.4, -25.65);
    glVertex3f(-4.3, -2.4, -25.35);
    glVertex3f(-4, -2.4, -25.35);
    glVertex3f(-4, -2.4, -25.65);

    glVertex3f(-4.5, -2.1, -25.65);
    glVertex3f(-4.5, -2.1, -25.35);
    glVertex3f(-4.3, -2.1, -25.35);
    glVertex3f(-4.3, -2.1, -25.65);

    glVertex3f(-4.5, -2.4, -25.65);
    glVertex3f(-4.5, -2.4, -25.35);
    glVertex3f(-4.3, -2.4, -25.35);
    glVertex3f(-4.3, -2.4, -25.65);

    glEnd();
    glPopMatrix();
}

// drawing the robot's hand 
// this function calls the 3 other functions that draw the parts of the hand
void drawHand() {
    drawShoulder();
    drawElbow();
    drawPalm();
}

// This function render the entire scene
void display() {
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    // display the menu with imgui
    if (show_menu)
        display_menu();
    // enabling/ disabling lights
    if (light1enable) {
        glEnable(GL_LIGHT1);
        lightning();
    }
    else {
        glDisable(GL_LIGHT1);
    }
    if (light2enable) {
        glEnable(GL_LIGHT2);
        lightning();
    }
    else {
        glDisable(GL_LIGHT2);
    }

    // rendering the menu
    ImGui::Render();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);
    setCamera();
    //draw the robot
    drawHead();
    drawNeck();
    drawBody();
    drawHand();
    drawTable();
    drawDrawers();
    drawFloor();
    drawTeapot();
    drawLamp();

    glDisable(GL_LIGHTING);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    glEnable(GL_LIGHTING);

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

//Handling window resizing, using a projective projection
void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1; //to prevent division by zero
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    ImGui_ImplGLUT_ReshapeFunc(width, height);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 70.0);
    glMatrixMode(GL_MODELVIEW);
}

// Handling keyboard input
void keyboardPressed(unsigned char key, int x, int y) {
    ImGui_ImplGLUT_KeyboardFunc(key, x, y);
    
    char lkey = tolower(key); //converting the key to lowercase to handle both upper and lower case inputs
    // Switch statement to handle different key presses
    switch (lkey)
    {
    case 'l':
        DEG_HEAD_RL += 5;
        break;
    case 'k':
        DEG_HEAD_RL -= 5;
        break;
    case 'o':
        if (DEG_HEAD_UD < MAX_DOWN_HEAD)
            DEG_HEAD_UD += 5;
        break;
    case 'i':
        if (DEG_HEAD_UD > MIN_UP_HEAD)
            DEG_HEAD_UD -= 5;
        break;
    case 'j':
        if (DEG_ELB < MAX_ELB_DEG)  //so it will not colide with the body
            DEG_ELB += 5;
        break;
    case 'h':
        if (DEG_ELB > MIN_ELB_DEG)
            DEG_ELB -= 5;
        break;
    case 'u':
        DEG_SHO -= 5;
        break;
    case 'y':
        DEG_SHO += 5;
        break;
    case 'a':
        ROB_X -= 0.2;
        break;
    case 'd':
        ROB_X += 0.2;
        break;
    case 'w':
        ROB_Z -= 0.2;
        break;
    case 's':
        ROB_Z += 0.2;
        break;
    case 'e':
        DEG_ROB -= 5;
        break;
    case 'r':
        DEG_ROB += 5;
        break;
    case 'n':
        DEG_PALM += 5;
        break;
    case 'm':
        DEG_PALM -= 5;
        break;
    case 'v':
        if (viewCamera)
            viewCamera = false;
        else
            viewCamera = true;
        break;
    case 'c':
        if (show_menu)
            show_menu = false;
        else
            show_menu = true;
        break;

    case 'z':
        if (light1enable) {
            light1enable = false;
            glDisable(GL_LIGHT1);
        }
        else {
            glEnable(GL_LIGHT1);
            light1enable = true;
        }
        break;
    case 'x':
        if (light2enable) {
            light2enable = false;
            glDisable(GL_LIGHT2);
        }

        else {
            glEnable(GL_LIGHT2);
            light2enable = true;
        }
        break;
    }

    display();
}


void display_menu()
{
    ImGui::Begin("Menu", &show_menu);

    if (ImGui::CollapsingHeader("Camera"))
    {
        ImGui::SliderFloat("camera x position", &vX, -10.0f, 10.0f);
        ImGui::SliderFloat("camera y position", &vY, -10.0f, 10.0f);
        ImGui::SliderFloat("camera z position", &vZ, -10.0f, 10.0f);
        ImGui::SliderFloat("rotate the camera", &vDeg, -45.0f, 45.0f);
    }

    if (ImGui::CollapsingHeader("Adjust Lights"))
    {
        ImGui::SliderFloat("adjust lamp's ambient light", &light1Amb, 0.0f, 1.0f);
        ImGui::SliderFloat("adjust lamp's diffuse light", &light1Dif, 0.0f, 1.0f);
        ImGui::SliderFloat("adjust lamp's specular light", &light1Spec, 0.0f, 1.0f);
        ImGui::SliderFloat("translate the lamp", &light1Z, -14.0f, -30.0f);
        ImGui::RadioButton("enable lamp", &light1enable, 1); ImGui::SameLine();
        ImGui::RadioButton("disable lamp", &light1enable, 0);
        ImGui::Separator();
        ImGui::SliderFloat("adjust spotlight's ambient light", &light2Amb, 0.0f, 1.0f);
        ImGui::SliderFloat("adjust spotlight's diffuse light", &light2Dif, 0.0f, 1.0f);
        ImGui::SliderFloat("adjust spotlight's specular light", &light2Spec, 0.0f, 1.0f);
        ImGui::SliderFloat("translate the spotlight - x", &light2X, -6.0f, 6.0f);
        ImGui::SliderFloat("translate the spotlight - y", &light2Y, 7.0f, 20.0f);
        ImGui::SliderFloat("translate the spotlight - z", &light2Z, -14.0f, -30.0f);
        ImGui::RadioButton("enable spotlight", &light2enable, 1); ImGui::SameLine();
        ImGui::RadioButton("disable spotlight", &light2enable, 0);
        ImGui::Separator();
    }

    if (ImGui::CollapsingHeader("Help")) {
        ImGui::Text("Hi :) Welcome to Bob's room");
        ImGui::TextWrapped("Here is all the information you need in order to have more fun then just look at Bob standing");
        ImGui::Separator();
        ImGui::Text("CAMERA:");
        ImGui::TextWrapped("this category affect the camera - your view point, you can change the settings to see the room from diffrent spots and angles");
        ImGui::Separator();
        ImGui::Text("LIGHTS:");
        ImGui::TextWrapped("this category affect the cone lamp and the spotlight.");
        ImGui::TextWrapped("you can control the light settings and see how it's effect the objects from different angles");
        ImGui::Separator();
        ImGui::Text("The Keys:");
        ImGui::Columns(2, "keyboard");
        ImGui::Separator();
        ImGui::Text("Key"); ImGui::NextColumn();
        ImGui::Text("Action"); ImGui::NextColumn();
        ImGui::Separator();
        ImGui::Text("'w'"); ImGui::NextColumn(); ImGui::Text("move the robot backward"); ImGui::NextColumn();
        ImGui::Text("'s'"); ImGui::NextColumn(); ImGui::Text("move the robot forward"); ImGui::NextColumn();
        ImGui::Text("'d'"); ImGui::NextColumn(); ImGui::Text("move the robot left"); ImGui::NextColumn();
        ImGui::Text("'a'"); ImGui::NextColumn(); ImGui::Text("move the robot right"); ImGui::NextColumn();
        ImGui::Text("'o'"); ImGui::NextColumn(); ImGui::Text("rotate the robot's head down"); ImGui::NextColumn();
        ImGui::Text("'i'"); ImGui::NextColumn(); ImGui::Text("rotate the robot's head up"); ImGui::NextColumn();
        ImGui::Text("'l'"); ImGui::NextColumn(); ImGui::Text("spin the robot's head left (of the robot)"); ImGui::NextColumn();
        ImGui::Text("'k'"); ImGui::NextColumn(); ImGui::Text("spin the robot's head right"); ImGui::NextColumn();
        ImGui::Text("'r'"); ImGui::NextColumn(); ImGui::Text("spin the robot to the left (of the robot)"); ImGui::NextColumn();
        ImGui::Text("'e'"); ImGui::NextColumn(); ImGui::Text("spin the robot to the right"); ImGui::NextColumn();
        ImGui::Text("'m'"); ImGui::NextColumn(); ImGui::Text("spin the robot's palm right"); ImGui::NextColumn();
        ImGui::Text("'n'"); ImGui::NextColumn(); ImGui::Text("spin the robot's palm left"); ImGui::NextColumn();
        ImGui::Text("'u'"); ImGui::NextColumn(); ImGui::Text("spin the robot's sholder right"); ImGui::NextColumn();
        ImGui::Text("'y'"); ImGui::NextColumn(); ImGui::Text("spin the robot's sholder left"); ImGui::NextColumn();
        ImGui::Text("'j'"); ImGui::NextColumn(); ImGui::Text("spin the robot's elbow right"); ImGui::NextColumn();
        ImGui::Text("'h'"); ImGui::NextColumn(); ImGui::Text("spin the robot's elbow left"); ImGui::NextColumn();
        ImGui::Text("'v'"); ImGui::NextColumn(); ImGui::Text("change the view point (between camera and the robot)"); ImGui::NextColumn();
        ImGui::Text("'c'"); ImGui::NextColumn(); ImGui::Text("show/ hide the menu"); ImGui::NextColumn();
        ImGui::Text("'z'"); ImGui::NextColumn(); ImGui::Text("turn on/ off the lamp"); ImGui::NextColumn();
        ImGui::Text("'x'"); ImGui::NextColumn(); ImGui::Text("turn on/ off the spotlight"); ImGui::NextColumn();
        ImGui::Columns(1);
    }
    ImVec4 buttonColor = ImColor(1.0f, 0.392f, 0.125f, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
    ImVec4 buttonColorHov = ImColor(0.871f, 0.267f, 0.0f, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonColorHov);
    ImVec4 buttonColorAct = ImColor(0.761f, 0.235f, 0.0f, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonColorAct);
    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.5f);
    ImGui::Indent(ImGui::GetWindowWidth() * 0.25f);
    if (ImGui::Button("Quit", ImVec2(ImGui::GetWindowSize().x * 0.5f, 0.0f))) {
        exit(0);
    }
    ImGui::PopStyleColor(3);
    ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::End();
}
