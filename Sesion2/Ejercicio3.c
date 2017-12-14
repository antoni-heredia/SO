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

int analizarDirectorio(char *path_padre, int *tamanio);

int main(int argc, char *argv[])
{
    int i;
    char tipoArchivo[30];
	DIR *directorio;
	
    if(argc!=2)
    {
        printf("\nSintaxis de ejecucion: Ejercicio2 [<path>]\n\n");
        exit(-1);
    }	
	int tamanio = 0;
	int cant = analizarDirectorio(argv[1], &tamanio);
	printf("\nLa cantidad de archivos encontrados es: %d.+\n\n", cant);
	printf("\nEl tamaño total de todos los ficheros encontrados es: %d.+\n\n", tamanio);
    return 0;
}

int analizarDirectorio(char *path_padre, int *tamanio){
	int cant = 0;
	struct dirent *ed;
	struct stat atributos;
	char path[256];
	char persmisos_antiguos[100];
	DIR *directorio = opendir(path_padre);
	if( directorio == NULL){
		printf("\nEl directorio no se pudo abrir.+\n\n");
        exit(-1);
	}

	while((ed=readdir(directorio))!=NULL){

		sprintf(path,"%s/%s",path_padre,ed->d_name);
		if(stat(path,&atributos) < 0) {
			printf("\nError al intentar acceder a los atributos de archivo");
			perror("\nError en stat");
			exit(-1);
		}

		if(S_ISREG(atributos.st_mode)){
			/*
				Primero le quitamos los bits no POXIS, luego hacemos el and para quedarnos solo con el bit que nos interesa
				y por ultimo compramos si es igual al FLAG que queremos
			*/
			if( (((atributos.st_mode & ~S_IFMT) & 0001)  == S_IXOTH) && (((atributos.st_mode & ~S_IFMT) & 0010)  == S_IXGRP) ){
				cant++;
				/*
					%lu es para el numero de inodo que es unsigned long
				*/
				printf("%s  %lu \n",path,atributos.st_ino);
				(*tamanio)=(*tamanio)+(int)atributos.st_size;
			}
		}else if(S_ISDIR(atributos.st_mode)){
			if( strncmp(ed->d_name, ".", 1) != 0 && strncmp(ed->d_name, "..", 2) != 0){
				cant += analizarDirectorio(path, tamanio);
			}
		}

	}
	return cant;
}