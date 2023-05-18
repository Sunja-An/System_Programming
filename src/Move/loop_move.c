#include "move.h"
#include "../Struct/tree.h"

Node *Link_Arr[BUFSIZE];
int idx;

void *Loop_Filename(void *args)
{
    MultipleArg *multiple_arg = (MultipleArg *)args;
    /* Variable */
    char *name;
    int i = 0;
    memset(name, 0, sizeof(name));
    strcpy(name, multiple_arg->option);
    if(name == NULL){
        fprintf(stderr, "No Input value to find file");
    }
    while(i<idx){
        printf("Link_Arr[i] : %s\n", Link_Arr[i++]->filepath);
        if(strstr(Link_Arr[i++]->filepath, name) == NULL){
            free(Link_Arr[i-1]);
            Link_Arr[i-1] = NULL;
        }
    }
    return NULL;
}

/* Selecting File or Directory [Recursive] */
void *Loop_Distance(void *args)
{
    MultipleArg *multiple_arg = (MultipleArg *)args;

    /* Variable */
    int i = 0;
    int st;
    int ed;

    /* Variable Setting */
    st = multiple_arg->start_time;
    ed = multiple_arg->end_time;

    while(i<idx){
        if(Link_Arr[i]->atime < st || Link_Arr[i++]->atime > ed){
            free(Link_Arr[i-1]);
            Link_Arr[i-1] = NULL;
        }
    }

    return NULL;
}