//
//  input.c
//  opengl
//
//  Created by Vicky D on 7/9/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array.h"
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

extern int width;
extern int height;

extern double rotate_x;
extern double rotate_y;
extern double rotate_z;

extern double translate_x;
extern double translate_y;
extern double translate_z;

extern float radius;
extern signed char *cubes;

extern int keys[150];
extern int special_keys[150];

extern float camNormal[];

extern float speed = 1;

int mouse_x_prev;
int mouse_y_prev;

void changeSpeed(float new) {
    speed = new;
}

void doStuff() {
    
    // Delete Key
    if (keys[127] == 1) {
        exit(0);
    }
    
    // D Key
    if (keys[100] == 1) {
        translate_x += camNormal[2]/10 * speed;
        translate_z += camNormal[0]/10 * speed;
    }
    
    // A key
    if (keys[97] == 1) {
        translate_x -= camNormal[2]/10 * speed;
        translate_z -= camNormal[0]/10 * speed;
    }
    
    // W key
    if (keys[119] == 1) {
        //printf("hello");
        translate_x += camNormal[0]/10 * speed;
        translate_y -= camNormal[1]/10 * speed;
        translate_z -= camNormal[2]/10 * speed;
    }
    
    // S key
    if (keys[115] == 1) {
        translate_x -= camNormal[0]/10 * speed;
        translate_y += camNormal[1]/10 * speed;
        translate_z += camNormal[2]/10 * speed;
    }
    // Space key
    if (keys[32] == 1)
        translate_y -= 0.1;
    
    // Q key
    if (keys[113] == 1)
        translate_y += 0.1;
    
    // E key
    if (keys[101] == 1)
        translate_y -= 0.1;
    
    if (special_keys[GLUT_KEY_RIGHT] == 1)
        rotate_y += 5;
    
    if (special_keys[GLUT_KEY_LEFT] == 1)
        rotate_y -= 5;
    
    if (special_keys[GLUT_KEY_UP] == 1)
        rotate_x -= 5;
    
    if (special_keys[GLUT_KEY_DOWN] == 1)
        rotate_x += 5;
    
    float yaw = degreesToRadians(rotate_y);
    float pitch = degreesToRadians(-rotate_x);
    camNormal[2] = cos(yaw) * cos(pitch);
    camNormal[0] = sin(yaw) * cos(pitch);
    camNormal[1] = sin(pitch);
    
    //int offset = radius * 20;
    
    //int x = (int)((translate_x/(radius*2)) + size);
    //int y = (int)(((translate_y + offset)/(radius*2)) + 64);
    //int z = (int)((translate_z/(radius*2)) + size);
    
    /**if(cubes[getIndex(x, y, z)] < 0) {
        if(cubes[getIndex(x, y - 1, z)] < 0) {
            if(cubes[getIndex(x, y + 1, z)] < 0) {
                translate_y += 0.2;
            } else {
                translate_y = ((y + 1 - 64) * (radius*2)) - offset;
            }
        } else {
            translate_y = ((y - 1 - 64) * (radius*2)) - offset;
        }
    } else {
        translate_y = ((y - 64) * (radius*2)) - offset;
    }**/
    
    // Request display update
    glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y)
{
    keys[(int)key] = 1;
}

void keyUp(unsigned char key, int x, int y)
{
    keys[(int)key] = 0;
}

void keySpecialDown(int key, int x, int y)
{
    special_keys[key] = 1;
}

void keySpecialUp(int key, int x, int y)
{
    special_keys[key] = 0;
}

void mouseRoutine(int x, int y) {
    //translate_x = -(x - width/2)/128.0;
    //translate_y = -(y - height/2 + 100)/128.0;
    
    /**
    rotate_y += (x - mouse_x_prev)/1;
    rotate_x += (y - mouse_y_prev)/1;
    
    mouse_x_prev = x;
    mouse_y_prev = y;
    
    
    float yaw = degreesToRadians(rotate_y);
    float pitch = degreesToRadians(-rotate_x);
    camNormal[2] = cos(yaw) * cos(pitch);
    camNormal[0] = sin(yaw) * cos(pitch);
    camNormal[1] = sin(pitch);
    
    //glutWarpPointer(width/2, height/2);
    **/
    glutPostRedisplay();
}

