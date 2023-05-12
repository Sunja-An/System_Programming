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

/* ls command and find the files according to conditions */
void Selecting_Extension(char filename[], char *ext);
void Selecting_Filename(char filename[], char *name);
void Selecting_time_distance(char filename[], int st, int ed);

/* Extension File Find */
void Ext_find(char *dirpath, char *ext);
void Ext_check(char filepath[], char *extname, char *ext, struct stat *info);

void Name_find(char *dirpath, char *name);
void Name_check(char *filepath, char *filename, char *name, struct stat *info);

void Atime_find(char *dirpath, int st, int ed);
void Atime_check(char *filepath, int st, int ed, struct stat *info);

/* Extrating Unix-Time value */
time_t MakeLocalTime_t(int YY, int MM, int DD);

/* Directory File Find */
int Directory_check(struct stat *info_p);

/* Extract the string that you want */
//void Extract_Name(char* filepath);
//void Extract_Extension(char* filepath);

/* Remove Dirpath first character */
void RemoveFirst(char *buf);
