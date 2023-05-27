#include "algo.h"

const float ticket_price_A=19, ticket_price_C=12, ticket_price_Co=42, ticket_price_OKU=8; // ticket_price
const string seat_id_a[10]= {"A01", "A02", "A03", "A04", "A05", "A06", "A07", "A08", "A09", "A10"};
const string seat_id_b[10]= {"B01", "B02", "B03", "B04", "B05", "B06", "B07", "B08", "B09", "B10"};
const string seat_id_c[10]= {"C01", "C02", "C03", "C04", "C05", "C06", "C07", "C08", "C09", "C10"};
const string seat_id_d[10]= {"D01", "D02", "D03", "D04", "D05", "D06", "D07", "D08", "D09", "D10"};
const string seat_id_couple[4]= {"E01&E02", "E03&E04", "E05&E06", "E07&E08"};
const string seat_id_oku[2]={"E09", "E10"};

struct movies{
	string mv_name;
};
class Movie_management
{
    protected:
    	fstream movies_file;
        string movie_name;
    public:
    void add_or_delete_movie()
    {
        fflush(stdin);
        string select;
        cout<<"\n==============================================================";
        cout<<"\n||                  Add or Delete Movie                     ||";
        cout<<"\n==============================================================";
        cout<<"\n";
        cout<<"1. Add Coming Soon Movie"<<endl;
        cout<<"2. Add Now Showing Movie"<<endl;
        cout<<"3. Delete Coming Soon Movie"<<endl;
        cout<<"4. Delete Now Showing Movie"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"Please enter your selection : ";
        getline(cin, select);
        cout<<"\nLoading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
		cout<<"\n\n";
		system("pause");
        system("cls");
        if(select=="Add Coming Soon Movie"||select=="add coming soon movie"||select=="1")
        {
            add_coming_soon_movie();
        }
        else if(select=="Add Now Showing Movie"||select=="add now showing movie"||select=="2")
        {
            add_now_showing_movie();
        }
        else if(select=="Delete Coming Soon Movie"||select=="delete coming soon movie"||select=="3")
        {
            delete_coming_soon_movie();
        }
        else if(select=="Delete Now Showing Movie"||select=="delete now showing movie"||select=="4")
        {
            delete_now_showing_movie();
        }
        else if(select=="Exit"||select=="exit"||select=="5")
        {}
        else
        {
            cout<<"\nInvalid selection"<<endl;
        }
    }
    void remove_all_seat()
    {
        movies_file.open("Now Showing Movie Name.txt", ios::in);
        while(!movies_file.eof())
        {
            getline(movies_file, movie_name);
            fstream morning(("movie storage/Seat/"+movie_name+"/Morning "+movie_name+".txt").c_str(), ios::out);
            fstream afternoon(("movie storage/Seat/"+movie_name+"/Afternoon "+movie_name+".txt").c_str(), ios::out);
            fstream night(("movie storage/Seat/"+movie_name+"/Night "+movie_name+".txt").c_str(), ios::out);
            morning.close();
            afternoon.close();
            night.close();
        }
        movies_file.close();
        cout<<"Remove all seat in system successful\n";
    }
    void add_coming_soon_movie()
    {
        add_cs_movie:
        fflush(stdin);
        string enter_content;
        int total_line;
        cout<<"\n==============================================================";
        cout<<"\n||                   Add Coming Soon Movie                  ||";
        cout<<"\n==============================================================";
        cout<<"\n";
        cout<<"Please enter the movie name want to add : ";
        getline(cin, movie_name);
        cout<<"\nLoading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
		cout<<"\n\n";
		system("pause");
        bool Searching = movie_searching("Coming Soon Movie Name.txt", "movie storage/Coming Soon/", movie_name);
        if(!Searching)
        {
            bool continue_add_in;
            movies_file.open("Coming Soon Movie Name.txt", ios::app);
            if(movies_file)
            {
                cout<<"movie name add in Successful"<<endl;
                movies_file<<endl<<movie_name;
                continue_add_in = true;
            }
            else
            {
                cout<<"movie name add in failed"<<endl;
                continue_add_in = false; 
            }
            movies_file.close();
            sleep(1);
            if(continue_add_in)
            {
                movies_file.open(("movie storage/Coming Soon/" + movie_name + ".txt").c_str(), ios::out);
                if(movies_file)
                {
                    cout<<"movie slot add in Successful"<<endl;
                    movies_file<<"Movie Name     - "<<movie_name<<endl;
                    cout<<"Enter the Release Date : ";
                    getline(cin, enter_content);
                    movies_file<<"Release Date   - "<<enter_content<<endl;
                    cout<<"Enter the Genre : ";
                    getline(cin, enter_content);
                    movies_file<<"Genre          - "<<enter_content<<endl;
                    cout<<"Enter the Running Time : ";
                    getline(cin, enter_content);
                    movies_file<<"Running Time   - "<<enter_content<<endl;
                    cout<<"Enter the Classification : ";
                    getline(cin, enter_content);
                    movies_file<<"Classification - "<<enter_content<<endl;
                    cout<<"Please enter the line of Synopsis want to add : ";
                    cin>>total_line;
                    fflush(stdin);
                    cout<<"Enter the Synopsis line 1 : ";
                    getline(cin, enter_content);
                    movies_file<<"Synopsis       - "<<enter_content;
                    for (int synopsis_line = 1; synopsis_line < total_line; synopsis_line++)
                    {
                        cout<<"Enter the Synopsis line "<<synopsis_line+1<<" : ";
                        getline(cin, enter_content);
                        movies_file<<"\n                 "<<enter_content;
                    }
                }
                else
                {
                    cout<<"movie slot add in failed"<<endl; 
                }
                movies_file.close();
            }
            else
            {
                cout<<"movie slot add in failed"<<endl; 
            }
        }
        else
        {
            cout<<endl<<"This movie already in coming soon slot"<<endl;
        }
        sleep(1);
        char sel;
        cout<<"\ndo you need continue add ? [Y/N] ";
        cin>>sel;
        sleep(1);
        system("cls");
        if(sel=='Y'||sel=='y')
            goto add_cs_movie;
    }
    void add_now_showing_movie()
    {
        add_ns_movie:
        fstream movies_ticket_file;
        fflush(stdin);
        string enter_content;
        int total_line;
        cout<<"\n==============================================================";
        cout<<"\n||                  Add Now Showing Movie                   ||";
        cout<<"\n==============================================================";
        cout<<"\n";
        cout<<"Please enter the movie name want to add : ";
        getline(cin, movie_name);
        cout<<"\nLoading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
		cout<<"\n\n";
		system("pause");
        bool Searching = movie_searching("Now Showing Movie Name.txt", "movie storage/Now Showing/", movie_name);
        if(!Searching)
        {
            bool continue_add_in;
            movies_file.open("Now Showing Movie Name.txt", ios::app);
            if(movies_file)
            {
                cout<<"movie name add in Successful"<<endl;
                movies_file<<endl<<movie_name;
                continue_add_in = true;
            }
            else
            {
                cout<<"movie name add in failed"<<endl;
                continue_add_in = false; 
            }
            movies_file.close();
            sleep(1);
            if(continue_add_in)
            {
                movies_file.open(("movie storage/Now Showing/" + movie_name + ".txt").c_str(), ios::out);
                if(movies_file)
                {
                    cout<<"movie slot add in Successful"<<endl;
                    movies_file<<"Movie Name     - "<<movie_name<<endl;
                    cout<<"Enter the Genre : ";
                    getline(cin, enter_content);
                    movies_file<<"Genre          - "<<enter_content<<endl;
                    cout<<"Enter the Running Time : ";
                    getline(cin, enter_content);
                    movies_file<<"Running Time   - "<<enter_content<<endl;
                    cout<<"Enter the Classification : ";
                    getline(cin, enter_content);
                    movies_file<<"Classification - "<<enter_content<<endl;
                    cout<<"Please enter the line of Synopsis want to add : ";
                    cin>>total_line;
                    fflush(stdin);
                    cout<<"Enter the Synopsis line 1 : ";
                    getline(cin, enter_content);
                    movies_file<<"Synopsis       - "<<enter_content;
                    for (int synopsis_line = 1; synopsis_line < total_line; synopsis_line++)
                    {
                        cout<<"Enter the Synopsis line "<<synopsis_line+1<<" : ";
                        getline(cin, enter_content);
                        movies_file<<"\n                 "<<enter_content;
                    }
                    movies_ticket_file.open(("movie storage/Seat/"+movie_name+"/Morning "+movie_name+".txt").c_str(), ios::out);
                    movies_ticket_file.close();
                    movies_ticket_file.open(("movie storage/Seat/"+movie_name+"/Afternoon "+movie_name+".txt").c_str(), ios::out);
                    movies_ticket_file.close();
                    movies_ticket_file.open(("movie storage/Seat/"+movie_name+"/Night "+movie_name+".txt").c_str(), ios::out);
                    movies_ticket_file.close();
                }
                else
                {
                    cout<<"movie slot add in failed"<<endl; 
                }
                movies_file.close();
            }
            else
            {
                cout<<"movie slot add in failed"<<endl; 
            }
        }
        else
        {
            cout<<endl<<"This movie already in now showing slot"<<endl;
        }
        sleep(1);
        char sel;
        cout<<"\ndo you need continue add ? [Y/N] ";
        cin>>sel;
        sleep(1);
        system("cls");
        if(sel=='Y'||sel=='y')
            goto add_ns_movie;
    }
    void delete_coming_soon_movie()
    {
        delete_cs_movie:
        fflush(stdin);
    	string movie_name_in_txt;
    	fstream new_movies_file;
        cout<<"\n==============================================================";
        cout<<"\n||                 Delete Coming Soon Movie                 ||";
        cout<<"\n==============================================================";
        cout<<"\n";
        cout<<"Please enter the movie name want to delete : ";
        getline(cin,movie_name);
        cout<<"\nLoading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
		cout<<"\n\n";
		system("pause");
        bool Searching = movie_searching("Coming Soon Movie Name.txt", "movie storage/Coming Soon/", movie_name);
        if(Searching)
        {
        	movies_file.open("Coming Soon Movie Name.txt", ios::in);
        	new_movies_file.open("new Coming Soon Movie Name.txt", ios::out);
        	getline(movies_file, movie_name_in_txt);
        	if(movie_name != movie_name_in_txt)
            {
                new_movies_file<<movie_name_in_txt;
            }
			while(!movies_file.eof())
			{
				getline(movies_file, movie_name_in_txt);
        		if(movie_name != movie_name_in_txt)
                {
                    new_movies_file<<endl<<movie_name_in_txt;
                }
			}
            movies_file.close();
            new_movies_file.close();
			remove("Coming Soon Movie Name.txt");
			rename("new Coming Soon Movie Name.txt", "Coming Soon Movie Name.txt");
            cout<<"movie name delete Successful"<<endl;
            sleep(1);
            remove(("movie storage/Coming Soon/" + movie_name + ".txt").c_str());
            cout<<"movie slot delete Successful"<<endl;
        }
        else
        {
            cout<<"This movie has not in movie storage"<<endl;
            sleep(1);
            cout<<"movie name delete failed"<<endl;
            cout<<"movie slot delete failed"<<endl;
        }
        sleep(1);
        char sel;
        cout<<"\ndo you need continue delete ? [Y/N] ";
        cin>>sel;
        sleep(1);
        system("cls");
        if(sel=='Y'||sel=='y')
            goto delete_cs_movie;
    }
    void delete_now_showing_movie()
    {
        delete_ns_movie:
        fflush(stdin);
    	string movie_name_in_txt;
    	fstream new_movies_file;
        cout<<"\n==============================================================";
        cout<<"\n||                  Delete Now Showing Movie                ||";
        cout<<"\n==============================================================";
        cout<<"\n";
        cout<<"Please enter the movie name want to delete : ";
        getline(cin,movie_name);
        cout<<"\nLoading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
		cout<<"\n\n";
		system("pause");
        bool Searching = movie_searching("Now Showing Movie Name.txt", "movie storage/Now Showing/", movie_name);
        if(Searching)
        {
        	movies_file.open("Now Showing Movie Name.txt", ios::in);
        	new_movies_file.open("new Now Showing Movie Name.txt", ios::out);
        	getline(movies_file, movie_name_in_txt);
        	if(movie_name != movie_name_in_txt)
            {
                new_movies_file<<movie_name_in_txt;
            }
			while(!movies_file.eof())
			{
				getline(movies_file, movie_name_in_txt);
        		if(movie_name != movie_name_in_txt)
                {
                    new_movies_file<<endl<<movie_name_in_txt;
                }
			}
            movies_file.close();
            new_movies_file.close();
			remove("Now Showing Movie Name.txt");
			rename("new Now Showing Movie Name.txt", "Now Showing Movie Name.txt");
            cout<<"movie name delete Successful"<<endl;
            sleep(1);
            remove(("movie storage/Now Showing/" + movie_name + ".txt").c_str());
            remove(("movie storage/Seat/"+movie_name+"/Morning "+movie_name+".txt").c_str());
            remove(("movie storage/Seat/"+movie_name+"/Afternoon "+movie_name+".txt").c_str());
            remove(("movie storage/Seat/"+movie_name+"/Night "+movie_name+".txt").c_str());
            cout<<"movie slot delete Successful"<<endl;
        }
        else
        {
            cout<<"This movie has not in movie storage"<<endl;
            sleep(1);
            cout<<"movie name delete failed"<<endl;
            cout<<"movie slot delete failed"<<endl;
        }
        sleep(1);
        char sel;
        cout<<"\ndo you need continue delete ? [Y/N] ";
        cin>>sel;
        sleep(1);
        system("cls");
        if(sel=='Y'||sel=='y')
            goto delete_ns_movie;
    }
};/*
class Food_and_Beverage_management
{
    protected:
    	fstream food_and_beverage_File;
        string FnB_name, none;
        float price;
        int remaining;
    public:
    void add_or_delete_food_and_beverage()
    {
        fflush(stdin);
        string select;
        cout<<"\n==============================================================";
        cout<<"\n||             Add or Delete Food and Beverage              ||";
        cout<<"\n==============================================================";
        cout<<"\n";
        cout<<"1. Adding Food and Beverage to Full"<<endl;
        cout<<"2. Add New Food and Beverage"<<endl;
        cout<<"3. Delete Food and Beverage"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Please enter your selection : ";
        getline(cin, select);
        cout<<"\nLoading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
		cout<<"\n\n";
		system("pause");
        system("cls");
        if(select=="Adding Food and Beverage to Full"||select=="adding food and beverage to full"||select=="1")
        {
            adding_food_and_beverage_to_full();
        }
        else if(select=="Add New Food and Beverage"||select=="add new food and beverage"||select=="2")
        {
            add_new_food_and_beverage();
        }
        else if(select=="Delete Food and Beverage"||select=="delete food and beverage"||select=="3")
        {
            delete_food_and_beverage();
        }
        else if(select=="Exit"||select=="exit"||select=="4")
        {}
        else
        {
            cout<<"\nInvalid selection"<<endl;
        }
    }
    void adding_food_and_beverage_to_full()
    {
        fflush(stdin);
        cout<<"\n==============================================================";
        cout<<"\n||            Adding Food and Beverage to Full              ||";
        cout<<"\n==============================================================";
        cout<<"\n";
        food_and_beverage_File.open("FnB.txt", ios::in);
        fstream new_food_and_beverage_File("newFnB.txt", ios::out);
        do{
            getline(food_and_beverage_File, FnB_name);
            food_and_beverage_File>>price;
            getline(food_and_beverage_File, none);
            if(!food_and_beverage_File.eof())
                new_food_and_beverage_File<<FnB_name<<endl<<price<<" 100\n";
            else
                new_food_and_beverage_File<<FnB_name<<endl<<price<<" 100";
        }while(!food_and_beverage_File.eof());
        food_and_beverage_File.close();
        new_food_and_beverage_File.close();
        remove("FnB.txt");
        rename("newFnB.txt", "FnB.txt");
        cout<<"\nLoading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
		cout<<"\n\n";
		cout<<"\nThe Food and Beverage in storage is full\n";
		system("pause");
		system("cls");
    }
    void add_new_food_and_beverage()
    {
        add_new_FnB:
        fflush(stdin);
        bool adding_new = true;
        cout<<"\n==============================================================";
        cout<<"\n||                Add New Food and Beverage                 ||";
        cout<<"\n==============================================================";
        cout<<"\n";
        cout<<"Please enter the New Food and Beverage name want to add : ";
        getline(cin, FnB_name);
        food_and_beverage_File.open("FnB.txt", ios::in);
        while(!food_and_beverage_File.eof())
        {
            getline(food_and_beverage_File, none);
            if(FnB_name==none)
            {
                adding_new = false;
                break;
            }
        }
        food_and_beverage_File.close();
        cout<<"\nLoading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
		cout<<"\n\n";
		system("pause");
        if(!adding_new)
        {
            cout<<"\nThis Food and Beverage already in slot";
        }
        else
        {
            food_and_beverage_File.open("FnB.txt", ios::app);
            if(food_and_beverage_File)
            {
                cout<<"\nNew Food and Beverage add in Successful";
            }
            cout<<"\nPlease enter the New Food and Beverage Price : RM ";
            cin>>price;
            food_and_beverage_File<<endl<<FnB_name<<endl<<price<<" 100";
            cout<<"\nNew Food and Beverage price add in Successful";
            food_and_beverage_File.close();
        }
        char sel;
        cout<<"\ndo you need continue add ? [Y/N] ";
        cin>>sel;
        sleep(1);
        system("cls");
        if(sel=='Y'||sel=='y')
            goto add_new_FnB;
    }
    void delete_food_and_beverage()
    {
        delete_FnB:
        fflush(stdin);
        bool delete_FnB = false;
        string FnB_name_in_storage;
        cout<<"\n==============================================================";
        cout<<"\n||                 Delete Food and Beverage                 ||";
        cout<<"\n==============================================================";
        cout<<"\n";
        cout<<"Please enter the New Food and Beverage name want to delete : ";
        getline(cin, FnB_name);
        food_and_beverage_File.open("FnB.txt", ios::in);
        while(!food_and_beverage_File.eof())
        {
            getline(food_and_beverage_File, none);
            if(FnB_name==none)
            {
                delete_FnB = true;
                break;
            }
        }
        food_and_beverage_File.close();
        cout<<"\nLoading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
		cout<<"\n\n";
		system("pause");
        if(delete_FnB)
        {
            food_and_beverage_File.open("FnB.txt", ios::in);
            fstream new_food_and_beverage_File("newFnB.txt", ios::out);
            do{
                getline(food_and_beverage_File, FnB_name_in_storage);
                food_and_beverage_File>>price;
                food_and_beverage_File>>remaining;
                getline(food_and_beverage_File, none);
                if(FnB_name!=FnB_name_in_storage)
                {
                    if(!food_and_beverage_File.eof())
                        new_food_and_beverage_File<<FnB_name_in_storage<<endl<<price<<" "<<remaining<<endl;
                    else
                        new_food_and_beverage_File<<FnB_name_in_storage<<endl<<price<<" "<<remaining;
                }
            }while(!food_and_beverage_File.eof());
            food_and_beverage_File.close();
            new_food_and_beverage_File.close();
            remove("FnB.txt");
            rename("newFnB.txt", "FnB.txt");
            cout<<"\nThe Food and Beverage delete Successful";
        }
        else
        {
            cout<<"\nThe name not in Food and Beverage storage";
        }
        sleep(1);
        char sel;
        cout<<"\ndo you need continue delete ? [Y/N] ";
        cin>>sel;
        sleep(1);
        system("cls");
        if(sel=='Y'||sel=='y')
            goto delete_FnB;
    }
    void view_remaining_food_and_beverage()
    {
        fflush(stdin);
        food_and_beverage_File.open("FnB.txt", ios::in);
        cout<<"\n==============================================================";
        cout<<"\n||              Food and Beverage storage                   ||";
        cout<<"\n==============================================================";
        cout<<"\n\n";
        do{
            getline(food_and_beverage_File, FnB_name);
            food_and_beverage_File>>price;
            food_and_beverage_File>>remaining;
            getline(food_and_beverage_File, none);
            cout<<"F&B set    : "<<FnB_name<<endl;
            cout<<"Price      : RM"<<fixed<<setprecision(2)<<price<<endl;
            cout<<"In storage : "<<remaining<<endl<<endl;
        }while(!food_and_beverage_File.eof());
        food_and_beverage_File.close();
    }
};
void recommendation()
{
    time_t now = time(0);
    string local_system_date = ctime(&now);
    tm *convert_to_UTC = gmtime(&now);
    string UTC_date = asctime(convert_to_UTC);
    string week= UTC_date.substr(0, 3);
    cout << "The week time now is : "<< week << endl;
    if(week=="Mon")
	{
		cout<<"\n======Today is Monday, recommend Early Bird Combo (Price: RM 18.00)======"<<endl;
        cout<<"\n======Enjoy RM 2 off for each Movie Tickets ! ======\n\n";
	}
    else if(week== "Tue")
    {
    	cout<<"\n======Today is Tuesday, recommend Happy Tuesday Combo (Price: RM 13.00)======"<<endl;
	}
	else if(week=="Wed")
	{
		cout<<"\n======Today is Wednesday, recommend Family Combo (Price: RM45.00)======"<<endl;
	}
	else if(week=="Thu")
	{
		cout<<"\n======Today is Thursday, recommend Signature Combo (Price: RM18.50)======"<<endl;	
	}
	else if(week=="Fri")
	{
		cout<<"\n======Today is Friday, recommend Limited Time Combo (Price: RM12.00)======"<<endl;	
	}
	else if(week=="Sat")
	{
		cout<<"\n======Today is Saturday, recommend Couple Combo (Price: RM25.00)======"<<endl;
	}
	else if(week=="Sun")	
	{
		cout<<"\n======Today is Sunday, recommend Large e-Combo (RM18.50) ======"<<endl;
	}
    cout<<"\n##############################################################";
	cout<<"\n\t\t\tPromotions";
	cout<<"\n##############################################################";
	cout<<"\n Enjoy RM 2 off for each movie tickets on every Monday !!";
	cout<<"\n##############################################################";
	cout<<"\n\t\t\tMember Discount";
	cout<<"\n##############################################################";
	cout<<"\n 5% discount for purchase of RM100";
	cout<<"\n10% discount for purchase of RM150";
	cout<<"\n15% discount for purchase of RM200";
    cout<<endl<<endl;
}*/
