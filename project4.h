#include "project3.h"
// Member structure

void view_member() {
    int i = 1;
    const int nameWidth = 20;
    
    LinkedQueue memberQueue; // Create a LinkedQueue object to store member information
    readMembersFromFile(memberQueue); // Read member information from the file and populate the queue
    
    // Display the member information from the queue
    if (memberQueue.isEmpty()) {
        cout << "No member information available." << endl;
    } else {
        cout << "-----------------------------------------------------------------------------------Member Information-----------------------------------------------------------------------------------" << endl;
        
        while (!memberQueue.isEmpty()) {
            Member_st* member = memberQueue.getFront();
            cout << i << ". Member Name : " << left << setw(nameWidth) << member->mem_name;
            cout << "| Member Phone Number : " << left << setw(nameWidth) << member->mem_phone;
            cout << "| Member Email : " << left << setw(nameWidth) << member->mem_email;
            cout << "| Member Password : " << "********" << endl;
            memberQueue.dequeue();
            i++;
        }
    }
}




class Admin_mode : protected Movie_management//, protected Food_and_Beverage_management
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
        /*cout<<"2. Add or Delete Food and Beverage"<<endl;
        cout<<"3. View Remaining Food and Beverage"<<endl;*/
        cout<<"2. View Users Information"<<endl;
        cout<<"3. Remove Seat Book In Movie"<<endl;
        cout<<"4. Exit"<<endl;
        if(ADM=="SA")
            cout<<"5. Add New Admin In System"<<endl;
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
        /*else if(select=="Add or Delete Food and Beverage"||select=="add or delete food and beverage"||select=="2")
        {
            add_or_delete_food_and_beverage();
        }
        else if(select=="View Remaining Food and Beverage"||select=="view remaining food and beverage"||select=="3")
        {
            view_remaining_food_and_beverage();
        }*/
        else if(select=="View Users Information"||select=="view users information"||select=="2")
        {
            view_member();
        }
        else if(select=="Remove Seat Book In Movie"||select=="remove seat book in movie"||select=="3")
        {
            remove_seat();
        }
        else if(select=="Exit"||select=="exit"||select=="4")
        {
            stack.stack_logout();
            return 0;
        }
        else if(select=="Add New Admin In System"||select=="add new admin in system"||select=="5"&&ADM=="SA")
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
   string Add_New_SA(string id, string ps) {
        int adminNum;
        string y;

        Admin_File.open("Admin/Admin.txt", ios::in);
        Admin_File >> adminNum;
        Admin_File >> y;
        Admin_File.close();

        Admin_File.open(("Admin/Admin" + y + ".txt").c_str(), ios::out);
        Admin_File << id << endl << ps;
        Admin_File.close();

        adminNum++;
        Admin_File.open("Admin/Admin.txt", ios::out);
        Admin_File << adminNum << " " << adminNum;
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
