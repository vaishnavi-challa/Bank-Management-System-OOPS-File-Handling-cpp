//*******************************************************
//      HEADER FILES USED IN THE PROJECT
//*******************************************************
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<stdio.h>
#include<conio.h>
using namespace std;

//*******************************************************
//      CLASS USED IN THE PROJECT
//*******************************************************

class Account
{
private:
    int accno;
    char name[50];
    int balance;
    char type;
public:
    void create_account();  //function to create account in the bank by getting data from the user
    void display_account(); //function to display the details of accounts present in the bank
    void modify();  //function to modify the existing account or to add new data
    void deposit(int); //function to deposit some amount into the existing account and update the balance
    void withdraw(int); //function to withdraw amount from the existing account and update the balance
    void report() const;  //function to show data in tabular form
    int retaccno() const;  //function to return account number
    int retbalance() const; //function to return balance amount
    char rettype() const;   //function to return type of account it is
};  //class ends here

//definition of member functions of the class
void Account::create_account()
{
    cout<<"\n\t\tEnter the account number : ";
    cin>>accno;
    cout<<"\n\t\tEnter the name of the account holder : ";
    cin.ignore();
    cin.getline(name,51);
    cout<<"\n\t\tEnter the type of the account (C/S) : ";
    cin>>type;
    type=toupper(type);
    cout<<"\n\t\tEnter the initial amount(>=500/- for Savings and >=1000/- for current account ) : ";
    cin>>balance;
    cout<<"\n\n\t\tACCOUNT CREATED..";
}
void Account::display_account()
{
    cout<<"\n\t\tAccount Number : "<<accno;
    cout<<"\n\t\tAccount Holder Name : "<<name;
    cout<<"\n\t\tType of Account : "<<type;
    cout<<"\n\t\tBalance Amount : "<<balance;
}
void Account::modify()
{
    cout<<"\n\t\tAccount number : "<<accno;
    cout<<"\n\t\tAccount Holder Name : ";
    cin.ignore();
    cin.getline(name,51);
    cout<<"\n\t\tModify type of the account (C/S) : ";
    cin>>type;
    type=toupper(type);
    cout<<"\n\t\tModify the Balance amount) : ";
    cin>>balance;

}
void Account::deposit(int m)
{
    balance+=m;
}
void Account::withdraw(int m)
{
    balance-=m;
}
void Account::report() const
{
    cout<<accno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(10)<<balance<<endl;
}
int Account::retaccno() const
{
    return accno;
}
int Account::retbalance()   const
{
    return balance;
}
char Account::rettype() const
{
    return type;
}

//*******************************************************************
//    DECLARATION OF FUNCTIONS USED FOR DEALING WITH THE DATA FILES
//*******************************************************************

void write_account();   //function to write the account details into a binary file
void display_account(int); //function to display specific account details given by the user
void modify_account(int);  //function to modify the existing details of the account record
void delete_account(int);  //function to delete the record of the file
void display_all(); //function to display all the records of account details
void deposit_withdraw(int, int);    //function to deposit/withdraw amount from the existing Account
void intro();   //introductory screen function

//*******************************************************
//     MAIN FUNCTION OF THE PROJECT
//*******************************************************
int main()
{
    char ch;
    int num;
    system("color E1");
    intro();
    do
    {
        system("cls");
        cout<<"\n\t\tMAIN MENU";
        cout<<"\n\t\t01. CREATE ACCOUNT";
        cout<<"\n\t\t02. DEPOSIT AMOUNT INTO EXISTING ACCOUNT";
        cout<<"\n\t\t03. WITHDRAW AMOUNT FROM EXISTING ACCOUNT";
        cout<<"\n\t\t04. BALANCE ENQUIRY OF EXISTING ACCOUNT";
        cout<<"\n\t\t05. DISPLAY OF ALL ACCOUNT HOLDER LIST IN THE BANK";
        cout<<"\n\t\t06. CLOSE AN EXISTING ACCOUNT";
        cout<<"\n\t\t07. MODIFY AN EXISTING ACCOUNT";
        cout<<"\n\t\t08. EXIT THE PROGRAM";
        cout<<"\n\n\t\tSelect your choice from the above options (1-8) : ";
        cin>>ch;
        system("cls");
        switch(ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout<<"\n\t\tEnter the account No. : ";
            cin>>num;
            deposit_withdraw(num,1);
            break;
        case '3':
            cout<<"\n\t\tEnter the account No. : ";
            cin>>num;
            deposit_withdraw(num,2);
            break;
        case '4':
            cout<<"\n\t\tEnter the account No. : ";
            cin>>num;
            display_account(num);
            break;
        case '5':
            display_all();
            break;
       case '6':
            cout<<"\n\t\tEnter the account No. : ";
            cin>>num;
            delete_account(num);
            break;
        case '7':
            cout<<"\n\t\tEnter the account No. : ";
            cin>>num;
            modify_account(num);
            break;
        case '8':
            cout<<"\n\t\tThanks for using this bank management system";
            break;
        default:
            cout<<"\a";
        }
        cin.ignore();
        cin.get();
        }while(ch!='8');
 return 0;
}

