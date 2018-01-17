#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char *argv[])
{

    if(argc != 3){
        perror("\nNumero de parametros incorrecto\n");
        exit(-1);
    }
    int	fd1, fd2;
    struct stat sb;

	char	*ptrin, *ptrout;
	
	umask(0);
	fd1 = open(argv[1], O_RDONLY);
    if(fd1<0){
        printf("Error al hacer open\n");
        exit(-1);
    }
    if (fstat (fd1, &sb) == -1) {
        printf("Error al hacer stat\n");
        return EXIT_FAILURE;
    }
	ptrin = (char*) mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd1, 0);

	fd2 = open(argv[2],O_RDWR|O_CREAT, S_IRWXU);
	if(fd2<0){
        printf("Error al hacer open\n");
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
	exit(EXIT_SUCCESS);
}