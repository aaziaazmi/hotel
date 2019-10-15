#include<fstream.h>
#include<conio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<dos.h>
#include<windows.h>
class hotel //Class declaration
{
	int room_no;
   char fname[30];
   char sname[30];
   char phone[15];
   int dur;
   int no_adult;
   int no_kid;
   char plate[10];
   char note[30];

	public:
   hotel() //Constructor
   {
   	no_kid=no_adult=0;
      strcpy(plate,"N/A");
   	strcpy(note,"N/A");
   }
   int retrno(); //Member function to return the room no
   int retname(char [],char); //Member function to compare name and entered string
   int retdur(); //Member function to return the duration of stay
   void assignroom(int); //Member function to allocate room to new customer
   void add(); //Member function to check in a customer
   void displayall(); //Member function to display all details of a customer
   void display(); //Member function to display only important details of a customer
   void modify(); //Member function to enter the updated details from the user
};
int check(int r)
{
    hotel h;
    int flag=0;
    ifstream fin("Record.dat",ios::binary);
    while(fin.read((char*)&h,sizeof(hotel)))
    {
    	if(h.retrno()==r)
      {
      	flag=1;
         break;
    	}
    }
    fin.close();
    return(flag);
}
int hotel::retrno()
{
	return room_no;
}
void hotel::add()
{
   char ch;
   cout<<"\nFIRST NAME: ";
   gets(fname);
   cout<<"\nSURNAME: ";
   gets(sname);
   cout<<"\nCONTACT DETAILS: ";
   gets(phone);
   cout<<"\nNO. OF ADULTS: ";
   cin>>no_adult;
   cout<<"\nNO. OF CHILDREN (upto 12 years): ";
   cin>>no_kid;
   cout<<"\nDURATION OF STAY (nights): ";
   cin>>dur;
   cout<<"\nVEHICLE (Y/N): ";
   cin>>ch;
   if(ch=='y'||ch=='Y')
   {
      cout<<"\nPLATE NUMBER: ";
      gets(plate);
   }
   cout<<"\nSPECIAL INFORMATION (Y/N): ";
   cin>>ch;
   if(ch=='y'||ch=='Y')
   {
      cout<<"\nNOTES: ";
      gets(note);
   }
   cout<<"\n\n";
   int total;
   int r;
   total=no_adult+no_kid;
   if(!no_kid)
   {
   	if(total==1)
      	cout<<"Check rooms 1001-1010 for 1 Adult";
      else if(total==2)
      	cout<<"Check rooms 1011-1025 for 2 Adults";
      else if(total>2)
      	cout<<"Check rooms 1026-1050 for more than 2 Adults";
   }
   else
   {
   	if(total<=4)
      	cout<<"Check rooms 2001-2035 for a Family of less than 4 persons";
      else
      	cout<<"Check rooms 3001-3010 for a Family of more than 4 persons";
   }
}
void hotel::assignroom(int a)
{
	room_no=a;
}
void checkin()  //Function to write the details of the new customer to the file
{
	ofstream fout("Record.dat",ios::binary|ios::app);
   hotel h;
   clrscr();
   cout<<"\t\t\tCHECK-IN\n\t\t\t********\n";
	cout<<"\nENTER THE CUSTOMER DETAILS => \n";
   cout<<"*****************************\n";
   h.add();
   int flag=1;
   int n;
   for(int i=0;flag==1;++i)
   {
   	cout<<"\n\nROOM CHECK: ";
   	cin>>n;
   	if(check(n)==0)
   	{
   		cout<<"Room "<<n<<" is available";
      	flag=1;
         break;
   	}
   	else
   		cout<<"Room "<<n<<" is not available";
   }
   char ch;
   cout<<"\n\nDo you wish to book Room "<<n<<" ?(Y/N)";
   cin>>ch;
   if(ch=='y'||ch=='Y')
   {
		cout<<"\n\nThe room has been successfully booked.";
   	h.assignroom(n);
		fout.write((char*)&h,sizeof(hotel));
   }
   fout.close();
   cout<<"\n\nPress any key to continue!!";
   getch();
}
void hotel::displayall()
{
   cout<<"\n\nROOM NO: ";
   cout<<room_no;
	cout<<"\nFIRST NAME: ";
   cout<<fname;
	cout<<"\nSURNAME: ";
	cout<<sname;
	cout<<"\nCONTACT DETAILS: ";
	cout<<phone;
	cout<<"\nNO. OF ADULTS: ";
	cout<<no_adult;
	cout<<"\nNO. OF CHILDREN (upto 12 years): ";
	cout<<no_kid;
   cout<<"\nDURATION OF STAY (nights): ";
   cout<<dur;
	cout<<"\nVEHICLE (Y/N): ";
	cout<<plate;
	cout<<"\nSPECIAL INFORMATION: ";
   cout<<note;
}
void hotel::display()
{
   cout<<"\n\nROOM NO: ";
   cout<<room_no;
	cout<<"\nFIRST NAME: ";
   cout<<fname;
	cout<<"\nSURNAME: ";
	cout<<sname;
	cout<<"\nCONTACT DETAILS: ";
	cout<<phone;
   cout<<"\nDURATION OF STAY (nights): ";
   cout<<dur;
}
void searchroom()  //Function to search a customer based on room no
{
	int r,flag=0;
   hotel h;
   clrscr();
   ifstream fin("Record.dat",ios::binary);
   cout<<"Enter the Room No. to be searched => ";
   cin>>r;
   while(fin.read((char*)&h,sizeof(h)))
   {
   	if(h.retrno()==r)
      {
      	h.displayall();
         flag=1;
         break;
      }
   }
   if(!flag)
   	cout<<"\n ROOM NOT FOUND OR VACANT";
   cout<<"\n\nPress any key to continue!!";
   getch();
   fin.close();
}
int hotel::retname(char na[],char ch)
{
	if(ch=='F'||ch=='f')
   	return strcmpi(fname,na);
   else
   	return strcmpi(sname,na);
}
void searchname()  //Function to search a customer based on name
{
	int flag=0;
   char str[30];
   char ch;
   hotel h;
   clrscr();
   ifstream fin("Record.dat",ios::binary);
   cout<<"Do you wish to search by First Name or Last Name ?(F/L) ";
   cin>>ch;
	cout<<"Enter the Name to be searched => ";
   gets(str);
	while(fin.read((char*)&h,sizeof(h)))
   {
   	if(!h.retname(str,ch))
      {
      	h.displayall();
         flag=1;
         cout<<endl<<endl;
      }
   }
   if(!flag)
   	cout<<"\n NAME NOT FOUND";
   cout<<"\n\nPress any key to continue!!";
	getch();
   fin.close();
}
int hotel::retdur()
{
	return dur;
}
void searchtime()  //Function to search a customer based on duration of stay
{
	int r,flag=0;
   hotel h;
   clrscr();
   ifstream fin("Record.dat",ios::binary);
   cout<<"Enter the Duration to be searched => ";
   cin>>r;
   while(fin.read((char*)&h,sizeof(h)))
   {
   	if(h.retdur()==r)
      {
      	h.displayall();
         cout<<endl<<endl;
         flag=1;
      }
   }
   if(!flag)
   	cout<<"\n STAY DURATION NOT FOUND";
   cout<<"\n\nPress any key to continue!!";
   getch();
   fin.close();
}
void hotel::modify()
{
	cout<<"\t\t\tEDIT\n\t\t\t****\n";
	cout<<"\nENTER THE MODIFIED DETAILS => \n";
   cout<<"*****************************\n";
   char ch;
   cout<<"\nFIRST NAME: ";
   gets(fname);
   cout<<"\nSURNAME: ";
   gets(sname);
   cout<<"\nCONTACT DETAILS: ";
   gets(phone);
   cout<<"\nNO. OF ADULTS: ";
   cin>>no_adult;
   cout<<"\nNO. OF CHILDREN (upto 12 years): ";
   cin>>no_kid;
   cout<<"\nDURATION OF STAY (nights): ";
   cin>>dur;
   cout<<"\nVEHICLE (Y/N): ";
   cin>>ch;
   if(ch=='y'||ch=='Y')
   {
      cout<<"\nPLATE NUMBER: ";
      gets(plate);
   }
   else
   	strcpy(plate,"N/A");
   cout<<"\nSPECIAL INFORMATION (Y/N): ";
   cin>>ch;
   if(ch=='y'||ch=='Y')
   {
      cout<<"\nNOTES: ";
      gets(note);
   }
   else
   	strcpy(plate,"N/A");
   cout<<"\n\n";
}
void edit()  //Function to edit a record stored in the file
{
	fstream f("Record.dat",ios::in|ios::out|ios::binary|ios::beg);
   int r,flag=0;
   long pos;
   char ch;
   hotel h;
   clrscr();
   cout<<"Enter the Room No: ";
   cin>>r;
   while(f.read((char*)&h,sizeof(h)))
   {
   	pos=f.tellg();
      if(h.retrno()==r)
   	{
         h.displayall();
         flag=1;
         cout<<endl<<endl;
         cout<<"Do you wish to edit room no. "<<r<<" ?(Y/N) ";
         cin>>ch;
         if(ch=='Y'||ch=='y')
         {
      		h.modify();
         	f.seekp(pos-sizeof(hotel));
         	f.write((char*)&h,sizeof(h));
         	cout<<"\nRecord has been successfully edited";
         	break;
         }
         else
         	break;
      }
   }
   if(!flag)
   	cout<<"\n ROOM NOT FOUND OR VACANT";
   cout<<"\n\nPress any key to continue!!";
   getch();
   f.close();
}
void checkout() //Function to check out a customer
{
	int flag=0;
   char ch;
   int r;
   clrscr();
   ifstream fin("Record.dat",ios::binary|ios::in);
   ofstream fout("Temp.dat",ios::binary|ios::out);
   hotel h;
   cout<<"Enter the Room No: ";
   cin>>r;
   while(fin.read((char*)&h,sizeof(h)))
   {
   	if(h.retrno()==r)
      {
      	h.displayall();
         cout<<"\n\nCHECK-OUT(Y/N): ";
         cin>>ch;
         if(ch=='n'||ch=='N')
         	fout.write((char*)&h,sizeof(h));
         else
         	cout<<"Room No. "<<r<<" has been checked out successfully";
      	flag=1;
      }
      else
       fout.write((char*)&h,sizeof(h));
   }
   fout.close();
   fin.close();
   if(!flag)
   	cout<<"\n ROOM NOT FOUND OR VACANT";
   else
   {
   	remove("Record.dat");
   	rename("Temp.dat","Record.dat");
   }
   cout<<"\n\nPress any key to continue!!";
   getch();
}
void mainmenu();
void all() //Function to display all occupied rooms with customer details
{
	int a=0;
   hotel h;
   clrscr();
   ifstream fin("Record.dat",ios::binary);
   cout<<"LIST OF OCCUPIED ROOMS: ";
   cout<<"\n**********************\n";
   while(fin.read((char*)&h,sizeof(h)))
   {
   	h.displayall();
      a++;
   }
   cout<<"\n\nNo. of Rooms occupied: ";
   cout<<a;
   fin.close();
   cout<<"\n\nPress any key to continue!!";
   getch();
   mainmenu();
}
void mainmenu()  //Function to display main menu and options
{
   clrscr();
	int choice;

  	while(choice!=5)
   {
       clrscr();
       cout<<"\n\t\t\t\t\t*************";
       cout<<"\n\t\t\t\t\t* MAIN MENU *";
       cout<<"\n\t\t\t\t\t*************";
       cout<<"\n\n\n\t\t\t\t1.Customer Check-In";
       cout<<"\n\t\t\t\t2.Customer Search based on Room No.";
       cout<<"\n\t\t\t\t3.Customer Search based on Name";
       cout<<"\n\t\t\t\t4.Customer Search based on Duration of Stay";
       cout<<"\n\t\t\t\t5.Rooms Occupied in Hotel";
       cout<<"\n\t\t\t\t6.Edit Record";
       cout<<"\n\t\t\t\t7.Customer Check-Out";
       cout<<"\n\t\t\t\t8.Exit";
       cout<<"\n\n\t\t\tENTER YOUR CHOICE FROM THE ABOVE MENU (1-8) => ";
       cin>>choice;
       switch(choice)
       {
           case 1: checkin();
                   break;
           case 2: searchroom();
                   break;
           case 3: searchname();
                   break;
           case 4: searchtime();
                   break;
           case 5: all();
                   break;
           case 6: edit();
                   break;
           case 7: checkout();
                   break;
           case 8: clrscr();
           			 sleep(1);
           			 cout<<"\n\n\n\n\n\n\t\t\t\aTHANK YOU FOR USING THE ANUZIA HOTEL MANAGEMENT SYSTEM. HAVE A GREAT DAY!!\n\t\t\t***************************************************************************";
                   sleep(2);
           			 exit(0);
           			 break;
           default:
                   {
                       cout<<"\n\n\t\t\tWrong choice!!!";
                       cout<<"\n\t\t\tPress any key to continue!!";
                       getch();
                   }
      }
   }
}
void main()
{

    system("color 3");
    cout<<"\a\n\t\t\t\t   ~HOTEL~";
    cout<<"\n\n\n\t\t\t****************************";
    cout<<"\n\t\t\t* HOTEL MANAGEMENT PROJECT *";
    cout<<"\n\t\t\t****************************";
    sleep(1);
    cout<<"\n\n\n\n\t\tMade By:";
    cout<<" AAZIA AZMI, ANUJA GOYAL, AND VAISHNAVI KRISHNAN";
    sleep(0.5);
    cout<<"\n\n\n\n\n\t\t\t  Press any key to continue!!";
    getch();
    clrscr();
	mainmenu();

}
