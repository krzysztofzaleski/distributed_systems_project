#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define USPORT 5600
#define TSPORT 5600
#define UPATH  "./ugniazdo"
#define UPATH2  "/tmp/ugniazdo2"


typedef sockaddr* adres_gniazda;

class Internet_Adres {
  
  int typ;
  socklen_t size;
  
  struct sockaddr_in adres; 
  
  struct in_addr adr;
  
  struct hostent *host;
  
  public:  
    
    
  Internet_Adres(); 
  
  void konfiguracja(int numer_portu,const char *host_nazwa,);
  
  operator adres_gniazda() { return (adres_gniazda)&adres; }
  
  socklen_t& rozmiar() {size= sizeof(adres); return size;}
  
  
};  


int wysyla(int des,const char *b,int ile);
int odbiera(int des,char *b,int ile);
