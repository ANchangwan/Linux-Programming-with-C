#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "book_data.h"


extern int login(char*argv[]){
    char logId[30];
    char logPassword[30];

  
    while(1){
        printf("1501023 안창완\n");
        printf("==================================\n");
        printf("ID >");
        scanf("%s", logId);
        printf("Password> ");
        scanf("%s", logPassword);
        printf("==================================\n");
        if(strcmp(logId,"1501023") == 0 && strcmp(logPassword,"1501023")== 0) break;
        else printf("again accunt\n");
    }
    return menu(argv);
}