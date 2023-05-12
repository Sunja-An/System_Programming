#include "Move/move.h"
#include "Struct/tree.h"
#include "Print/print_form.h"

int main(int argc, char *argv[])
{
    int selection;
    char *ext;
    pid_t pid;
    pid_t pid_child;
    int status;
    char name[BUFSIZE];
    struct tm st;
    struct tm ed;
    int st_time;
    int ed_time;

    printf("Select what you want? (1: extension 2: Filename 3: Time Distance): ");
    scanf("%d", &selection);
    switch (selection)
    {
    /* From home directory and Selecting files according to Extension option */
    case 1:
        printf("Input Extension name: ");
        scanf("%s", ext);
        pid = fork();
        if (pid < 0)
            perror("fork error");
        else if (pid == 0)
        {
            Selecting_Extension("/home", ext);
            exit(0);
        }
        else
        {
            pid_child = wait(&status);
            Print_Success();
        }
        break;
    case 2:
        printf("Input Filename: ");
        scanf("%s", name);
        pid = fork();
        if (pid < 0)
            perror("fork error");
        else if (pid == 0)
        {
            Selecting_Filename("/home", name);
            exit(0);
        }
        else
        {
            pid_child = wait(&status);
            Print_Success();
        }
        break;
    case 3:
        printf("--------------------\n");
        printf("Start Year : ");
        scanf("%d", &st.tm_year);
        printf("Start Month : ");
        scanf("%d", &st.tm_mon);
        printf("Start Day : ");
        scanf("%d", &st.tm_mday);
        printf("--------------------\n");
        printf("End Year : ");
        scanf("%d", &ed.tm_year);
        printf("End Month : ");
        scanf("%d", &ed.tm_mon);
        printf("End Day : ");
        scanf("%d", &ed.tm_mday);
        st_time = MakeLocalTime_t(st.tm_year, st.tm_mon, st.tm_mday);
        ed_time = MakeLocalTime_t(ed.tm_year, ed.tm_mon, ed.tm_mday);
        pid = fork();
        if (pid < 0)
            perror("fork error");
        else if (pid == 0)
        {
            Selecting_time_distance("/home", st_time, ed_time);
            exit(0);
        }
        else
        {
            pid_child = wait(&status);
            Print_Success();
        }
        break;
    default:
        printf("wrong value..\n");
        printf("Try again!! :-)\n");
        break;
    }
    return 0;
}