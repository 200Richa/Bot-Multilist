#include "PES1UG20CS334_H.h"

// Function to get source coordinates
int* source_coord(char* filename)
{
    char arr[100];
    static int coord[2];
    FILE * fp = fopen(filename, "r");
    if(fp==NULL)
    {
        return NULL;
    }
    fgets(arr, 100, fp);
    coord[0] = arr[0]-48;
    coord[1] = arr[2]-48;
    return coord;

}

// Function to get destination coordinates
int* dst_coord(char* filename)
{
    char arr[100];
    static int coord[2];
    FILE * fp = fopen(filename, "r");
    if(fp==NULL)
    {
        return NULL;
    }
    fgets(arr, 100, fp);
    fgets(arr, 100, fp);
    coord[0] = arr[0]-48;
    coord[1] = arr[2]-48;
    return coord;
}

struct node* read_map(char* filename)
{
    // Initializations
    char arr[100];
    int i=0;
    struct node* row=NULL;
    struct node* col =NULL;
    int iter = 1;
    struct node* head = NULL;
    struct node* pres = NULL;
    struct node* temp = NULL;
    int col_num = 0;
    int row_num =0; 
    
    FILE * fp = fopen(filename, "r");
    if(fp==NULL)
    {
        return NULL;
    }
    // Skipping First Two Lines
    fgets(arr, 100, fp);
    fgets(arr, 100, fp);
    head = (struct node*)malloc(sizeof(struct node));
    head->down = head->up = head->right = head->left =head;

    while(fgets(arr,100,fp) != NULL)
    {
        // Row addition for every iteration
        if(head->down == head)
        {
            head->down = (struct node*)malloc(sizeof(struct node));
            head->down->x = head->down->y = -100;
            head->up = head->down;
            head->down->down = head;
            head->down->up = head;
            head->down->right = head->down->left = head->down;
        }
        else
        {
            pres = head->up;
            pres->down = (struct node*)malloc(sizeof(struct node));
            pres->down->x = pres->down->y =-100;
            pres->down->down = head;
            pres->down->right = pres->down->left =pres->down;
            head->up = pres->down;
        }

        row = head->up;
        col = head->right;
        col_num = 0;

        while(arr[i] != '\n')
        {
            // Column addition for first iteration
            if(iter==1 && arr[i] != ' ')
            {
                if(head->right == head)
                {
                    head->right = (struct node*)malloc(sizeof(struct node));
                    head->right->x=head->right->y=-100;
                    head->left = head->right;
                    head->right->right = head;
                    head->right->left = head;
                    head->right->down = head->right->up = head->right;
                    col = head->right;
                }
                else
                {
                    pres = head->left;
                    pres->right = (struct node*)malloc(sizeof(struct node));
                    pres->right->x = pres->right->y=-100;
                    pres->right->right = head;
                    pres->right->down = pres->right->up =pres->right;
                    head->left = pres->right;
                    col = head->left;
                }
            }
            
            // When node found

            if (arr[i] =='0')
            {
                temp = (struct node*)malloc(sizeof(struct node));

                // Right and Down Pointers
                temp->right = row;
                temp->down = col;

                // Coordinates
                temp->x = row_num;
                temp->y = col_num;

                // Up and Down Pointers
                temp->up = col->up;
                temp->left = row->left;

                // Predecessors
                col->up->down = temp;
                row->left->right = temp;

                // Circular List
                col->up = temp;
                row->left = temp;

            }

            
            if(arr[i] != ' ')
            {
                if(iter != 1)
                    col = col->right;
                col_num++;
            }
            i++;

        }
        i = 0;
        iter++;
        row_num++;
    }
    fclose(fp);
    return head;
}


struct node** find_path (struct node* head, int s1, int s2, int d1, int d2)
{
    // Stack
    static struct node* stk[500]; 

    int top = -1; // top
    int i =0;

    // Pointers

    struct node* pres = NULL;
    struct node* source = NULL;
    struct node* temp = NULL;
    struct node* row =NULL;
    struct node* col =NULL;

    // Initializing the Stack
    for (i=0; i<500; i++)
    {
        stk[i] = NULL;
    }

    // Return if head is NULL
    if(head == NULL || head->down == head || head->right == head)
        return NULL;


    // Fixing source Pointer

    // Navigating along rows
    row = head->down;
    for(i=0; i!=s1; i++)
    {
        row = row->down;
    }

    // Navigating along columns
    source=row->right;
    while(source != row && source->y != s2)
    {
        source=source->right;
    }
    if(source == row)
    {
        printf("source==row\n");
        return NULL;
    }
    // Pushing Source Pointer in Stack

    push(stk,&top,source);
    pres = source;
    temp = pres->right;

    while( isEmpty(top)==0 && inStack(stk,top,d1,d2)==0)
    {
        if((pres->y == ((temp->y)-1)) && pres->x == temp->x)
        {
            push(stk,&top,temp);
            pres = temp;
            temp=pres->right;
        }
        else
        {
            temp = pres->down;
            if(pres->y == (temp->y) && pres->x == temp->x-1)
            {
                push(stk,&top,temp);
                pres = temp;
                temp = pres->right;
            }
            else
            {
                temp = pop(stk,&top);
                temp->left->right = temp->right;
                temp->right->left = temp->left;
                temp->up->down = temp->down;
                temp->up->down = temp->down;
                temp->right=temp->left=temp->up = temp->down =NULL;
                free(temp);
                pres=peek(stk, top);
                temp = pres->right; // down
            }
        }
        
    }

    if(isEmpty(top))
    {
        printf("No path Exists\n");
        return NULL;
    }

    return stk;
}


void push (struct node* stk[],int* top, struct node* temp)
{
    (*top)++;
    stk[*top] = temp;
}

struct node* pop(struct node* stk[], int* top)
{
    struct node* x = NULL;
    if(*top == -1)
        return x;
    x = stk[*top];
    
    stk[*top] = NULL;

    (*top)--;
    return x;
}

struct node* peek(struct node* stk[], int top)
{
    if(top == -1)
        return NULL;
    return stk[top];
}

int isEmpty(int top)
{
    if(top==-1)
        return 1;
    return 0;
}


int inStack(struct node* stk[], int top, int x, int y)
{
    if(top==-1)
        return 0;
    for(int i=top; i>=0 ; i--)
    {
        if(stk[i]->x == x && stk[i]->y ==y)
            return 1;
    }
    return 0;
}


void display(struct node* head)
{
    if(head == NULL)
        return;
    struct node* tdown = head->down;
    struct node* tnode = head->down->right;

    while(tdown != head)
    {
        while(tnode != tdown)
        {
            printf("%d %d\n",tnode->x, tnode->y);
            tnode = tnode->right;
        }
        printf("\n");
        tdown = tdown->down;
        tnode = tdown->right;
    }
}


void store_path(struct node** stk, char* filename)
{
    FILE * fp = fopen(filename, "w");
    struct node* pres=NULL;
    if(fp==NULL)
    {
        printf("File Error in store_path Function\n");
        return;
    }
    else
    {
        if(stk==NULL)
        {
            fprintf(fp,"-1\n");
            return;
        }
        pres = stk[0];
        int i=0;
        while(pres!=NULL)
        {
            fprintf(fp,"%d %d\n",pres->x, pres->y);
            i++;
            pres = stk[i];
        }

        fclose(fp);

    }

    
}

