#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;
bool com (string arr1,string arr2)
{
	int a=arr1.size() , b=arr2.size();
	for(int i=0 ; i<a ; i++)
	{
		if( (arr1[i]==arr2[0]) && (a-i>b-1) && ( ((i>0) && (arr1[i-1] ==' ')) || (i==0) ) )
		{
			int count =0 , w=i;
			bool tf=true;
			while ( ( w<a ) && (arr1[w]!=' ') )
			{
				count++;
				w++;
			}
			if(count==b)
			{
				w=i;
				for( int j=0 ; j<b ; )
				{
					if(arr1[w++]!=arr2[j++])
					{
						tf =false;
						break;
					}
				}
				if(tf)
					return true;
			}
		}
	}
	return false;
}
int researchInt( string arr )
{
	if(arr.size()==0)
		return 0;
	int size=arr.size();
	for( int i=0 ; i < size ; i++ )
	{
		if( !( (arr[i]>47) && (arr[i]<58) ) )
			return 0;
	}
	return stoi(arr);
}

struct Book
{
	int id, pubDate, amount ,numBorrowedBook;
	string title, field;
	struct Book* next;
	bool isHead ;
	Book()
	{
		isHead = false;
		id = pubDate = numBorrowedBook =0;
		amount = 1;
		title = "untitled";
		field = "non";
		next=NULL;
	}
};

struct Section
{
	Book *fristE;
	int id, numOfBooks,totleBorrowBook;
	string field;
	Section* next;
	Section()
	{
		id = numOfBooks = totleBorrowBook = 0;
		field = "non";
		fristE = NULL;
		next=NULL;
	}
};

class Library
{
	Section* secHead;
	Book* bookHead;
	int availableBooksNum, lengthOfSection, lengthOfBook ; 
	//Book* borrowedBooks;
public:
	Library()
	{
		lengthOfBook = availableBooksNum = lengthOfSection = 0;
		bookHead = NULL;
		secHead = NULL;
	}
	void AddSection(int ID, int numOfBooks, string field);
	void AddBook(string);
	void BorrowBook(int  , string , int  , int );
	void ReturnBook(int  , string , int  , int );
	void DisplayBooks(int);
	Book* SearchField(string ,int &);
	int BorrowedBooks(bool);
	void TransferSection( int , string , int , string );
	Book* ArrangeRecords(int);
	void display(Book* , int );
};

