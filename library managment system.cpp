#include <iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include <windows.h>       
using namespace std;

int ThisIsIt;// i have declared this global variable to manage the y-axis in gotoxy function in line 361,386

void gotoxy(short x, short y) 
{

COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


class book
{
	char BookNo[6];
	char BookName[50];
	char AuthorName[20];
	public :
     void createbook()
     {
     	cout<<"\nNEW BOOK ENTRY...\n";
        cout<<"\nEnter The book no.";
        cin>>BookNo;fflush(stdin);  // it is used to flush or clear the output buffer of the stream.
        cout<<"\n\nEnter The Name of The Book ";
        gets(BookName);fflush(stdin);// it is used to flush or clear the output buffer of the stream.
        cout<<"\n\nEnter The Author's Name ";
        gets(AuthorName);
        cout<<"\n\n\nBook Created..";
     }

     void showbook()
     {
     	cout<<"\nBOOK NUMBER :"<<BookNo;
     	cout<<"\nBOOK NAME :";
     	puts(BookName);
     	cout<<"\nAUTHOR NAME :";
     	puts(AuthorName);
     }

     void modifybook()
     {
      cout<<"\nBOOK NUMBER :"<<BookNo;
      cout<<"\nModify book name :";
      gets(BookName);
      cout<<"\nModify AUTHORS name :";
      gets(AuthorName);

     }
   char* retBookNo() // return type is a character array
   {
      return BookNo;
   } 

   void report()
   {gotoxy(1,ThisIsIt);
   	cout<<BookNo;
    gotoxy(11,ThisIsIt);
    cout<<BookName;
    gotoxy(31,ThisIsIt);
    cout<<AuthorName<<endl; 
   }  
};//class ends here

class student
{
char AdmissionNumber[10];
	char name[20];
	char stBookNo[6];
	int token ;
	public :
     void createstudent()
     {
     	system("cls");
     	cout<<"\nNEW STUDENT ENTRY...\n";
        cout<<"\nEnter The admission no. ";
        cin>>AdmissionNumber;
        cout<<"\n\nEnter The Name of The Student ";
        cin>>gets(name);fflush(stdin);
        token=0;
        stBookNo[0]='/0';
        cout<<"\n\nStudent Record Created..";
     }

     void showstudent()
     {
     	cout<<"\nADMISSION NUMBER :"<<AdmissionNumber;
     	cout<<"\nSTUDENT NAME :";
     	puts(name);
     	cout<<"\nNO. OF BOOKS ISSUED :"<<token;
     	if (token==1)
     	{
     		cout<<"\nBOOK NUMBER"<<stBookNo;
     	}
     }

     void modifystudent()
     {
      cout<<"\nADMISSION NUMBER :"<<AdmissionNumber;
      cout<<"\nModify student name :";
      gets(name);
     }
   char* retAdmissionNumber() // return type is a character array
   {
      return AdmissionNumber;
   } 

   char* retstBookNo() // return type is a character array
   {
      return stBookNo;
   } 
   int rettoken() 
   {
      return token;
   } 

   void addtoken()
   {
   	token = 1;
   }

   void resettoken()
   {
   	token = 0;
   }

   void getsBookNo(char t[])
   {
   	strcpy(stBookNo,t);
   }

    void report()
   { 
    
    gotoxy(1,ThisIsIt);
    cout<<AdmissionNumber;
    gotoxy(18,ThisIsIt);
    cout<<name;
    gotoxy(39,ThisIsIt);
    cout<<token<<endl; 
   }

}; // class ends here


fstream fs,fs1;
book bk;
student st;

void writebook()
{
    char ch;
    fs.open("book.txt",ios::out|ios::app); // ios::out is used to write and ios::app is used to append the data
    do
    { 
        system("cls");// it clears the screen
        bk.createbook();
        fs.write((char*)&bk,sizeof(book));//To write the data i need to mention the address and size of the data
        cout<<"\n\nDo you want to add more record..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fs.close();
}


void writestudent()
{
    char ch;
    fs.open("student.txt",ios::out|ios::app); // ios::out is used to write and ios::app is used to append the data
    do
    { 
        system("cls");// it clears the screen
        st.createstudent();
        fs.write((char*)&st,sizeof(student));//To write the data i need to mention the address and size of the data
        cout<<"\n\nDo you want to add more record..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fs.close();
}


void displayspb(char n[])
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fs.open("book.txt",ios::in); // ios::in  its the read mode
    while(fs.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retBookNo(),n)==0)// strcmpi is used to compare to strings
        {
            bk.showbook();
             flag=1;
        }
    }

    fs.close();
    if(flag==0)
        cout<<"\n\nBook does not exist";
    getch();
}

void displaysps(char n[])
{
    cout<<"\nSTUDENT DETAILS\n";
    int flag=0;
    fs.open("student.txt",ios::in);// ios::in  its the read mode
    while(fs.read((char*)&st,sizeof(student)))
    {
        if((strcmpi(st.retAdmissionNumber(),n)==0))// strcmpi is used to compare to strings
        {
            st.showstudent();
            flag=1;
        }
    }

    fs.close();
    if(flag==0)
            cout<<"\n\nStudent does not exist";
     getch();
}

