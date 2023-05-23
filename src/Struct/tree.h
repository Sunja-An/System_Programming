#pragma once

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

typedef struct
{
    char filepath[BUFSIZE]; /* File path */
    char option[BUFSIZE];   /* Option to find*/
    int start_time;         /* Start Time of Sidstance */
    int end_time;           /* End Time of Distance */
    int idx;                /* List Index */
} MultipleArg;

extern Node *Link_Arr[BUFSIZE]; /* Saving Node* variable to link*/
extern int idx;                 /* Link Arr Index */

/* Checking the flag  */
#define ON 1
#define OFF 0

/* Flag setting to filtering */
