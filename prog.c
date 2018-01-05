/* 


 funkcja exec 

 cwiczenie:
1) utworzyc program ktory oblicza iloraz
2) utworzyc program w ktorym proces macierzysty tworzy
   potomka ten przez wywolanie exec wykonuje program z dysku
   a proces macierzysty czeka na jego zakonczenie
    
*/ 


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/ioctl.h>
#define max 50
main()
{

int fd[2];


pipe(fd);
 
if (fork()==0) {
printf("proces potomny wykonuje program <program>:\n");

close(fd[0]);
dup2(fd[1],1);

//execlp("ls","ls","-l",0);
execlp("./iloraz","5", "2",NULL);

printf("koniec procesu potomnego\n");
exit(0);
}

else {     // proces macierzysty 

close(fd[1]);

int s;
wait(&s); // czeka na zakonczenie procesu potomnego

// sprawdza status zakonczenia potomka
if ( s == 0 ) printf("koniec procesu potomnego: sukces\n");
else printf("blad procesu potomnego: numer bladu %d\n",s);


char wynik[100];
bzero(wynik,100);

read(fd[0],wynik,100);

printf("proces macierzysty: %s",wynik);
}

return 0; //proces macierzysty konczy dzialanie
 
}
