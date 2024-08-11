#include "transformations.h"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//converting from degrees to radians
double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

//rotation of a given point about the X axis
Point3D rXTrans(const Point3D& p1, float angle_deg) {
    double angle_rad = degreesToRadians(angle_deg);

    Point3D res = { p1.x, p1.y * cos(angle_rad) - p1.z * sin(angle_rad), p1.y * sin(angle_rad) + p1.z * cos(angle_rad) };
    return res;
}

//rotation of a given point about the Y axis
Point3D rYTrans(const Point3D& p1, float angle_deg) {
    double angle_rad = degreesToRadians(angle_deg);

    Point3D res = { p1.z * sin(angle_rad) + p1.x * cos(angle_rad), p1.y, p1.z * cos(angle_rad) - p1.x * sin(angle_rad) };
    return res;
}

//rotation of a given point about the Z axis
Point3D rZTrans(const Point3D& p1, float angle_deg) {
    double angle_rad = degreesToRadians(angle_deg);
    Point3D res = { p1.x * cos(angle_rad) - p1.y * sin(angle_rad), p1.x * sin(angle_rad) + p1.y * cos(angle_rad),  p1.z };
    return res;
}

//translation of a given point in the 3D world
Point3D tTrans(const Point3D& p1, float tx, float ty, float tz) {
    Point3D res = { p1.x + tx, p1.y + ty, p1.z + tz };
    return res;
}
