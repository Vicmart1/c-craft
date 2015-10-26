//
//  draw.c
//  opengl
//
//  Created by Vicky D on 7/9/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array.h"
#include "vector3.h"
#include "texture.h"
#include "chunk.h"
#include "draw.h"
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

extern float radius;

extern double translate_x;
extern double translate_y;
extern double translate_z;

extern float camNormal[];

void drawCube(float center[3], float radius, int xyz[3], int type, struct chunk *chunk) {
    
    signed char *cubes = chunk->cubes;
    if(type == 1 && xyz[1] + 1 < 8 * 2 && cubes[getIndex(xyz[0], xyz[1] + 1, xyz[2])] != -1)
        type = 3;
    
    float coor[8] = { 0 };
    glColor3f( 1.0f, 1.0f, 1.0f );
    
    /**
    if(xyz[2] + 1 < 16) {
        getTextCoor(coor, type, 1);
        float xoffset = 0;
        float yoffset = 0;
        float zoffset = 0;
        
        if(chunk->cubes[getIndex(xyz[0], xyz[1], xyz[2] + 1)] != -1) {
            zoffset += radius;
        }
        
        float side0[3] = {radius + center[0] + xoffset,  -radius + center[1] + yoffset, radius + center[2]};
        float side1[3] = {radius + center[0] + xoffset,  radius + center[1] + yoffset, radius + center[2] + zoffset};
        float side2[3] = {-radius + center[0] + xoffset,  radius + center[1] + yoffset, radius + center[2] + zoffset};
        float side3[3] = {-radius + center[0] + xoffset,  -radius + center[1] + yoffset, radius + center[2]};
        
        addSide(side0[0], side0[1], side0[2], coor[6], coor[7],
                side1[0], side1[1], side1[2], coor[0], coor[1],
                side2[0], side2[1], side2[2], coor[2], coor[3],
                side2[0], side2[1], side2[2], coor[2], coor[3],
                side3[0], side3[1], side3[2], coor[4], coor[5],
                side0[0], side0[1], side0[2], coor[6], coor[7],
                chunk);
    }**/
    
    // FRONT
    float normal[] = {0, 0, 1};
    struct chunk *next = chunk->front;
    if((xyz[2] + 1 >= 8 * 2 && (!next || next->cubes[getIndex(xyz[0], xyz[1], 0)] == -1)) || (xyz[2] + 1 < 16 && cubes[getIndex(xyz[0], xyz[1], xyz[2] + 1)] < 0)) {
        getTextCoor(coor, type, 1);
        
        addSide(radius + center[0],  -radius + center[1],  radius + center[2], coor[6], coor[7],
                radius + center[0],  radius + center[1], radius + center[2], coor[0], coor[1],
                -radius + center[0],  radius + center[1], radius + center[2], coor[2], coor[3],
                -radius + center[0],  radius + center[1],  radius + center[2], coor[2], coor[3],
                -radius + center[0],  -radius + center[1], radius + center[2], coor[4], coor[5],
                radius + center[0],  -radius + center[1], radius + center[2], coor[6], coor[7],
                chunk);
    }
    
    // BACK
    normal[2] = -1;
    next = chunk->back;
    if((xyz[2] - 1 < 0 && (!next || next->cubes[getIndex(xyz[0], xyz[1], 15)] == -1)) || (xyz[2] - 1 >= 0 && cubes[getIndex(xyz[0], xyz[1], xyz[2] - 1)] < 0 )) {
        getTextCoor(coor, type, 2);

        addSide(-radius + center[0],  radius + center[1],  -radius + center[2], coor[0], coor[1],
                radius + center[0],  radius + center[1], -radius + center[2], coor[2], coor[3],
                radius + center[0],  -radius + center[1], -radius + center[2], coor[4], coor[5],
                radius + center[0],  -radius + center[1],  -radius + center[2], coor[4], coor[5],
                -radius + center[0],  -radius + center[1], -radius + center[2], coor[6], coor[7],
                -radius + center[0],  radius + center[1], -radius + center[2], coor[0], coor[1],
                chunk);
    }
    
    // RIGHT
    normal[2] = 0;
    normal[0] = 1;
    next = chunk->right;
    if((xyz[0] + 1 >= 16 && (!next || next->cubes[getIndex(0, xyz[1], xyz[2])] == -1)) || (xyz[0] + 1 < 16 && cubes[getIndex(xyz[0] + 1, xyz[1], xyz[2])] < 0)) {
        getTextCoor(coor, type, 3);

        addSide(radius + center[0],  -radius + center[1],  -radius + center[2], coor[6], coor[7],
                radius + center[0],  radius + center[1], -radius + center[2], coor[0], coor[1],
                radius + center[0],  radius + center[1], radius + center[2], coor[2], coor[3],
                radius + center[0],  radius + center[1],  radius + center[2], coor[2], coor[3],
                radius + center[0],  -radius + center[1], radius + center[2], coor[4], coor[5],
                radius + center[0],  -radius + center[1], -radius + center[2], coor[6], coor[7],
                chunk);
    }
    
    // LEFT
    normal[0] = -1;
    next = chunk->left;
    //if(next) printf("%i\n", next->cubes[getIndex(15, xyz[1], xyz[2])]);
    if((xyz[0] - 1 < 0 && (!next || next->cubes[getIndex(15, xyz[1], xyz[2])] == -1)) || (xyz[0] - 1 >= 0 && cubes[getIndex(xyz[0] - 1, xyz[1], xyz[2])] < 0)) {
        getTextCoor(coor, type, 4);
        
        addSide(-radius + center[0],  -radius + center[1],  radius + center[2], coor[2], coor[7],
                -radius + center[0],  radius + center[1], radius + center[2], coor[4], coor[1],
                -radius + center[0],  radius + center[1], -radius + center[2], coor[6], coor[3],
                -radius + center[0],  radius + center[1],  -radius + center[2], coor[6], coor[3],
                -radius + center[0],  -radius + center[1], -radius + center[2], coor[0], coor[5],
                -radius + center[0],  -radius + center[1], radius + center[2], coor[2], coor[7],
                chunk);
    }
    
    // TOP
    normal[0] = 0;
    normal[1] = 1;
    next = chunk->top;
    if((xyz[1] + 1 >= 16 && (!next || next->cubes[getIndex(xyz[0], 0, xyz[2])] == -1)) || (xyz[1] + 1 < 16 && cubes[getIndex(xyz[0], xyz[1] + 1, xyz[2])] < 0)) {
        getTextCoor(coor, type, 5);
        
        addSide(radius + center[0],  radius + center[1],  radius + center[2], coor[0], coor[1],
                     radius + center[0],  radius + center[1], -radius + center[2], coor[2], coor[3],
                     -radius + center[0],  radius + center[1], -radius + center[2], coor[4], coor[5],
                     -radius + center[0],  radius + center[1],  -radius + center[2], coor[4], coor[5],
                     -radius + center[0],  radius + center[1], radius + center[2], coor[6], coor[7],
                     radius + center[0],  radius + center[1], radius + center[2], coor[0], coor[1],
                        chunk);
    }
    
    // BOTTOM
    next = chunk->bottom;
    normal[1] = -1;
    if((xyz[1] - 1 < 0 && (!next || next->cubes[getIndex(xyz[0], 15, xyz[2])] == -1)) || (xyz[1] - 1 >= 0 && cubes[getIndex(xyz[0], xyz[1] - 1, xyz[2])] < 0)) {
        getTextCoor(coor, type, 6);

        addSide(radius + center[0],  -radius + center[1],  -radius + center[2], coor[0], coor[1],
                radius + center[0],  -radius + center[1], radius + center[2], coor[2], coor[3],
                -radius + center[0],  -radius + center[1], radius + center[2], coor[4], coor[5],
                -radius + center[0],  -radius + center[1],  radius + center[2], coor[4], coor[5],
                -radius + center[0],  -radius + center[1], -radius + center[2], coor[6], coor[7],
                radius + center[0],  -radius + center[1], -radius + center[2], coor[0], coor[1],
                chunk);
    }
}

