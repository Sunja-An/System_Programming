#include "../Move/move.h"
#include "../Struct/tree.h"
#include "print_form.h"

Node *Link_Arr[BUFSIZE];
int idx;

/* Not implemented */
void Print_Success()
{
    printf("------------Selected Data Information---------------\n");
    for (int i = 0; i < idx; i++)
    {
        printf("%s \n", Link_Arr[i]->filepath);
    }
}

void Print_Failed(){
    fprintf(stdout, "We try to catch file. Buf We cannot file you want");
}

void Print_Delete(){
    fprintf(stdout, "[DELETED FILE LIST]");
    for (int i = 0; i < idx; i++)
    {
        printf("------------Selected Data Information---------------\n");
        printf("%s \n", Link_Arr[i]->filepath);
    }
}

void Flag_Error(char* function_name)
{
    if(CONFIG_FILE)
        fprintf(stderr, "%s() : CONFIG file accessed", function_name);
    if(CACHE_FILE)
        fprintf(stderr, "%s() : CACHE file accessed", function_name);
}