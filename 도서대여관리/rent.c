#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_data.h"

void RentManager(char*argv[], struct rent*data,struct tagBook*tb, struct tagCustomer*tc);

void RentManager(char*argv[],struct rent*data, struct tagBook*tb, struct tagCustomer*tc){
    int select;
    while(1){
        printf("\n++++++++++++++++++++++++++++++++++++++++\n");
        printf("1501023 안창완\n");
        printf("========================================\n");
        printf("1. Rent a Book\n 2. Return a Book\n 3.List up All Rented Book\n 4.Search Rented Books\n 5. Detail REnt Log for a Book\n 0. Return to Main Menu\n");
        printf("========================================\n");
        printf("Choose Num> ");
        scanf("%d",&select);
        if(select == 1 ) RentalBook(argv,&tb,&tc);
        else if(select == 2) ReturnBook(argv);
        else if(select == 3) ListupAllRentedBooks(argv,&data);
        else if (select == 4) SearchRentedBooksbyCustomerName(argv);
        else if (select == 5) DetailRentLogforaBook(argv);
        else if (select == 0) return 0;
        else printf("다시 입력해주세요\n");
        
    }
}

int rentSort(char*argv[],struct rent*data){
    struct rent temp;
    int count = rentCount(argv);
    data = (struct rent*)malloc(sizeof(struct rent)*count);
    rentArray(argv,data);
    FILE*rt = fopen(argv[3],"wb+");
    for(int i=0; i<count-1;i++){
        for (int j=i+1;j<count; j++){
            if(strcmp(data[i].rentalDate,data[j].rentalDate)>0){
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
    for (int i =0; i<count; i++){
        fwrite(&data[i],sizeof(data[i]),1,rt);
    }
    fclose(rt);
    return 0;

}
int rentArray(char*argv[],struct rent*data){
    FILE* rt = fopen(argv[3],"rb");
    struct rent log;
    for(int i =0; fread(&log,sizeof(log),1,rt)>0; i++){
        strcpy(data[i].rentalDate,log.rentalDate);
        strcpy(data[i].rentBook,log.rentBook);
        strcpy(data[i].rentCustomerName,log.rentCustomerName);
        strcpy(data[i].returnRentalDate,log.returnRentalDate);
    }
    fclose(rt);
}
int rentCount(char * argv[]){
    struct rent log;
    FILE* rt = fopen(argv[3],"rb");
    int count = 0;
    while(fread(&log, sizeof(log),1,rt)>0){
        count++;
    }

    return count;
}


int RentalBook(char* argv[], struct tagBook*tb, struct tagCustomer*tc){
    FILE* b;
    FILE* c ;
    int bookId;
    int customerId;
    int key =0;
    int count = bookCount(argv);
    int count2 = CustomerCount(argv);
    tb = (struct tagBook*)malloc(sizeof(struct tagBook)*count);
    reArray(argv,tb);
    tc = (struct tagCustomer*)malloc(sizeof(struct tagCustomer)* count2 );
    CustomerArray(argv,tc);

    if((b =fopen(argv[1],"rb+")) == NULL){
        fprintf(stderr,"file open error\n");
        return 2;
    }else{
        printf("checking the bookID\n");
        printf("bookID >");
        scanf("%d",&bookId);
        for(int i=0; i<count;i++){
            if(tb[i].bookid == bookId){
                printf("exist book!\n");
                key =1;
                free(tb);
                fclose(b);
                break;
            }
        }
        if(key == 0 ) {
            printf("don't exist book\n");
            free(tb);
            fclose(b);
            return 0;
        }
    }
    if((c = fopen(argv[2],"rb+"))==NULL){
        fprintf(stderr,"file open error\n");
        return 2;
    }else{
        printf("checking the customerID\n");
        printf("customer ID >");
        scanf("%d", &customerId);
        for(int i=0; i<count2; i++){
            if(tc[i].customerid!=customerId){
                printf("exist customerID!\n");
                key =0;
                free(tc);
                fclose(c);
                break;
            }
        }
        if(key == 1){
                printf("don't exist customerID!\n");
                free(tc);
                fclose(c);
                return 0;
            }
    }
    inputData(argv);

    
}

int inputData(char*argv[]){
    FILE* rt = fopen(argv[3],"ab");
    struct rent log;
    char returnedDate[Max] = "Not Returned";
    char select;
    char c;
    while(1){
        printf("Book title > ");
        scanf("%s",log.rentBook);
        printf("\n");
        printf("customer Name >");
        scanf("%s", log.rentCustomerName);
        printf("rent date>");
        scanf("%s", log.rentalDate);
        strcpy(log.returnRentalDate,returnedDate);
        printf("Are you sure to rent(Y/N)\n");
        scanf(" %c", &select);
        if(select == 'y' || select == 'Y'){
            
            fwrite(&log,sizeof(log),1, rt);
            fclose(rt);
            return 0;
        }
        else if(select == 'n' || select == 'N') return 0;
        else printf("input again\n");
    }

}

int ReturnBook(char*argv[]){
    struct rent log;
    char returnBook[Max];
    FILE*c = fopen(argv[3],"rb+");

    printf("반납할 책을 입력하세요 >");
    scanf("%s",returnBook);
    while(fread(&log,sizeof(log),1,c)>0){
        if(strcmp(log.rentBook, returnBook) == 0){
            fseek(c,-sizeof(log),SEEK_CUR);
            printf("반납일 입력 >");
            scanf("%s",log.returnRentalDate);
            fwrite(&log,sizeof(log),1,c);
            fclose(c);
            return 0;
        }
    }




}

int ListupAllRentedBooks(char*argv[],struct rent*data){
    struct rent log;
    struct tagBook tb;
    struct tagCustomer tc;

    FILE* rt1 = fopen(argv[3],"rb");
    
    
    printf("2. ListupAllRentedBooks\n");
    printf("=============================================\n");
    printf("%-16s %-16s %-12s %-20s %-12s %-17s %-15s %-12s\n","도서번호","도서명","저자명","대여고객번호","고객명","전화번호","대여일","반납일");
    printf("=============================================\n");
   
    rentSort(argv,data);
    fflush(stdin);
    while(fread(&log,sizeof(log),1,rt1)>0){
        FILE* bk = fopen(argv[1], "rb");
        FILE*ct = fopen(argv[2],"rb");
        while(fread(&tb,sizeof(tb),1,bk)>0){
            if(strcmp(log.rentBook,tb.chTitle)==0){
                printf("%-12s %-12s %-12s",tb.chNumber,tb.chTitle,tb.chAuthor);
            }
            
        }
        
        while(fread(&tc,sizeof(tc),1,ct)>0){
            
            if(strcmp(log.rentCustomerName, tc.chName)==0){
                printf("%-12d %-12s %-12s",tc.customerid,tc.chName,tc.chPhoneNumber);
            }
            
        }

        printf("%-12s %-12s\n",log.rentalDate,log.returnRentalDate);
        fclose(bk);
        fclose(ct);
    }
    fclose(rt1);
    return 0;
    
}


int SearchRentedBooksbyCustomerName(char*argv[]){

    struct rent log;
    char searchName[Max];
    int num=1;
    
    FILE* rt = fopen(argv[3],"rb");
    FILE* bk = fopen(argv[1], "rb");
    FILE* ct = fopen(argv[2],"rb");

    printf("search Rented Book>");
    scanf("%s",searchName);
    fflush(stdin);

    printf("%s rent these books\n",searchName);
    while(fread(&log,sizeof(log),1,rt)>0){
        FILE* ct = fopen(argv[2],"rb");
        if(strcmp(log.rentCustomerName, searchName)){
            printf("%d. %-6s %s\n",num,log.rentBook,log.rentalDate);
            num++;
        }
           
    }
}


int DetailRentLogforaBook(char*argv[]){
    struct tagBook tb; 
    struct tagCustomer tc;
    struct rent log;


    FILE* r = fopen(argv[3],"rb");
    FILE* b = fopen(argv[1], "rb");
    FILE* c = fopen(argv[2],"rb");
    int select;

    printf("input Book ID >");
    scanf("%d",&select);
    while(fread(&tb,sizeof(tb),1,b)>0){
       if(select == tb.bookid){
            printf("Title : %s\n",tb.chTitle);
            printf("Author : %s\n",tb.chAuthor);
            printf("Publisher : %s\n",tb.chPublichser);
       }
    }
    printf("---------------------------------------\n");
    printf("%-12s %-12s %-12s %-12s %-12s\n","Name","PhoneNumber","email","rentdate","returndate");
    while(fread(&log,sizeof(log),1,r)>0){
        while(fread(&tc,sizeof(tc),1,c)>0){
            if(strcmp(log.rentCustomerName,tc.chName) ==0){
                printf("%-12s %-12s %-6s",tc.chName,tc.chPhoneNumber,tc.chEmail);   
            }
                  
        }
        printf("%-12s %-12s\n",log.rentalDate,log.returnRentalDate);
    }

}

