//
//  draw.h
//  opengl
//
//  Created by Vicky D on 7/9/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#ifndef opengl_draw_h
#define opengl_draw_h

#include "chunk.h"
#include "vertex.h"
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void drawCube(float [], float, int [], int, struct chunk *);
void addSide(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat,
                  GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat,
                    struct chunk *);
void drawTriangles(struct chunk *);
int checkVisible(float [], struct chunk *);
int findEditCube();

#endif
