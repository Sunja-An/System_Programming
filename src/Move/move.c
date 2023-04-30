#include "move.h"
#include "tree.h"

/* Gloabl Variable */
static Node *Link_Arr[BUFSIZE]; /* Saving Node* variable to link*/
static int idx = 0;             /* Link Arr Index */
char slash[2] = "/";

/* Selecting File or Directory [Recursive] */
void Select_Files(char filename[])
{
    /* Variable */
    DIR *dir_ptr;
    struct stat info;
    struct dirent *direntp;
    char path[256];
    char newpath[256];

    /* Change the directory */
    if (chdir(filename) != 0)
    {
        perror(filename);
        exit(1);
    }

    /* Get the Target Path  */
    getcwd(path, sizeof(path));

    /* Open directory and Finding process */
    if ((dir_ptr = opendir(path)) == NULL)
        fprintf(stderr, "Select_Files Func Error: cannot open %s\n", path);
    else
    {
        while ((direntp = readdir(dir_ptr)) != NULL)
        {
            printf("%s\n", direntp->d_name);
            /* directory name '.' and '..' is ignored */
            if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
                continue;
            if (stat(direntp->d_name, &info) == -1)
                perror("stat error");
            else
            {
                /* If File is directory, get Inside and search ( Recursive ) */
                if (!Directory_check(&info))
                {
                    strcpy(newpath, path);
                    strcat(newpath, slash);
                    strcat(newpath, direntp->d_name);
                    Ext_find(newpath, "c");
                }
                /* If not directory, checking Extension */
                else
                    Ext_check(direntp->d_name, "c", &info);
            }
        }
        closedir(dir_ptr);
    }
}

void Ext_find(char *dirpath, char *ext)
{
    /* Variable */
    DIR *dir_ptr;
    struct dirent *direntp;
    struct stat info;
    char newpath[256];

    if ((dir_ptr = opendir(dirpath)) == NULL)
        fprintf(stderr, "cannot open current directory\n");
    else
    {
        while ((direntp = readdir(dir_ptr)) != NULL)
        {
            if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
                continue;
            strcpy(newpath, dirpath);
            strcat(newpath, slash);
            strcat(newpath, direntp->d_name);
            if (stat(newpath, &info) == -1)
                perror(dirpath);
            else
            {
                if (!Directory_check(&info))
                    Ext_find(newpath, ext);
                else
                    Ext_check(direntp->d_name, ext, &info);
            }
        }
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
            printf("%s ", extname);
            printf("%ln\n", &info->st_atime);
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