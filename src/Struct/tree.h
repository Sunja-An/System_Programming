#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFSIZE 4096

typedef struct
{
    char filepath[BUFSIZE]; /* Filepath Judge */
    time_t atime;           /* Modified Time Judge */
} Node;