//*******************************************************
//      function to write the account details into a binary file
//*******************************************************
void write_account()
{
    Account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*> (&ac), sizeof(Account));
    outFile.close();
}

//*******************************************************
//      function to display specific account details given by the user
//*******************************************************

void display_account(int n)
{
    Account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile)
    {
        cout<<"File could not open..!! Press any key...";
        return;
    }
    cout<<"\n\t\tBALANCE DETAILS\n";
    while(inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account)))
    {
        if(ac.retaccno() == n)
        {
            ac.display_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\t\tSorry, Account does not exist..if you need you can create new account...";
}

//*******************************************************
//     function to modify the existing details of the account record
//*******************************************************
void modify_account(int n)
{
    bool found=false;
    Account ac;
    fstream File;
    File.open("account.dat",ios::binary | ios::in | ios::out);
    if(!File)
    {
         cout<<"File could not open..!! Press any key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char*> (&ac), sizeof(Account));
        if(ac.retaccno() == n)
        {
            ac.display_account();
            cout<<"\n\t\tEnter the new details of the account "<<endl;
            ac.modify();
            int pos = (-1)*static_cast<int>(sizeof(Account));
            File.seekg(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(Account));
            cout<<"\n\t\tRecord Updated..!!";
            found=true;
        }
    }
    File.close();
    if(found==false)
         cout<<"\n\t\tSorry, Account does not exist..if you need you can create new account...";
}

//*******************************************************
//     function to delete the record of the file
//*******************************************************
void delete_account(int n)
{
    Account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
         cout<<"File could not open..!! Press any key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    int cnt=0;
    while(inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account)))
    {
        if(ac.retaccno()!=n)
        {
            outFile.write(reinterpret_cast<char*> (&ac), sizeof(Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    int s = rename("Temp.dat","account.dat");
    cout<<"\n\t\tAccount deleted..";
    getch();
}

//*******************************************************
//     function to display all the records of account details
//*******************************************************

void display_all()
{
    Account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
         cout<<"File could not open..!! Press any key...";
        return;
    }
    cout<<"\n\t\tAccount Holder list\n\n";
    cout<<"======================================================\n";
    cout<<"A/c no.  NAME                Type    Balance\n";
    cout<<"======================================================\n";
    while(inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account)))
    {
        ac.report();
    }
    inFile.close();
}

//****************************************************************
//      function to deposit/withdraw amount from the existing Account
//****************************************************************

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    Account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if(!File)
    {
         cout<<"File could not open..!! Press any key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char*> (&ac), sizeof(Account));
        if(ac.retaccno()==n)
        {
            ac.display_account();
            if(option==1)
            {
                cout<<"\n\t\tTO DEPOSIT AMOUNT ";
                cout<<"\n\t\tEnter the amount to be deposited : ";
                cin>>amt;
                ac.deposit(amt);
            }
            if(option==2)
            {
              cout<<"\n\t\tTO WITHDRAW AMOUNT ";
                cout<<"\n\t\tEnter the amount to be withdraw : ";
                cin>>amt;
                ac.withdraw(amt);
            }
            int pos = (-1)*static_cast<int>(sizeof(Account));
            File.seekg(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(Account));
            cout<<"\n\t\tRecord Updated..!!";
            found=true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\t\tSorry, Account does not exist..if you need you can create new account...";
}

//*******************************************************
//      introductory screen function
//*******************************************************

void intro()
{
    cout<<"\n\n\n\n\n\n\n\t\t\t\t   BANK";
    cout<<"\n\t\t\t\t\tMANAGEMENT";
    cout<<"\n\n\t\t\t\t\t\tSYSTEM";
    cout<<"\n\n\n\n\t\t\tPress Enter key..To proceed..!!";
    cin.get();
}

//*******************************************************
//      END OF THE PROJECT
//*******************************************************
