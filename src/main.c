#include "move.h"
#include "tree.h"
#include "print_form.h"

int main(int argc, char *argv[])
{
    int selection;
    printf("Select what you want? (1: extension 2: Filename 3: Time Distance): ");
    scanf("%d", &selection);
    switch (selection)
    {
    /* From home directory and Selecting files according to Extension option */
    case 1:
        Select_Files("/home");
        Print_Success();
    }
    return 0;
}