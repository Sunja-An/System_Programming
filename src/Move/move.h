#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <pthread.h>

/* Checking the flag  */
#define ON 1
#define OFF 0

/* Flag setting to filtering */
char CONFIG_FILE;
char CACHE_FILE;

/* ls command and find the files according to conditions */
void *Selecting_Filename(void *args);
void Name_find(char *dirpath, char *name);
void Name_check(char *filepath, char *filename, char *name, struct stat *info);

/* Time Distance Find */
void *Selecting_time_distance(void *args);
void Atime_find(char *dirpath, int st, int ed);
void Atime_check(char *filepath, int st, int ed, struct stat *info);

/* Directory File Find */
int Directory_check(struct stat *info_p);

/* Extrating Unix-Time value */
time_t MakeLocalTime_t(int YY, int MM, int DD);

/* Remove Dirpath first character */
void RemoveFirst(char *buf);