void addSide(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat u1, GLfloat v1,
                  GLfloat x2, GLfloat y2, GLfloat z2, GLfloat u2, GLfloat v2,
                  GLfloat x3, GLfloat y3, GLfloat z3, GLfloat u3, GLfloat v3,
                  GLfloat x4, GLfloat y4, GLfloat z4, GLfloat u4, GLfloat v4,
                  GLfloat x5, GLfloat y5, GLfloat z5, GLfloat u5, GLfloat v5,
                  GLfloat x6, GLfloat y6, GLfloat z6, GLfloat u6, GLfloat v6,
                    struct chunk *chunk) {
    
    // Vertex 1
    chunk->allverticies[chunk->verticiesnum].x = x1;
    chunk->allverticies[chunk->verticiesnum].y = y1;
    chunk->allverticies[chunk->verticiesnum].z = z1;
    
    chunk->alluvcoors[chunk->uvcoornum].u = u1;
    chunk->alluvcoors[chunk->uvcoornum].v = v1;
    
    chunk->verticiesnum++;
    chunk->uvcoornum++;
    
    // Vertex 2
    if(chunk->verticiesnum < INT32_MAX) {
    chunk->allverticies[chunk->verticiesnum].x = x2;
    chunk->allverticies[chunk->verticiesnum].y = y2;
    chunk->allverticies[chunk->verticiesnum].z = z2;
    
    chunk->alluvcoors[chunk->uvcoornum].u = u2;
    chunk->alluvcoors[chunk->uvcoornum].v = v2;
    }
    chunk->verticiesnum++;
    chunk->uvcoornum++;
    
    // Vertex 3
    chunk->allverticies[chunk->verticiesnum].x = x3;
    chunk->allverticies[chunk->verticiesnum].y = y3;
    chunk->allverticies[chunk->verticiesnum].z = z3;
    
    chunk->alluvcoors[chunk->uvcoornum].u = u3;
    chunk->alluvcoors[chunk->uvcoornum].v = v3;
    
    chunk->verticiesnum++;
    chunk->uvcoornum++;
    
    // Vertex 4
    chunk->allverticies[chunk->verticiesnum].x = x4;
    chunk->allverticies[chunk->verticiesnum].y = y4;
    chunk->allverticies[chunk->verticiesnum].z = z4;
    
    chunk->alluvcoors[chunk->uvcoornum].u = u4;
    chunk->alluvcoors[chunk->uvcoornum].v = v4;
    
    chunk->verticiesnum++;
    chunk->uvcoornum++;
    
    // Vertex 5
    chunk->allverticies[chunk->verticiesnum].x = x5;
    chunk->allverticies[chunk->verticiesnum].y = y5;
    chunk->allverticies[chunk->verticiesnum].z = z5;
    
    chunk->alluvcoors[chunk->uvcoornum].u = u5;
    chunk->alluvcoors[chunk->uvcoornum].v = v5;
    
    chunk->verticiesnum++;
    chunk->uvcoornum++;
    
    // Vertex 6
    chunk->allverticies[chunk->verticiesnum].x = x6;
    chunk->allverticies[chunk->verticiesnum].y = y6;
    chunk->allverticies[chunk->verticiesnum].z = z6;
    
    chunk->alluvcoors[chunk->uvcoornum].u = u6;
    chunk->alluvcoors[chunk->uvcoornum].v = v6;
    
    chunk->verticiesnum++;
    chunk->uvcoornum++;
    
}

