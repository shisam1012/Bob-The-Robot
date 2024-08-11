#pragma once
#include "glandstuff.h"

//rotation of a given point about the X axis
Point3D rXTrans(const Point3D&, float );
//rotation of a given point about the Y axis
Point3D rYTrans(const Point3D&, float);
//rotation of a given point about the Z axis
Point3D rZTrans(const Point3D&, float);
//translation of a given point in the 3D world
Point3D tTrans(const Point3D&, float, float, float);
