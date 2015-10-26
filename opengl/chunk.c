//
//  chunk.c
//  opengl
//
//  Created by Vicky D on 7/12/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "chunk.h"
#include "array.h"
#include "simplex.h"
#include "node.h"
#include "draw.h"
#include "frustum.h"
#include "random.h"
float theradius = 0.2;

int offset_x = 0;
int offset_y = 0;
int offset_z = 0;

extern struct chunk *chunk_head;
extern struct chunk *chunk_curr;

long max = 0;

struct chunk* create_chunk_list(signed char *cubes, int x, int y, int z)
{
    struct chunk *ptr = (struct chunk*)malloc(sizeof(struct chunk));
    if(NULL == ptr)
    {
        printf("\n struct chunk creation failed \n");
        return NULL;
    }
    ptr->index = max;
    max++;
    ptr->head = ptr->curr = NULL;
    ptr->cubes = cubes;
    ptr->next = NULL;
    ptr->x = x;
    ptr->y = y;
    ptr->z = z;
    ptr->verticiesnum = 0;
    ptr->uvcoornum = 0;
    
    fill_chunk(ptr->cubes, x, y, z);
    find_open_cubes(ptr);
    
    chunk_head = chunk_curr = ptr;
    
    struct chunk *chnk = search_chunk_only_in_list(x + 1, y, z);
    if(chnk) chnk->left = ptr;
    chnk = search_chunk_only_in_list(x - 1, y, z);
    if(chnk) chnk->right = ptr;
    chnk = search_chunk_only_in_list(x, y - 1, z);
    if(chnk) chnk->top = ptr;
    chnk = search_chunk_only_in_list(x, y + 1, z);
    if(chnk) chnk->bottom = ptr;
    chnk = search_chunk_only_in_list(x, y, z - 1);
    if(chnk) chnk->front = ptr;
    chnk = search_chunk_only_in_list(x, y, z + 1);
    if(chnk) chnk->back = ptr;
    find_neighbors(ptr);
    
    intializeDisplayList(ptr);
    
    return ptr;
}

struct chunk* add_chunk_to_list(int x, int y, int z)
{
    signed char *cubes = (signed char*)malloc(sizeof(signed char) * 16 * 16 * 16);
    
    if (offset_x == 0 && offset_y == 0 && offset_z == 0) {
        offset_x = random_in_range(INT16_MIN, INT16_MAX);
        offset_y = random_in_range(INT16_MIN, INT16_MAX);
        offset_z = random_in_range(INT16_MIN, INT16_MAX);
    }
    
    if(NULL == chunk_head)
    {
        return create_chunk_list(cubes, x, y, z);
    }
    
    struct chunk *ptr = (struct chunk*)malloc(sizeof(struct chunk));
    if(NULL == ptr)
    {
        printf("\n struct chunk creation failed \n");
        return NULL;
    }
    
    ptr->index = max;
    max++;
    ptr->head = ptr->curr = NULL;
    ptr->cubes = cubes;
    ptr->next = NULL;
    ptr->x = x;
    ptr->y = y;
    ptr->z = z;
    ptr->verticiesnum = 0;
    ptr->uvcoornum = 0;
    
    fill_chunk(ptr->cubes, x, y, z);
    find_open_cubes(ptr);
    
    chunk_curr->next = ptr;
    chunk_curr = ptr;
    
    struct chunk *chnk = search_chunk_only_in_list(x + 1, y, z);
    if(chnk) chnk->left = ptr;
    chnk = search_chunk_only_in_list(x - 1, y, z);
    if(chnk) chnk->right = ptr;
    chnk = search_chunk_only_in_list(x, y - 1, z);
    if(chnk) chnk->top = ptr;
    chnk = search_chunk_only_in_list(x, y + 1, z);
    if(chnk) chnk->bottom = ptr;
    chnk = search_chunk_only_in_list(x, y, z - 1);
    if(chnk) chnk->front = ptr;
    chnk = search_chunk_only_in_list(x, y, z + 1);
    if(chnk) chnk->back = ptr;
    find_neighbors(ptr);
        
    intializeDisplayList(ptr);
    
    return ptr;
}

struct chunk* search_chunk_in_list(int x, int y, int z, struct chunk **prev)
{
    struct chunk *ptr = chunk_head;
    struct chunk *tmp = NULL;
    int found = 0;
    
    while(ptr != NULL)
    {
        if(ptr->x == x && ptr->y == y && ptr->z == z)
        {
            found = 1;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }
    
    if(found == 1)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}

struct chunk* search_chunk_only_in_list(int x, int y, int z)
{
    struct chunk *ptr = chunk_head;
    int found = 0;
    
