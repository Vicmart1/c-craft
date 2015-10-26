//
//  array.c
//  opengl
//
//  Created by Vicky D on 7/9/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "array.h"
#include "node.h"

/**
void findOpenCubes(signed char *cubes)
{
    int countF = 0;
    for(int i = 0; i < (size * size * 128 * 4) ; i++)
    {
        if(cubes[i] != -1) {
            int *xyz = getLoc(i);
            int count = 0;
            int index = getIndex(xyz[0] + 1, xyz[1], xyz[2]);
            if(xyz[0] + 1 >= size * 2 || cubes[index] == -1)
                count++;
        
            index = getIndex(xyz[0] - 1, xyz[1], xyz[2]);
            if(xyz[0] - 1 < 0 || cubes[index] == -1)
                count++;
        
            index = getIndex(xyz[0], xyz[1] + 1, xyz[2]);
            if(xyz[1] + 1 >= 128 || cubes[index] == -1)
                count++;
        
            index = getIndex(xyz[0], xyz[1] - 1, xyz[2]);
            if(xyz[1] - 1 < 0 || cubes[index] == -1)
                count++;
        
            index = getIndex(xyz[0], xyz[1], xyz[2] + 1);
            if(xyz[2] + 1 >= size * 2 || cubes[index] == -1)
                count++;
        
            index = getIndex(xyz[0], xyz[1], xyz[2] - 1);
            if(xyz[2] - 1 < 0 || cubes[index] == -1)
                count++;
        
            if(count > 0) {
                add_to_list((float []){xyz[0], xyz[1], xyz[2]}, i, head, curr);
                countF++;
            }
        }
    }
    printf("%i\n", countF);
}
**/

int *getLoc(int i){
    return (int []){i % (16),(i / 16) % (16), i / (16 * 16)};
}

int getIndex(int x, int y, int z) {
    return x + (y * 16) + (z * 16 * 16);
}
