#include <iostream>
#include <string> //string class , c_str() , getline(string)
#include <fstream> //file handling operations
#include <stdio.h> //remove,rename
#include <stdlib.h> //exit()

using namespace std;
class admin
{
    public:
        admin()
        {
            cout<<"\n -------------------- ATTENDANCE MANAGEMENT SYSTEM ------------------";
            cout<<"\n\n----------MADE BY : TANISHQ 2K19/CO/405 & UDAY 2K19/CO/417-----------";
            cout<<"\n\n---------------SUBJECT : OBJECT ORIENTED PROGRAMMING --------------";
            getchar();
        }
        int adminLogin();
        int adminView();
        int registerStudent();
        int deleteStudent();
        int checkListOfStudentsRegistered();
        int checkPresenseCountOfStudent();
};
class student
{
    public:
        int studentLogin();
        int studentView();
        int markMyAttendance(string);
        int countMyAttendance(string);
};
int checkStudentCredentials(string , string );

int admin::adminLogin()
{
cout<<"\n --------- Admin Login --------";

string username;
string password;

cout<<"\n Enter username : ";
cin>>username;
cout<<"\n Enter password : ";
cin>>password;

if(username=="tanishq" && password=="uday")
{
    adminView();
    getchar();
}
else
{
cout<<"\n Error ! Invalid Credintials..";
cout<<"\n Press any key for main menu ";
getchar();getchar();
}

return 0;
}

int admin::adminView()
{
int goBack = 0;
while(1)
{
cout<<"\n 1. Register a Student";
cout<<"\n 2. Delete a student record";
cout<<"\n 3. Check List of Students registered by username";
cout<<"\n 4. Check presence count of student";
cout<<"\n 0. Go Back <- \n";
int choice;

cout<<"\n Enter your choice: ";
cin>>choice;

switch(choice)
{
	case 1: registerStudent();break;
	case 2: deleteStudent(); break;
	case 3: checkListOfStudentsRegistered(); break;
	case 4: checkPresenseCountOfStudent(); break;
	case 0: goBack = 1;break;
    default: cout<<"\n Invalid choice. Enter again ";
    getchar();
}
if(goBack == 1)
break; //break the loop
}
return 0;
}

int admin::registerStudent()
{
    cout<<"\n ----- Form to Register Student ---- \n";

    string name, username, rollno, father, mother;
    char password[100];

    cout<<"\n Enter Name : ";     cin>>name;
    cout<<"\n Enter Username : ";     cin>>username;
    cin.ignore();
    cout<<"\n Enter password : ";     cin.getline(password,100);
    cout<<"\n Enter rollno : ";     cin>>rollno;
    getchar();

    char add[100];
    cout<<"\n Enter address : ";     cin.getline(add, 100);
    cout<<"\n Enter father's name : ";     cin>>father;
    cout<<"\n Enter mother's name : ";     cin>>mother;

    //check if record already exists..
    ifstream read;
    read.open("db.dat");

    if(read)
    {   int recordFound =0;
	    string line;
	    while(getline(read, line))
	    {
    	if(line == username )
    	{
    		recordFound = 1 ;
    	    break;
		}
        }
        if(recordFound == 1)
        {
    	cout<<"\n Username already Registered. Please choose another username ";
    	getchar(); getchar();
    	read.close();
    	return 0;
		}
	}
    read.close();

    ofstream out;
	out.open("db.dat", ios::app);
	out<<username<<"\n";
	out.close();

	ofstream out1;
	string temp = username+".dat";
	out1.open(temp.c_str());
	out1<<"NAME- "<<name<<"\n"; 	out1<<"USERNAME- "<<username<<"\n"; 	out1<<"PASSWORD- "<<password<<"\n";
	out1<<"ROLL NO.- "<<rollno<<"\n"; 	out1<<"ADDRESS- "<<add<<"\n"; 	out1<<"FATHER'S NAME- "<<father<<"\n";
	out1<<"MOTHER'S NAME- "<<mother<<"\n";
	out1.close();

	cout<<"\n Student Registered Successfully !!";

    cout<<"\n Press any key to continue..";
	getchar();getchar();
	return 0;
}

int admin::deleteStudent()
{
    string username;
    cout<<"\n Enter username of the student ";
    cin>>username;

    ifstream read;
    string temp=username+".dat";
    read.open(temp.c_str());
    if(read)
    {
    cout<<"\n Student record has been deleted!";
    read.close();
    remove(temp.c_str());
    }
    else
    	cout<<"invalid username!";
    read.close();


    ifstream fin;
    ofstream fout;

    fin.open("db.dat");
    if(fin)
    {
        fout.open("tempfile.dat");
	    string line;
	    while(getline(fin, line))
	    {
    	    if(line != username )
    	    {
    		    fout<<line;
		    }
		    getline(fin,line);
        }
        fin.close();
        fout.close();
        remove("db.dat");
        rename("tempfile.dat","db.dat");
    }
    fin.close();

    cout<<"\n Press any key to continue..";
    getchar();getchar();
    return 0;
}

