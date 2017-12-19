#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/wait.h>
#include <sys/types.h>

 
int main(int argc, char *argv[])
{
    __pid_t childpid;
    const int NUM_HIJOS = 5;
    setvbuf(stdout,NULL,_IONBF,0); //vaciar los buffers para que los mensajes salgan como debe
    for(int i = 0; i < NUM_HIJOS; i++){
        if((childpid = fork()) < 0){
            printf("\nError al crear el hijo\n");
            exit(-1);
        }

        if(childpid == 0){
            printf("\nSoy el hijo PID:%d\n",getpid());
            exit(0);
        }
    }
    int quedan = NUM_HIJOS;
    int estado;
    for(int i = 0; i < NUM_HIJOS; i++){
            __pid_t pid = wait(&estado);
            quedan--;
            printf("\nAcaba de finalizar hijo PID:%d\n",pid);
            printf("\nSolo me quedan:%d\n",quedan);
    }
    
    
    return 0;
}