/***********************************************************************************/
//		NAME:	        AYUSHI TIWARI
//		PROJECT NAME:	ATM SIMULATION SYSTEM
//		LANGUAGE:		C++
//		CONCEPTS:		OBJECT ORIENTED + DATA STRUCTURES
//		DESIGN MENU:	CRUD OPERATIONS MOSTLY
//		DATABASE:		FILING
//		DESCRIPTION: The following system simulates the ATM using the filing
//		it consists on creating accounts, managing accounts and managing data
//		IT handles the operations like: WITHDRAW, DEPOSIT and INQUIRIES OF ACCOUNTS
//
//************************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//structure to store the account number information just
struct Account{
	string Id;
	string Password;
};

//structure for the linked list, to store list data
struct Node
{
public:
    Node* next;
    string id;
	string pass;
	int balance;
};

//starting of accounts list, just as singly linked list
struct Node *accounts;
ofstream transOut;

//method to create the new accounts
void createAccount(struct Account myAcc);

//method to withdraw the money from an account
void withdraw(struct Account myAcc);

//method to deposit the money in an account
void deposit(struct Account myAcc);

//method to ask inquiry about an account information
void inquiry(struct Account myAcc);

//method to display the all lists of the current accounts
void listAccounts();

//method to load all the data from the file to the accounts list
void load();

//method to unload all the data from the list to file back
void unload();

//method to display the menu
int menu();

//method to show the transactions
void showTransactions();

//main driver method, it is used to start the ATM
int main()
{
	load();
	struct Account myAcc;
	ofstream outFile;
	int choice=0;
	do
	{
		choice=menu();
		switch(choice)
		{
		case 1:
			cout<<"       CREATE ACCOUNT MENU        \n";
			createAccount(myAcc);
			cout<<"----------------------------------\n";
			break;
		case 2:
			cout<<"         WITHDRAW MENU            \n";
			withdraw(myAcc);
			cout<<"----------------------------------\n";
			break;
		case 3:
			cout<<"         DEPOSIT MENU             \n";
			deposit(myAcc);
			cout<<"----------------------------------\n";
			break;
		case 4:
			cout<<"     INQUIRY OF BALANCE MENU      \n";
			inquiry(myAcc);
			cout<<"----------------------------------\n";
			break;
		case 5:
			cout<<"        ACCOUNTS LIST MENU        \n";
			listAccounts();
			cout<<"----------------------------------\n";
			break;
		case 6:
			cout<<"     SHOW TRANSACTIONS MENU       \n";
			showTransactions();
			cout<<"----------------------------------\n";
			break;
		case 7:
			cout<<"----------------------------------\n";
			cout<<"Good Bye \n";
			cout<<"----------------------------------\n";
			break;
		default:
			cout<<"----------------------------------\n";
			cout<<"Invalid Input... \n";
			cout<<"----------------------------------\n";
		}
	}while(choice!=7);
	unload();
	return 0;
}

void createAccount(struct Account myAcc)
{
	cout<<"Enter Account Number: ";
	cin>>myAcc.Id;
	cout<<"Enter Password: ";
	cin>>myAcc.Password;
	bool flag=true;
	struct Node *temp=accounts;
	while(temp->next!=NULL)
	{
		if(temp->id==myAcc.Id)
			flag=false;
		temp=temp->next;
	}
	if(flag && temp->id!=myAcc.Id)
	{
		temp->next=new Node;
		temp=temp->next;
		temp->id=myAcc.Id;
		temp->pass=myAcc.Password;
		temp->balance=0;
		temp->next=NULL;
	}
	else
		cout<<"Account number already exists... \n";
}

