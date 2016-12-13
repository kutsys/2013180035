#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 500

void elfoption(char* argv1,char* argv2) {
    char temp[SIZE];
    if(strstr(argv1,"e") != NULL) {
        sprintf(temp,"readelf -h %s",argv2);
    	system(temp);
    }

    if(strstr(argv1,"p") != NULL){
    	sprintf(temp,"readelf -l %s",argv2);
    	system(temp);
    }

    if(strstr(argv1,"s") != NULL){
    	sprintf(temp,"readelf -S %s",argv2);
    	system(temp);
    }
}

int main(int argc,char* argv[]) {
    char temp[SIZE];
    
    switch(argc) {
	case 2 :
            sprintf(temp,"readelf -h %s", argv[1]);
            system(temp);
            break;
	
        case 3 :
            elfoption(argv[1],argv[2]);
            break;
	
        default:
            printf("command is wrong..\n");
            break;
    }
	return 0;
}
