//
//  vertex.h
//  opengl
//
//  Created by Vicky D on 8/18/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#ifndef opengl_vertex_h
#define opengl_vertex_h

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

struct vertex
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct uvcoor
{
    GLfloat u;
    GLfloat v;
};

#endif
