#include "move.h"
#include "tree.h"
#include "print_form.h"

Node *Link_Arr[BUFSIZE];
int idx;

void Print_Success()
{
    for (int i = 0; i < idx; i++)
    {
        printf("------------Selected Data Information---------------\n");
        printf("%s \n", Link_Arr[i]->filepath);
        printf("%s \n", Link_Arr[i]->name);
        printf("%s \n", Link_Arr[i]->ext);
    }
}