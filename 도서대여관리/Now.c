#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_data.h"


void Now(char* argv[]){

	int pid=0;
   
   
    
    pid = fork();
    
    if(pid == 0){
        now_function(argv);
    }else printf("1501023 안창완\n");
    
	return 0;

}

void now_function(char*argv[]){
    int countBook = 0;
    int countCustomer = 0;
    countBook = bookCount(argv);
    printf("\n현재 %d권의 책이 존재합니다.\n", countBook);
    countCustomer = CustomerCount(argv);
    printf("현재 %d명의 회원수가 존재합니다.\n",countCustomer);
}