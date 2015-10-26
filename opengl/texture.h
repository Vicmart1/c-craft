//
//  texture.h
//  opengl
//
//  Created by Vicky D on 7/11/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#ifndef opengl_texture_h
#define opengl_texture_h



#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLuint loadBMP_custom(const char *);
void getUVCoor(float *, float x, float y, float n);
void getTextCoor(float *, int type, int side);