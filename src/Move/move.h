#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <pthread.h>
#include <ncurses.h>

/* ls command and find the files according to conditions */
void *Selecting_Filename(void *args);
void Name_find(char *dirpath, char *name, int select);
void Name_check(char *filepath, char filename[], char *name, int select,struct stat *info);

/* Time Distance Find */
void *Selecting_time_distance(void *args);
void Atime_find(char *dirpath, int st, int ed);
void Atime_check(char *filepath, char filename[] ,int st, int ed, struct stat *info);

/* Directory File Find */
int Directory_check(struct stat *info_p);

/* Extrating Unix-Time value */
time_t MakeLocalTime_t(int YY, int MM, int DD);

/* Remove Dirpath first character */
void RemoveFirst(char *buf);

/* Selected files to move and backup */
int filecopy(const char *src, const char *dst);
void moving(int* arr, int num);
void back_up(int* arr, int num);

/* String Setting */
char* cutting_filename(char* filepath);
bool Discriminate_name(char filepath[], char* name);
bool Discriminate_ext(char filepath[], char* ext);
