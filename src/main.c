#include "Move/move.h"
#include "Struct/tree.h"
#include "Print/print_form.h"
#include "ui.h"

extern Node *Link_Arr[BUFSIZE]; /* Saving Node* variable to link*/
extern int idx;                 /* Link Arr Index */
char CONFIG_FILE;
char CACHE_FILE;
char FILEPATH = 0;

extern char MOVE_FILE_PATH[BUFSIZE];
extern char BACK_UP_PATH[BUFSIZE];

int main(int argc, char *argv[])
{
    FILE* fp;
    if(fp = fopen(".tmp/FTM_MOVE","r")){
        fclose(fp);
    }else{    
        mkdir("/tmp/FTM_MOVE",0777);
        mkdir("/tmp/FTM_BACK_UP",0744);    
        strcpy(MOVE_FILE_PATH, "/tmp/FTM_MOVE");
        strcpy(BACK_UP_PATH, "/tmp/FTM_BACK_UP");
    }
    WINDOW *menubar, *exeScreen, *about;
    int key, status;
    initScreen();
    bkgd(COLOR_PAIR(color));
    menubar = subwin(stdscr, 1, 130, 0, 0);
    exeScreen = subwin(stdscr, 30, 130, 1, 0);
    title(exeScreen);
    makeMenubar(menubar);
    refresh();
    while (1)
    {
        WINDOW **menuItems;
        int selectedItem;

        key = getch();
        wrefresh(exeScreen);
        
        if (key == 'a' || key == 'A')
        {
            menuItems = menuList(0);
            selectedItem = scrollMenu(menuItems, 4, 20, 0);
            deleteMenu(menuItems, 5);
            switch (selectedItem)
            {
            case 0:
                moveMode(exeScreen);
                break;
            case 1:
                copyMode(exeScreen);
                break;
            case 2:
                title(exeScreen);
                break;
            case 3:
                credit(exeScreen);
                break;
            default:
                wprintw(exeScreen, "Nothing have selected.");
            }
            touchwin(stdscr);
            refresh();
        }
        if (key == ESCAPE || key == 'q' || key == 'Q')
        {
            if (checkQuit() == 1)
                break;
        }
        if (key == 'c' || key == 'C') config(exeScreen);
        touchwin(stdscr);
        title(exeScreen);
        refresh();
    }
    endwin();
    echo();

    return 0;
}

WINDOW **menuList(int start_col)
{
    int i;
    WINDOW **items;
    items = (WINDOW **)malloc(5 * sizeof(WINDOW *));
    items[0] = newwin(6, 19, 1, start_col);
    wbkgd(items[0], COLOR_PAIR(2));
    box(items[0], ACS_VLINE, ACS_HLINE);
    items[1] = subwin(items[0], 1, 17, 2, start_col + 1);
    items[2] = subwin(items[0], 1, 17, 3, start_col + 1);
    items[3] = subwin(items[0], 1, 17, 4, start_col + 1);
    items[4] = subwin(items[0], 1, 17, 5, start_col + 1);
    for (i = 1; i < 5; i++)
        wprintw(items[i], "%s", fileItem[i]);
    wbkgd(items[1], COLOR_PAIR(1));
    wrefresh(items[0]);
    return items;
}

