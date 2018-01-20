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



int main (int argc, char*argv[]) {
    int dg,ddg; //deskryptor
    int dls,dlc,dl;
    char buf[101],host[128];
    int ch;
    float arg1, arg2;
    char nazwa_programu[10];
    char execStr1[20];
    char execStr2[20];
    int prog_nr;

    Internet_Adres sadres,cadres;

    // tworzy gniazdo
    if ((dg=socket (PF_INET,SOCK_STREAM,0)) < 0)		//dekrypto=funkcja tworz¹ca gniazdo
        err_sys("nie moge utworzyc gniazda");			//jesli deskyptor z³apie b³¹d wtedy nie bêdzie równy 0 i zwroci b³¹d 

    sadres.konfiguracja(TSPORT,0);						

    if (bind (dg,sadres,sadres.rozmiar()) < 0)			//wi¹zanie adresu z gniazdem
        err_sys("nie moge zwiazac adresu lokalnego");	//jeœli coœ pójdzie nit tak, bindowanie zwraca <>0 i my obs³ugujemy ten b³¹d

    listen(dg,5);										//funkcja okreœlaj¹ca liczbê zadañ po³¹czenia

    while(1) {
        printf("Czekam na polaczenie...\t?\n");
        ddg=accept(dg,cadres,&cadres.rozmiar());		//funkcja wywolywana po stronie servera do przyjmowania zadania poloczenia ze strony klienta dg-deskryptor gniazda zwracany przez socket
        printf("Polaczenie nawiazane!\tok\n");

        int fd[2];
        pipe(fd);

        // PROCES POTOMNY
        if (fork()==0) {

            fflush(stdout);
            //pobranie od uzytk. ktory program
        	wysyla(ddg,"Wybierz jak¹ operacjê chcesz wykonaæ?\n 1. lista folderow, 2. przywitanie\n:",100);

        	int i = 1;
        	for (int i = 1; i < 4; i++) {
        		if ( odbiera(ddg,buf,100)==0) break;

                if(i==1){
                    prog_nr = atoi(buf);
        		    wysyla(ddg, "", 100);
        		};
        		if(i==2) {
        		    wysyla(ddg, "", 100);
                   // arg1 = atof(buf);
                };        		
        	};

           // sprintf(execStr1, "%f", arg1);
            //sprintf(execStr2, "%f", arg2);

            close(fd[0]);
            dup2(fd[1],1);


            if(prog_nr == 1) {
//                printf("proces potomny wykonuje program <LISTA>:\n");
                execlp("./lista", execStr1, execStr2, NULL);
            } else if(prog_nr == 2) {
//                printf("proces potomny wykonuje program <WITAM>:\n");
                execlp("./witam", NULL, NULL, NULL);
            } else {
                wysyla(ddg, "Zle argumenty! Na dzisiaj wystarczy...", 100);
            }

            printf("Koniec procesu potomnego\n");
        	close (ddg);
            exit(0);
        }

        else {     // proces macierzysty
            close(fd[1]);
            int s;
            wait(&s); // czeka na zakonczenie procesu potomnego
            // sprawdza status zakonczenia potomka
            if ( s == 0 ) printf("Koniec procesu potomnego, sukces!\n"); //jeœli zakoñczenie nie wykona siê poprawnie/wystapi b³¹d w procesie potomnym wynik jest <>0 wiec jest blad
            else printf("Blad procesu potomnego! Numer bledu: %d\n",s);

            char wynik[100];
            bzero(wynik,100);
            read(fd[0],wynik,100);
            printf("Proces macierzysty: %s", wynik);
            wysyla(ddg,wynik,100);
        }

    }
    return 0;
}

void err_sys(const char *b) {
     char buf[100];
     fprintf(stderr,"%s\n",b);
     perror(buf);
     exit(1);
}
