#include <stdio.h>
#include <unistd.h>
#include <cstdlib>

int main (int argc, char*argv[]) {
    float x,y;
    x = atof(argv[0]); y = atof(argv[1]);
    printf("Wynik odejmowania: %.2f\n",(float)x-y);
    return 0;
 }    
