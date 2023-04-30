#include "move.h"
#include "tree.h"

/* Gloabl Variable */
static Node *Link_Arr[BUFSIZE]; /* Saving Node* variable to link*/
static int idx = 0;             /* Link Arr Index */

void Select_Files(char filename[])
{
    DIR *dir_ptr;
    struct dirent *direntp;
    char path[256];
    struct stat info;
    if (chdir(filename) != 0)
    {
        perror(filename);
        exit(1);
    }
    getcwd(path, sizeof(path));
    printf("path: %s\n", path);
    if ((dir_ptr = opendir(path)) == NULL)
        fprintf(stderr, "Select_Files Func Error: cannot open %s\n", path);
    else
    {
        while ((direntp = readdir(dir_ptr)) != NULL)
        {
            if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
                continue;
            if (stat(direntp->d_name, &info))
                if (!Directory_check(&info))
                {
                    Ext_find(direntp->d_name, "c");
                    Select_Files(direntp->d_name);
                }
                /* Testing Finding the .c extension in File */
                else
                    Ext_check(direntp->d_name, "c", &info);
        }
        closedir(dir_ptr);
    }
}

void Ext_find(char *dirpath, char *ext)
{
    DIR *dir_ptr;
    struct dirent *direntp;
    struct stat info;
    if ((dir_ptr = opendir(dirpath)) == NULL)
        fprintf(stderr, "cannot open current directory\n");
    else
    {
        while ((direntp = readdir(dir_ptr)) != NULL)
            if (stat(dirpath, &info) == -1)
                Ext_check(direntp->d_name, ext, &info);
        closedir(dir_ptr);
    }
}

void Ext_check(char *extname, char *ext, struct stat *info)
{
    char ptr[BUFSIZE];
    strcpy(ptr, extname);
    char *comp = strpbrk(ptr, ".");
    if (comp != NULL)
    {
        RemoveFirst(comp);
        if (strcmp(comp, ext) == 0)
        {
            Node *newnode = (Node *)malloc(sizeof(Node));
            getcwd(newnode->filepath, sizeof(BUFSIZE));
            newnode->name = extname;
            newnode->ext = ext;
            newnode->atime = &info->st_atime;
            Link_Arr[idx++] = newnode;
        }
    }
}

int Directory_check(struct stat *info_p)
{
    if (S_ISDIR(info_p->st_mode))
        return 0;
    else
        return -1;
}

void RemoveFirst(char *buf)
{
    int i;
    for (i = 1; buf[i]; i++)
        buf[i - 1] = buf[i];
    buf[i - 1] = '\0';
}