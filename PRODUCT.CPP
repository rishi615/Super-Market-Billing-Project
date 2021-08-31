//                 SUPER MARKET BILLING PROJECT
//================================================================
// HEADER FILES USED IN PROJECT
//================================================================
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<fstream.h>
#include<dos.h>
//================================================================
// CLASS USED IN PROJECT
//================================================================
class product
{
	int pno;
	char name[50];
	float price,qty,tax,dis;
 public:
    void create_product()
      { clrscr();
	cout<<"\nPlease Enter The Product No. of The Product ";
	cin>>pno;
	cout<<"\n\nPlease Enter The Name of The Product ";
	gets(name);
	cout<<"\nPlease Enter The Price of The Product ";
	cin>>price;
	cout<<"\nPlease Enter The Discount (%) ";
	cin>>dis;
      }
    void show_product()
      { clrscr();
	cout<<"\nThe Product No. of The Product : "<<pno;
	cout<<"\nThe Name of The Product : ";
	puts(name);
	cout<<"\nThe Price of The Product : "<<price;
	cout<<"\nDiscount : "<<dis<<"%";
      }
   int retpno()
   {return pno;}
   float retprice()
   {return price;}
   char* retname()
   {return name;}
   int retdis()
   {return dis;}
}; //class ends here
//================================================================
// global declaration for stream object, object
//================================================================
fstream fp;
product pr;
//================================================================
// function to write in file
//================================================================
void write_product()
{  clrscr();
   fp.open("Shop.dat",ios::out|ios::app);
   pr.create_product();
   fp.write((char*)&pr,sizeof(product));
   fp.close();
   cout<<"\n\nThe Product Has Been Created ";

getch();
}
//================================================================
// function to read specific record from file
//================================================================
void display_sp(int n)
{   clrscr();
    int flag=0;
    fp.open("Shop.dat",ios::in|ios::binary);
    while(fp.read((char*)&pr,sizeof(product)))
     {
	if(pr.retpno()==n)
	 {
	  clrscr();
	  pr.show_product();
	  flag=1;
	 }
     }
fp.close();
if(flag==0)
cout<<"\n\nrecord not exist";
getch();
}
//================================================================
// function to modify record of file
//================================================================
void modify_product()
{
	int no,found=0;
	clrscr();
	cout<<"\n\n\tTo Modify ";
	cout<<"\n\n\tPlease Enter The Product No. of The Product";
	cin>>no;
	fp.open("Shop.dat",ios::in|ios::out|ios::binary);
	while(fp.read((char*)&pr,sizeof(product)) && found==0)
	{
	  if(pr.retpno()==no)
	   {
	     pr.show_product();
	     cout<<"\nPlease Enter The New Details of Product"<<endl;
	     pr.create_product();
	     int pos=-1*sizeof(pr);
	     fp.seekp(pos,ios::cur);
	     fp.write((char*)&pr,sizeof(product));
	     cout<<"\n\n\t Record Updated";
	     found=1;
	   }
       }
fp.close();
if(found==0)
cout<<"\n\n Record Not Found ";
getch();
}
//================================================================
// function to delete record of file
//================================================================
void delete_product()
	 {
	  int no;
	  clrscr();
	  cout<<"\n\n\n\tDelete Record";
	  cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
	  cin>>no;
	  fp.open("Shop.dat",ios::in|ios::out|ios::binary);
	  fstream fp2;
	  fp2.open("Temp.dat",ios::out|ios::binary);
	  fp.seekg(0,ios::beg);
	  while(fp.read((char*)&pr,sizeof(product)))
	  {
	    if(pr.retpno()!=no)
	     {
	       fp2.write((char*)&pr,sizeof(product));
	     }
	  }
fp2.close();
fp.close();
remove("Shop.dat");
rename("Temp.dat","Shop.dat");
cout<<"\n\n\tRecord Deleted ..";
getch();
}
//================================================================
// function to display all products price list
//================================================================
void menu()
      {
	clrscr();
	fp.open("Shop.dat",ios::in|ios::binary);
	if(!fp)
	 {
	   cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
	   cout<<"\n\n\n Program is closing .";
	   delay(2000);
	   getch();
	   exit(0);
	 }
       cout<<"\n\n\t\tPRODUCT MENU\n\n";
       for(int i=1;i<=65;i++)
       cout<<char(205);
       cout<<"\nP.NO.\t\tNAME\t\t\tPRICE\n";
       for(i=1;i<=65;i++)
       cout<<char(205);
       cout<<endl;
       while(fp.read((char*)&pr,sizeof(product)))
	{
	 cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	}
fp.close();
}
//================================================================
// function to place order and generating bill for Products
//================================================================
void place_order()
	{ clrscr();
	  int order_arr[50],quan[50],c=0;
	  float amt,damt,total=0;
	  char ch='Y';
	  menu();
	  for(int i=1;i<=65;i++)
	  cout<<char(205);
	  cout<<"\n PLACE YOUR ORDER\n";
	  for(i=1;i<=65;i++)
	  cout<<char(205);
	  do{
	     cout<<"\n\nEnter The Product No. Of The Product : ";
	     cin>>order_arr[c];
	     cout<<"\nQuantity in number : ";
	     cin>>quan[c];
	     c++;
	     cout<<"\nDo You Want To Order Another Product ? (y/n)";
	     cin>>ch;
	    }
	  while(ch=='y' ||ch=='Y');
	    cout<<"\n\nThank You For Placing The Order";
	    getch();
	    clrscr();
	    for(i=1;i<=30;i++)
	    cout<<char(205);
	    cout<<"BILL";
	    for(i=34;i<=75;i++)
	    cout<<char(205);
	    cout<<"\nPr No.\tPr Name\t\tQuantity \tPrice \tAmount \tAmount after discount\n";
	    for(int x=0;x<=c;x++)
	    {
	      fp.open("Shop.dat",ios::in|ios::binary);
	      fp.read((char*)&pr,sizeof(product));
	      while(!fp.eof())
	      {
	       if(pr.retpno()==order_arr[x])
		{
		 amt=pr.retprice()*quan[x];
		 damt=amt-(amt*pr.retdis()/100);
		 cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
		 total+=damt;
		}
	       fp.read((char*)&pr,sizeof(product));
	     }
fp.close();
}
cout<<"\n\n\t\t\t\t\tTOTAL = "<<total<<endl;
for(i=1;i<=77;i++)
cout<<char(205);
getch();
gotoxy (1,2);
}
//================================================================
// SECURITY FUNCTION
//================================================================
void password()
{ char str[7];
 cout<<"\n\n\nEnter Password\t";
 gets(str);
 if(strcmp(str,"rishi10")==0)
 return;
 else
 cout<<"\nUNAUTHORISED ACCESS";
 delay(1500); exit(0);
}
//================================================================
// INTRODUCTION FUNCTION
//================================================================
void intro()
{  clrscr();
   gotoxy(19,9);
   cout<<char(201); //  |-
   for(int i=20;i<=60;i++)
   {
   gotoxy(i,9);
   cout<<char(205); //  =
   }
   cout<<char(187); //  -|
   gotoxy(19,16);
   cout<<char(200); //  |_
   for(i=20;i<=60;i++)
   {
   gotoxy(i,16);
   cout<<char(205);
   }
   cout<<char(188);  //_|
   for(i=10;i<=15;i++)
   {
   gotoxy(19,i);
   cout<<char(186); //||
   }
   for(i=10;i<=15;i++)
   {
   gotoxy(61,i);
   cout<<char(186); //||
   }
   gotoxy(21,10);cout<<"NAME      :  RISHIKESH";
   gotoxy(21,11);cout<<"CLASS     :  XII SCI";
   gotoxy(21,12);cout<<"SCHOOL    :  KENDRIYA VIDYALAYA I.S.P";
   gotoxy(21,13);cout<<"GUIDED BY :  MRS. RACHNA SINGH";
   gotoxy(21,14);cout<<"ROLL NO.  :  32";
   gotoxy(5,24);  cout<<"Press any key to continue";
   getch();
   }
