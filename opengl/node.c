//
//  node.c
//  opengl
//
//  Created by Vicky D on 7/9/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "chunk.h"

struct node* create_list(float pts[], int idx, struct node *head, struct node *curr)
{
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    if(NULL == ptr)
    {
        printf("\n struct node creation failed \n");
        return NULL;
    }
    ptr->xyz[0] = pts[0];
    ptr->xyz[1] = pts[1];
    ptr->xyz[2] = pts[2];
    ptr->index = idx;
    ptr->next = NULL;
    
    head = curr = ptr;
    return ptr;
}

struct node* add_to_list(float pts[], int idx, struct node *head, struct node *curr)
{
    if(NULL == head)
    {
        return (create_list(pts, idx, head, curr));
    }
    
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    if(NULL == ptr)
    {
        printf("\n struct node creation failed \n");
        return NULL;
    }
    ptr->xyz[0] = pts[0];
    ptr->xyz[1] = pts[1];
    ptr->xyz[2] = pts[2];
    ptr->index = idx;
    ptr->next = NULL;
    
    curr->next = ptr;
    curr = ptr;
    
    return ptr;
}

struct node* search_in_list(int idx, struct node **prev, struct node *head, struct node *curr)
{
    struct node *ptr = head;
    struct node *tmp = NULL;
    int found = 0;
    
    while(ptr != NULL)
    {
        if(ptr->index == idx)
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

int delete_from_list(int idx, struct node *head, struct node *curr)
{
    struct node *prev = NULL;
    struct node *del = NULL;
    
    del = search_in_list(idx,&prev, head, curr);
    if(del == NULL)
    {
        return -1;
    }
    else
    {
        if(prev != NULL)
            prev->next = del->next;
        
        if(del == curr)
        {
            curr = prev;
        }
        else if(del == head)
        {
            head = del->next;
        }
    }
    
    free(del);
    del = NULL;
    
    return 0;
}