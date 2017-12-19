#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/wait.h>
#include <sys/types.h>

 
int main(int argc, char *argv[])
{
    const int NUM_HIJOS = 5;
    __pid_t childpid[NUM_HIJOS];

    setvbuf(stdout,NULL,_IONBF,0); //vaciar los buffers para que los mensajes salgan como debe
    for(int i = 0; i < NUM_HIJOS; i++){
        if((childpid[i] = fork()) < 0){
            printf("\nError al crear el hijo\n");
            exit(-1);
        }

        if(childpid[i] == 0){
            printf("\nSoy el hijo PID:%d\n",getpid());
            exit(0);
        }
    }
    int quedan = NUM_HIJOS;
    int estado;
    for(int i = 0; i < NUM_HIJOS; i+=2){
            waitpid(childpid[i],&estado,0);
            quedan--;
            printf("\nAcaba de finalizar hijo PID:%d\n",childpid[i]);
            printf("\nSolo me quedan:%d\n",quedan);
    }

    for(int i = 1; i < NUM_HIJOS; i+=2){
            waitpid(childpid[i],&estado,0);
            quedan--;
            printf("\nAcaba de finalizar hijo PID:%d\n",childpid[i]);
            printf("\nSolo me quedan:%d\n",quedan);
    }
    
    return 0;
}