int checkQuit()
{
    WINDOW *check;
    int key;
    check = newwin(3, 40, 3, 5);
    wmove(check, 1, 2);
    wprintw(check, "Exit program (y/n) ? ");
    wbkgd(check, COLOR_PAIR(2));
    box(check, ACS_VLINE, ACS_HLINE);
    refresh();
    key = wgetch(check);
    delwin(check);
    if (key == 'y' || key == 'Y')
        return 1;
    else
        return 0;
}
void deleteMenu(WINDOW **items, int count)
{
    int i;
    for (i = 0; i < count; i++)
        delwin(items[i]);
    free(items);
}
int scrollMenu(WINDOW **items, int count, int menu_start_col, int index_num)
{
    int key;
    int selected = 0;
    while (1)
    {
        key = getch();
        if (key == KEY_DOWN || key == KEY_UP)
        {
            wbkgd(items[selected + 1], COLOR_PAIR(2));
            wnoutrefresh(items[selected + 1]);
            if (key == KEY_DOWN)
                selected = (selected + 1) % count;
            else
                selected = (selected + count - 1) % count;
            wbkgd(items[selected + 1], COLOR_PAIR(1));
            wnoutrefresh(items[selected + 1]);
            doupdate();
        }
        else if (key == ESCAPE)
            return -1;
        else if (key == ENTER)
            return selected;
    }
}
void initScreen()
{
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_WHITE);
    curs_set(2);
    noecho();
    keypad(stdscr, TRUE);
}
void makeMenubar(WINDOW *menubar)
{
    wbkgd(menubar, COLOR_PAIR(2));
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, " Menu");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(a)");
}
void moveMode(WINDOW *scr)
{
    int opt;
    werase(scr);
    mvwprintw(scr, 1, 2, " Move Mode : Option Select Stage");
    mvwprintw(scr, 2, 2, "*****************************************************************************************");
    mvwprintw(scr, 3, 2, " Press the button to choose option");
    mvwprintw(scr, 4, 2, " 1. extension");
    mvwprintw(scr, 5, 2, " 2. filename");
    mvwprintw(scr, 6, 2, " 3. time distance");
    mvwprintw(scr, 7, 2, "-----------------------------------------------------------------------------------------");
    mvwprintw(scr, 8, 2, " Option Detail");
    mvwprintw(scr, 9, 2, " 1. collect files by extension");
    mvwprintw(scr, 10, 2, " 2. collect files by filename");
    mvwprintw(scr, 11, 2, " 3. collect files by time distance");
    mvwprintw(scr, 12, 2, "****************************************************************************************");
    mvwprintw(scr, 13, 2, " README");
    mvwprintw(scr, 14, 2, " Move Mode can collect files in your disk");
    mvwprintw(scr, 15, 2, " User will choose what to save and to delete among collected files");
    mvwprintw(scr, 16, 2, " This mode is made for finding and managing old file easily");
    opt = wgetch(scr);
    switch (opt)
    {
    case '1':
        moveOpt1(scr);
        break;
    case '2':
        moveOpt2(scr);
        break;
    case '3':
        moveOpt3(scr);
        break;
    }
}
void copyMode(WINDOW *scr)
{
    int opt;
    werase(scr);
    mvwprintw(scr, 1, 2, "Backup Mode : Option Select Stage");
    mvwprintw(scr, 2, 2, "*****************************************************************************************");
    mvwprintw(scr, 3, 2, " Press the button to choose option");
    mvwprintw(scr, 4, 2, " 1. extension");
    mvwprintw(scr, 5, 2, " 2. filename");
    mvwprintw(scr, 6, 2, " 3. time distance");
    mvwprintw(scr, 7, 2, "-----------------------------------------------------------------------------------------");
    mvwprintw(scr, 8, 2, " Option Detail");
    mvwprintw(scr, 9, 2, " 1. collect files by extension");
    mvwprintw(scr, 10, 2, " 2. collect files by filename");
    mvwprintw(scr, 11, 2, " 3. collect files by time distance");
    mvwprintw(scr, 12, 2, "****************************************************************************************");
    mvwprintw(scr, 13, 2, " README");
    mvwprintw(scr, 14, 2, " Backup Mode can collect files in your disk");
    mvwprintw(scr, 15, 2, " User will choose what to backup and to delete among collected files");
    mvwprintw(scr, 16, 2, " This mode is made for backup files easily");
    opt = wgetch(scr);
    switch (opt)
    {
    case '1':
        copyOpt1(scr);
        break;
    case '2':
        copyOpt2(scr);
        break;
    case '3':
        copyOpt3(scr);
        break;
    }
}

