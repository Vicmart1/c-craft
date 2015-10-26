//
//  main.c
//  opengl
//
//  Created by Vicky D on 7/6/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "frustum.h"
#include "random.h"
#include "node.h"
#include "array.h"
#include "draw.h"
#include "input.h"
#include "vector3.h"
#include "colors.h"
#include "texture.h"
#include "simplex.h"
#include "chunk.h"
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

void display();
void doStuff();
void output(int, int, char* );

const int frames_per_second = 60;
int width = 1280;
int height = 800;
float radius = 0.2;

double rotate_x = 0;
double rotate_y = 0;
double rotate_z = 0;

double translate_x = 0;
double translate_y = -5;
double translate_z = 0;

int keys[150] = { 0 };
int special_keys[150] = { 0 };

float camNormal[] = {0, 0, 0};
float frustum[6][4];

struct chunk *chunks;

struct chunk *chunk_head = NULL;
struct chunk *chunk_curr = NULL;

int prev_x_index;
int prev_y_index;
int prev_z_index;

int section = 0;

float magnitude(float vec[3])
{
    return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

float dotProduct(float vec1[3], float vec2[3])
{
    return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2])/(magnitude(vec1) * magnitude(vec2));
}

void display()
{
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
    // Reset Transformations
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set the perspective: viewing angle, aspect ratio, zNear, zFar
    gluPerspective(45, 16.0 / 9.0, 0.1, 1000);
    
    glViewport(0, 0, width, height);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    // Rotate when user changes rotate_x and rotate_y
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y + 180, 0.0, 1.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    
    // Translate
    glTranslatef(translate_x, translate_y, translate_z + 1);
    
    // Specify which direction to cull
    glCullFace(GL_BACK);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // Enable and load texturing
    glEnable (GL_TEXTURE_2D); /* enable texture mapping */
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Extract the viewing frustum from the perspective matrix
    extractFrustum();
    
    // Keep colors when using lighting
    glEnable(GL_COLOR_MATERIAL);
    
    // Other Transformations
    // glScalef( 2.0, 2.0, 0.0 );          // Not included
    
    /**int editCube = findEditCube();
    //printf("%i\n", editCube);
    if(editCube >= 0 && editCube < (size * size * 4 * 128))
        cubes[editCube] = 2;
    **/
    // Draw the cubes
    //float center[] = {0.0f, 0.0f, 0.0f};
    
    struct chunk *chunk_ptr = chunk_head;
    
    while(chunk_ptr != NULL)
    {
        if(cubeInFrustum(chunk_ptr->x*16*radius*2,chunk_ptr->y*16*radius*2,chunk_ptr->z*16*radius*2,8) > 0)
            drawTriangles(chunk_ptr);
        
        chunk_ptr = chunk_ptr->next;
    }
    
    glDisable(GL_TEXTURE_2D);
    
    glFlush();
    glutSwapBuffers();
    
    doStuff();
}

void output(int x, int y, char *string)
{
    int len, i;
    
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
    glPopMatrix();
}

// ----------------------------------------------------------
// mainThread() Callback Function
// ----------------------------------------------------------
void mainThread() {
    
    int x_index = (int)(-translate_x/(8 * radius * 2));
    int y_index = (int)(-translate_y/(8 * radius * 2));
    int z_index = (int)(-translate_z/(8 * radius * 2));
    x_index = x_index > 0 ? (x_index + 1)/2 : (x_index - 1)/2;
    y_index = y_index > 0 ? (y_index + 1)/2 : (y_index - 1)/2;
    z_index = z_index > 0 ? (z_index + 1)/2 : (z_index - 1)/2;
    
    int view_dist = 8;
    
    int x_loc_prev = view_dist;
    int y_loc_prev = view_dist;
    int z_loc_prev = view_dist;
    
    if(x_index != prev_x_index || y_index != prev_y_index || z_index != prev_z_index) {
        for(int r = 0; r <= view_dist; r++)
            for(int theta = 3 * (section); theta < 3 * (section + 1); theta += 45/(r/2.6 + 1))
                for(int phi = 0; phi < 180; phi += 45/(r/2.6 + 1)) {
                    int x_loc = x_index + (int)(cos(degreesToRadians(theta)) * sin(degreesToRadians(phi)) * r);
                    int y_loc = y_index + (int)(cos(degreesToRadians(phi)) * r) - 1;
                    int z_loc = z_index + (int)(sin(degreesToRadians(theta)) * sin(degreesToRadians(phi)) * r);
                    if(!(x_loc == x_loc_prev && y_loc == y_loc_prev && z_loc == z_loc_prev))
                        if(search_chunk_only_in_list(x_loc, y_loc, z_loc) == NULL)
                            add_chunk_to_list(x_loc, y_loc, z_loc);
                
                    x_loc_prev = x_loc;
                    y_loc_prev = y_loc;
                    z_loc_prev = z_loc;
                }
    
        struct chunk *chunk_ptr = chunk_head;
        struct chunk *chunk_ptr_bckp = chunk_ptr;
    
        while(chunk_ptr != NULL)
        {
            chunk_ptr_bckp = chunk_ptr->next;
            if(Vector3_Magnitude((float []){chunk_ptr->x - x_index, chunk_ptr->y - y_index, chunk_ptr->z - z_index}) > view_dist)
                delete_chunk_from_list(chunk_ptr->x, chunk_ptr->y, chunk_ptr->z);
            chunk_ptr = chunk_ptr_bckp;
        }
        if(section >= 119) {
            prev_x_index = x_index;
            prev_y_index = y_index;
            prev_z_index = z_index;
            section = 0;
            
            //struct chunk *chunk_ptr = chunk_head;
            
            /**while(chunk_ptr != NULL)
            {
                intializeDisplayList(chunk_ptr);
                chunk_ptr = chunk_ptr->next;
            }**/
            
        } else {
            section++;
        }
    }
    //printf("%i\n",section);
    //printf("x: %i ; y: %i ; z: %i \n", x_index, y_index, z_index);
    //printf("x: %f ; y: %f ; z: %f\n", translate_x, translate_y, translate_z);
    display();
    
    //printf("%f\n", elapsed * 5.0);
    
    usleep( (1000 * 1000) / frames_per_second);
}

// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){
    
    // Sets the window size
    glutInitWindowSize(width, height);
    
    //  Initialize GLUT and process user parameters
    glutInit(&argc,argv);
    
    //  Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Create window
    glutCreateWindow("VicCraft");
    
    //  Enable Z-buffer depth test and backface culling
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    // Callback functions
    glutDisplayFunc(mainThread);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(keySpecialDown);
    glutSpecialUpFunc(keySpecialUp);
    glutPassiveMotionFunc(mouseRoutine);
    
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
    
    printf("note: if no textures appear you must change the texture directory within the source code.");
    printf("file: main.c, line 270");
    glBindTexture (GL_TEXTURE_2D, loadBMP_custom("/Users/vickyd/Google\ Drive/C\:C++\:ObjC/OpenGL/opengl/opengl/Textures/all.bmp"));
    
    printf("Keyboard controls: WASD to move and arrow keys for camera. Backspace to quit");
    
    //  Pass control to GLUT for events
    glutMainLoop();
    
    //  Return to OS
    return 0;
    
}
