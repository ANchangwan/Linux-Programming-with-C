#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_data.h"


void CustomerManager(char* argv[], struct tagCustomer* data);


int ListupAllCustomers(char* argv[],struct tagCustomer* data)
{
	struct tagCustomer cs;
	FILE* sd;
	if ((sd = fopen(argv[2], "rb")) == NULL) {
		fprintf(stderr, "파일 열기 오류/n");
		return 2;
	}
	else {
		printf("\n1. ListupAllCustomers\n");
		printf("=============================================================\n");
		printf("%-12s %-12s %-12s %-12s %-12s %-12s %-12s\n", "고객id","계정","비밀번호","이름","전화번호","이메일","출생년도");
		printf("=============================================================\n");
		customerSort(argv,data);
		fflush(stdin);
		while (fread(&cs, sizeof(cs), 1, sd) > 0)
		{
			if (cs.customerid != 0) printf("%-12d %-12s %-12s %-12s %-12s %-12s %-12s\n", cs.customerid, cs.chid, cs.chPassword, cs.chName, cs.chPhoneNumber, cs.chEmail, cs.chBirthYYYYMMDD);
		}

	}
	fclose(sd);
	return 0;

}
int customerSort(char*argv[],struct tagCustomer * data)
{
	struct tagCustomer temp;
	int count = CustomerCount(argv);
	data = (struct tagCustomer*)malloc(sizeof(struct tagCustomer) * count);
	CustomerArray(argv, data);
	FILE* sd = fopen(argv[2], "wb+");
	for(int i = 0; i<count-1; i++){
		for (int j=i+1; j<count; j++){
			if(strcmp(data[i].chName,data[j].chName) >0){
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
				
			}

		}
	}
	for(int i = 0; i<count; i++){

		fwrite(&data[i],sizeof(data[i]),1,sd);
	}
	fclose(sd);
	return 0;
}

int AddNewCustomer(char* argv[]) {
	struct tagCustomer cs;
	FILE* sd= fopen(argv[2],"ab");
	printf("2. AddNewCustomer\n");
	printf("========================================\n");
	printf("%-12s %-12s %-12s %-12s %-12s %-12s %-12s\n", "고객id","계정","비밀번호","이름","전화번호","이메일","출생년도");
	printf("========================================\n");
	printf("AddCustomer : ");
	scanf("%d", &cs.customerid);
	fflush(stdin);
	scanf("%s %s %s %s %s %s", cs.chid, cs.chPassword, cs.chName, cs.chPhoneNumber, cs.chEmail, cs.chBirthYYYYMMDD);
	fflush(stdin);
	fwrite(&cs, sizeof(cs), 1, sd);
	fclose(sd);
	
	
	
}

int UpdateCustomer(char* argv[]) {
	struct tagCustomer cs;
	int id;
	FILE* sd;
	if ((sd = fopen(argv[2], "rb+")) == NULL) {
		fprintf(stderr, "파일 열기 오류\n");
		return 2;
	}
	else {
		printf("수정할 책을 검색하세요(id로 검색) : \n");
		scanf("%d", &id);
		while (fread(&cs, sizeof(cs), 1, sd) > 0){
			if (cs.customerid == id && cs.customerid != 0) {
				printf("========================================\n");
				printf("%-12s %-12s %-12s %-12s %-12s %-12s %-12s\n", "고객id","계정","비밀번호","이름","전화번호","이메일","출생년도");
				printf("========================================\n");
				printf("%-12d %-12s %-12s %-12s %-12s %-12s %-12s\n", cs.customerid, cs.chid, cs.chPassword, cs.chName, cs.chPhoneNumber, cs.chEmail, cs.chBirthYYYYMMDD);
				fseek(sd, -sizeof(cs), SEEK_CUR);
				printf("업데이트할 정보를 입력하세요 : ");
				scanf("%d", &cs.customerid);
				fflush(stdin);
				scanf("%s %s %s %s %s %s", cs.chid, cs.chPassword, cs.chName, cs.chPhoneNumber, cs.chEmail, cs.chBirthYYYYMMDD);
				fwrite(&cs, sizeof(cs), 1, sd);
				fclose(sd);
				return 0;
			}
		}
	}
	printf("데이터 %d 없음 \n", id);
	fclose(sd);
	return 0;
}
int CustomerArray(char* argv[], struct tagCustomer* data) {
	FILE* sd = fopen(argv[2], "rb");
	struct tagCustomer cs;
	for (int i = 0; fread(&cs, sizeof(cs), 1, sd) > 0; i++) {
		data[i].customerid = cs.customerid;
		strcpy(data[i].chid, cs.chid);
		strcpy(data[i].chPassword, cs.chPassword);
		strcpy(data[i].chName, cs.chName);
		strcpy(data[i].chPhoneNumber, cs.chPhoneNumber);
        strcpy(data[i].chEmail, cs.chEmail);
        strcpy(data[i].chBirthYYYYMMDD,cs.chBirthYYYYMMDD);
	}
	fclose(sd);
}


