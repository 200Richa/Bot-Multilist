#include "PES1UG20CS334_H.h"


int main()
{
    int* src = source_coord("input.txt");
    int* dst = dst_coord("input.txt");
    if(src==NULL || dst==NULL)
    {
        printf("Error in finding source and destination coordinates\n");
    }
    else
    {
        struct node* head = read_map("input.txt");
        struct node** p = find_path(head,src[0],src[1],dst[0],dst[1]);
        store_path(p, "out.txt");

                    // OR

        // store_path(find_path(read_map("input.txt"),src[0],src[1],dst[0],dst[1]),"out.txt");
    }
    return 0;
}