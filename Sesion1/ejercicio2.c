/*
stat()  and  fstatat()  retrieve  information  about  the  file pointed to by pathname; the differences for
fstatat() are described below.

lstat() is identical to stat(), except that if pathname is a symbolic link,  then  it  returns  information
about the link itself, not the file that it refers to.
*/
/*
Ejercicio 4 de la sesion 2 de SO
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#define S_ISREG2(mode) (mode & S_IFMT == S_IFREG)
int main(int argc, char *argv[])
{

	
}