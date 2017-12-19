#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        perror("\nNumero de parametros incorrecto\n");
        perror("\n./Ejercicio6 nombre_programa [argumentos] [\"bg\"]\n");
        exit(-1);
    }
    pid_t pid;
    int estado;

    if(!strcmp(argv[argc-1],"bg")){
        
        printf("Ejecutando en segundo plano\n");
        if( (pid=fork())<0) {
            perror("\nError en el fork");
            exit(-1);
        }		
        else if(pid==0) { //proceso hijo ejecutando el programa
            if( (execlp(argv[1],argv[1],argv[2],NULL)<0)) {
                    perror("\nError en el execl");
                    exit(-1);
            }            
        }
        wait(&estado);
        printf("\nMi hijo %d ha finalizado con el estado %d\n",pid,estado);
    }else
        if( (execlp(argv[1],argv[1],argv[2],NULL)<0)) {
            perror("\nError en el execl");
            exit(-1);
        }

    
    exit(0);
}