//
//  node.h
//  opengl
//
//  Created by Vicky D on 7/9/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#ifndef opengl_node_h
#define opengl_node_h

struct node{
    float xyz[3];
    int index;
    struct node *next;
};

struct node* create_list(float [], int, struct node *, struct node *);
struct node* add_to_list(float [], int, struct node *, struct node *);
struct node* search_in_list(int, struct node **, struct node *, struct node *);
int delete_from_list(int, struct node *, struct node *);

#endif