void title(WINDOW *scr)
{
    werase(scr);
    mvwprintw(scr, 1, 2, "----------------------------------");
    mvwprintw(scr, 2, 2, "-          File Manager          -");
    mvwprintw(scr, 3, 2, "----------------------------------");
    mvwprintw(scr, 4, 2, "-  Press the button              -");
    mvwprintw(scr, 5, 2, "-  a : open menu, q : quit       -");
    mvwprintw(scr, 6, 2, "-  c : configuration             -");
    mvwprintw(scr, 7, 2, "----------------------------------");
    wrefresh(scr);
}
void credit(WINDOW *scr)
{
    werase(scr);
    mvwprintw(scr, 1, 2, "  ELEC0462-002 System Programming");
    mvwprintw(scr, 2, 2, "  2023 Spring Semester Term Project");
    mvwprintw(scr, 3, 2, "**************************************");
    mvwprintw(scr, 4, 2, "  Team 6 : File manager");
    mvwprintw(scr, 5, 2, "**************************************");
    mvwprintw(scr, 6, 2, "           Members of Team 6        ");
    mvwprintw(scr, 7, 2, "      ID          Name        Major");
    mvwprintw(scr, 8, 2, "-------------------------------------");
    mvwprintw(scr, 9, 2, "  2020116575   Sunwoo Ahn      CSE");
    mvwprintw(scr, 10, 2, "  2021115360   Donghyeok Seo   CSE");
    mvwprintw(scr, 11, 2, "**************************************");
    mvwprintw(scr, 12, 2, "  Version : 3.0, Date : 2023-05-25");
    mvwprintw(scr, 13, 2, "**************************************");
}
void config(WINDOW *scr){
    int opt;
    while(1){
        werase(scr);
        mvwprintw(scr, 1, 2, " Configuration");
        mvwprintw(scr, 2, 2, "********************************************");
        mvwprintw(scr, 3, 2, " Press the button to choose option");
        mvwprintw(scr, 4, 2, " 1. Set save move filepath");
        mvwprintw(scr, 5, 2, " 2. Set save backup filepath");
        mvwprintw(scr, 6, 2, " 3. Set print form");
        mvwprintw(scr, 7, 2, " 4. Go back to main menu");
        mvwprintw(scr, 8, 2, "********************************************");
        wrefresh(scr);
        opt = wgetch(scr);
        switch (opt)
        {
        case '1':
            con_movepath(scr);
            break;
        case '2':
            con_backuppath(scr);
            break;
        case '3':
            con_printpath(scr);
            break;
        case '4':
            return;
        default:
            continue;
        }
    }
}
void moveOpt1(WINDOW *scr)
{
    /* Option Variable */
    char ext[BUFSIZE], tmp[BUFSIZE], *tok, *toktmp;
    int input[BUFSIZE];
    /* Thread variable */
    pthread_t first_take;
    MultipleArg multiple_arg;
    void *thr_ret;
    echo();
    werase(scr);
    mvwprintw(scr, 1, 2, "Option 1 : extension Collection");
    mvwprintw(scr, 2, 2, "----------------------------------------------------------------");
    mvwprintw(scr, 3, 2, " String that name include (for instance : .c, .java)");
    mvwprintw(scr, 4, 2, " String : ");
    mvwscanw(scr, 4, 12, " %s", ext);
    mvwprintw(scr, 5, 2, "---------------------------------------------------------------");

    /* From home directory and Selecting files according to Extension option */
    multiple_arg.filepath = "/home";
    multiple_arg.option = ext;
    multiple_arg.select = 0;

    if (pthread_create(&first_take, NULL, Selecting_Filename, (void *)&multiple_arg) != 0)
    {
        puts("pthread_create() error");
        exit(1);
    }

    if (pthread_join(first_take, &thr_ret) != 0)
    {
        puts("pthread_join() error");
        exit(1);
    }

    print_takeindex(scr);
    noecho();
    wrefresh(scr);
    free(thr_ret);
}
void moveOpt2(WINDOW *scr)
{
    /* Option Variable */
    char name[BUFSIZE], tmp[BUFSIZE], *tok;
    int* input = (int*)malloc(4*BUFSIZE);
    /* Thread variable */
    pthread_t first_take;
    MultipleArg multiple_arg;
    void *thr_ret;
    echo();
    werase(scr);
    mvwprintw(scr, 1, 2, "Option 2 : name Collection");
    mvwprintw(scr, 2, 2, "----------------------------------------------------------------");
    mvwprintw(scr, 3, 2, " String that name include ");
    mvwprintw(scr, 4, 2, " String : ");
    mvwscanw(scr, 4, 12, " %s", name);
    mvwprintw(scr, 5, 2, "---------------------------------------------------------------");

    multiple_arg.filepath = "/home";
    multiple_arg.option = name;
    multiple_arg.select = 1;

    if (pthread_create(&first_take, NULL, Selecting_Filename, (void *)&multiple_arg) != 0)
    {
        puts("pthread_create() error");
        exit(1);
    }
    if (pthread_join(first_take, &thr_ret) != 0)
    {
        puts("pthread_join() error");
        exit(1);
    }
    print_takeindex(scr);
    noecho();
    wrefresh(scr);
    free(thr_ret);
}
void moveOpt3(WINDOW *scr)
{
    /* time distance variable */
    struct tm st;
    struct tm ed;
    int st_time;
    int ed_time;

    /* Thread variable */
    pthread_t first_take;
    MultipleArg multiple_arg;
    void *thr_ret;
    echo();
    werase(scr);
    mvwprintw(scr, 1, 2, "Option 3 : Date Classify");
    mvwprintw(scr, 2, 2, "----------------------------------------------------------------");
    mvwprintw(scr, 3, 2, " start time (distant past)");
    mvwprintw(scr, 4, 2, " Year : ");
    mvwscanw(scr, 4, 12, "%d", &st.tm_year);
    mvwprintw(scr, 5, 2, " Month : ");
    mvwscanw(scr, 5, 12, "%d", &st.tm_mon);
    mvwprintw(scr, 6, 2, " Date : ");
    mvwscanw(scr, 6, 12, "%d", &st.tm_mday);
    mvwprintw(scr, 7, 2, "---------------------------------------------------------------");
    mvwprintw(scr, 8, 2, " end time (near past)");
    mvwprintw(scr, 9, 2, " Year : ");
    mvwscanw(scr, 9, 12, "%d", &ed.tm_year);
    mvwprintw(scr, 10, 2, " Month : ");
    mvwscanw(scr, 10, 12, "%d", &ed.tm_mon);
    mvwprintw(scr, 11, 2, " Date : ");
    mvwscanw(scr, 11, 12, "%d", &ed.tm_mday);
    mvwprintw(scr, 12, 2, "---------------------------------------------------------------");
    st_time = MakeLocalTime_t(st.tm_year, st.tm_mon, st.tm_mday);
    ed_time = MakeLocalTime_t(ed.tm_year, ed.tm_mon, ed.tm_mday);
    
    multiple_arg.filepath = "/home";
    multiple_arg.start_time = st_time;
    multiple_arg.end_time = ed_time;

    noecho();

    if (pthread_create(&first_take, NULL, Selecting_time_distance, (void *)&multiple_arg) != 0)
    {
        puts("pthread_create() error");
        exit(1);
    }
    if (pthread_join(first_take, &thr_ret) != 0)
    {
        puts("pthread_join() error");
        exit(1);
    }
    print_takeindex(scr);
    noecho();
    wrefresh(scr);
    free(thr_ret);
}

