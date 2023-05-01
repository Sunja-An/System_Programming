#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

/* ls command and find the files according to conditions */
void Select_Files(char filename[], char *ext);

/* Extension File Find */
void Ext_find(char *dirpath, char *ext);
void Ext_check(char filepath[], char *extname, char *ext, struct stat *info);

/* Directory File Find */
int Directory_check(struct stat *info_p);

/* Remove Dirpath first character */
void RemoveFirst(char *buf);

/* Not maked
void Mtime_find();
void Name_find();
void Find_print();
*/