int admin::checkListOfStudentsRegistered(){
cout<<"\n - Check List of Students Registered by Username-- ";

//check if record already exist..
ifstream read;
read.open("db.dat");

if(read)
{
    string line;
    while(getline(read, line))
    {
    	cout<<" \n " << line;
    }
    read.close();
}
else
{
cout<<"\n No Record found :(";
}
cout<<"\n Press any key to continue..";
getchar();getchar();
return 0;
}

int admin::checkPresenseCountOfStudent()
{
    string username;
    cout<<"\n Enter username to check Presence count ";
    cin>>username;

    ifstream fin;
    string temp= username+".dat";
    fin.open(temp.c_str());
    if(fin)
    {
        string line;
        int presenceCount=0;
        while(getline(fin,line))
        {
            if(line=="P")
            presenceCount++;
        }
        cout<<"\n Presence count is "<<presenceCount<<endl;
        cout<<"\n press any key to continue..";
        getchar();getchar();
        return 0;
    }
    fin.close();
    return 0;
}


int student::studentLogin()
{
studentView();
return 0;
}

int student::studentView()
{
cout<<"\n ------- Student Login-------- \n";

string username, password;

cout<<"\n Enter username : ";
cin>>username;
cin.ignore();
cout<<"\n Enter password : ";
getline(cin,password);

int res = checkStudentCredentials(username, password);

if(res  == 0)
{
   cout<<"\n Invalid Credentials !!";
   cout<<"\n Press any key for Main Menu..";
   getchar();getchar();
   return 0;
}

int goBack = 0;
while(1)
{

cout<<"\n 1. Mark Attendance for Today ";
cout<<"\n 2. Count my Attendance";
cout<<"\n 0. Go Back <- \n";
int choice;

cout<<"\n Enter your choice: ";
cin>>choice;

switch(choice)
{
	case 1: markMyAttendance(username); break;
	case 2: countMyAttendance(username); break;
	case 0: goBack = 1;break;
    default: cout<<"\n Invalid choice. Enter again ";
    getchar();
}
if(goBack == 1)
break; //break the loop
}
}

int checkStudentCredentials(string username, string password)
{
// read file line by line & check if username exists?
// if it exsist return 1 else 0

ifstream read;
read.open("db.dat");
if(read) {
// The file exists, and is open for input
int recordFound = 0;
string line;
string temp = username ;
while(getline(read, line)) {
	if(line == temp)
	{
		recordFound = 1;
		break;
	}
}

if(recordFound == 0)
    return 0;
else
   return 1;
}
else
{
   return 0;
}

}

int student::markMyAttendance(string username)
{
    ofstream fout;
    string temp= username+".dat";
    fout.open(temp.c_str(),ios::app);
    fout<<"P\n";

    cout<<"\n Your Attendance has been marked for today !!\n";
    cout<<"\n Press any key to continue..";
    getchar();getchar();
    return 0;
}

int student::countMyAttendance(string username)
{
    ifstream fin;
    string temp= username+".dat";
    fin.open(temp.c_str());
    if(fin)
    {
        int presenceCount=0;
        string line;
        while(getline(fin,line))
        {
            if(line=="P")
            presenceCount++;
        }
        cout<<"\n Your attendace count is "<<presenceCount<<endl;
        cout<<"\n Press any key to continue..";
        getchar();getchar();
        return 0;
    }
    fin.close();
    return 0;
}

int main()
{
	admin ADMIN;
	student STUDENT;
while(1)
{
	cout<<"\n Attendance Management System \n";
	cout<<"-------------------------------------\n\n";

	cout<<"1. Admin Login\n";
	cout<<"2. Student Login\n";

	cout<<"0. Exit\n";
	int choice;

	cout<<"\n Enter your choice: ";
	cin>>choice;

	switch(choice)
	{
	case 1: ADMIN.adminLogin(); break;
	case 2: STUDENT.studentLogin(); break;
	case 0:
	        while(1)
	        {
        	cout<<"\n Are you sure you want to exit? y | n \n";
        	char ex;
        	cin>>ex;
        	if(ex == 'y' || ex == 'Y')
        	   exit(0);
        	else if(ex == 'n' || ex == 'N')
             {
             	 break;
             }
             else{
             	cout<<"\n Invalid choice !!!";
             	getchar();
             }

     	   }
            break;

    default: cout<<"\n Invalid choice. Enter again ";
    getchar();
	}

}

return 0;
}