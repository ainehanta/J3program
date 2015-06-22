#include <stdio.h>
#include <stdlib.h>
 
struct CELL {
        int data;
        struct CELL *next;
};

struct CELL *make_node(int in_data);
void print_list(struct CELL *p);
struct CELL *search_point(int in_data, struct CELL *p);
 
int main(void)
{
        struct CELL *root, *p;
        int in_data;

        root = init_list();
        p = root;

        scanf("%d", &in_data);

        while (in_data > 0) {
                                          
                scanf("%d", &in_data);
        }

        print_list(root);

        return 0;
}
 
struct CELL *make_node(int in_data)
{

}

void print_list(struct CELL *p)
{

}

struct CELL *search_point(int in_data, struct CELL *p)
{

}
