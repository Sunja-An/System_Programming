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
void Selecting_Files(char filename[], char* ext);
void Selecting_Filename(char filename[], char *name);
void Selecting_time_distance(char filename[],struct tm* st,struct tm* ed);

/* Extension File Find */
void Ext_find(char *dirpath, char *ext);
void Ext_check(char filepath[], char *extname, char *ext, struct stat *info);

/* Directory File Find */
int Directory_check(struct stat *info_p);

/* Remove Dirpath first character */
void RemoveFirst(char *buf);

void Name_find(char *dirpath, char *name);
void Name_check(char* filepath, char* filename, char* name, struct stat *info);

void Atime_find(char *dirpath, int st, int ed);
void Atime_check(char *filepath, int st, int ed, struct stat* info);
time_t MakeLocalTime_t(int YYYY, int MM, int DD);