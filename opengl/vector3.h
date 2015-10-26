//
//  vector2.h
//  opengl
//
//  Created by Vicky D on 7/9/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#ifndef opengl_vector3_h
#define opengl_vector3_h
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


typedef struct {
    float x;
    float y;
    float z;
} Vector3;

void Vector3_Subtract(float *, float [], float []);
void Vector3_Add(float *, float [], float []);
void Vector3_Multi(float *, float [], float );
float Vector3_Magnitude(float []);
void Vector3_Normalize(float *, float []);


#endif
