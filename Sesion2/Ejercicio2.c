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
    int i;
    struct stat atributos;
    char tipoArchivo[30];
	DIR *directorio;
	char path[256];
	char persmisos_antiguos[100];
    if(argc!=3)
    {
        printf("\nSintaxis de ejecucion: Ejercicio2 [<path>] [<directorio>]+\n\n");
        exit(-1);
    }
	char *pfinal;
	if(strtol(argv[2],&pfinal,10) > 7777 || strtol(argv[2],&pfinal,10) < 0){
		printf("\nLos permisos no pueden tienen que estar entre 0000 y 7777+\n\n");
        exit(-1);	
	}
	directorio = opendir(argv[1]);
	if( directorio == NULL){
		printf("\nEl directorio no se pudo abrir.+\n\n");
        exit(-1);
	}

	struct dirent *ed;
	while((ed=readdir(directorio))!=NULL){
		sprintf(path,"%s/%s",argv[1],ed->d_name);

		
		if(stat(path,&atributos) < 0) {
			printf("\nError al intentar acceder a los atributos de archivo");
			perror("\nError en stat");
			exit(-1);
		}
		if(S_ISREG(atributos.st_mode)){
			printf("%s: %o ",path,atributos.st_mode);
			chmod(path,strtol(argv[2],&pfinal,10));
			if(chmod(path,strtol(argv[2],&pfinal,10)) < 0) {
				printf("Error: %s\n",strerror(errno));
			}
			else{
				stat(path,&atributos);
				printf("%o \n",atributos.st_mode);
			}
		}

	}
    return 0;
}