void copyOpt1(WINDOW *scr)
{
    /* Option Variable */
    char ext[BUFSIZE], tmp[BUFSIZE], *tok, *toktmp;
    int input[BUFSIZE];
    /* Thread variable */
    pthread_t first_take;
    MultipleArg multiple_arg;
    void *thr_ret;
    echo();
    werase(scr);
    mvwprintw(scr, 1, 2, "Option 1 : extension Collection");
    mvwprintw(scr, 2, 2, "----------------------------------------------------------------");
    mvwprintw(scr, 3, 2, " String that name include (for instance : .c, .java)");
    mvwprintw(scr, 4, 2, " String : ");
    mvwscanw(scr, 4, 12, " %s", ext);
    mvwprintw(scr, 5, 2, "---------------------------------------------------------------");

    /* From home directory and Selecting files according to Extension option */
    multiple_arg.filepath = "/home";
    multiple_arg.option = ext;
    multiple_arg.select = 0;

    if (pthread_create(&first_take, NULL, Selecting_Filename, (void *)&multiple_arg) != 0)
    {
        puts("pthread_create() error");
        exit(1);
    }

    if (pthread_join(first_take, &thr_ret) != 0)
    {
        puts("pthread_join() error");
        exit(1);
    }

    print_takeindex(scr);
    noecho();
    wrefresh(scr);
    free(thr_ret);
}

