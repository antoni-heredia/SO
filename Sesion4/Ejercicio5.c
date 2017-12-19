
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[])
{   
    if(argc != 3){
        perror("\nNumero de parametros incorrecto\n");
        exit(-1);
    }

    int limite_inf = atoi(argv[1]);
    int limite_sup = atoi(argv[2]);
    int medio = (limite_sup-limite_inf)/2;
    int bytesLeidos1, val1,bytesLeidos2, val2;
    const int NUM_PIPE = 2;
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    pid_t PID1;
    pid_t PID2;
    if ( (PID1= fork())<0) {
        perror("\nError en fork");
        exit(-1);
    }
    

    char inf[100],sup[100];
    if (PID1 == 0) { // ls
        //Cerrar el descriptor de lectura de cauce en el proceso hijo
        close(fd1[0]);
        //Duplicar el descriptor de escritura en cauce en el descriptor
        //correspondiente a la salida estda r (stdout), cerrado previamente en
        //la misma operación
        dup2(fd1[1],STDOUT_FILENO);
        sprintf(inf,"%d",limite_inf);
        sprintf(sup,"%d",medio);

        if(execlp("./Ejercicio5Esclavo","Ejercicio5Esclavo",inf, sup, NULL) < 0) {
            perror("\nError en el execl");
            exit(-1);
        }
        
    }else{
        close(fd1[1]);
        //Duplicar el descriptor de lectura de cauce en el descriptor
        //correspondiente a la entrada estándar (stdin), cerrado previamente en
        //la misma operación
        //bucle lectura 
        while((bytesLeidos1 = read(fd1[0],&val1, sizeof(int))) > 0){
            printf("%d\n ", val1);
        }
    }
    
    if ( (PID2= fork())<0) {
        perror("\nError en fork");
        exit(-1);
    }
    char inf2[100],sup2[100];

    if(PID2 == 0){
        //Cerrar el descriptor de lectura de cauce en el proceso hijo
        close(fd2[0]);
        
        dup2(fd2[1],STDOUT_FILENO);

        sprintf(inf2,"%d",medio);
        sprintf(sup2,"%d",limite_sup);
        if(execlp("./Ejercicio5Esclavo","Ejercicio5Esclavo",inf2, sup2, NULL) < 0) {
            perror("\nError en el execl");
            exit(-1);
        }
    }else { // sort. Proceso padre porque PID != 0.
        //Cerrar el descriptor de escritura en cauce situado en el proceso padre
        close(fd2[1]);

        while((bytesLeidos2 = read(fd2[0],&val2, sizeof(int))) > 0){
            printf("%d\n ", val2);
        }
    }
    
    return(0);
}