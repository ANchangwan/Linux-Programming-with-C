#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "book_data.h"




int main(int argc, char* argv[])
{	int num;
	int select_num;
	struct tagCustomer* customer;
	struct tagBook* book;
	
	
	
	if (argc < 3) {
		fprintf(stderr, "파일 열기 오류 : %s book.dat/customer.dat\n", argv[0]);
		exit(1);
	}

	login(argv);
	
	// if (num = 1) select_num =num;
	// else if (num = 2) select_num = num;
	// else select_num = num;


	
	// if (strcmp(argv[1], "book.dat") == 0) select_num = num;
	// else if (strcmp(argv[1], "customer.dat") == 0) select_num = num;
	// else select_num = num;
	

	// if (num == 1) BookManager(argv, &book);
	// else if (num == 2) CustomerManager(argv, &customer);
	// else
	// {
	// 	printf("종료\n");
	// 	exit(0);
	// }


}