void withdraw(struct Account myAcc)
{
	transOut.open("transactions.txt",ios::app);
	int amount=0;
	cout<<"Enter Account Number: ";
	cin>>myAcc.Id;
	cout<<"Enter Password: ";
	cin>>myAcc.Password;
	bool flag=false;
	struct Node *temp=accounts;
	while(temp!=NULL && !flag)
	{
		if(temp->id==myAcc.Id && temp->pass==myAcc.Password)
		{
			flag=true;
			cout<<"Enter amount to withdraw: ";
			cin>>amount;
			while(amount<0)
			{
				cout<<"Enter a positive amount only: ";
				cin>>amount;
			}
			if(amount<=temp->balance)
			{
				temp->balance-=amount;
				transOut<<"\n"<<"account number: "<<myAcc.Id;
				transOut<<"\n"<<"action: withdraw";
				transOut<<"\n"<<"amount: "<<amount;
			}
			else
			{
				cout<<"----------------------------------\n";
				cout<<"Not Enough Balance...\n";
				cout<<"----------------------------------\n";
			}
		}
		temp=temp->next;
	}
	if(!flag)
	{
		cout<<"--------------------------------\n";
		cout<<"Invalid Id or password ";
		cout<<"--------------------------------\n";
	}
	transOut.close();
}

//deposti method
void deposit(struct Account myAcc)
{
	//open file for deposit transactions add
	transOut.open("transactions.txt",ios::app);
	int amount=0;
	cout<<"Enter Account Number: ";
	cin>>myAcc.Id;
	cout<<"Enter Password: ";
	cin>>myAcc.Password;
	bool flag=false;
	struct Node *temp=accounts;
	while(temp!=NULL && !flag)
	{
		//adding all the transactions to deposit method as well
		if(temp->id==myAcc.Id && temp->pass==myAcc.Password)
		{
			flag=true;
			cout<<"Enter amount to deposit: ";
			cin>>amount;
			while(amount<0)
			{
				cout<<"Enter a positive amount only: ";
				cin>>amount;
			}
			temp->balance+=amount;
			transOut<<"\n"<<"account number: "<<myAcc.Id;
			transOut<<"\n"<<"action: deposit";
			transOut<<"\n"<<"amount: "<<amount;
		}
		temp=temp->next;
	}
	if(!flag)
	{
		//check if the credentials were wrong
		cout<<"----------------------------------\n";
		cout<<"Invalid Id or password ";
		cout<<"----------------------------------\n";
	}
	transOut.close();
}

//inquiry method, to get details of some account
void inquiry(struct Account myAcc)
{
	
	//get input the details
	cout<<"Enter Account Number: ";
	cin>>myAcc.Id;
	cout<<"Enter Password: ";
	cin>>myAcc.Password;
	bool flag=false;
	struct Node *temp=accounts;
	
	//loop over the accounts
	while(temp!=NULL)
	{
		if(temp->id==myAcc.Id && temp->pass==myAcc.Password)
		{
			flag=true;
	
			//display all the accounts
			cout<<"----------------------------------\n";
			cout<<"Account Number: "<<temp->id<<endl;
			cout<<"Account Balance: "<<temp->balance<<endl;
			cout<<"----------------------------------\n";
		}
		temp=temp->next;
	}
}

//methods to list the acconts
void listAccounts()
{
	//loop over all the accounts
	struct Node *temp=accounts;
	while(temp!=NULL)
	{
		//list and display the account details
		cout<<"----------------------------------\n";
		cout<<"Account Number: "<<temp->id<<endl;
		cout<<"Account Balance: "<<temp->balance<<endl;
		cout<<"----------------------------------\n";
		temp=temp->next;
	}
}

//method to show transactions
void showTransactions()
{
	//starting from msg
	string msg;
	//open input file
	ifstream transIn("transactions.txt");
	//loop over the file
	while(!transIn.eof())
	{
		cout<<"----------------------------------\n";
		//write all data to screen
		getline(transIn,msg);
		cout<<msg<<endl;
		getline(transIn,msg);
		cout<<msg<<endl;
		getline(transIn,msg);
		cout<<msg<<endl;
	}
	cout<<"----------------------------------\n";
	//close the file
	transIn.close();
}

