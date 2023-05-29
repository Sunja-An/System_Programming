#include "../Move/move.h"
#include "../Struct/tree.h"
#include "print_form.h"

#define CUT "---------------------------------------------------------------------------------------------------------------------"

extern Node *Link_Arr[BUFSIZE];
extern int idx;

extern char FILEPATH;
extern char CONFIG_FILE;
extern char CACHE_FILE;

int zero = 0;

/* Not implemented */
void Print_Success(WINDOW *scr, int page)
{
    werase(scr);
    mvwprintw(scr, 1, 2, "[choose phase] number of files are %d\n", idx);
    mvwprintw(scr, 2, 2, "[Page %d/%d]%s\n", page+1, (idx/20)+1, CUT);
    for (int i = 0; i < 20; i++)
    {
        if (Link_Arr[i+page*20] == NULL)
            continue;
        if (FILEPATH)
            mvwprintw(scr, i+3, 2, "%d %s", i+1, Link_Arr[i+page*20]->filepath);
        else
            mvwprintw(scr, i+3, 2, "%d %s", i+1, Link_Arr[i+page*20]->filename);
    }
    mvwprintw(scr, 24, 2, "%s[Page %d/%d]", CUT, page+1, (idx/20)+1);
    wrefresh(scr);
}

void Print_Failed(WINDOW *scr)
{
    fprintf(stdout, "We try to catch file. Buf We cannot file you want");
}

void Print_Delete(WINDOW *scr, int page, int n, int* input)
{
    werase(scr);
    mvwprintw(scr, 1, 2, "[check phase] number of chosen files are %d\n", n);
    mvwprintw(scr, 2, 2, "[Page %d/%d]%s\n", page+1, (n/20)+1, CUT);
    for (int i = 0; i < 20; i++)
    {
        if (input[i+page*20] == -1) break;
        
        if (FILEPATH)
            mvwprintw(scr, i+3, 2, "%d %s", i+1, Link_Arr[input[i+page*20]]->filepath); 
        else
            mvwprintw(scr, i+3, 2, "%d %s", i+1, Link_Arr[input[i+page*20]]->filename);
    }
    mvwprintw(scr, 24, 2, "%s[Page %d/%d]", CUT, page+1, (n/20)+1);
    wrefresh(scr);
}

void Flag_Error(char *function_name)
{
    if (CONFIG_FILE)
        fprintf(stderr, "%s() : CONFIG file accessed", function_name);
    if (CACHE_FILE)
        fprintf(stderr, "%s() : CACHE file accessed", function_name);
}
