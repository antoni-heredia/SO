/*
ejercicio2.c
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>
int main(int argc, char *argv[])
{
    __pid_t childpid;
    printf("\nEl pid del proceso es:%d\n",getpid());
    printf("\nEl pid del proceso padre es:%d\n",getppid());
    for(int i = 0; i < 5; i++){
        if((childpid = fork()) < 0){
            printf("\nError al crear el hijo\n");
            exit(-1);
        }

        if(childpid){
            printf("\nEl pid del proceso es:%d\n",getpid());
            printf("\nEl pid del proceso padre es:%d\n",getppid());
            break;
        }
           
       
        
    }
    
    return 0;
}