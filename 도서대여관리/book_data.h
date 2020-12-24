#define Max 30

struct tagBook
{
	int bookid;
	char chTitle[Max];
	char chAuthor[Max];
	char chNumber[Max];
	char chPublichser[Max];
	char chDay[Max];
};

struct tagCustomer
{
	int customerid;
	char chid[Max];
	char chPassword[Max];
	char chName[Max];
	char chPhoneNumber[Max];
	char chEmail[Max];
	char chBirthYYYYMMDD[Max];

};

struct rent{

	char rentalDate[Max];
	char returnRentalDate[Max];
	char rentCustomerName[Max];
	char rentBook[Max];
};

extern int sec;


extern void Now(char* argv[]);
extern void BookManager(char* argv[], struct tagBook*data);
extern void CustomerManager(char* argv[], struct tagCustomer* data);
extern void RentManager(char*argv[], struct rent* data,struct tagBook* tb, struct tagCustomer* tc);
