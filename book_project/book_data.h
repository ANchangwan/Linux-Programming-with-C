

struct tagBook
{
	int bookid;
	char chTitle[30];
	char chAuthor[30];
	char chNumber[30];
	char chPublichser[30];
	char chDay[30];
};

struct tagCustomer
{
	int customerid;
	char chid[30];
	char chPassword[30];
	char chName[30];
	char chPhoneNumber[30];
	char chEmail[30];
	char chBirthYYYYMMDD[30];

};



extern void BookManager(char* argv[], struct tagBook* data);
extern void CustomerManager(char* argv[], struct tagCustomer* data);

