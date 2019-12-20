#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>



char* set_time(struct tm *u)
{
    char s[40];
    char *tmp;
    for (int i = 0; i<40; i++) s[i] = 0;
    int length = strftime(s, 40, "%d.%m.%Y %H:%M:%S, %A", u);
    tmp = (char*)malloc(sizeof(s));
    strcpy(tmp, s);
    return(tmp);
}

int main() {
    int file_descriptor_fifo;
    char *f;
    pid_t fork_result;
    char bufferIn[100];
    char bufferOut[100];

    unlink("/tmp/fifo0001.1");

    if ((mknod("/tmp/fifo0001", S_IFIFO | S_IRUSR | S_IWUSR, NULL) == -1)){
        printf("Невозможно создать FIFO\n");
        exit(0);
    }
    if ((file_descriptor_fifo = open("/tmp/fifo0001", O_RDWR)) == -1 ) {
        printf("Невозможно открыть FIFO\n");
        exit(0);
    } else{
        switch (fork_result = fork()){
            case -1: {
                printf("Невозможно создать дочерний процесс\n");
                exit(0);
            }
            case 0: {
                printf("CHILD: Я дочерний процесс\n");
                read(file_descriptor_fifo, bufferIn, sizeof(bufferIn));
                printf("CHILD: Я считал из FIFO : %s\n", bufferIn);
                printf("CHILD: Пока пока я завершаюсь\n");

                exit(0);
            }
            default: {
                printf("PARENT: Я родитель\n");
                const time_t  timer = time(NULL);
                f = set_time(localtime(&timer));
                printf("PARENT: Мой PID %d и текущее время %s : \n", getpid(), f);
                sprintf(bufferOut, "%d, %s",  getpid(), f);
                write(file_descriptor_fifo, bufferOut, sizeof(bufferOut));
                printf("PARENT: Жду пока дочерний процесс не вызовет exit()...\n");wait(0);
                printf("PARENT: Выход!\n");

                exit(0);
            }
        }
    }















}
