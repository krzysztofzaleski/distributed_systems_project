#include <stdio.h>
#include <unistd.h>
#include <cstdlib>

int main (int argc, char*argv[]) {
    float x,y;
    x = atof(argv[0]); y = atof(argv[1]);
    if (y==0) printf("Chcesz dzielić przez 0!");
    else printf("Wynik dzielenia: %.2f\n",(float)x/y);
    return 0;
}