void copyOpt2(WINDOW *scr)
{
    /* Option Variable */
    char name[BUFSIZE], tmp[BUFSIZE], *tok;
    int* input = (int*)malloc(4*BUFSIZE);
    /* Thread variable */
    pthread_t first_take;
    MultipleArg multiple_arg;
    void *thr_ret;
    echo();
    werase(scr);
    mvwprintw(scr, 1, 2, "Option 2 : extension Collection");
    mvwprintw(scr, 2, 2, "----------------------------------------------------------------");
    mvwprintw(scr, 3, 2, " String that name include ");
    mvwprintw(scr, 4, 2, " String : ");
    mvwscanw(scr, 4, 12, "%s", name);
    mvwprintw(scr, 5, 2, "---------------------------------------------------------------");

    multiple_arg.filepath = "/home";
    multiple_arg.option = name;
    multiple_arg.select = 1;

    if (pthread_create(&first_take, NULL, Selecting_Filename, (void *)&multiple_arg) != 0)
    {
        puts("pthread_create() error");
        exit(1);
    }
    if (pthread_join(first_take, &thr_ret) != 0)
    {
        puts("pthread_join() error");
        exit(1);
    }
    print_takeindex(scr);
    noecho();
    wrefresh(scr);
    free(thr_ret);
}

void copyOpt3(WINDOW *scr)
{
    /* time distance variable */
    struct tm st;
    struct tm ed;
    int st_time;
    int ed_time;

    /* Thread variable */
    pthread_t first_take;
    MultipleArg multiple_arg;
    void *thr_ret;
    echo();
    werase(scr);
    mvwprintw(scr, 1, 2, "Option 3 : Date Classify");
    mvwprintw(scr, 2, 2, "----------------------------------------------------------------");
    mvwprintw(scr, 3, 2, " start time (distant past)");
    mvwprintw(scr, 4, 2, " Year : ");
    mvwscanw(scr, 4, 12, "%d", &st.tm_year);
    mvwprintw(scr, 5, 2, " Month : ");
    mvwscanw(scr, 5, 12, "%d", &st.tm_mon);
    mvwprintw(scr, 6, 2, " Date : ");
    mvwscanw(scr, 6, 12, "%d", &st.tm_mday);
    mvwprintw(scr, 7, 2, "---------------------------------------------------------------");
    mvwprintw(scr, 8, 2, " end time (near past)");
    mvwprintw(scr, 9, 2, " Year : ");
    mvwscanw(scr, 9, 12, "%d", &ed.tm_year);
    mvwprintw(scr, 10, 2, " Month : ");
    mvwscanw(scr, 10, 12, "%d", &ed.tm_mon);
    mvwprintw(scr, 11, 2, " Date : ");
    mvwscanw(scr, 11, 12, "%d", &ed.tm_mday);
    mvwprintw(scr, 12, 2, "---------------------------------------------------------------");
    st_time = MakeLocalTime_t(st.tm_year, st.tm_mon, st.tm_mday);
    ed_time = MakeLocalTime_t(ed.tm_year, ed.tm_mon, ed.tm_mday);
    
    multiple_arg.filepath = "/home";
    multiple_arg.start_time = st_time;
    multiple_arg.end_time = ed_time;

    noecho();

    if (pthread_create(&first_take, NULL, Selecting_time_distance, (void *)&multiple_arg) != 0)
    {
        puts("pthread_create() error");
        exit(1);
    }
    if (pthread_join(first_take, &thr_ret) != 0)
    {
        puts("pthread_join() error");
        exit(1);
    }
    print_takeindex(scr);
    noecho();
    wrefresh(scr);
    free(thr_ret);
}

