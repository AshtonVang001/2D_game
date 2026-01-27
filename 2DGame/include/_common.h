#ifndef _COMMON_H
#define _COMMON_H

#include <GL/glew.h>
#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <string.h>
#include <time.h>
#include <fstream>

#define PI 3.14159265358979

using namespace std;

typedef struct{

    float x;
    float y;

} vec2;

typedef struct{

    float x;
    float y;
    float z;

} vec3;

typedef struct{

    float r;
    float g;
    float b;

} col3;

typedef struct{

    float r;
    float g;
    float b;
    float a;

} col4;


#endif // _COMMON_H
