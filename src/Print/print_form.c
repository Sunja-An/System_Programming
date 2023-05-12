#include "../Move/move.h"
#include "../Struct/tree.h"
#include "print_form.h"

Node *Link_Arr[BUFSIZE];
int idx;

/* Not implemented */
void Print_Success()
{
    printf("idx is %d\n", idx);
    for (int i = 0; i < idx; i++)
    {
        printf("------------Selected Data Information---------------\n");
        printf("%s \n", Link_Arr[i]->filepath);
    }
}