//================================================================
// DETAILS FUNCTION
//================================================================
void details()
{       clrscr() ;
	gotoxy(28,5) ;cout<<" Welcome to Project" ;
	textcolor(RED+BLINK) ; textbackground(WHITE) ;
	gotoxy(22,7) ;cprintf(" SUPER MARKET BILLING PROJECT") ;
	textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
	gotoxy(15,10) ;cout<<"This is the project where you can maintain records" ;
	gotoxy(15,11) ;cout<<"of Products." ;
	gotoxy(15,13) ;cout<<"One member can create products,query about them" ;
	gotoxy(15,14) ;cout<<"modify products,delete products,see list" ;
	gotoxy(15,15) ;cout<<"you can also order them" ;
	gotoxy(27,24) ;cprintf("Press any key to continue") ;
	getch() ;
}
//================================================================
// THE MAIN FUNCTION OF PROGRAM
//================================================================
void main()
{
  clrscr();
  password();
  int i;
  char ch;
  details();
  intro();
  ok:
  clrscr();
  char ch2;
  cout<<"    ";
  for(i=1;i<=35;i++)
  cout<<char(205);
  cout<<"\n\t* MAIN MENU *\n    ";
  for(i=1;i<=35;i++)
  cout<<char(205);
  cout<<"\n\n\t1.CREATE ";
  cout<<"\n\n\t2.QUERY  ";
  cout<<"\n\n\t3.MODIFY ";
  cout<<"\n\n\t4.DELETE ";
  cout<<"\n\n\t5.LIST   ";
  cout<<"\n\n\t6.ORDER  ";
  cout<<"\n\n\t7.HELP   ";
  cout<<"\n\n\t0.EXIT   ";
  cout<<"\n\n\n\tPlease Enter Your Choice (0-7)\n    ";
  for(i=1;i<=35;i++)
  cout<<char(205);
  gotoxy(42,21);
  ch2=getche();
  switch(ch2)
  {
    case '1': write_product();goto ok;
	      break;
    case '2': int num;clrscr();
	      cout<<"\n\n\tPlease Enter The Product No. ";
	      cin>>num;
	      display_sp(num);  goto ok;break;
    case '3': modify_product();  goto ok;
	      break;
    case '4': delete_product();   goto ok;
	      break;
    case '5': menu();
	      for(i=1;i<=65;i++)
	      cout<<char(205);
	      getch(); goto ok;
	      break;
    case '6': place_order(); goto ok;
	      break;
    case '7': details();goto ok;
	      goto ok;
    case '0': exit(0);
    default : goto ok;
  }
}
//================================================================
// END OF PROJECT
//================================================================
//1r1i1s1h1i1