//load method to load from file into the list
void load()
{
	//starting from the node
	accounts=new Node;

	ifstream input("accounts.txt");

	//take input the account credentials
	input>>accounts->id;
	input>>accounts->pass;
	input>>accounts->balance;
	accounts->next=NULL;
	//start from first account

	struct Node *temp=accounts;

	//loop over the file
	while(!input.eof())
	{
		temp->next=new Node;
		temp=temp->next;
		input>>temp->id;
		input>>temp->pass;
		input>>temp->balance;
		temp->next=NULL;
	}

	//close the file at end
	input.close();
}

//unload mthoed
void unload()
{

	//opens files where data is to write
	ofstream out("accounts.txt");
	struct Node *temp=accounts;

	//loop over thea ccounts
	while(temp->next!=NULL)
	{

		//put data into file
		out<<temp->id<<"\n";
		out<<temp->pass<<"\n";
		out<<temp->balance<<"\n";
		temp=temp->next;
	}

	//for last node data
	out<<temp->id<<"\n";
	out<<temp->pass<<"\n";
	out<<temp->balance;
	out.close();
}

//menu method
int menu()
{

	//choice variable for choie
	int choice;

	//showing list of menus
	cout<<"1.	Create Account \n";
	cout<<"2.	Withdraw \n";
	cout<<"3.	Deposit \n";
	cout<<"4.	Inquiry \n";
	cout<<"5.	List Accounts \n";
	cout<<"6.	Show Transactions \n";
	cout<<"7.	Quit \n";
	cout<<"----------------------------------\n";
	cout<<"Enter option(1-7): ";

	//taking input choice
	cin>>choice;
	while(choice<1 || choice>7)
	{
		cout<<"Please enter right option: ";
		cin>>choice;
	}

	cout<<"----------------------------------\n";
	return choice;
}

/*********************************  OUTPUT  *********************************
1.      Create Account
2.      Withdraw
3.      Deposit
4.      Inquiry
5.      List Accounts
6.      Show Transactions
7.      Quit
----------------------------------
Enter option(1-7): 6
----------------------------------
     SHOW TRANSACTIONS MENU
----------------------------------
account number: dummy
action: deposit
amount: 0
----------------------------------
account number: jkl
action: deposit
amount: 500
----------------------------------
account number: jkl
action: withdraw
amount: 5
----------------------------------
----------------------------------
1.      Create Account
2.      Withdraw
3.      Deposit
4.      Inquiry
5.      List Accounts
6.      Show Transactions
7.      Quit
----------------------------------
Enter option(1-7): 5
----------------------------------
        ACCOUNTS LIST MENU
----------------------------------
Account Number: dummy
Account Balance: 0
----------------------------------
----------------------------------
Account Number: abc
Account Balance: 589
----------------------------------
----------------------------------
Account Number: def
Account Balance: 400
----------------------------------
----------------------------------
Account Number: jkl
Account Balance: 717
----------------------------------
----------------------------------
1.      Create Account
2.      Withdraw
3.      Deposit
4.      Inquiry
5.      List Accounts
6.      Show Transactions
7.      Quit
----------------------------------
Enter option(1-7): 1
----------------------------------
       CREATE ACCOUNT MENU
Enter Account Number: UUU
Enter Password: 123
----------------------------------
1.      Create Account
2.      Withdraw
3.      Deposit
4.      Inquiry
5.      List Accounts
6.      Show Transactions
7.      Quit
----------------------------------
Enter option(1-7): 2
----------------------------------
         WITHDRAW MENU
Enter Account Number: JKL
Enter Password: 777
--------------------------------
Invalid Id or password --------------------------------
----------------------------------
1.      Create Account
2.      Withdraw
3.      Deposit
4.      Inquiry
5.      List Accounts
6.      Show Transactions
7.      Quit
----------------------------------
Enter option(1-7): 2
----------------------------------
         WITHDRAW MENU
Enter Account Number: jkl
Enter Password: 777
Enter amount to withdraw: 50
----------------------------------
1.      Create Account
2.      Withdraw
3.      Deposit
4.      Inquiry
5.      List Accounts
6.      Show Transactions
7.      Quit
----------------------------------
Enter option(1-7): 7
----------------------------------
----------------------------------
Good Bye
----------------------------------
Press any key to continue . . .

****************************************************************************/