void Library::AddSection(int ID = 0, int numOfBooks = 0, string field = "non")
{
	Section* newSection = new Section;
	newSection->id = ID, newSection->numOfBooks = numOfBooks, newSection->field = field;

	// insert new section
	newSection->next = secHead;
	secHead = newSection;

	// add books
	for (int i = 0; i < numOfBooks; i++)
		AddBook(field);

	newSection->fristE = bookHead;
	bookHead->isHead = true;
	lengthOfSection++;
	lengthOfBook += numOfBooks;
}
void Library::AddBook(string secfield)
{
	while(true)
	{
		cout<<" please enter book  (id)   and   (pubdate)   and   (amount)   and   (title)   and   (field) \n";
		string id , pubdate , amount , title , field="yehya" ;
		getline(cin,id);
		getline(cin,pubdate);
		getline(cin,amount);
		getline(cin,title);
		getline(cin,field);
		if( ( researchInt(id) == 0 ) || ( researchInt(pubdate) == 0 ) || ( researchInt(amount) == 0 ) || ( title[0] ==' ' ) || ( field[0] ==' ' ) || !( com(field,secfield) ) )
			cout<<"You entered wrong information please try agen"<<endl;
		else
		{
			Book *newBook=new Book;
			newBook->id = researchInt(id) ; newBook->pubDate = researchInt(pubdate) ; newBook->amount = researchInt(amount) ; 
			newBook->title = title ; newBook->field = field ;
			// insert book
			newBook->next = bookHead;
			bookHead = newBook;
			break;
		}
	}
}
void Library::display(Book* start = NULL, int end = 0)
{
	if(!start)
	{
		if(bookHead==NULL)
		{
			cout<<"We Dont have any Book"<<endl;
		}
		start = bookHead;
	}
	if(!end)//display all book
		while (start != NULL)
		{
			cout << "{  Id = " << start->id << "    PublishingDate = ";
			cout << start->pubDate << "    amount = ";
			cout << start->amount << "    title = ";
			cout << start->title << "    field = ";
			cout << start->field << "  }\n";
			start = start->next;
		}
	else//display part of book
		while (end--)
		{
			cout << "[ " << start->id << " | ";
			cout << start->pubDate << " | ";
			cout << start->amount << " | ";
			cout << start->title << " | ";
			cout << start->field << " ]\n";
			start = start->next;
		}
}
Book* Library::SearchField(string Field,int & sizeOfBook)
{
	//get the section have the same field we need 
	Section *cursec=secHead;
	while(cursec!=NULL)
	{
		if(cursec->field == Field)
			break;
		cursec=cursec->next;
	}
	Book *curbook=NULL;
	if(cursec!=NULL)
		curbook=cursec->fristE;
	else
	{ 
		Book *ar=NULL;
		sizeOfBook=-1;
		return ar;
	}
	Book *arr=new Book[cursec->numOfBooks];
	int i=0;
	do {
			arr[i++] = *curbook;
			curbook = curbook->next;
			if(curbook == NULL)
					break;
	} while (curbook->isHead != true);
	sizeOfBook=cursec->numOfBooks;
	return arr;
}
void Library::BorrowBook(int ID , string TITLE , int AMOUNT , int PUBDATA)
{
	Book *borrowBook=bookHead;
	while(borrowBook!=NULL)
	{
		if ( (borrowBook->id == ID) && (!borrowBook->title.compare(TITLE)) && (borrowBook->pubDate == PUBDATA) )
		{
			if( (borrowBook->amount - AMOUNT ) > -1)//number of book you need great than the number of books you have 
			{
				borrowBook->amount -= AMOUNT;
				borrowBook->numBorrowedBook += AMOUNT;
				cout<<"the procees was done"<<endl;
				return ;
			}
			else 
			{
				cout<<"we dont have this number of book"<<endl;
				cout<<"All We have "<<borrowBook->amount<<endl;
				cout<<"you can try agan by press ( continue ) and if you need end press any key"<<endl;
				string newAmount , Continue;
				getline(cin,Continue);
				if( Continue=="continue" )
				{
					while(true)
					{
						cout<<"enter the New Amount You Need To Borrow Book"<<endl;
						getline(cin,newAmount);
						int research = researchInt(newAmount);
						if( research == 0 )
						{
							cout<<"you enter incorrect number please enter correct number"<<endl;
						}
						else 
						{
							BorrowBook(ID , TITLE , research , PUBDATA);
							break;
						}
					}
				}
				else	
					return ;
			}
		}
		borrowBook=borrowBook->next;
	}
	if(borrowBook!=NULL)
		cout<<"we dont have this book"<<endl;
}
int Library::BorrowedBooks(bool tf=false)
{
	int size = 0 , count=1;
	Section* cursec = secHead;
	while (cursec != NULL) 
	{
		Book* curbook = cursec->fristE;
		if(!curbook)
		{
			cursec = cursec->next;
			Book* curbook = cursec->fristE;
		}
		cursec->totleBorrowBook = 0;
		do {
			if (curbook->numBorrowedBook > 0)
				cursec->totleBorrowBook++;
			curbook = curbook->next;
			if (curbook == NULL)
				break;
		} while (curbook->isHead != true);
		size += cursec->totleBorrowBook;
		if(tf==true)
			cout<<"\nthe number of totle borrowed book of section "<<count++<<" = "<<cursec->totleBorrowBook;
		cursec = cursec->next;
	}
	return size;
}
void Library::DisplayBooks(int pubDate)
{
	//this function prient the book of pubDate >= pubDate you need   
	Book * start = bookHead;
	while (start != NULL)
	{
		if ( (start->amount) && (start->pubDate >=pubDate))
		{
			cout << "[ " << start->id << " | ";
			cout << start->pubDate << " | ";
			cout << start->title << " | ";
			cout << start->field << " ]\n";
		}
		start = start->next;
	}
}
void Library::ReturnBook(int ID , string TITLE , int AMOUNT , int PUBDATA)
{
	//retrun the book you borrowed
	Book *borrowBook=bookHead;
	while(borrowBook!=NULL)
	{
		if ( (borrowBook->id == ID) && (!borrowBook->title.compare(TITLE)) && (borrowBook->pubDate == PUBDATA) )
		{
			if( ( AMOUNT > 0) && (AMOUNT <= borrowBook->numBorrowedBook) )
			{
				borrowBook->amount += AMOUNT;
				borrowBook->numBorrowedBook -= AMOUNT;
				break;
			}
			else
			{
				cout<<"amount < 0 or amount out of range"<<endl;
				break;
			}
		}
		borrowBook=borrowBook->next;
	}
	if(borrowBook==NULL)
	{
		cout<<"you dont borrowed this book please sure you enter correct information"<<endl;
	}
}
Book* Library::ArrangeRecords(int sizeOfArr) 
{
	//Organize the book borrowing’s records from newest to oldest
	int size = sizeOfArr, i = 0;//size of totle borrowed book from function BorrowedBooks
	Book *arr = new Book[size], *temp = bookHead;
	
	while (temp)
	{
		if (temp->numBorrowedBook)
			arr[i++] = *temp;
		temp = temp->next;
	}

	for (i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (arr[i].pubDate < arr[j].pubDate)
				swap(arr[i], arr[j]);
		}
	}
	return arr;
}
void Library::TransferSection(int ID, string TITLE, int PUBDATA, string newField)
{
	bool getbook = 0;
	Book *transBook=NULL,  *prevBook = bookHead;
	Section* cursec = secHead;

	// get Selected book and the prev.
	while (cursec != NULL) {

		transBook = cursec->fristE;
		if(!transBook)
		{
			cursec = cursec->next;
			transBook = cursec->fristE;
		}
		do {

			if ((transBook->id == ID) && (!transBook->title.compare(TITLE)) && (transBook->pubDate == PUBDATA) && ( com( transBook->field , newField) ) )
			{
				getbook = 1;
				break;
			}
			prevBook = transBook;
			transBook = transBook->next;

			if (transBook == NULL)
				break;
		} while (transBook->isHead != true);
		if (getbook)
			break;
		cursec = cursec->next;
	}


	
	// get the new section and the frist book of it
	Section* newSec = secHead;
	while (newSec != NULL)
	{
		if (newSec->field == newField)
			break;
		newSec = newSec->next;
	}
	Book* fristBook=NULL;
	if(newSec!=NULL)
		fristBook = newSec->fristE;

	if( transBook==NULL || newSec==NULL)
	{
		cout<<"we dont have the book or we dont find the new section \n";
		return;
	}
	// handling bondery case
	if (transBook->isHead)
	{
		transBook->isHead = false;

		if (!transBook->next || transBook->next->isHead)
		{
			cursec->fristE = NULL;
			//if (transBook->next->isHead)
				

		}	
		else
		{
			cursec->fristE = transBook->next;
			cursec->fristE->isHead = true;
		}
	}


	// trasfer the book to the new section
	if (transBook == bookHead)
		bookHead = bookHead->next;

	prevBook->next = transBook->next;
	transBook->next = fristBook->next;
	fristBook->next = transBook;

}

