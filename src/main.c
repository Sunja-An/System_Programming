#include "Move/move.h"
#include "Struct/tree.h"
#include "Print/print_form.h"

int main(int argc, char *argv[])
{
    /* scanf variable*/
    int selection;
    char ext[BUFSIZE];
    char name[BUFSIZE];

    /* Process variable */
    pid_t pid;
    pid_t pid_child;
    int status;
    
    /* Thread variable */
    pthread_t first_take;
    pthread_t second_take;
    pthread_t third_take;

    MultipleArg *multiple_arg;
    void *thr_ret;

    /* time distance variable */
    struct tm st;
    struct tm ed;
    int st_time;
    int ed_time;

    /* init program */
    CACHE_FILE = OFF;
    CONFIG_FILE = OFF;

    printf("Select what you want? (1: extension 2: Filename 3: Time Distance): ");
    scanf("%d", &selection);
    switch (selection)
    {
    /* From home directory and Selecting files according to Extension option */
    case 1:
        printf("Input Extension name: ");
        scanf("%s", ext);

        multiple_arg = (MultipleArg *)malloc(sizeof(MultipleArg));
        strcpy(multiple_arg->filepath, "/home");
        strcpy(multiple_arg->option, ext);

        if (pthread_create(&first_take, NULL, Selecting_Filename, (void *)multiple_arg) != 0)
        {
            puts("pthread_create() error");
            return -1;
        }

        if (pthread_join(first_take, &thr_ret) != 0)
        {
            puts("pthread_join() error");
            return -1;
        }

        Print_Success();
        free(thr_ret);

        break;
    case 2:
        printf("Input Filename: ");
        scanf("%s", name);
        multiple_arg = (MultipleArg *)malloc(sizeof(MultipleArg));
        strcpy(multiple_arg->filepath, "/home");
        strcpy(multiple_arg->option, name);

        if (pthread_create(&first_take, NULL, Selecting_Filename, (void *)multiple_arg) != 0)
        {
            puts("pthread_create() error");
            return -1;
        }
        if (pthread_join(first_take, &thr_ret) != 0)
        {
            puts("pthread_join() error");
            return -1;
        }

        Print_Success();
        free(thr_ret);
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