void drawTriangles(struct chunk* chunk){
    glEnable(GL_TEXTURE_2D);
    glClientActiveTexture(GL_TEXTURE0);
    
    glVertexPointer(3,                      // number of coordinates per vertex (x,y,z)
                    GL_FLOAT,               // they are floats
                    0,                      // stride
                    chunk->allverticies);              // the array pointer
    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glTexCoordPointer(2,                     // number of coordinates per coor (u, v)
                    GL_FLOAT,               // they are floats
                    0,                      // stride
                    chunk->alluvcoors);                   // the array pointer
    
    glDrawArrays(GL_TRIANGLES, 0, chunk->verticiesnum);
}

/**
int checkVisible(float center[], struct chunk *chunk) {
    float *cam = (float []){translate_x, translate_y, translate_z};
    float *pos = (float []){0, 0, 0};
    float *cur = (float []){center[0], center[1], center[2]};
    float *ray = (float []){0, 0, 0};
    Vector3_Subtract(ray, center, cam);
    float mag = Vector3_Magnitude(ray);
    Vector3_Normalize(ray, ray);
    
    while(Vector3_Magnitude(pos) < mag) {
        Vector3_Add(cur, center, pos);
        
        cur[0] = (int)((cur[0]/(radius * 2)) - (chunk->x * 16) + 8);
        cur[1] = (int)((cur[1]/(radius * 2)) - (chunk->y * 16) + 8);
        cur[2] = (int)((cur[2]/(radius * 2)) - (chunk->z * 16) + 8);
        
        if(cur[0] < 0) {
            if(chunk->left) {
                chunk = chunk->left;
                cur[0] = (int)((cur[0]/(radius * 2)) - (chunk->x * 16) + 8);
            } else {
                return -1;
            }
        } else if(cur[0] > 15) {
            if(chunk->right) {
                chunk = chunk->right;
                cur[0] = (int)((cur[0]/(radius * 2)) - (chunk->x * 16) + 8);
            } else {
                return -1;
            }
        }
    
        if(cur[1] < 0) {
            if(chunk->bottom) {
                chunk = chunk->bottom;
                cur[1] = (int)((cur[1]/(radius * 2)) - (chunk->y * 16) + 8);
            } else {
                return -1;
            }
        } else if(cur[1] > 15) {
            if(chunk->top) {
                chunk = chunk->top;
                cur[1] = (int)((cur[1]/(radius * 2)) - (chunk->y * 16) + 8);
            } else {
                return -1;
            }
        }
        
        if(cur[2] < 0) {
            if(chunk->back) {
                chunk = chunk->back;
                cur[2] = (int)((cur[2]/(radius * 2)) - (chunk->z * 16) + 8);
            } else {
                return -1;
            }
        } else if(cur[2] > 15) {
            if(chunk->front) {
                chunk = chunk->front;
                cur[2] = (int)((cur[2]/(radius * 2)) - (chunk->z * 16) + 8);
            } else {
                return -1;
            }
        }
    
        if(chunk->cubes[getIndex(cur[0], cur[1], cur[2])] < 0)
            return 1;
        
        Vector3_Add(pos, pos, ray);
        //printf("%f\n", Vector3_Magnitude(pos));
    }
    return 0;
}**/

int findEditCube(signed char *cubes) {
    float *cam = (float []){translate_x, translate_y, translate_z};
    float normalVec[3];
    Vector3_Normalize(normalVec, camNormal);
    
    normalVec[1] *= -1;
    
    Vector3_Multi(normalVec, normalVec, radius);
    float *norm = normalVec;
    float ray[3];
    Vector3_Add(ray, cam, norm);
    
    //printf("%f\n", Vector3_Magnitude(norm));
    //printf("%f, %f, %f\n", norm[0], norm[1], norm[2]);
    //printf("%f, %f, %f\n", camNormal[0], camNormal[1], camNormal[2]);
    
    while(Vector3_Magnitude(norm) < 8 * 2) {
        int idx = getIndex(ray[0] + 8, ray[1] + 8, ray[2] + 8);
        if(idx >= 0 && idx < (pow(16, 3)) && cubes[idx] != -1)
            return idx;
        Vector3_Add(norm, norm, normalVec);
        Vector3_Add(ray, cam, norm);
    }
    
    return -1;
}
