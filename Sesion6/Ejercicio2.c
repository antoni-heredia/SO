#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc != 4){
        perror("\nEl numero de parametros es incorrecto\n");
        exit(-1);
    }


    if(strcmp(argv[2],"|") == 0){
        int fd[2];
        pipe(fd);
        __pid_t PID;
        if((PID = fork()) < 0){
            perror("\nError al realizar el fork\n");
            exit(-1);
        }

        if(PID != 0){
            close(STDOUT_FILENO);
            close(fd[0]);
            if(fcntl(fd[1],F_DUPFD,STDOUT_FILENO) == -1){
                perror("Fallo en  fcntl");
            }
            execlp(argv[1],argv[1], NULL);
            close(fd[1]);

        }else{
            close(STDIN_FILENO);
            close(fd[1]);

            if(fcntl(fd[0],F_DUPFD,STDIN_FILENO) == -1){
                perror("Fallo en  fcntl");
            }
            execlp(argv[3],argv[1], NULL);
            close(fd[0]);

        }
        

    }else{
        perror("\nSe debe introducir < o >\n");
        exit(-1);
    }
    return(0);
}