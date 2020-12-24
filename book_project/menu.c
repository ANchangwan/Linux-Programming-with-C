#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_data.h"


extern int menu(char*argv[]) {
	int num;
	int menu_num;
	struct tagBook* bk;
	struct tagCustomer* cs;
	while (1) {
		printf("1. Book Management\n");
		printf("2. Customer Management\n");
		printf("0. Exit\n");
		printf("Choose num >> ");
		scanf("%d", &menu_num);
		if (menu_num == 1 || menu_num == 2 || menu_num == 0) break;
		else printf("잘못 입력했습니다.\n");
	}

	if (menu_num == 1) BookManager(argv, &bk);
	else if (menu_num == 2) CustomerManager(argv, &cs);
	else
	{
		printf("종료\n");
		exit(0);
	}

}