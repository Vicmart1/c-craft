//
//  texture.c
//  opengl
//
//  Created by Vicky D on 7/11/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLuint loadBMP_custom(const char * imagepath){
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char *data;
    
    FILE * file = fopen(imagepath,"rb");
    if (!file) {
        printf("Image at could not be opened\n");
        return 0;
    }
    
    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return 0;
    }
    
    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file\n");
        return 0;
    }
    
    // Read ints from the byte array
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    
    // Some BMP files are misformatted, guess missing informc ation
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way
    
    // Create a buffer
    data = malloc(sizeof(unsigned char) * imageSize);
    
    // Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);
    
    //Everything is in memory now, the file can be closed
    fclose(file);
    
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
}

void getUVCoor(float *coors, float x, float y, float n) {
    coors[0] = x * (1.0f/n);
    coors[1] = 1.0f - (y * (1.0f/n));
    coors[2] = (x + 1.0f) * (1.0f/n);
    coors[3] = (1.0f - y * (1.0f/n));
    coors[4] = (x + 1.0f) * (1.0f/n);
    coors[5] = 1.0f - (y + 1) * (1.0f/n);
    coors[6] = x * (1.0f/n);
    coors[7] = (1.0f - (y + 1) * (1.0f/n));
}

void getTextCoor(float *coor, int type, int side) {
    switch(type) {
        case 0:
            getUVCoor(coor, 1, 0, 16);
            break;
        case 1:
            if(side == 5) {
                getUVCoor(coor, 0, 0, 16);
            } else if(side == 6) {
                getUVCoor(coor, 2, 0, 16);
            } else {
                getUVCoor(coor, 3, 0, 16);
            }
            break;
        case 2:
            getUVCoor(coor, 0, 1, 16);
            break;
        case 3:
            getUVCoor(coor, 2, 0, 16);
            break;
    }
}