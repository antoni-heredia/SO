#include <stdio.h>
#include <signal.h>
static int j;
static int contadores[31];

int main()
{
    sigset_t new_mask;
    /* inicializar la nueva mascara de señales */
    sigemptyset(&new_mask);
    sigfillset(&new_mask);
    sigdelset(&new_mask , SIGUSR1);
    
    printf("El proceso se va a bloquear hasta que se reciba SIGUSR1\n");
    /*esperar a cualquier señal excepto SIGUSR1 */
    sigsuspend(&new_mask);
    printf("El proceso se ha desbloqueado.\n");
}