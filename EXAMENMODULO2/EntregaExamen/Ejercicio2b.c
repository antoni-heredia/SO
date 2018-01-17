/*
Ejercicio2.c
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
#include <sys/mman.h>
#include <sys/wait.h>

int analizarDirectorio(char *path_padre,char *path_copia, char * nombrePorgrama);
void copiarFichero(char *origen, char *destino);
int main(int argc, char *argv[])
{
    int i, estado;
    char tipoArchivo[30];
	
    if(argc!=3)
    {
        printf("\nSintaxis de ejecucion: Ejercicio1 [<path>] [<path_destino>]\n\n");
        exit(-1);
    }
    DIR *directorio  =opendir(argv[2]);
    if(directorio == NULL && errno == ENOENT ){
        mkdir(argv[2],0777);
    }
	int cant = analizarDirectorio(argv[1],argv[2], argv[0]);
    //Ponemos en la salida estandar la cantidad de archivos que ha copiado
    write(STDOUT_FILENO,&cant,sizeof(int));
    while (wait(&estado)!=-1);
    return 0;
}

int analizarDirectorio(char *path_padre, char *path_copia, char * nombrePorgrama){
	int cant = 0;
	struct dirent *ed;
	struct stat atributos;
	char path[256];
    char path_fichero_copia[256];

	char persmisos_antiguos[100];
	DIR *directorio = opendir(path_padre);
	if( directorio == NULL){
		perror("\nEl directorio no se pudo abrir.+\n\n");
        exit(-1);
	}
    int fd1[2];
    pipe(fd1);
	while((ed=readdir(directorio))!=NULL){

		sprintf(path,"%s/%s",path_padre,ed->d_name);
		if(stat(path,&atributos) < 0) {
			perror("\nError al intentar acceder a los atributos de archivo");
			perror("\nError en stat");
			exit(-1);
		}
        
		if(S_ISREG(atributos.st_mode)){
			
            cant++;
            
            sprintf(path_fichero_copia,"%s/%s",path_copia,ed->d_name);

            copiarFichero(path,path_fichero_copia);
			
		}else if(S_ISDIR(atributos.st_mode)){
			if( strncmp(ed->d_name, ".", 1) != 0 && strncmp(ed->d_name, "..", 2) != 0){
                __pid_t pid = fork();
                char ejecutable[256];
                //Para saber cual es el nombre del ejecutable
                sprintf(ejecutable,"./%s",nombrePorgrama);
                
                if(pid == 0){
                    close(fd1[0]);
                    dup2(fd1[1],STDOUT_FILENO);
				    execl(ejecutable,nombrePorgrama, path, path_copia,NULL);

                }else if (pid > 0){
                    close(fd1[1]);
                    int val1,bytesLeidos;
                    int estado;
                    if((bytesLeidos = read(fd1[0],&val1, sizeof(int))) < 0){
                        perror("\n No se ha podido leer del cauce\n");
                        exit(-1);
                    }
                    cant+=val1;
                }else{
                    perror("\nFallo al realizar fork\n");
                    exit(-1);
                }
			}
		}
	}
	return cant;
}

void copiarFichero(char *origen, char *destino){
    int	fd1, fd2;
    struct stat sb;

	char	*ptrin, *ptrout;
	
	umask(0);
	fd1 = open(origen, O_RDWR);
    if(fd1<0){
        perror("Error al hacer open\n");
        exit(-1);
    }
    if (fstat (fd1, &sb) == -1) {
        perror("Error al hacer stat\n");
        exit(-1);
    }
	ptrin = (char*) mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd1, 0);

	fd2 = open(destino,O_RDWR|O_CREAT, sb.st_mode);
	if(fd2<0){
        perror("Error al hacer open\n");
        exit(-1);
    }
    ftruncate(fd2, sb.st_size);

    ptrout = (char*) mmap(NULL, sb.st_size, PROT_WRITE, MAP_SHARED, fd2, 0);

    memcpy(ptrout,ptrin,sb.st_size);
    //Liberamos los mapas de memoria
    munmap(ptrout, sb.st_size);
    munmap(ptrin, sb.st_size);

    //Cerramos los descriptores de fichero
    close(fd1);
    close(fd2);
    
}