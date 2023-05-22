#include "project3.h"
void view_member()
{
	int i=1;
    string none, f1;
	const int nameWidth = 20;
	ifstream cusfile("members.txt");
  	if( cusfile.fail())
    { 
        cout << "File opening failed.\n";
    }
    else
    {
     	cout<<"\n-----------------------------------------------------------------------------------Member Information-----------------------------------------------------------------------------------"<<endl;     	
     	while(!cusfile.eof())
     	{
            getline(cusfile, cus.mem_name);
            getline(cusfile, cus.mem_phone);
            getline(cusfile, cus.mem_email);
            getline(cusfile, cus.mem_password);
            getline(cusfile, none);
            if(!cusfile.eof())
            {
                f1=cus.mem_password; //copy password string into another name
                int length = f1.size(); //detect the length of password string
                cout<<i<<". Member Name : "<<left<<setw(nameWidth)<<cus.mem_name;
                cout<<"| Member Phone Number : "<<left<<setw(nameWidth)<<cus.mem_phone;
                cout<<"| Member Email : "<<left<<setw(nameWidth)<<cus.mem_email;
                cout<<"| Member Password : "<<f1.at(0);
                for(int j=2;j<length;j++)//count the number of "*" to display according to 
                {                    //length of password excluding first and last character
                    cout<<"*";
                }
                cout<<f1.at(length-1)<<endl;//display the last character of password
                i++;
            }
	    }
    }
    cusfile.close();
}

class Admin_mode : protected Movie_management, protected Food_and_Beverage_management
{
    protected:
	    string Admin_id, Admin_ps, keyin_id, keyin_ps, ac_num, ADM;
	    bool access;
	    fstream Admin_File;
    public:
    Admin_mode()
    {
        fflush(stdin);
    	access= false;
        cout<<"Enter Admin Account Number : ";
        getline(cin,ac_num);
        if(ac_num=="@@@@")
        {
            ADM="SA";
            Admin_File.open("Admin/SuperAdmin.txt", ios::in);
        }
        else
        {
            ADM="A";
            Admin_File.open(("Admin/Admin"+ac_num+".txt").c_str(), ios::in);
        }
        getline(Admin_File, Admin_id);
        getline(Admin_File, Admin_ps);
        if(!Admin_File)
        {
            cout<<"\nInvalid Admin Accout Number\n";
            Admin_File.close();
            goto end;
        }
        Admin_File.close();
        Admin_mode_login();
        end:;
    }
    void Admin_mode_login()
    {
        fflush(stdin);
        system("cls");
        cout<<"\n==============================================================";
        cout<<"\n||                 ADMIN   MODE   LOGIN                     ||";
        cout<<"\n==============================================================";
        cout<<"\nAdmin Mode ID : ";
        getline(cin, keyin_id);
        cout<<"Admin Mode Password : ";
        getline(cin, keyin_ps);
        cout<<"\nLoading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
        access= check();
        system("pause");
        system("cls");
    }
    bool check()
    {
        if(keyin_id!=Admin_id && keyin_ps!=Admin_ps)
        {
            cout<<"\nInvalid ID and Password\n";
            return false;
        }
        else if(keyin_id!=Admin_id && keyin_ps==Admin_ps)
        { 
            cout<<"\nInvalid ID\n";
            return false;
        }
        else if(keyin_id==Admin_id && keyin_ps!=Admin_ps)
        { 
            cout<<"\nInvalid Password\n";
            return false;
        }
        else
        {
            cout<<"\nLogin Successful\n";
            return true;
        }
    }
    bool get_access()
    {
        fflush(stdin);
        return access;
    }
    int Admin_mode_menu()
    {
        stack.stack_login();
        admin_menu:
        fflush(stdin);
        string select;
        cout<<"\n==============================================================";
        cout<<"\n||                  ADMIN   MODE   MENU                     ||";
        cout<<"\n==============================================================";
        cout<<"\n";
        cout<<"1. Add or Delete Movie"<<endl;
        cout<<"2. Add or Delete Food and Beverage"<<endl;
        cout<<"3. View Remaining Food and Beverage"<<endl;
        cout<<"4. View Users Information"<<endl;
        cout<<"5. Remove All Seat Book In System"<<endl;
        cout<<"6. Exit"<<endl;
        if(ADM=="SA")
            cout<<"7. Add New Admin In System"<<endl;
        cout<<"Please enter your selection : ";
        getline(cin, select);
        cout<<"Loading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
		cout<<"\n\n";
        system("cls");
        if(select=="Add or Delete Movie"||select=="add or delete movie"||select=="1")
        {
            add_or_delete_movie();
        }
        else if(select=="Add or Delete Food and Beverage"||select=="add or delete food and beverage"||select=="2")
        {
            add_or_delete_food_and_beverage();
        }
        else if(select=="View Remaining Food and Beverage"||select=="view remaining food and beverage"||select=="3")
        {
            view_remaining_food_and_beverage();
        }
        else if(select=="View Users Information"||select=="view users information"||select=="4")
        {
            view_member();
        }
        else if(select=="Remove All Seat Book In System"||select=="remove all seat book in system"||select=="5")
        {
            remove_all_seat();
        }
        else if(select=="Exit"||select=="exit"||select=="6")
        {
            stack.stack_logout();
            return 0;
        }
        else if(select=="Add New Admin In System"||select=="add new admin in system"||select=="7"&&ADM=="SA")
        {
            Add_New_SA();
        }
        else
        {
            cout<<"\nInvalid selection"<<endl;  
        }
        system("pause");
        system("cls");
        goto admin_menu;
    }
    void Add_New_SA()
    {
        string id, ps, yes;
        cout<<"Please enter new id want to add : ";
        getline(cin, id);
        cout<<"Please enter password of it : ";
        getline(cin, ps);
        cout<<"ID : "<<id<<endl;
        cout<<"PS : "<<ps<<endl;
        cout<<"Do you sure you want to add [yes/no]"<<endl;
        getline(cin, yes);
        transform(yes.begin(), yes.end(), yes.begin(), ::toupper);
        if(yes=="YES")
        {
            string new_num = Add_New_SA(id, ps);
            cout<<"This is the new admin account number  :  "<<new_num<<endl;
        }
    }
    string Add_New_SA(string id, string ps)
    {
        int x;
        string y;
        Admin_File.open("Admin/Admin.txt", ios::in);
        Admin_File>>x;
        Admin_File>>y;
        Admin_File.close();
        Admin_File.open(("Admin/Admin"+y+".txt").c_str(), ios::out);
        Admin_File<<id<<endl<<ps;
        Admin_File.close();
        x++;
        Admin_File.open("Admin/Admin.txt", ios::out);
        Admin_File<<x<<" "<<x;
        Admin_File.close();
        return y;
    }
    ~Admin_mode()
    {
        fflush(stdin);
        if(access)
        {
        	cout<<"\nADMIN MODE LOGIOUT\n";
        	access= false;
	        Admin_id="";
	        Admin_ps="";
	        keyin_id="";
	        keyin_ps="";
		}
    }
};
void access_admin_mode()
{
    Admin_mode *Admin= new Admin_mode;
    if(Admin->get_access())
        Admin->Admin_mode_menu();
    else
        cout<<"\nYou not get access to admin mode\n\n";
    delete Admin;
}
