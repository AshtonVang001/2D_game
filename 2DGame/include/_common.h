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

const float imgRatioX = 8;          //2912
const float imgRatioY = 5.015;      //1824
const float worldScale = 4.5;

static int levelModifier = 1;
static int coinCount = 0;

#endif // _COMMON_H
