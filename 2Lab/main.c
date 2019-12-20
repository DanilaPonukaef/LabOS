#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <string.h>

void strmode(mode_t mode, char* buf){
    const char chars[] = "rwxrwxrwx";
    for(size_t i = 0; i < 9; i++){
        buf[i] = (mode & (1 << (8 - i))) ? chars[i] : '-';
    }
    buf[9] = '\0';
}

char* set_time(struct tm *u)
{
    char s[40];
    char *tmp;
    for (int i = 0; i<40; i++) s[i] = 0;
    u = localtime((const time_t *) u);
    int length = strftime(s, 40, "%d.%m.%Y %H:%M:%S, %A", u);
    tmp = (char*)malloc(sizeof(s));
    strcpy(tmp, s);
    return(tmp);
}

int main() {

    DIR* dir;
    struct dirent* entry;
    struct stat info;
    struct passwd *pwd;
    struct group *grp;
    char*      bufTime;

    dir = opendir("/home/danila/linux/OS/labs/Lab2(MyLS)");
    if(!dir){
        perror("diropen");
        exit(1);
    }

    while((entry = readdir(dir)) != NULL)
    {
        char mode[10];
        stat(entry->d_name, &info);
        pwd = getpwuid(info.st_uid);
        grp = getgrgid(info.st_gid);
        bufTime = set_time((struct tm *) &info.st_ctim);
        strmode(info.st_mode, mode);
        printf("%s %ld %s %s %ld %s %s\n", mode,info.st_nlink, pwd->pw_name, grp->gr_name, info.st_size, bufTime, entry->d_name);
    }
    closedir(dir);

    return 0;
}