int main()
{
	bool Close=true;
	Library library;
	string close="continue",select,numOperation;
	for(;;)
	{
		cout<<"Are you\n(1) librarian\n(2) member\n(3) if you want to close the library enter"<<endl;
		getline(cin,select);cout<<endl;
		if( ( researchInt(select) > 3 )  || ( researchInt(select) < 1 ) )
		{
			cout<<"please enter correct Input process"<<endl;
		}
		while( researchInt(select) == 1 )
		{
			system("cls");
			cout<<"please enter the number of operation you need to di it"<<endl;
			cout<<" (1) AddSection \n (2) display \n (3) SearchField \n (4) BorrowBook \n (5) BorrowedBooks \n (6) DisplayBooks \n (7) ReturnBook \n (8) ArrangeRecords \n (9) TransferSection"<<endl;
			getline(cin,numOperation);
			if( researchInt(numOperation) < 1 || researchInt(numOperation) > 9)
				cout<<"failed the access please enter the correct operation"<<endl;
			//select operation
			else if ( researchInt(numOperation) == 1 ) 
			{
				string id , numOfBooks , field="yehya" ;
				cout<<"please enter the id of section"<<endl;
				getline(cin,id);
				cout<<"please enter the numOfBooks of section"<<endl;
				getline(cin,numOfBooks);
				cout<<"please enter the field of section"<<endl;
				getline(cin,field);
				if( ( researchInt(id) == 0 ) || ( researchInt(numOfBooks) == 0 ) || ( field[0] ==' ' ) )
					cout<<"You entered wrong information please try agen"<<endl;
				else
					library.AddSection( researchInt(id) , researchInt(numOfBooks) , field );
			}  


			else if ( researchInt(numOperation) == 2 ) 
			{
				library.display();		
			}


			else if ( researchInt(numOperation) == 3 ) 
			{
				int size=0;
				cout<<"please enter the field you want to research it"<<endl;
				string field;
				getline(cin,field);
				Book *arr=library.SearchField(field,size);
				if(size==-1)
					cout<<"We Dont Have This Field"<<endl;
				else
				{
					for ( int i=0 ; i<size ; i++ )
					{
						cout << "{  Id = " << arr[i].id << "    PublishingDate = ";
						cout << arr[i].pubDate << "    amount = ";
						cout << arr[i].amount << "    title = ";
						cout << arr[i].title << "    field = ";
						cout << arr[i].field << "  }\n";
					}
				}
			}


			else if ( researchInt(numOperation) == 4 ) 
			{
				string ID , TITLE , AMOUNT , PUBDATA ;
				cout<<"please enter the book that is you need  (Id)  and  (Ttle)  and  (Amount)  and  (Pubdate)" <<endl;
				getline(cin,ID);
				getline(cin,TITLE);
				getline(cin,AMOUNT);
				getline(cin,PUBDATA);
				int id=researchInt( ID ) , amount=researchInt( AMOUNT ) , pubdata=researchInt( PUBDATA );
				if( ( id == 0 ) || ( TITLE[0] == ' ' ) || ( amount == 0 ) || ( pubdata == 0 ) )
				{
					cout<<"you entered a wrong information"<<endl;
				}
				else
					library.BorrowBook( id , TITLE , amount , pubdata );	
			}


			else if ( researchInt(numOperation) == 5 ) 
			{
					cout<<"\nthe number of totle borrowed book = "<<library.BorrowedBooks(true)<<endl;
			}


			else if ( researchInt(numOperation) == 6 ) 
			{
				cout<<"enter the Publishing data :"<<endl;
				string pubdata;
				getline(cin,pubdata);
				int Pubdata = researchInt(pubdata);
				if( Pubdata==0 )
					cout<<"you enter incorrect information"<<endl;
				else 
				{
					cout<<"the books have a great than or equel the Publishing data \n";
					library.DisplayBooks(Pubdata);
				}
			}


			else if ( researchInt(numOperation) == 7 ) 
			{
				string ID , TITLE , AMOUNT , PUBDATA ;
				cout<<"enter the book you want to return in the library   (ID)  and  (TITLE)  and  (AMOUNT)  and  (PUBDATA)"<<endl;
				getline(cin,ID);
				getline(cin,TITLE);
				getline(cin,AMOUNT);
				getline(cin,PUBDATA);
				int id=researchInt(ID) , amount=researchInt(AMOUNT) , pubdata=researchInt(PUBDATA);
				if( (id==0) || (amount==0) || (pubdata==0) || (TITLE[0]==' ') )
				{
					cout<<"you enter incorrect information"<<endl;
				}
				else
					library.ReturnBook(id,TITLE,amount,pubdata);
			}


			else if ( researchInt(numOperation) == 8 ) 
			{
				int size = library.BorrowedBooks();
				Book *arr=library.ArrangeRecords( size );
				cout<<"the book borrowing’s records ()"<<endl;
				for(int i=0 ; i<size ;i++)
				{
					cout << "{  Id = " << arr[i].id << "    PublishingDate = ";
					cout << arr[i].pubDate << "    amount = ";
					cout << arr[i].amount << "    title = ";
					cout << arr[i].title << "    field = ";
					cout << arr[i].field << "  }\n";
				}
			}


			else if ( researchInt(numOperation) == 9 ) 
			{
				string ID, TITLE, PUBDATA, newField ;
				cout<<"enter the book you want to trensfar to another field  (ID)  and  (TITLE)  and  (PUBDATA)  and  (newField)"<<endl;
				getline(cin,ID);
				getline(cin,TITLE);
				getline(cin,PUBDATA);
				getline(cin,newField);
				int id = researchInt(ID) , pubdata = researchInt(PUBDATA);
				if( (id == 0) || (pubdata == 0) || (TITLE[0] == ' ') || (newField[0]) == ' ')
					cout<<"you enter wrong information"<<endl;
				else
					library.TransferSection(id,TITLE,pubdata,newField);


			}	
			//select continue or restart prigram or close library
			while(true)
			{
				Close=true;
				cout<<"\n(1) To Continue\n(2) To Restart The Program\n(3) To Close The Library"<<endl;
				getline(cin,close);cout<<endl;
				if( ( researchInt(close) < 1 ) || ( researchInt(close) > 3 ) )
					cout<<"wrong operation try agen"<<endl;
				if( ( researchInt(close) == 1 ) || ( researchInt(close) == 2 ) || ( researchInt(close) == 3 ) )
					break;
			}
			if( ( researchInt(close) == 2 ) || ( researchInt(close) == 3 ) )
				Close=false;
			system("cls");
			if(!Close)
				break;
		}
		while( researchInt(select) == 2 ) //enter to member operation
		{
			system("cls");
			cout<<"this is all book in the library"<<endl;
			library.display();
			cout<<"\n(1) borrow book\n(2) research books in field\n(3) display books there have great or equal publishing data you want"<<endl;
			getline(cin,numOperation);
			if( researchInt(numOperation) < 1 || researchInt(numOperation) > 3)
				cout<<"failed the access please enter the correct operation"<<endl;
			//select operation
			else if ( researchInt(numOperation) == 2 ) 
			{
				int size=0;
				cout<<"please enter the field you want to research it"<<endl;
				string field;
				getline(cin,field);
				Book *arr=library.SearchField(field,size);
				if(size==-1)
					cout<<"We Dont Have This Field"<<endl;
				else
				{
					for ( int i=0 ; i<size ; i++ )
					{
						cout << "{  Id = " << arr[i].id << "    PublishingDate = ";
						cout << arr[i].pubDate << "    amount = ";
						cout << arr[i].amount << "    title = ";
						cout << arr[i].title << "    field = ";
						cout << arr[i].field << "  }\n";
					}
				}
			}


			else if ( researchInt(numOperation) == 1 ) 
			{
				string ID , TITLE , AMOUNT , PUBDATA ;
				cout<<"please enter the book that is you need  (Id)  and  (Ttle)  and  (Amount)  and  (Pubdate)" <<endl;
				getline(cin,ID);
				getline(cin,TITLE);
				getline(cin,AMOUNT);
				getline(cin,PUBDATA);
				int id=researchInt( ID ) , amount=researchInt( AMOUNT ) , pubdata=researchInt( PUBDATA );
				if( ( id == 0 ) || ( TITLE[0] == ' ' ) || ( amount == 0 ) || ( pubdata == 0 ) )
				{
					cout<<"you entered a wrong information"<<endl;
				}
				else
					library.BorrowBook( id , TITLE , amount , pubdata );	
			}
			else if ( researchInt(numOperation) == 3 ) 
			{
				cout<<"enter the Publishing data :"<<endl;
				string pubdata;
				getline(cin,pubdata);
				int Pubdata = researchInt(pubdata);
				if( Pubdata==0 )
					cout<<"you enter incorrect information"<<endl;
				else 
				{
					cout<<"the books have a great than or equel the Publishing data \n";
					library.DisplayBooks(Pubdata);
				}
			}

			//select continue or restart prigram or close library
			while(true)
			{
				Close=true;
				cout<<"\n(1) To Continue\n(2) To Restart The Program\n(3) To Close The Library"<<endl;
				getline(cin,close);cout<<endl;
				if( ( researchInt(close) < 1 ) || ( researchInt(close) > 3 ) )
					cout<<"wrong operation try agen"<<endl;
				if( ( researchInt(close) == 1 ) || ( researchInt(close) == 2 ) || ( researchInt(close) == 3 ) )
					break;
			}
			if( ( researchInt(close) == 2 ) || ( researchInt(close) == 3 ) )
				Close=false;
			system("cls");
			if(!Close)
				break;
		}

		//close the library
		if( ( researchInt(close) == 3 ) || ( researchInt(select) == 3 ) )
		{
			cout<<"Thank you for using our library goodbye"<<endl;
			break;
		}
	}
}
/*
cin.ignore();
*/
