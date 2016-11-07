#include <stdio.h>
#include <unistd.h>
#include <time.h>

void main(){
    time_t ptime;

    printf("\n[      local time      ]\n");

    while(1){
        time(&ptime);
        printf("%s", ctime(&ptime));
        sleep(2);
    }
}
