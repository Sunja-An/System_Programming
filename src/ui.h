#include <ncurses.h>

#define ESCAPE 27
#define ENTER 10

int color = 1;
char *fileItem[] = {"", "move", "copy", "main menu", "credits"};
WINDOW **menuList(int start_col);
void makeMenubar(WINDOW *menubar);
void deleteMenu(WINDOW **items, int count);
int scrollMenu(WINDOW **items, int count, int menu_start_col, int index_num);
int checkQuit();
void initScreen();
void moveMode(WINDOW *scr);
void copyMode(WINDOW *scr);
void title(WINDOW *scr);
void credit(WINDOW *scr);
void config(WINDOW *scr);
void moveOpt1(WINDOW *scr);
void moveOpt2(WINDOW *scr);
void moveOpt3(WINDOW *scr);
void copyOpt1(WINDOW *scr);
void copyOpt2(WINDOW *scr);
void copyOpt3(WINDOW *scr);
void print_takeindex(WINDOW *scr);
void con_movepath(WINDOW *scr);
void con_backuppath(WINDOW *scr);
void con_printpath(WINDOW *scr);
void colorset(WINDOW *scr);