#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    pid_t  child;
    int rv;

    switch (child = fork()){
        case -1:
            printf("Неудалось создать процесс\n");

        case 0:
            printf("CHILD: Это процесс потомок\n");
            printf("CHILD: Мой PID %d\n", getpid());
            printf("CHILD: PID моего родителя %d\n", getppid());

            exit(0);

        default:
            printf("PARENT: Это процесс продитель\n");
            printf("PARENT: Мой PID %d\n", getpid());
            printf("PARENT: PID моего протомка %d\n", child);
            printf("PARENT: Жду пока дочерний процесс не вызовет exit()...\n");

    }










    return 0;
}