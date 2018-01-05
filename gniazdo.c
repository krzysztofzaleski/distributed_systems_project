#include "gniazdo.h"


Internet_Adres::Internet_Adres() {}


void Internet_Adres::konfiguracja(int port,const char *s) {
     
     host=NULL;
     if (s != NULL) {
//	  in_addr adr;
//	  adr.s_addr=inet_addr(s);
//          host = gethostbyaddr(&adr,sizeof(adr),AF_INET);  //adres stacji
          if (host == NULL) host = gethostbyname(s); 
     }
  
// wypelnia strukture adresu 
bzero(&adres,sizeof(adres));
adres.sin_family = AF_INET;  
adres.sin_port=htons(port);  

if (host == NULL)
    adres.sin_addr.s_addr = INADDR_ANY;
else
    memcpy(&adres.sin_addr,host->h_addr,host->h_length);
}


int wysyla(int des, const char *b, int ilosc) {
    int l,ile=ilosc;
    while (ile>0) {
    
    if ((l=write(des,b,ile)) <0) return l;
    ile-=l;
    b+=l;
    }
    
    return ilosc-ile;
}


int odbiera(int des, char *b, int ilosc) {
    int l,ile=ilosc;
    
    while (ile>0) {
    
    if ((l=read(des,b,ile)) <0) return l;
    else if (l==0) break;
    ile-=l;
    b+=l;
    }
    return ilosc-ile;
    
}