int CustomerCount(char* argv[]) {
	struct tagCustomer cs;
	FILE* sd = fopen(argv[2],"rb");
	int count = 0;
	while (fread(&cs, sizeof(cs), 1, sd)) {
		count++;
	}
	return count;
}

int RemoveaCustomer(char* argv[],struct tagCustomer *data) {
	int select_del;
	int count = CustomerCount(argv);
	data = (struct tagCustomer*)malloc(sizeof(struct tagCustomer) * count);
	CustomerArray(argv,data);
	FILE* sd = fopen(argv[2], "wb+");
	printf("삭제할 ID 검색 : ");
	scanf("%d", &select_del);
	for (int i = 0; i < count; i++) {

		if (data[i].customerid != select_del) fwrite(&data[i], sizeof(data[i]), 1, sd);

	}
	free(data);
	fclose(sd);
	

}

int SearchCustomerInformationbyName(char* argv[]) {
	struct tagCustomer cs;
	char searchTitle[30];
	FILE* sd;

	if ((sd = fopen(argv[2], "rb")) == NULL) {
		fprintf(stderr, "파일 열기 오류 \n");
		return 2;
	}
	else {
		printf("검색할 이름 : ");
		scanf("%s", searchTitle);
		printf("========================================\n");
		printf("%-12s %-12s %-12s %-12s %-12s %-12s %-12s\n", "고객id","계정","비밀번호","이름","전화번호","이메일","출생년도");
		printf("========================================\n");
		while (fread(&cs, sizeof(cs), 1, sd) > 0) {
			if (cs.customerid != 0 && strcmp(cs.chName, searchTitle) == 0) {
				printf("%-12d %-12s %-12s %-12s %-12s %-12s %-12s\n", cs.customerid, cs.chid, cs.chPassword, cs.chName, cs.chPhoneNumber, cs.chEmail, cs.chBirthYYYYMMDD);
			}
		}
	}
	fclose(sd);
	return 0;
}
int SearchCustomerInformationbyPhoneNumber(char* argv[]) {
	struct tagCustomer cs;
	char searchPhoneNumber[30];
	FILE* sd;

	if ((sd = fopen(argv[2], "rb")) == NULL) {
		fprintf(stderr, "파일 열기 오류 \n");
		return 2;
	}
	else {
		printf("검색할 전화번호 : ");
		scanf("%s", searchPhoneNumber);
		printf("========================================\n");
		printf("%-12s %-12s %-12s %-12s %-12s %-12s %-12s\n", "고객id","계정","비밀번호","이름","전화번호","이메일","출생년도");
		printf("========================================\n");
		while (fread(&cs, sizeof(cs), 1, sd) > 0) {
			if (cs.customerid != 0 && strcmp(cs.chPhoneNumber, searchPhoneNumber) == 0) {
				printf("%-12d %-12s %-12s %-12s %-12s %-12s %-12s\n", cs.customerid, cs.chid, cs.chPassword, cs.chName, cs.chPhoneNumber, cs.chEmail, cs.chBirthYYYYMMDD);
			}
		}
	}
	fclose(sd);
	return 0;


}



void CustomerManager(char* argv[], struct tagCustomer* data)
 {
	int select_num;
	while (1) {
		printf("1501023 안창완\n");
		printf(" 1.List up All Customers\n 2.Add New Customer\n 3. Update Customer\n 4. Remove a Customer\n 5. Search Customer Information by Name\n 6. Search Customer Information by Phone Number\n 0.Return to Main Menu\n");
		printf("Choose menu : ");
		scanf("%d", &select_num);
		if (select_num == 1) ListupAllCustomers(argv,data);
		else if (select_num == 2) AddNewCustomer(argv);
		else if (select_num == 3) UpdateCustomer(argv);
		else if (select_num == 4) RemoveaCustomer(argv,data);
		else if (select_num == 5) SearchCustomerInformationbyName(argv);
        else if (select_num == 6) SearchCustomerInformationbyPhoneNumber(argv);
		else if (select_num == 0) return menu(argv);
		else printf("다시 입력해주세요!\n");

	}

}
