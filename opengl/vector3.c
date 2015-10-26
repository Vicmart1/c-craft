//
//  vector2.c
//  opengl
//
//  Created by Vicky D on 7/9/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "vector3.h"

void Vector3_Subtract(float *target, float first[], float second[]) {
    target[0] = second[0] - first[0];
    target[1] = second[1] - first[1];
    target[2] = second[2] - first[2];
}

void Vector3_Add(float *target, float first[], float second[]) {
    target[0] = second[0] + first[0];
    target[1] = second[1] + first[1];
    target[2] = second[2] + first[2];
}

void Vector3_Multi(float *target, float first[], float factor) {
    target[0] = first[0] * factor;
    target[1] = first[1] * factor;
    target[2] = first[2] * factor;
}

float Vector3_Magnitude(float vector[]) {
    return sqrt(pow(vector[0],2) + pow(vector[1],2) + pow(vector[2],2));
}

void Vector3_Normalize(float *target, float vector[]) {
    float mag = Vector3_Magnitude(vector);
    target[0] = (float)vector[0]/mag;
    target[1] = (float)vector[1]/mag;
    target[2] = (float)vector[2]/mag;
}