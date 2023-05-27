#include "../Move/move.h"
#include "../Struct/tree.h"
#include "print_form.h"

#define CUT "---------------------------------------------------------------------------------------------------------------------"

extern Node *Link_Arr[BUFSIZE];
extern int idx;

extern char CONFIG_FILE;
extern char CACHE_FILE;

/* Not implemented */
void Print_Success(WINDOW *scr, int page)
{
    werase(scr);
    mvwprintw(scr, 1, 2, "number of files are %d\n", idx);
    mvwprintw(scr, 2, 2, "[Page %d/%d]%s\n", page, idx/20, CUT);
    for (int i = 0; i < 20; i++)
    {
        if (Link_Arr[i+page*20] == NULL)
            continue;
        mvwprintw(scr, i+3, 2, "%d %s", i+1, Link_Arr[i+page*20]->filename);
    }
    mvwprintw(scr, 24, 2, "%s[Page %d/%d]", CUT, page, idx/20);
    wrefresh(scr);
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
