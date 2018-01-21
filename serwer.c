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

int checker(char input[], char check[]) {
	int i, result = 1;
	for (i = 0; input[i] != '\0' || check[i] != '\0'; i++) {
		if (input[i] != check[i]) {
			result = 0;
			break;
		}
	}
	return result;
}


int main(int argc, char*argv[]) {
	int dg, ddg; //deskryptor
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
			//pobranie od uzytk. ktory program
			//wysyla(ddg, "Nazwa programu", 100);
			odbiera(ddg, buf, 100);
			puts(buf);
			int i = 1;
			
			prog_nr = atoi(buf);
			wysyla(ddg, "", 100);
				
				
					//wysyla(ddg, "Podaj 2 liczbe\t", 100);
					//arg1 = atof(buf);
				
				
					//arg2 = atof(buf);
				
			};

			sprintf(execStr1, "%f", arg1);
			sprintf(execStr2, "%f", arg2);

			close(fd[0]);
			dup2(fd[1], 1);


			//if (prog_nr == 1) {
				//                printf("proces potomny wykonuje program <ILORAZ>:\n");
				execlp("./prog_nr", execStr1, execStr2, NULL);
			//}
			//else if (prog_nr == 2) {
				//                printf("proces potomny wykonuje program <ILOCZYN>:\n");
			//	execlp("./iloczyn", execStr1, execStr2, NULL);
			//}
			//else if (prog_nr == 3) {
				//                printf("proces potomny wykonuje program <SUMA>:\n");
			//	execlp("./suma", execStr1, execStr2, NULL);
			//}
			//else if (prog_nr == 4) {
				//                printf("proces potomny wykonuje program <ROZNICA>:\n");
			//	execlp("./roznica", execStr1, execStr2, NULL);
		//	}
			//else {
			//	wysyla(ddg, "Podales zle argumenty! Konczymy wspolprace...", 100);
			//}

			printf("Koniec procesu potomnego\n");
			close(ddg);
			exit(0);
		}

		else {     // proces macierzysty
			close(fd[1]);
			int s;
			wait(&s); // czeka na zakonczenie procesu potomnego
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
