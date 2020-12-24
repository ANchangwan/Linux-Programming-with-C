#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "book_data.h"

int sec = 0;

void alarmHandler(int sig);

void NowBookandCustomerCount(char* argv[]);

extern int menu(char*argv[]) {
	int num,menu_num;
	struct tagBook* bk;
	struct tagBook* tb;
	struct tagCustomer* cs;
	struct tagCustomer*tc;
	struct rent* rm;
	signal(SIGALRM,alarmHandler);
	alarm(60);

	while(1){
		while (1) {	
			printf("1. Book Management\n2. Customer Management\n3. Rent ManageMent\n4. show me clock now\n5. Now Book and customer count\n0. Exit\nChoose num >> ");
			scanf("%d", &menu_num);
			if (menu_num < 6) break;
			else printf("잘못 입력했습니다.\n");
		}

		if (menu_num == 1) BookManager(argv, &bk);
		else if (menu_num == 2) CustomerManager(argv, &cs);
		else if (menu_num == 3) RentManager(argv,&rm,&tb,&tc);
		else if (menu_num == 4){ 
		printf("=========================\n");
		printf("now time\n");
		printf("%d minute\n",sec);
		printf("=========================\n"); }
		else if(menu_num == 5) Now(argv);
		else
		{
			printf("종료\n");
			exit(0);
		}

	}
}



void alarmHandler(int sig) {
	 sec += 1; 
	 alarm(60);
	 }
