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
            Select_Files("/home", ext);
            exit(0);
        }
        else
        {
            pid_child = wait(&status);
            Print_Success();
        }
    }
    return 0;
}