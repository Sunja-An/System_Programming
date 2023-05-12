#include "move.h"
#include "../Struct/tree.h"

/* Gloabl Variable */
extern Node *Link_Arr[BUFSIZE]; /* Saving Node* variable to link*/
extern int idx;             /* Link Arr Index */
char slash[2] = "/";

// Selecting_Name 이랑 엮어서 추출해내면 될듯
void Selecting_Extension(char filename[], char *ext)
{
    memset(&idx, 0, sizeof(int));
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
            /* directory name '.' and '..' is ignored */
            if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
                continue;
            if (stat(direntp->d_name, &info) == -1)
                perror("stat error");
            else
            {
                strcpy(newpath, path);
                strcat(newpath, slash);
                strcat(newpath, direntp->d_name);

                /* If File is directory, get Inside and search ( Recursive ) */
                if (!Directory_check(&info))
                    Ext_find(newpath, ext);
                /* If not directory, checking Extension */
                else
                    Ext_check(newpath, direntp->d_name, ext, &info);
            }
        }
        closedir(dir_ptr);
    }
}

void Selecting_Filename(char filename[], char *name)
{
    memset(&idx, 0, sizeof(int));
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
            /* directory name '.' and '..' is ignored */
            if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
                continue;
            if (stat(direntp->d_name, &info) == -1)
                perror("stat error");
            else
            {
                strcpy(newpath, path);
                strcat(newpath, slash);
                strcat(newpath, direntp->d_name);

                /* If File is directory, get Inside and search ( Recursive ) */
                if (!Directory_check(&info))
                    Name_find(newpath, name);
                /* If not directory, checking Extension */
                else
                    Name_check(newpath, direntp->d_name, name, &info);
            }
        }
        closedir(dir_ptr);
    }
}

/* Selecting File or Directory [Recursive] */
void Selecting_time_distance(char filename[], int st, int ed)
{
    memset(&idx, 0, sizeof(int));
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
            /* directory name '.' and '..' is ignored */
            if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
                continue;
            if (stat(direntp->d_name, &info) == -1)
                perror("stat error");
            else
            {
                strcpy(newpath, path);
                strcat(newpath, slash);
                strcat(newpath, direntp->d_name);
                printf("%s\n",direntp->d_name);
                /* If File is directory, get Inside and search ( Recursive ) */
                if (!Directory_check(&info))
                    Atime_find(newpath, st, ed);
                /* If not directory, checking Extension */
                else
                    Atime_check(newpath, st, ed, &info);
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
    {
        printf("Error path: %s\n", dirpath);
        fprintf(stderr, "Extension find: cannot open current directory\n");
    }
    else
    {
        while ((direntp = readdir(dir_ptr)) != NULL)
        {
            if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
                continue;

            /* Stat by file to guess the Directory and check extension */
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
                    Ext_check(newpath, direntp->d_name, ext, &info);
            }
        }
        closedir(dir_ptr);
    }
}

void Ext_check(char filepath[], char *extname, char *ext, struct stat *info)
{
    char ptr[BUFSIZE];
    char newfilepath[256];
    strcpy(ptr, extname);
    char *comp = strpbrk(ptr, ".");
    if (comp != NULL)
    {
        RemoveFirst(comp);
        if (strcmp(comp, ext) == 0)
        {
            Node *newnode = (Node *)malloc(sizeof(Node));

            /* File Path Take */
            strcpy(newfilepath, filepath);

            /* Put in data to use list */
            strcpy(newnode->filepath, newfilepath);
            newnode->atime = info->st_atime;

            printf("%s\n",comp);
            printf("filepath : %s\n", newnode->filepath);
            fflush(stdout);

            /* Put in list */
            Link_Arr[idx++] = newnode;
        }
    }
}

