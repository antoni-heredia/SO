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
    if(argc!=2)
    {
        printf("\nSintaxis de ejecucion: Ejercicio2 [<entero>]\n\n");
        exit(-1);
    }
    __pid_t pid = fork();
    int numero = atoi(argv[1]);
    if(pid == 0){
        if(numero % 2 == 0)
            printf("\nEl numero es par\n");
        else
            printf("\nEl numero es impar\n");

    }else{
        if(numero % 4 == 0)
            printf("\nEl numero es divisible por 4\n");
        else
            printf("\nEl numero no es divisible por 4\n");
    }
    return 0;
}