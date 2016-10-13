#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char block[1024];
    int in, out;
    int nread;
    char input[30], output[30];

    if(argc != 3) {
        printf("error:please write input file name and output file name\n");
        exit(1);
    }

    strcpy(input, argv[1]);
    strcpy(output, argv[2]);

    in = open(input, O_RDONLY);
    out = open(output, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

    while((nread = read(in, block, sizeof(block))) > 0) {
       write(out, block, nread);
       printf(".");
       
    }
    
    close(in);
    close(out);
    printf("\ncopy is finished\n");
    return 0;
}
