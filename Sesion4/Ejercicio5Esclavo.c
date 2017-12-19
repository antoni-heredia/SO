
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>

int main(int argc, char *argv[])
{   
    if(argc != 3){
        perror("\nNumero de parametros incorrecto\n");
        exit(-1);
    }
    int limite_inf = atoi(argv[1]);
    int limite_sup = atoi(argv[2]);
    char buf[80];
    for(double i = limite_inf; i <= limite_sup;i++){
        int tiene = 0;
        for(double x = 2; x <= sqrt(i);x++){
            if((int)i%(int)x==0){
                tiene = 1;
                break;
            }
        }
        if(tiene == 0){
            sprintf(buf,"%d\n",(int)i);
            write(STDOUT_FILENO,&buf,sizeof(int));
        }
    }
    return(0);
}