// File find. Not directory
void Name_find(char *dirpath, char *name)
{
    /* Variable */
    DIR *dir_ptr;
    struct dirent *direntp;
    struct stat info;
    char newpath[256];

    if ((dir_ptr = opendir(dirpath)) == NULL)
    {
        printf("Error path: %s\n", dirpath);
        fprintf(stderr, "Extension find: cannot open current directory\n");
    }
    else
    {
        while ((direntp = readdir(dir_ptr)) != NULL)
        {
            if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
                continue;

            /* Stat by file to guess the Directory and check extension */
            strcpy(newpath, dirpath);
            strcat(newpath, slash);
            strcat(newpath, direntp->d_name);

            if (stat(newpath, &info) == -1)
                perror(dirpath);
            else
            {
                // Directory?
                if (!Directory_check(&info))
                    Name_find(newpath, name);
                else
                    Name_check(newpath, direntp->d_name, name, &info);
            }
        }
        closedir(dir_ptr);
    }
}

void Name_check(char *filepath, char *filename, char *name, struct stat *info)
{
    char newfilepath[256];
    if (name != NULL)
    {
        if (strstr(filename, name) != NULL)
        {
            Node *newnode = (Node *)malloc(sizeof(Node));

            /* File Path Take */
            strcpy(newfilepath, filepath);

            /* Put in data to use list */
            strcpy(newnode->filepath, newfilepath);
            newnode->atime = info->st_atime;

            printf("filepath : %s\n", newnode->filepath);
            fflush(stdout);
            /* Put in list */
            Link_Arr[idx++] = newnode;
        }
    }
}

void Atime_find(char *dirpath, int st, int ed)
{
    /* Variable */
    DIR *dir_ptr;
    struct dirent *direntp;
    struct stat info;
    char newpath[256];

    if ((dir_ptr = opendir(dirpath)) == NULL)
    {
        printf("Error path: %s\n", dirpath);
        fprintf(stderr, "Extension find: cannot open current directory\n");
    }
    else
    {
        while ((direntp = readdir(dir_ptr)) != NULL)
        {
            if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
                continue;

            /* Stat by file to guess the Directory and check extension */
            strcpy(newpath, dirpath);
            strcat(newpath, slash);
            strcat(newpath, direntp->d_name);

            if (stat(newpath, &info) == -1)
                perror(dirpath);
            else
            {
                // Directory?
                if (!Directory_check(&info))
                    Atime_find(newpath, st, ed);
                else
                    Atime_check(newpath, st, ed, &info);
            }
        }
        closedir(dir_ptr);
    }
}

void Atime_check(char *filepath, int st, int ed, struct stat *info)
{
    char ptr[BUFSIZE];
    char newfilepath[256];
    if (st <= info->st_atime && ed >= info->st_atime)
    {
        Node *newnode = (Node *)malloc(sizeof(Node));

        /* File Path Take */
        strcpy(newfilepath, filepath);

        /* Put in data to use list */
        strcpy(newnode->filepath, newfilepath);
        newnode->atime = info->st_atime;

        printf("filepath : %s\n", newnode->filepath);
        fflush(stdout);
        /* Put in list */
        Link_Arr[idx++] = newnode;
    }
}

int Directory_check(struct stat *info_p)
{
    if (S_ISDIR(info_p->st_mode))
        return 0;
    else
        return -1;
}

time_t MakeLocalTime_t(int YY, int MM, int DD)
{
    struct tm st_tm;

    st_tm.tm_year = YY - 1900;
    st_tm.tm_mon = MM - 1;
    st_tm.tm_mday = DD;
    st_tm.tm_hour = 0; // default value
    st_tm.tm_min = 0;  // default value
    st_tm.tm_sec = 0;  // default value

    return mktime(&st_tm);
}

/*
void Extract_Name(char* filepath){
    char *prev;
    char *ptr = strtok(filepath, "/");
    
    while(ptr!=NULL){
        prev = ptr;
        ptr=strtok(NULL,"/");
    }

    return prev;
}

void Extract_Extension(char* filepath){
    char *prev;
    char *ptr = strtok(filepath, ".");
    
    while(ptr!=NULL){
        prev = ptr;
        ptr = strtok(NULL,".");
    }

    return prev;
}
*/

void RemoveFirst(char *buf)
{
    int i;
    for (i = 1; buf[i]; i++)
        buf[i - 1] = buf[i];
    buf[i - 1] = '\0';
}