void modifybook()
{
    char n[6];
    int found=0;

    cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
    cout<<"\n\n\tEnter The book no. of The book";
    cin>>n;
    fs.open("book.txt",ios::in|ios::out); 
    while(fs.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmpi(bk.retBookNo(),n)==0)
        {
            bk.showbook();
            cout<<"\nEnter The New Details of book"<<endl;
            bk.modifybook();
            int pos=-1*sizeof(bk); // this is to point to the starting address of the modify book 
                fs.seekp(pos,ios::cur);// ios::curl  is used to go back or forward in the data  from the current position 
                fs.write((char*)&bk,sizeof(book));
                cout<<"\n\n\t Record Updated";
                found=1;
        }
    }

        fs.close();
        if(found==0)
            cout<<"\n\n Record Not Found ";
        getch();
}
void modifystudent()
{
    char n[10];
    int found=0;

    cout<<"\n\n\tMODIFY STUDENT RECORD... ";
    cout<<"\n\n\tEnter The admission no. of The student";
    cin>>n;
    fs.open("student.txt",ios::in|ios::out);
    while(fs.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.retAdmissionNumber(),n)==0)
        {
            st.showstudent();
            cout<<"\nEnter The New Details of student"<<endl;
            st.modifystudent();
            int pos=-1*sizeof(st);
            fs.seekp(pos,ios::cur);
            fs.write((char*)&st,sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }

    fs.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
}
void deletestudent()
{
    char n[10];
    int flag=0;

        cout<<"\n\n\n\tDELETE STUDENT...";
        cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
        cin>>n;
        fs.open("student.txt",ios::in|ios::out);
        fstream fs2;
        fs2.open("Temp.txt",ios::out);
        fs.seekg(0,ios::beg);
        while(fs.read((char*)&st,sizeof(student)))// we are basically reading data from student.txt and writing into temp.txt
    {
        if(strcmpi(st.retAdmissionNumber(),n)!=0)
                 fs2.write((char*)&st,sizeof(student));
        else
               flag=1;
    }

    fs2.close();
        fs.close();
        remove("student.txt");
        rename("Temp.txt","student.txt");
        if(flag==1)
             cout<<"\n\n\tRecord Deleted ..";
        else
             cout<<"\n\nRecord not found";
        getch();
}


void deletebook()
{
    char n[6];

    cout<<"\n\n\n\tDELETE BOOK ...";
    cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin>>n;
    fs.open("book.txt",ios::in|ios::out);
    fstream fs2;
    fs2.open("Temp.txt",ios::out);
    fs.seekg(0,ios::beg);
    while(fs.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retBookNo(),n)!=0)
        {
            fs2.write((char*)&bk,sizeof(book));
        }
    }

    fs2.close();
        fs.close();
        remove("book.txt");
        rename("Temp.txt","book.txt");
        cout<<"\n\n\tRecord Deleted ..";
        getch();
}



void displayalls()
{

         fs.open("student.txt",ios::in);
         if(!fs)
         {
               cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
               getch();
               return;
         }
 system("cls");// it clears the screen
    cout<<"\n\n\t\tSTUDENT LIST\n\n";
    cout<<"AdmissionNo.    |"<<"|Name              |"<<"|Book Issued\n";
           ThisIsIt = 4 ;
    while(fs.read((char*)&st,sizeof(student)))
    {      ThisIsIt++ ;
        st.report();
    }

    fs.close();
    getch();
}



void displayallb()
{

    fs.open("book.txt",ios::in);
    if(!fs)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
               getch();
               return;
         }
    system("cls");
    cout<<"\n\n\t\tBook LIST\n\n";
    cout<<" BookNo.|"<<"|Book Name         |"<<"|Author\n";
       ThisIsIt = 4 ;
    while(fs.read((char*)&bk,sizeof(book)))
    {    ThisIsIt++; 
        bk.report();
    }
         fs.close();
         getch();
}


void bookissue()
{
    char sn[6],bn[6];
    int found=0,flag=0;

    cout<<"\n\nBOOK ISSUE ...";
    cout<<"\n\n\tEnter The student's admission no.";
    cin>>sn;
    fs.open("student.txt",ios::in|ios::out);
        fs1.open("book.txt",ios::in|ios::out);
        while(fs.read((char*)&st,sizeof(student)) && found==0)
           {
        if(strcmpi(st.retAdmissionNumber(),sn)==0)
        {
            found=1;
            if(st.rettoken()==0)
            {
                      cout<<"\n\n\tEnter the book no. ";
                cin>>bn;
                while(fs1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                       if(strcmpi(bk.retBookNo(),bn)==0)
                    {
                        bk.showbook();
                        flag=1;
                        st.addtoken();
                        st.getsBookNo(bk.retBookNo());
                               int pos=-1*sizeof(st);
                        fs.seekp(pos,ios::cur);
                        fs.write((char*)&st,sizeof(student));
                        cout<<"\n\n\t Book issued successfully";
                    }
                    }
                  if(flag==0)
                        cout<<"Book no does not exist";
            }
                else
                  cout<<"You have not returned the last book ";

        }
    }
          if(found==0)
        cout<<"Student record not exist...";
    getch();
      fs.close();
      fs1.close();
}


