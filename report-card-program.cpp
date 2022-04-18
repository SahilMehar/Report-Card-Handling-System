//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include<iomanip>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class student
{
    int rollno;
    char name[50];
    int ds_marks,c_marks,m_marks,e_marks,l_marks;
    float per;
    char grade;
    int std;
    void perc()
    {
        per=(ds_marks+c_marks+m_marks+e_marks+l_marks)/5.0;
        if(per>=80)
            grade='A';
        else if(per>=50 && per<80)
            grade='B';
        else if(per>=33 && per<50)
            grade='C';
        else
            grade='F';
    }
public:
    void getdata()
    {
        cout<<"\nEnter the Roll Number Of Student: ";
        cin>>rollno;
        cin.ignore();
        cout<<"\n\nEnter the Name of Student: ";
        gets(name);
        cout<<"\nEnter the marks in Data Structure out of 100 : ";
        cin>>ds_marks;
        cout<<"\nEnter the marks in C++ out of 100 : ";
        cin>>c_marks;
        cout<<"\nEnter the marks in Maths out of 100 : ";
        cin>>m_marks;
        cout<<"\nEnter the marks in Career Skills out of 100 : ";
        cin>>e_marks;
        cout<<"\nEnter the marks in Logic Design out of 100 : ";
        cin>>l_marks;
        perc();
    }

    void showdata()
    {
        cout<<"\nRoll number of student : "<<rollno;
        cout<<"\nName of student : "<<name;
        cout<<"\nMarks in Data Structure : "<<ds_marks;
        cout<<"\nMarks in C++ : "<<c_marks;
        cout<<"\nMarks in Maths : "<<m_marks;
        cout<<"\nMarks in Career Skills : "<<e_marks;
        cout<<"\nMarks in Logic Design :"<<l_marks;
        cout<<"\nPercentage of student is  :"<<setprecision(2)<<per;
        cout<<"\nGrade of student is :"<<grade;
    }

    void show_tabular()
    {
        cout<<rollno<<setw(13)<<name<<setw(11)<<ds_marks<<setw(5)<<c_marks<<setw(5)<<m_marks<<setw(8)<<e_marks<<setw(15)<<l_marks<<setw(12)<<setprecision(3)<<per<<"    "<<grade<<endl;
    }

    int  retrollno()
    {
        return rollno;
    }

};         //class ends here



//***************************************************************
//      global declaration for stream object, object
//****************************************************************

fstream fp;
student st;

//***************************************************************
//      function to write in file
//****************************************************************

void write_student()
{
    fp.open("student.dat",ios::out|ios::app);
    st.getdata();
    fp.write((char*)&st,sizeof(student));
    fp.close();
    cout<<"\n\nStudent record has been created ";
}


//***************************************************************
//      function to read all records from file
//****************************************************************


void display_all()
{
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        st.showdata();
        cout<<"\n\n====================================\n";
    }
    fp.close();
}


//***************************************************************
//      function to read specific record from file
//****************************************************************


void display_sp(int n)
{
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if(st.retrollno()==n)
        {
            st.showdata();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
        cout<<"\n\nRecord does not exist";
}


//***************************************************************
//      function to modify record of file
//****************************************************************


void modify_student()
{
    int no,found=0;
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter the Roll Number of Student";
    cin>>no;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(st.retrollno()==no)
        {
            st.showdata();
            cout<<"\nPlease Enter the new details of student"<<endl;
            st.getdata();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
}


//***************************************************************
//      function to delete record of file
//****************************************************************


void delete_student()
{
    int no;
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter the Roll Number of student you want to DELETE";
    cin>>no;
    fp.open("student.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if(st.retrollno()!=no)
        {
            fp2.write((char*)&st,sizeof(student));
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    cout<<"\n\n\tRecord Deleted ..";
}


//***************************************************************
//      function to display all students grade report
//****************************************************************

void class_result()
{
    fp.open("student.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
        cout<<"\n\n\n Program is closing ....";

    }

    cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
    cout<<"=====================================================================================\n";
    cout<<"Roll No. Name          DS  C++  Maths  Career Skills  Logic Design  %age Grade\n";
    cout<<"=====================================================================================\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
        st.show_tabular();
    }
    fp.close();
}




//***************************************************************
//      function to display result menu
//****************************************************************

void result()
{
    int ans,rno;
    char ch;
    cout<<"\n\n\nRESULT MENU";
    cout<<"\n\n\n1. Class Result\n\n2. Student Report Card\n\n3.Back to Main Menu";
    cout<<"\n\n\nEnter Choice (1/2)? ";
    cin>>ans;
    switch(ans)
    {
    case 1 :
        class_result();
        break;
    case 2 :
    {
        do
        {
            char ans;
            cout<<"\n\nEnter Roll Number Of Student : ";
            cin>>rno;
            display_sp(rno);
            cout<<"\n\nDo you want to See More Result (y/n)?";
            cin>>ans;
        }
        while(ans=='y'||ans=='Y');

        break;
    }
    case 3:
        break;
    default:
        cout<<"\a";
    }
}

//***************************************************************
//      INTRODUCTION FUNCTION
//****************************************************************

void heading()
{
    cout<<"STUDENT";
    cout<<" REPORT CARD";
    cout<<" PROJECT";
    cout<<"\n\nMADE BY : SAHIL MEHAR";
    cout<<"\n\nSECTION : F";
    cout<<"\n\n\nSEM   : III";

}

//***************************************************************
//      ENTRY / EDIT MENU FUNCTION
//****************************************************************
void entry_menu()
{
    char ch2;
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
    cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
    ch2=getche();
    switch(ch2)
    {
    case '1':
        write_student();
        break;
    case '2':
        display_all();
        break;
    case '3':
        int num;
        cout<<"\n\n\tPlease Enter The roll number ";
        cin>>num;
        display_sp(num);
        break;
    case '4':
        modify_student();
        break;
    case '5':
        delete_student();
        break;
    case '6':
        break;
    default:
        cout<<"\a";
        entry_menu();
    }
}


//***************************************************************
//      THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
    char ch;
    heading();
    do
    {
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. RESULT MENU";
        cout<<"\n\n\t02. ENTRY/EDIT MENU";
        cout<<"\n\n\t03. EXIT";
        cout<<"\n\n\tPlease Select Your Option (1-3) ";
        ch=getche();
        switch(ch)
        {
        case '1':
            result();
            break;
        case '2':
            entry_menu();
            break;
        case '3':

        default :
            cout<<"\a";
        }
    }
    while(ch!='3');
}

//***************************************************************
//                      END OF PROJECT
//***************************************************************
