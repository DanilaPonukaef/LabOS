#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void doSumpfing();

int main() {

    pid_t  child;
    int hook;

    switch (child = fork()){
        case -1:
            printf("Неудалось создать процесс\n");
            break;

        case 0:
            hook = atexit(doSumpfing);
            if(hook == 0)
                printf("CHILD: atexit зарегистрирован\n");
            else
                printf("CHILD: atexit не зарегестрирован\n");

            printf("CHILD: Это процесс потомок\n");
            printf("CHILD: Мой PID %d\n", getpid());
            printf("CHILD: PID моего родителя %d\n", getppid());
            printf("CHILD: Выход!\n");

            exit(0);
            break;

        default:
            atexit(doSumpfing);
            printf("PARENT: Это процесс продитель\n");
            printf("PARENT: Мой PID %d\n", getpid());
            printf("PARENT: PID моего протомка %d\n", child);
            printf("PARENT: Жду пока дочерний процесс не вызовет exit()...\n");wait(0);
            printf("PARENT: Мой потомок завершиляс со значением %d\n");
            printf("PARENT: Выход!\n");

            exit(0);
    }


    return 0;
}

void doSumpfing()
{
    printf("Сработала зарегистрированная функция atexit()\n");
}











