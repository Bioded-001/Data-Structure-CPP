#include "project4.h"
void selectpage(string name)//page for user to proceed after choose guest mode
{
    char conti_or_not;
    stack.stack_login();
    do{
        Invalid_sel:
        system("cls");
        string user_s;
        string mavie_name;
        cout<<"Welcome, "<<name<<endl;
        cout<<"..............................M E N U.............................."<<endl;
        cout<<"1. View movies"<<endl;
        /*cout<<"2. Order snack & beverages"<<endl;*/
        cout<<"2. Search movies for Coming Soon"<<endl;
        cout<<"3. Search movies for Now Showing"<<endl;
        cout<<"4. Recommendation"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"\nPlease enter select : ";
        cin>>user_s;
        fflush(stdin);
        if(user_s!="1"&&user_s!="2"&&user_s!="3"&&user_s!="4"&&user_s!="5"&&user_s!="6")
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
            access_movie(false);
        /*else if(user_s=="2")
            access_FnB(false);*/
        else if(user_s=="2")
        {
            cout<<"\nWhat is the movie name you want to search "<<endl;
            getline(cin, mavie_name);
            search_for_cs(mavie_name);//pass movie name
            system("pause");
            system("cls");
        }
        else if(user_s=="3")
        {
            cout<<"\nWhat is the movie name you want to search "<<endl;
            getline(cin, mavie_name);
            search_for_ns(mavie_name);
            system("pause");
            system("cls");
        }
        else if(user_s=="4")
            recommendation();
        else if(user_s=="5")
            goto endloop;
        else
            cout<<"Invalid selection ! Please select again"<<endl;
            system("pause");
            goto Invalid_sel;
        fflush(stdin);
        cout<<"\ndo you want continue guest mode ? [Y/N] :\n";
        cin>>conti_or_not;
        fflush(stdin);
    }while(toupper(conti_or_not)=='Y');
    endloop:;
    stack.stack_logout();
}
void guest()//select guest mode
{
    guest_page:
	string guest_name;
    cout<<"________________________________________________________________"<<endl;
    cout<<"\t\t || THE - J W - CINEMA || \t\t"<<endl;
    cout<<"                        [  GUEST MODE  ]                        "<<endl;
    cout<<"________________________________________________________________"<<endl;
	cout<<"\nPlease enter your guest mode name : ";
    getline(cin, guest_name);
    cout<<"\nLoading..";
    for(int i=0;i<2;i++)
    {
        sleep(1);
        cout<<"..";
    }
    cout<<"\n\n";
    system("cls");
    if(guest_name.empty())//make sure user input is not empty
    {
        cout<<"\nYou did not enter any name."<<endl;
        cout<<"Please try again."<<endl;
        system("pause");
        system("cls");
        goto guest_page;
    }
    else
        selectpage(guest_name);
} 
string home()
{
	string select;
	cout<<"\n==============================================================================================";
    cout<<"\n ||    |||     |||     |||     |||     |||      |||    |||    |||    |||    |||    |||    ||  ";
    cout<<"\n==============================================================================================";
    cout<<"\n       |///////|     The    |////////|                |////////|                |////////|    ";
    cout<<"\n       |///////|            |////////|      J W       |////////|                |////////|    ";
    cout<<"\n       |///////|            |////////|                |////////|     Cinema     |////////|    ";
    cout<<"\n==============================================================================================";
    cout<<"\n ||    |||     |||     |||     |||     |||      |||    |||    |||    |||    |||    |||    ||  ";
    cout<<"\n==============================================================================================";
	cout<<"\nWelcome to The Grandview Cinema"<<endl;
	cout<<"1. Login"<<endl;
    cout<<"2. Register"<<endl;
    cout<<"3. Guest Mode"<<endl;
	cout<<"4. Exit"<<endl;
	cout<<"Please enter your selection number: ";
	cin>>select;
    fflush(stdin);
    if(select!="1"&&select!="2"&&select!="3"&&select!="4"&&select!="@@@@")
    {
        select="0";
    }
    cout<<"\nLoading..";
    for(int i=0;i<2;i++)
    {
        sleep(1);
    	cout<<"..";
	}
	cout<<"\n\n";
	return select;
}
int main()
{
    main_page:
	string select = home();
	system("cls");
    if(select=="1")
        user_login();
    else if(select=="2")
        mem_setdata();
    else if(select=="3")
        guest();
    else if(select=="4")
    {cout<<"System Exit";
            exit(1);}
    else if(select=="@@@@")
        access_admin_mode();
    else
        cout<<"Invalid selection, please enter again";
    system("pause");
    system("cls");
	goto main_page;
}
