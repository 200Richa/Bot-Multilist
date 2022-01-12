#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Multilist structures

// Nodes in Multilist
struct node {
    struct node *up, *down, *left, *right;
    int x, y;
};

// Function declarations
int* source_coord(char*);
int* dst_coord(char*);
struct node* read_map(char*);
struct node** find_path (struct node*, int, int, int, int);
void store_path(struct node**, char*);

// Stack Functions
void push (struct node* [],int*, struct node*);
struct node* pop(struct node* [], int*);
struct node* peek(struct node* [], int);
int isEmpty(int);
int inStack(struct node* [], int, int, int);

// Display function for multilist
void display(struct node*);