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
    int dg;																				 //deskryptor
    Internet_Adres sadres;																//adres serwera
    char buf[101],*host,*prog;															//buf-tablica przesy³ana klinet ->serwer 

																						// pobiera adres serwera
    if (argc<2) err_sys("brak nazwy serwera");
    host = argv[1];																		//nazwa stacji
    if (host==NULL) err_sys("adres:");
	prog = argv[2];																		//nazwa programu
																						// tworzy gniazdo
    if ((dg=socket (PF_INET,SOCK_STREAM,0)) < 0)
        err_sys("nie moge utworzyc gniazda");

    sadres.konfiguracja(TSPORT,host);

																						// tworzy polaczenie
    if (connect (dg, sadres, sadres.rozmiar()) < 0)
        err_sys("nie moge poloczyc sie z serverem");

	strcpy(buf, prog);
    wysyla(dg,buf,100);
    fflush(stdout);
	odbiera(dg,buf,100);
    puts(buf);


    close (dg);
    return 0;
}

void err_sys(const char *b) {
     perror(b);
     exit(1);
}
