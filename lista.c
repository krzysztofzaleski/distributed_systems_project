#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <dirent.h> 

int main (int argc, char*argv[]) {
		DIR *d;
		struct dirent *dir;
		d = opendir(".");
		if (d) {
			while ((dir = readdir(d)) != NULL) {
				printf("%s\n", dir->d_name);
			}
			closedir(d);
		}
		return(0);
	
 }     
