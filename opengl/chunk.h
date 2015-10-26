//
//  chunk.h
//  opengl
//
//  Created by Vicky D on 7/12/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#ifndef opengl_chunk_h
#define opengl_chunk_h

#include "vertex.h"
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

struct chunk{
    signed char *cubes;
    long index;
    int x;
    int y;
    int z;
    signed char visible;
    struct node *head;
    struct node *curr;
    struct chunk *next;
    struct chunk *left;
    struct chunk *right;
    struct chunk *top;
    struct chunk *bottom;
    struct chunk *front;
    struct chunk *back;
    struct vertex allverticies[16*16*16*3];
    struct uvcoor alluvcoors[16*16*16*3];
    int verticiesnum;
    int uvcoornum;
};

struct chunk* create_chunk_list(signed char *, int, int, int);
struct chunk* add_chunk_to_list(int, int, int);
struct chunk* search_chunk_in_list(int, int, int, struct chunk **);
struct chunk* search_chunk_only_in_list(int, int, int);
int delete_chunk_from_list(int, int, int);
void clean_list(struct chunk *);
void fill_chunk(signed char *, int, int, int);
void find_open_cubes(struct chunk *);
void find_neighbors(struct chunk *);
void intializeDisplayList(struct chunk *);

#endif
