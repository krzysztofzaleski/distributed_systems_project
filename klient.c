#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/errno.h>
#include "gniazdo.h"

void err_sys(const char *);

int main (int argc, char*argv[]) {
    int dg; //deskryptor
    Internet_Adres sadres;
    char buf[101],*host;

    // pobiera adres serwera
    if (argc<2) err_sys("brak nazwy serwera");
    host = argv[1];  //nazwa stacji
    if (host==NULL) err_sys("adres:");

    // tworzy gniazdo
    if ((dg=socket (PF_INET,SOCK_STREAM,0)) < 0)
        err_sys("nie moge utworzyc gniazda");

    sadres.konfiguracja(TSPORT,host);

    // tworzy polaczenie
    if (connect (dg, sadres, sadres.rozmiar()) < 0)
        err_sys("nie moge poloczyc sie z serverem");


    odbiera(dg,buf,100);
    puts(buf);
    fflush(stdout);

    int i=0;
    while (fgets(buf,100,stdin) != NULL && strcmp(buf,".\n") && i < 3) {
        wysyla(dg,buf,100);
        odbiera(dg,buf,100);
        puts(buf);
        i++;
    }

    close (dg);
    return 0;
}


void err_sys(const char *b) {
     perror(b);
     exit(1);
}
