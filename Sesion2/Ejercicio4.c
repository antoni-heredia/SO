/*
ejercicio2.c
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
int tamanio = 0;
int cant = 0;
int analizarDirectorio(char *path,const struct stat* stat, int flags, struct FTW* ftw){
	struct dirent *ed;
	struct stat atributos;


	if(S_ISREG(stat->st_mode)){
		/*
			Primero le quitamos los bits no POXIS, luego hacemos el and para quedarnos solo con el bit que nos interesa
			y por ultimo compramos si es igual al FLAG que queremos
		*/
		if( (((stat->st_mode & ~S_IFMT) & 0001)  == S_IXOTH) && (((stat->st_mode & ~S_IFMT) & 0010)  == S_IXGRP) ){
			cant += 1;
			/*
				%lu es para el numero de inodo que es unsigned long
			*/
			printf("%s  %lu \n",path,stat->st_ino);
			tamanio+=(int)stat->st_size;
		}
	}
	return 0;
}

int main(int argc, char *argv[]){
	
    if(argc!=2)
    {
        printf("\nSintaxis de ejecucion: Ejercicio2 [<path>]\n\n");
        exit(-1);
    }	
	
	nftw(argv[1],analizarDirectorio,10,0 );
	printf("\nLa cantidad de archivos encontrados es: %d.+\n\n", cant);
	printf("\nEl tamaño total de todos los ficheros encontrados es: %d.+\n\n", tamanio);
    return 0;
}

