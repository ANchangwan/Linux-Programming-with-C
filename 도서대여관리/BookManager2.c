#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_data.h"


void BookManager(char* argv[], struct tagBook* data);

int ListupAllBook(char* argv[],struct tagBook *data)
{
	struct tagBook dt;
	FILE* fd;
	if ((fd = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "파일 열기 오류/n");
		return 2;
	}
	else {
		printf("1. ListUpAllBook\n");
		printf("=============================================================\n");
		printf("%-12s %-12s %-12s %-12s %-12s %-12s \n", "책id","타이틀","작가","번호","출판사","날짜");
		printf("=============================================================\n");
		sort(argv,data);
        fflush(stdin);
		while (fread(&dt, sizeof(dt), 1, fd) > 0)
		{
			if (dt.bookid != 0) printf("%-12d %-12s %-12s %-12s %-12s %-12s\n", dt.bookid, dt.chTitle, dt.chAuthor, dt.chNumber, dt.chPublichser, dt.chDay);
		}

	}
	fclose(fd);
	return 0;

}

int sort(char*argv[],struct tagBook * data)
{
	struct tagBook temp;
	int count = bookCount(argv);
	data = (struct tagBook*)malloc(sizeof(struct tagBook) * count);
	reArray(argv, data);
	FILE* fd = fopen(argv[1], "wb+");
	for(int i = 0; i<count-1; i++){
		for (int j=i+1; j<count; j++){
			if(strcmp(data[i].chTitle,data[j].chTitle) >0){
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
				
			}

		}
	}
	for(int i = 0; i<count; i++){

		fwrite(&data[i],sizeof(data[i]),1,fd);
	}
	fclose(fd);
	return 0;
}




int AddNewBook(char* argv[]) {
	struct tagBook dt;
	FILE* fd= fopen(argv[1],"ab");
	printf("2. AddNewBook\n");
	printf("========================================\n");
	printf("%-12s %-12s %-12s %-12s %-12s %-12s\n", "책id","타이틀","작가","번호","출판사","날짜");
	printf("========================================\n");
	printf("AddBook : ");
	scanf("%d", &dt.bookid);
	fflush(stdin);
	scanf("%s %s %s %s %s", dt.chTitle, dt.chAuthor, dt.chNumber, dt.chPublichser, dt.chDay);
	fflush(stdin);
	fwrite(&dt, sizeof(dt), 1, fd);
	fclose(fd);
}

int UpdateBook(char* argv[]) {
	struct tagBook dt;
	int id;
	FILE* fd;
	if ((fd = fopen(argv[1], "rb+")) == NULL) {
		fprintf(stderr, "파일 열기 오류\n");
		return 2;
	}
	else {
		printf("수정할 책을 검색하세요(id로 검색) : \n");
		scanf("%d", &id);
		while (fread(&dt, sizeof(dt), 1, fd) > 0){
			if (dt.bookid == id && dt.bookid != 0) {
				printf("========================================\n");
				printf("%10s %6s %6s %13s %6s %10s\n", "책id","타이틀","작가","번호","출판사","날짜");
				printf("========================================\n");
				printf("%10d %6s %6s %13s %6s %10s\n", dt.bookid, dt.chTitle, dt.chAuthor, dt.chNumber, dt.chPublichser, dt.chDay);
				fseek(fd, -sizeof(dt), SEEK_CUR);
				printf("업데이트할 정보를 입력하세요 : ");
				scanf("%d", &dt.bookid);
				fflush(stdin);
				scanf("%s %s %s %s %s", dt.chTitle, dt.chAuthor, dt.chNumber, dt.chPublichser, dt.chDay);
				fwrite(&dt, sizeof(dt), 1, fd);
				fclose(fd);
				return 0;
			}
		}
	}
	printf("데이터 %d 없음 \n", id);
	fclose(fd);
	return 0;
}

int reArray(char* argv[], struct tagBook* data) {
	FILE* fd = fopen(argv[1], "rb");
	struct tagBook dt;
	for (int i = 0; fread(&dt, sizeof(dt), 1, fd) > 0; i++) {
		data[i].bookid = dt.bookid;
		strcpy(data[i].chTitle, dt.chTitle);
		strcpy(data[i].chAuthor, dt.chAuthor);
		strcpy(data[i].chNumber, dt.chNumber);
		strcpy(data[i].chPublichser, dt.chPublichser);
		strcpy(data[i].chDay, dt.chDay);
	}
	fclose(fd);
}


extern int bookCount(char* argv[]) {
	struct tagBook dt;
	FILE* fd = fopen(argv[1],"rb");
	int count = 0;
	while (fread(&dt, sizeof(dt), 1, fd)) {
		count++;
	}
    
	return count;
}

int RemoveABook(char* argv[],struct tagBook *data) {
	int select_del;
	int count = bookCount(argv);
	data = (struct tagBook*)malloc(sizeof(struct tagBook) * count);
	reArray(argv,data);
	FILE* fd = fopen(argv[1], "wb+");
	printf("삭제할 ID 검색 : ");
	scanf("%d", &select_del);
	for (int i = 0; i < count; i++) {

		if (data[i].bookid != select_del) fwrite(&data[i], sizeof(data[i]), 1, fd);

	}
	free(data);
	fclose(fd);
	

}

int SearchBookInformationByTitle(char* argv[]) {
	struct tagBook dt;
	int searchId;
	FILE* fd;

	if ((fd = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "파일 열기 오류 \n");
		return 2;
	}
	else {
		printf("검색할 책의 id : ");
		scanf("%d", &searchId);
		fflush(stdin);
		printf("========================================\n");
		printf("%-12s %-12s %-12s %-12s %-12s %-12s\n", "책id","타이틀","작가","번호","출판사","날짜");
		printf("========================================\n");
		while (fread(&dt, sizeof(dt), 1, fd) > 0) {
			if (dt.bookid != 0 && dt.bookid == searchId) {
				printf("%-12d %-12s %-12s %-12s %-12s %-12s\n", dt.bookid, dt.chTitle, dt.chAuthor, dt.chNumber, dt.chPublichser, dt.chDay);
			}
		}
	}
	fclose(fd);
	return 0;


}



void BookManager(char* argv[], struct tagBook* data) {
	int select_num;
	while (1) {
		printf("\n");
		printf("1501023 안창완\n");
		printf(" 1.List up All Book\n 2.Add New Book\n 3. Update Book\n 4. Remove a Book\n 5. Search Book Information by Title\n 0. Return to Main Menu\n");
		printf("Choose menu : ");
		scanf("%d", &select_num);
		if (select_num == 1) ListupAllBook(argv,data);
		else if (select_num == 2) AddNewBook(argv);
		else if (select_num == 3) UpdateBook(argv);
		else if (select_num == 4) RemoveABook(argv,data);
		else if (select_num == 5) SearchBookInformationByTitle(argv);
		else if (select_num == 0) return menu(argv);
		else printf("다시 입력해주세요!\n");

	}

}