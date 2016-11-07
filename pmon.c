#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio_ext.h>

pid_t getPtestId(){
    FILE *pid;
    char buf[10];
    int len;

    if((pid = popen("pidof ptest", "r")) == NULL)
        printf("error\n");
  
    while((len = fscanf(pid, "%s", buf)) > 0){
        pclose(pid);
        return (pid_t)atoi(buf);
    }

    pclose(pid);
    return -1;
}

void ptestRun(){
    pid_t pid = getPtestId("ptest");
    
    if(pid != -1) {
        printf("\nrunning\n>>");
    }

    else {
        printf("\nnot existed\n>>");
    }

    fflush(stdout);
    alarm(5);
}

int main(){
    char ch;
    pid_t pid;
    (void) signal(SIGALRM, ptestRun);
    
    alarm(5);

    while(1){
        pid = getPtestId("ptest");
        printf(">>");
        ch = getchar();
        __fpurge(stdin);
        switch(ch){
            case 'q':
                printf("quit pmon\n");
                return 0;
                break;
            case 'k':
                pid = getPtestId("ptest");
                if(pid != -1){
                    kill(pid, SIGKILL);
                }
                break;
            case's':
                if(pid != -1){
                    printf("already running\n");
                }
                else {
                   system("gnome-terminal --command \"./ptest\"");
                }
                break;
            case 'r':
                pid=getPtestId();
                if(pid != -1){
                    if(kill(pid,SIGKILL) == 0){
                        system("gnome-terminal --command \"./ptest\"");
                    }
                }
                else printf("ptest newly started\n");
                break;
        }
    }
    return 0;
}