void bookdeposit()
{
    char sn[10],bn[6];
    int found=0,flag=0,day,fine;

    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The student’s admission no.";
    cin>>sn;
    fs.open("student.txt",ios::in|ios::out);
    fs1.open("book.txt",ios::in|ios::out);
    while(fs.read((char*)&st,sizeof(student)) && found==0)
       {
        if(strcmpi(st.retAdmissionNumber(),sn)==0)
        {
            found=1;
            if(st.rettoken()==1)
            {
            while(fs1.read((char*)&bk,sizeof(book))&& flag==0)
            {
               if(strcmpi(bk.retBookNo(),st.retstBookNo())==0)
            {
                bk.showbook();
                flag=1;
                cout<<"\n\nBook deposited in no. of days";
                cin>>day;
                if(day>15)
                {
                   fine=(day-15)*1;
                   cout<<"\n\nFine has to deposited Rs. "<<fine;
                }
                    st.resettoken();
                    int pos=-1*sizeof(st);
                    fs.seekp(pos,ios::cur);
                    fs.write((char*)&st,sizeof(student));
                    cout<<"\n\n\t Book deposited successfully";
            }
            }
          if(flag==0)
            cout<<"Book no does not exist";
              }
         else
            cout<<"No book is issued..please check!!";
        }
       }
      if(found==0)
    cout<<"Student record not exist...";
    getch();
  fs.close();
  fs1.close();
  }

void start()
{
	system("cls");// it clears the screen
	cout<<"\n\n\n\n\n\t\t\t\tLIBRARY";
	cout<<"\n\t\t\t\tMANAGMENT";
	cout<<"\n\t\t\t\tSYSTEM";
	cout<<"\n\nSubmitted by : Vinayak chachra";
	cout<<"\n\nSubmitted to : Dr.Shelly Mam";
	getch();
}
void adminmenu()
{
	system("cls");
	int ch2;
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1. CREATE STUDENT RECORD";
	cout<<"\n\n\t2. DISPLAY ALL STUDENT RECORD";
	cout<<"\n\n\t3. DISPLAY SPECIFIC STUDENT RECORD";
	cout<<"\n\n\t4. MODIFY STUDENT RECORD";
	cout<<"\n\n\t5. DELETE STUDENT RECORD";
	cout<<"\n\n\t6. CREATE BOOK";
	cout<<"\n\n\t7. DISPLAY ALL BOOKS";
	cout<<"\n\n\t8. DISPLAY SPECIFIC BOOK";
	cout<<"\n\n\t9. MODIFY BOOK RECORD";
	cout<<"\n\n\t10. DELETE DELETE RECORD";
	cout<<"\n\n\t11. BACK TO MAIN MENU";
	cout<<"\n\n\tPlease enter your choice(1-11)";
	cin>>ch2;
	switch(ch2)
	{
	  case 1 :
	  writestudent();
	  break; 
	  case 2 :
	  displayalls();
	  break;
	  case 3 :
	  char num[6];
	  system("cls");
	  cout<<"\n\n\tPlease enter the admission number";
	  displaysps(num);
	  break;
	  case 4 :
	   modifystudent();
	  break;
	  case 5 :
	   deletestudent();
	  break;
	  case 6 :
	   writebook();
	  break; 
	  case 7 :
	   displayallb();
	  break;
	  case 8 :
	  char num1[6];
	  system("cls");
	  cout<<"\n\n\tPlease enter the book number";
	  displayspb(num);
	  break;
	  case 9 :
	   modifybook();
	  break;
	  case 10 :
	   deletebook();
	  break;
	  case 11 :
	  return; // it will go back to main menu

	  default :
	  cout <<"INVALID CHOICE try again";


	}
	
  adminmenu();
}

int main()
{   char ch;
	start();
	do
	{
		system("cls");
		cout<<"\n\n\n\nMAIN MENU";
		cout<<"\n\n\n\n\t1. Book Issue";
		cout<<"\n\n\n\n\t2. Book Deposit";
		cout<<"\n\n\n\n\t3. Administrator Menu";
		cout<<"\n\n\n\n\t4. EXIT";
        ch = getch();
        switch(ch)
        {
        	case '1' :
        	bookissue();
        	break;
        	case '2' :
        	bookdeposit();
        	break;
        	case '3' :
        	adminmenu();
        	break;
        	case '4' :
        	exit(0);
        	break;
        	default :
        	cout<<"invalid choice , TRy again";
        }
	}
	while(ch!=4);	
	return 0;
}