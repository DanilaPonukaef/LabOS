#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/wait.h>
//В [1] писать из [0] читать

char* set_time(struct tm *u)
{
    char s[40];
    char *tmp;
    memset( s, 0, 40 );
    int length = strftime(s, 40, "%d.%m.%Y %H:%M:%S, %A", u);
    tmp = (char*)malloc(sizeof(s));
    strcpy(tmp, s);
    return(tmp);
}

int main() {
    int file_descriptor[2];
    char *f;
    pid_t fork_result;
    char bufferIn[100];
    char bufferOut[100];
    if (pipe(file_descriptor) == 0) {
        switch (fork_result = fork()){
            case -1:
                printf("Неудалось создать процесс\n");

            case 0:
                read(file_descriptor[0], bufferIn, sizeof(bufferIn));
                printf("CHILD: Я считал это сообщение из pipe %s\n", bufferIn);
                printf("CHILD: Выход!\n");

                exit(0);

            default:
                printf("PARENT: Это процесс продитель\n");
                const time_t  timer = time(NULL);
                f = set_time(localtime(&timer));
                printf("PARENT: Я передаю свой PID %d и время %s\n ", getpid(), f);
                sprintf(bufferOut, "%d, %s",  getpid(), f);
                write(file_descriptor[1], bufferOut, sizeof(bufferOut));
                printf("PARENT: Жду пока дочерний процесс не вызовет exit()...\n");
                wait(0);
                printf("PARENT: Выход!\n");

                exit(0);
        }
    }

    return 0;
}