    while(ptr != NULL)
    {
        if(ptr->x == x && ptr->y == y && ptr->z == z)
        {
            found = 1;
            break;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    
    if(found == 1)
    {
        return ptr;
    }
    else
    {
        return NULL;
    }
}


int delete_chunk_from_list(int x, int y, int z)
{
    struct chunk *prev = NULL;
    struct chunk *del = NULL;
    
    del = search_chunk_in_list(x, y, z, &prev);
    if(del == NULL)
    {
        return -1;
    }
    else
    {
        if(prev != NULL)
            prev->next = del->next;
        
        if(del == chunk_curr)
        {
            chunk_curr = prev;
        }
        else if(del == chunk_head)
        {
            chunk_head = del->next;
        }
    }
    
    struct chunk *chnk = search_chunk_only_in_list(x + 1, y, z);
    if(chnk) chnk->left = NULL;
    chnk = search_chunk_only_in_list(x - 1, y, z);
    if(chnk) chnk->right = NULL;
    chnk = search_chunk_only_in_list(x, y - 1, z);
    if(chnk) chnk->top = NULL;
    chnk = search_chunk_only_in_list(x, y + 1, z);
    if(chnk) chnk->bottom = NULL;
    chnk = search_chunk_only_in_list(x, y, z - 1);
    if(chnk) chnk->front = NULL;
    chnk = search_chunk_only_in_list(x, y, z + 1);
    if(chnk) chnk->back = NULL;
    
    clean_list(del);
    free(del->cubes);
    //free(del->allverticies);
    //free(del->alluvcoors);
    free(del);
    del = NULL;
    
    return 0;
}

void clean_list(struct chunk *pll)
{
    struct node *pnext;
    
    for (struct node *pnode = pll->head; pnode != NULL; pnode = pnext)
    {
        pnext = pnode->next;
        free(pnode);
    }
}

void fill_chunk(signed char *cubes, int x, int y, int z) {
    int divisor = 64;
    
    for(int i = 0; i < (16 * 16 * 16) ; i++)
    {
        int *xyz = getLoc(i);
        xyz[0] += x * 16;
        xyz[1] += y * 16;
        xyz[2] += z * 16;
        
        int octaves = 1;
        
        if(simplex_noise(octaves, 3.0f * ((float) xyz[0] / (divisor)), 3.0f * ((float) xyz[1] / (divisor)), 3.0f * ((float) xyz[2] / (divisor)))  > 1.1f * octaves) {
            cubes[i] = 1;
        }  else
            cubes[i] = -1;
    }
}

void find_neighbors(struct chunk *chunk)
{
    int x = chunk->x;
    int y = chunk->y;
    int z = chunk->z;
    
    chunk->left = search_chunk_only_in_list(x - 1, y, z);
    chunk->right = search_chunk_only_in_list(x + 1, y, z);
    chunk->top = search_chunk_only_in_list(x, y + 1, z);
    chunk->bottom = search_chunk_only_in_list(x, y - 1, z);
    chunk->front = search_chunk_only_in_list(x, y, z + 1);
    chunk->back = search_chunk_only_in_list(x, y, z - 1);
}

void find_open_cubes(struct chunk *chunk)
{
    signed char *cubes = chunk->cubes;
    int countF = 0;
    
    for(int i = 0; i < (16 * 16 * 16) ; i++)
    {
        if(cubes[i] != -1) {
            int *xyz = getLoc(i);
            
            int count = 0;
            int index = getIndex(xyz[0] + 1, xyz[1], xyz[2]);
            if(xyz[0] + 1 >= 16) {
                count++;
            } else if(cubes[index] == -1)
                count++;
            
            index = getIndex(xyz[0] - 1, xyz[1], xyz[2]);
            if(xyz[0] - 1 < 0) {
                count++;
            } else if(cubes[index] == -1)
                count++;
            
            index = getIndex(xyz[0], xyz[1] + 1, xyz[2]);
            if(xyz[1] + 1 >= 16) {
                //struct chunk *next = search_chunk_only_in_list(chunk->x, chunk->y + 1, chunk->z);
                //printf("%i\n", (next) ? next->index : 4);
                //if(!next || next->cubes[getIndex(xyz[0], 0, xyz[2])] == -1)
                //count++;
                count++;
            } else if(cubes[index] == -1)
                count++;
            //cubes[i] = (xyz[1] + 1 < 16 && cubes[index] >= 0) ? 3 : cubes[i];
            
            index = getIndex(xyz[0], xyz[1] - 1, xyz[2]);
            if(xyz[1] - 1 < 0){
                count++;
            } else if (cubes[index] == -1)
                count++;
            
            index = getIndex(xyz[0], xyz[1], xyz[2] + 1);
            if(xyz[2] + 1 >= 16) {
                count++;
            } else if(cubes[index] == -1)
                count++;
            
            index = getIndex(xyz[0], xyz[1], xyz[2] - 1);
            if(xyz[2] - 1 < 0) {
                count++;
            } else if(cubes[index] == -1)
                count++;
            
            if(count > 0) {
                struct node *ptr = add_to_list((float []){xyz[0], xyz[1], xyz[2]}, i, chunk->head, chunk->curr);
                if(chunk->head == NULL) {
                    chunk->head = ptr;
                }
                chunk->curr = ptr;
                countF++;
            }
        }
    }
    
    //printf("%i\n", countF);
}

void intializeDisplayList(struct chunk *ptr){
    float center[] = {0.0f, 0.0f, 0.0f};
    
    struct node *block_ptr = ptr->head;
    while(block_ptr != NULL)
    {
        //printf("\n [%d] \n",block_ptr->val);
        float x = block_ptr->xyz[0] - 8;
        float y = block_ptr->xyz[1] - 8;
        float z = block_ptr->xyz[2] - 8;
        int j = block_ptr->index;
        if(ptr->cubes[j] != -1) {
            center[0] = (x + (ptr->x * 16)) * theradius * 2;
            center[1] = (y + (ptr->y * 16)) * theradius * 2;
            center[2] = (z + (ptr->z * 16)) * theradius * 2;
            //if(cubeInFrustum(center[0], center[1], center[2], theradius) > 0) {
                int xyz[] = {x + 8, y + 8, z + 8};
                //if(checkVisible(center, ptr) != 1)
                drawCube(center , theradius, xyz, ptr->cubes[j], ptr);
            //}
        }
        block_ptr = block_ptr->next;
    }
}