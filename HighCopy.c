#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    char block[1024];
    int nread;
    FILE *in, *out;
    
    if(argc != 3) {
        printf("error:please write input file name and output file name\n");
        exit(1);
    }

    if((in = fopen(argv[1], "r")) == NULL) {
        printf("file is not found\n");
        exit(1);
    }
    out = fopen(argv[2], "w");

    while(fgets(block, 1024, in)!= NULL) {
       fputs(block,out);       
       printf(".");
    }
    
    fclose(in);
    fclose(out);
    printf("\ncopy is finished\n");
    return 0;
}
