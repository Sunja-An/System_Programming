#include "move.h"
#include "../Struct/tree.h"

/* Gloabl Variable */
extern Node *Link_Arr[BUFSIZE]; /* Saving Node* variable to link*/
extern int idx;                 /* Link Arr Index */
char slash[2] = "/";

void* Selecting_Filename(void* args)
{
    MultipleArg *multiple_arg = (MultipleArg*)args;
    
    memset(&idx, 0, sizeof(int));
    
    /* Variable */
    DIR *dir_ptr;
    struct stat info;
    struct dirent *direntp;
    char *filename;
    char *name;
    char path[256];
    char newpath[256];

    /* Variable Setting */
    strcpy(filename, multiple_arg->filepath);
    strcpy(name, multiple_arg->option);

    /* Change the directory */
    if (chdir(filename) != 0)
    {
        perror(filename);
        exit(1);
    }

    /* Get the Target Path  */
    getcwd(path, sizeof(path));

    /* Open directory and Finding process */
    if ((dir_ptr = opendir(path)) == NULL){
        if(strstr(path, "CACHE") || strstr(path,"cache"))
            CACHE_FILE = ON;
        if(strstr(path, "CONFIG") || strstr(path,"config") || strstr(path,"conf"))
            CONFIG_FILE = ON;
    }
    //fprintf(stderr, "Selecting_Filename() : cannot open %s\n", path);
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
    return NULL;
}

// File find. Not directory
void Name_find(char *dirpath, char *name)
{
    /* Variable */
    DIR *dir_ptr;
    struct dirent *direntp;
    struct stat info;
    char newpath[256];

    // printf("Error path: %s\n", dirpath);
    // fprintf(stderr, "Extension find: cannot open current directory\n");

    if ((dir_ptr = opendir(dirpath)) == NULL)
    {
        if ((strstr(dirpath, "config") != NULL) || (strstr(dirpath, "conf") != NULL) || (strstr(dirpath, "CONFIG") != NULL) || (strstr(dirpath, "cf") != NULL))
            CONFIG_FILE = ON;
        if ((strstr(dirpath, "cache") != NULL) || (strstr(dirpath, "CACHE") != NULL))
            CACHE_FILE = ON;
    }
    else
    {
        while ((direntp = readdir(dir_ptr)) != NULL)
        {
            if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
                continue;
            /* Stat by file to guess the Directory and check extension */
            if ((strstr(direntp->d_name, "config") != NULL) || (strstr(direntp->d_name, "conf") != NULL) || (strstr(dirpath, "CONFIG") != NULL) || (strstr(dirpath, "cf") != NULL))
                continue;
            if ((strstr(direntp->d_name, "cache") != NULL) || (strstr(direntp->d_name, "CACHE") != NULL))
                continue;
            if ((strstr(direntp->d_name, "package") != NULL))
                continue;
            if ((strstr(direntp->d_name, "data") != NULL) || (strstr(direntp->d_name, "User") != NULL))
                continue;
            if ((strstr(direntp->d_name, "extensions") != NULL))
                continue;
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
            fflush(stdout);
            /* Put in list */
            Link_Arr[idx++] = newnode;
        }
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

void RemoveFirst(char *buf)
{
    int i;
    for (i = 1; buf[i]; i++)
        buf[i - 1] = buf[i];
    buf[i - 1] = '\0';
}
