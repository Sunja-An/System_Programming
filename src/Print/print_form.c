#include "../Move/move.h"
#include "../Struct/tree.h"
#include "print_form.h"
#include <ncurses.h>

#define CUT "---------------------------------------------------------------------------------------------------------------------"

extern Node *Link_Arr[BUFSIZE];
extern int idx;

extern char CONFIG_FILE;
extern char CACHE_FILE;

/* Not implemented */
void Print_Success(WINDOW *scr, int page)
{
    mvwprintw(scr, 1, 2,"[Page %d]%s", page, CUT);
    scrollok(scr, TRUE);
    for (int i = 0; i < 20; i++)
    {
        if (Link_Arr[i+page*20] == NULL)
            continue;
        mvwprintw(scr, i+2, 2, "%d %s \n", i+1, Link_Arr[i+page*20]->filepath);
    }
    mvwprintw(scr, 23, 2,"%s[Page %d]", CUT, page);
}

void Print_Failed()
{
    fprintf(stdout, "We try to catch file. Buf We cannot file you want");
}

void Print_Delete()
{
    fprintf(stdout, "[DELETED FILE LIST]");
    for (int i = 0; i < idx; i++)
    {
        printf("------------Selected Data Information---------------\n");
        printf("%s \n", Link_Arr[i]->filepath);
    }
}

void Flag_Error(char *function_name)
{
    if (CONFIG_FILE)
        fprintf(stderr, "%s() : CONFIG file accessed", function_name);
    if (CACHE_FILE)
        fprintf(stderr, "%s() : CACHE file accessed", function_name);
}
