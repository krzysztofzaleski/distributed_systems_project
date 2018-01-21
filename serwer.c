#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include "gniazdo.h"
#define max 50

void err_sys(const char*);


int main(int argc, char*argv[]) {
	int dg, ddg;																		//deskryptor
	int dls, dlc, dl;
	char buf[101], host[128], prog[128];
	int ch;
	float arg1, arg2;
	char nazwa_programu[10];
	char execStr1[20];
	char execStr2[20];
	char prog_nr;

	Internet_Adres sadres, cadres;

																						// tworzy gniazdo
	if ((dg = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("nie moge utworzyc gniazda");

	sadres.konfiguracja(TSPORT, 0);

	if (bind(dg, sadres, sadres.rozmiar()) < 0)
		err_sys("nie moge zwiazac adresu lokalnego");

	listen(dg, 5);

	while (1) {
		printf("Czekam na polaczenie...\t?\n");
		ddg = accept(dg, cadres, &cadres.rozmiar());
		printf("Polaczenie nawiazane!\tok\n");

		int fd[2];
		pipe(fd);

		// PROCES POTOMNY
		if (fork() == 0) {

			fflush(stdout);
			odbiera(ddg, buf, 100);														//pobranie od uzytk. ktory program
			
			sprintf(execStr1, "%s", buf);												//parsuje do stringa bo execlp nie czyta inaczej
			

			close(fd[0]);
			dup2(fd[1], 1);

			execlp(execStr1, NULL);														//uruchamia program

			printf("Koniec procesu potomnego\n");
			close(ddg);
			exit(0);
		}

		else {																		  // proces macierzysty
			close(fd[1]);
			int s;
			wait(&s);																  // czeka na zakonczenie procesu potomnego
																					  // sprawdza status zakonczenia potomka
			if (s == 0) printf("Koniec procesu potomnego, sukces!\n");
			else printf("Blad procesu potomnego! Numer bledu: %d\n", s);

			char wynik[100];
			bzero(wynik, 100);
			read(fd[0], wynik, 100);
			printf("Proces macierzysty: %s", wynik);
			wysyla(ddg, wynik, 100);
		}
	}
	return 0;
}

void err_sys(const char *b) {
	char buf[100];
	fprintf(stderr, "%s\n", b);
	perror(buf);
	exit(1);
}