void print_takeindex(WINDOW *scr){
    int pages = idx / 20;
    int j = 0;
    char tmp[BUFSIZE], *tok;
    int* input = (int*)malloc(4*BUFSIZE);
    for (int i = 0; i <= pages; i++)
    {
        Print_Success(scr, i);
        memset(tmp, 0, sizeof(tmp));
        mvwprintw(scr, 25, 2, "choose the index numbers, delimeter is \' \'(space)");
        mvwgetstr(scr, 26, 2, tmp);
        tok = strtok(tmp, " ");
        while (tok != NULL)
        {
            input[j] = (atoi(tok) - 1)+ (i  * 20);
            tok = strtok(NULL, " ");
            j++;
        }
    }
    noecho();
    int deletepages=j/20, opt;
    for (int i = 0; i <= deletepages; i++)
    {
        Print_Delete(scr, i, j, input);
        mvwprintw(scr, 25, 2, "press any key to next page, if last page program will return to main menu");
        opt = wgetch(scr);
    }
    
    moving(input, j+1); 
    /*switch(mc){
        case 0: moving(input, j+1); 
        case 1: filecopy(input, j+1); 
    }*/
    
    free(input);
}

void con_movepath(WINDOW *scr){
    werase(scr);
    echo();
    wrefresh(scr);
    mvwprintw(scr, 1, 2, " Set save filepath : input where to save");
    mvwprintw(scr, 2, 2, " please type absolute path");
    mvwprintw(scr, 3, 2, " ex) /home/usrname/WorkSpace/fileBackup");
    mvwprintw(scr, 4, 2, " default save location) /tmp/FTM_MOVE");
    mvwprintw(scr, 5, 2, "*************************************************");
    mvwprintw(scr, 8, 2, "*************************************************");
    mvwprintw(scr, 6, 2, "Move file path(absolute) : ");
    mvwgetstr(scr, 7, 2, MOVE_FILE_PATH);
    noecho();
    wrefresh(scr);
}

void con_backuppath(WINDOW *scr){
    werase(scr);
    echo();
    wrefresh(scr);
    mvwprintw(scr, 1, 2, " Set save filepath : input where to save");
    mvwprintw(scr, 2, 2, " please type absolute path");
    mvwprintw(scr, 3, 2, " ex) /home/usrname/WorkSpace/fileBackup");
    mvwprintw(scr, 4, 2, " default save location) /tmp/FTM_BACK_UP");
    mvwprintw(scr, 5, 2, "*************************************************");
    mvwprintw(scr, 8, 2, "*************************************************");
    mvwprintw(scr, 6, 2, "Backup file path(absolute) : ");
    mvwgetstr(scr, 7, 2, BACK_UP_PATH);
    noecho();
    wrefresh(scr);
}


void con_printpath(WINDOW *scr){
    int opt;
    werase(scr);
    mvwprintw(scr, 1, 2, "Set print form : choose the form");
    mvwprintw(scr, 2, 2, "********************************************");
    mvwprintw(scr, 3, 2, " Press the button to choose option");
    mvwprintw(scr, 4, 2, " 1. filename with absolute path");
    mvwprintw(scr, 5, 2, " 2. only filename");
    mvwprintw(scr, 6, 2, "********************************************");
    opt = wgetch(scr);
    switch (opt)
    {
    case '1':
        FILEPATH=1;
        break;
    case '2':
        FILEPATH=0;
        break;
    }
    wrefresh(scr);
}
