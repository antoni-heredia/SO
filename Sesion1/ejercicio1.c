/*
Ejercicio 1 de la sesion 2 de SO
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
int main(int argc, char *argv[])
{

	const int TAM = 80;
	int fdi, fdo;
	char buf1[80];

	if(argc > 2){
		perror("\nNumero de argumentos incorrectos");
		exit(-1);
	}else if(argc == 2){
		if( (fdi=open(argv[1],O_RDONLY))<0) {
			printf("\nError %d en open",errno);
			perror("\nError en open");
			exit(-1);
		}
	}else{
		fdi = STDIN_FILENO;
	}

	

	if( (fdo=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
		printf("\nError %d en open",errno);
		perror("\nError en open");
		exit(-1);
	}

	int cantidad  = read(fdi,buf1,TAM);
	int num_bloques = 0;
	char s[40]; 
	write(fdo,"                              ",30);

	while(cantidad == TAM){
		num_bloques++;
		
 		sprintf(s, "\nBloque %d\n",num_bloques);		
		write(fdo,s,strlen(s));

		write(fdo,buf1,cantidad);
		cantidad  = read(fdi,buf1,TAM);	
		
	}
	write(fdo,buf1,cantidad);

	lseek(fdo,0, SEEK_SET);
	sprintf(s, "El numero de bloques es: %d",num_bloques);		
	write(fdo,s,strlen(s));

	close(fdo);
	close(fdi);
}