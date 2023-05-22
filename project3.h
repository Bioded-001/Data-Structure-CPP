#include "project2.h"
class Member
{
	private:
	string mem_name, mem_email, mem_password, mem_phone, log_name;
    bool access;
//	fstream cusfile;
    public:
    Member()
    {
    	access = false;
	}
    void login()//login page
    {
        login_pa:
        int mem_status=0;
        string none;
        string login_c;
        string log_password, log_phone;
        system("cls");
        cout<<"________________________________________________________________"<<endl;
        cout<<"\t\t || THE - J W - CINEMA || \t\t"<<endl;
        cout<<"                          [  LOGIN  ]                           "<<endl;
        cout<<"________________________________________________________________"<<endl;
        cout<<"Login by : "<<endl;
        cout<<"1. Name "<<endl;
        cout<<"2. Phone number "<<endl;
        cout<<"\nPlease enter your choice : ";
        getline(cin, login_c);
        if(login_c=="1")
        {
            cout<<"\nPlease enter your member name : ";
            getline(cin,log_name);
            cout<<"\nPlease enter password : ";
            getline(cin,log_password);
        }
        else if(login_c=="2")
        {
            cout<<"\nPlease enter your member phone number : ";
            getline(cin,log_phone);
            cout<<"\nPlease enter password : ";
            getline(cin,log_password);
        }
        else
        {
            cout<<"Sorry, this is an invalid option. Please try again. "<<endl;
            system("pause");
            goto login_pa;
        }
        cout<<"\nLoading..";
        for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
        cout<<"\n\n";
        fstream cusfile("members.txt", ios::in);
        if(cusfile.fail())
        { 
            cout <<"File opening failed.\n";
        }
        else
        {
            while(!cusfile.eof())
            {
                getline(cusfile, mem_name);
                getline(cusfile, mem_phone);
                getline(cusfile, mem_email);
                getline(cusfile, mem_password);
                getline(cusfile, none);
                if(cusfile.eof())
                    break;
                if((log_phone== mem_phone||log_name==mem_name)&&log_password==mem_password)
                {
                    log_name=mem_name; //to display name when successful log in
                    mem_status=1;
                    break;
                }
                else if((log_phone== mem_phone||log_name==mem_name)&&log_password!= mem_password)
                {
                    mem_status=2;
                    break;
                }
            }  
        }  
        cusfile.close();
        if(mem_status==1)
        {
            mem_status=1;
            cout << "\nLogin successful." <<endl;
            cout << "Welcome, "<<log_name<<endl;
            access=true;
        }
        else if(mem_status==2)
        {
            mem_status=2;
            cout << "\nSorry, password entered is wrong. " <<endl;
        }
        else
        {
            mem_status=0;
            cout<<"\nSorry, member not found. " <<endl;
        }
        system("pause");
        system("cls");
    }
    bool get_access()
    {
        return access;
    }
    void user_select_menu()
    {
        char conti_or_not;
        stack.stack_login();
        bool data_edit = true;
        do{
            Invalid_sel:
            system("cls");
            string user_s;
            string mavie_name;
            cout<<"Welcome, "<<log_name<<endl;
            cout<<"..............................M E N U.............................."<<endl;
            cout<<"1. View movies"<<endl;
            cout<<"2. Order snack & beverages"<<endl;
            cout<<"3. Search movies for Coming Soon"<<endl;
            cout<<"4. Search movies for Now Showing"<<endl;
            cout<<"5. Edit Personal Detail"<<endl;
            cout<<"6. Recommendation"<<endl;
            cout<<"7. Exit"<<endl;
            cout<<"\nPlease enter select : ";
            cin>>user_s;
            fflush(stdin);
            if(user_s!="1"&&user_s!="2"&&user_s!="3"&&user_s!="4"&&user_s!="5"&&user_s!="6"&&user_s!="7")
            {
                user_s="0";
            }
            cout<<"\nLoading..";
            for(int i=0;i<2;i++)
            {
                sleep(1);
                cout<<"..";
            }
            cout<<"\n\n";
            system("cls");
            if(user_s=="1")
                access_movie(true);
            else if(user_s=="2")
                access_FnB(true);
            else if(user_s=="3")
            {
                cout<<"\nWhat is the movie name you want to search "<<endl;
                getline(cin, mavie_name);
                search_for_cs(mavie_name);//pass movie name
                system("pause");
                system("cls");
            }
            else if(user_s=="4")
            {
                cout<<"\nWhat is the movie name you want to search "<<endl;
                getline(cin, mavie_name);
                search_for_ns(mavie_name);//pass movie name
                system("pause");
                system("cls");
            }
            else if(user_s=="5")
            {
                if(data_edit)
                    {
                        data_edit = edit_member();
                    }    
                    else
                    {
                        cout<<"\nUser, you just edited your Personal Detail recently.\n";
                        cout<<"\nYou can only edit your data next time you login.\n";
                    }
            }
            else if(user_s=="6")
                recommendation();
            else if(user_s=="7")
                goto endloop;
            else
                cout<<"Invalid selection ! Please select again"<<endl;
                system("pause");
                goto Invalid_sel;
            cout<<"\ndo you want continue user mode ? [Y/N]:\n";
            cin>>conti_or_not;
            fflush(stdin);
        }while(toupper(conti_or_not)=='Y');
        endloop:;
        stack.stack_logout();
    }
    bool edit_member()
    {
        bool change=false;
        string name, phone, email, password, none;
        do{
            cout<<"----------------Edit Member Information----------------"<<endl;
            //key in old information
            cout<<"Please enter your old member name : ";
            getline(cin, mem_name);
            if(log_name!=mem_name)
            {
                cout<<"\nThis is not you own member name!!\n";
                cout<<"\nPlease Enter your own member name!!\n";
                system("pause");
                system("cls");
            }
        }while(log_name!=mem_name);
        cout<<"Please enter your old member phone number : ";
        getline(cin, mem_phone);
        cout<<"Please enter your old member email : ";
        getline(cin, mem_email);
        cout<<"Please enter your old member password : ";
        getline(cin, mem_password);
        ifstream cusfile("members.txt"); //Read from original member file
        ofstream temcusfile("temporary.txt"); //Temporary file to act as a new file
        if(!cusfile || !temcusfile)
        {
            cout << "Error in opening files" << endl;
        }
        else
        {
            while(!cusfile.eof())//read original member file and get data
            {
                getline(cusfile, name);
                getline(cusfile, phone);
                getline(cusfile, email);
                getline(cusfile, password);
                getline(cusfile, none);
                if(cusfile.eof()&&(mem_name!=name||mem_phone!=phone||mem_email!=email||mem_password!=password))
                {
                    break;
                }
                if(!cusfile.eof()&&mem_name==name&&mem_phone==phone&&mem_email==email&&mem_password==password)
                {   //check and file which data to replace
                    //key in new information
                    cout<<"\nPlease enter your new member name : ";
                    getline(cin,name);
                    cout<<"Please enter your new member phone number : ";
                    getline(cin, phone);
                    cout<<"Please enter your new member email : ";
                    getline(cin,email);
                    cout<<"Please enter your new member password : ";
                    getline(cin, password);
                    log_name = name;
                    change=true;
                }
                temcusfile<<name<<endl<<phone<<endl<<email<<endl<<password<<endl<<endl;//write new data into new temporary file 
            }
        }
        cusfile.close();
        temcusfile.close();
        if(change)
        {
            int result = remove("members.txt");//delete original member file
            if(result==0)
            {//delete successfully
                cout<<"\nDeleting old data.";         
            }
            else
            {//delete failed
                cout<<"\nEdit was uncomplete. Errors occur.";
            }
            int re_name = rename("temporary.txt", "members.txt");
            if(re_name==0)//rename new temporary file to same as original member file
            {//rename successful
                cout<<"\nNew data inserted. Edit successful. ";
            }
            else
            {//rename failed
                cout<<"\nEdit was uncomplete. New data was not inserted. ";
            }
        }
        else
        {
            cout <<"This are wrong old member information" << endl;
            remove("temporary.txt");
        }
        fflush(stdin);
        system("pause");
        system("cls");
        return false;
    }
    ~Member()
    {
    	if(access)
    		cout<<"\nlog out ";
    	access = false;
	}
    friend void view_member();
    friend void mem_setdata();
}cus;
void user_login()
{
    Member *user= new Member;
    user->login();
    if(user->get_access())
        user->user_select_menu();
    else
        cout<<"\n\nLogin failed\n\n";
    delete user;
}
void mem_setdata()//register as member
{
	system("cls");
	fflush(stdin);
	cout<<"\n \" The J W Cinema -- Your first choice cinema \" "<<endl;
	cout<<"\n   ~ Welcome to join us as a member ! ~ "<<endl;
	cout<<"\n----------------[  Member Registration Form  ]----------------"<<endl;
    cout<<"\n   if want return to home page enter @@@@ "<<endl;
	na_back:
    cout<<"\nYour name : ";
	getline(cin,cus.mem_name);
    if(cus.mem_name=="@@@@")
    {
        goto end_re;
    }
    if((cus.mem_name).empty())
    {
        cout<<"\nYou must enter the user name for register";
        goto na_back;
    }
    ph_back:
	cout<<"\nYour phone number : ";
    getline(cin,cus.mem_phone);
    if(cus.mem_phone=="@@@@")
    {
        goto end_re;
    }
    if((cus.mem_phone).empty())
    {
        cout<<"\nYou must enter the phone number for register";
        goto ph_back;
    }
    em_back:
	cout<<"\nYour email : ";
	getline(cin,cus.mem_email);
    if(cus.mem_email=="@@@@")
    {
        goto end_re;
    }
    if((cus.mem_email).empty())
    {
        cout<<"\nYou must enter the your email for register";
        goto em_back;
    }
    pa_back:
	cout<<"\nPlease create a password for your account : ";
	getline(cin,cus.mem_password);
    if(cus.mem_password=="@@@@")
    {
        goto end_re;
    }
    if((cus.mem_password).empty())
    {
        cout<<"\nYou must enter the your account password for register";
        goto pa_back;
    }
	if(!(cus.mem_name).empty()&&!(cus.mem_phone).empty()&&!(cus.mem_email).empty()&&!(cus.mem_password).empty())
	{
		fstream cusfile("members.txt", ios::app);
	    if(cusfile.fail())
	    {
	        cout<<"Failed to open file."<<endl; 
	    }
	    else
	    {
			cusfile<<cus.mem_name<<endl<<cus.mem_phone<<endl<<cus.mem_email<<endl<<cus.mem_password<<endl<<endl;
	        cout<<"\n\nResgister successful! "<<endl;
		}
	    cusfile.close();
	}
    end_re:;
}
