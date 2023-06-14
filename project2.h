#include "project1.h"
class movie_page{
	private: 
	float *tic_p, total_p;
	int num_ticket = 0;
	movies  *now_s, *c_soon;
	fstream now_showing, coming_soon, ticket_file;
	int n,c;
    string movie_sel, sel_time, *ticket;
    string sel_in_menu;
    bool discount;
	public:
    movie_page() {
        total_p = 0;

        // Read the "Now Showing" movie names into a vector
        vector<string> nowShowingMovies;
        ifstream now_showing("Now Showing Movie Name.txt");
        string movieName;
        while (getline(now_showing, movieName)) {
            nowShowingMovies.push_back(movieName);
        }
        now_showing.close();

        // Sort the Now Showing movies
        selectionSort(nowShowingMovies);

        // Set the size and populate the now_s array
        n = nowShowingMovies.size();
        now_s = new movies[n];
        for (int i = 0; i < n; i++) {
            now_s[i].mv_name = nowShowingMovies[i];
        }

        // Read the "Coming Soon" movie names into a vector
        vector<string> comingSoonMovies;
        ifstream coming_soon("Coming Soon Movie Name.txt");
        while (getline(coming_soon, movieName)) {
            comingSoonMovies.push_back(movieName);
        }
        coming_soon.close();

        // Sort the Coming Soon movies
        selectionSort(comingSoonMovies);

        // Set the size and populate the c_soon array
        c = comingSoonMovies.size();
        c_soon = new movies[c];
        for (int i = 0; i < c; i++) {
            c_soon[i].mv_name = comingSoonMovies[i];
        }
    }
	int m_menu(bool dis)
	{
        discount= dis;
		menu_page:
		cout<<"**************************************** "<<endl;
		cout<<"||              MOVIES                || "<<endl;
		cout<<"**************************************** "<<endl;
		cout<<"1. Now Showing 		 "<<endl;
		cout<<"2. Coming Soon		 "<<endl;
        cout<<"3. Book Movie		 "<<endl;
		cout<<"4. Back To Menu		 "<<endl;
		cout<<"\nPlease select your choice : ";
		getline(cin,sel_in_menu);
		cout<<"\nLoading..";
	    for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
		cout<<"\n\n";
		system("cls");
		if(sel_in_menu=="Now Showing" || sel_in_menu=="now showing" || sel_in_menu=="1")
		{
			n_showing();
		}
		else if(sel_in_menu=="Coming Soon" || sel_in_menu=="coming soon" || sel_in_menu=="2")
		{
			coming_s();
		}
        else if(sel_in_menu=="Book Movie" || sel_in_menu=="book movie" || sel_in_menu=="3")
		{
			sel_movie();
		}
		else if(sel_in_menu=="Back To Menu" || sel_in_menu=="back to menu" || sel_in_menu=="4")
		{}
		else
		{
			cout<<"Invalid Selection!"<<endl;
			cout<<"Please enter again"<<endl;
		}
		system("pause");
		system("cls");
        if(sel_in_menu=="Book Movie" || sel_in_menu=="book movie" || sel_in_menu=="3"||sel_in_menu=="Back To Menu" || sel_in_menu=="back to menu" || sel_in_menu=="4")
            return 0;
        goto menu_page;
	}
	void sel_movie()
	{
		sel_movie_page:
        string is;
		int m_code;
		int i;
		for(i=0;i<n;i++)
		{
			cout<<i+1<<" "<<now_s[i].mv_name<<endl;
		}
        cout<<i+1<<" "<<"Back To Menu"<<endl;
		cout<<"\nPlease Enter the Movie Code: ";
		cin>>m_code;
        fflush(stdin);
        if (cin.fail()) {
		    m_code = 0;
		    cin.clear();  // clear the error flags on cin
		    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ignore any remaining input
		}
        if(m_code>n+1||m_code<1)
        {
            cout<<"Invalid choosing !"<<endl;
			cout<<"Please enter again"<<endl;
            system("pause");
		    system("cls");
            goto sel_movie_page;
        }
        else if(m_code==n+1)
        {
            sel_in_menu="4";
        }
        else{
            bool search=movie_searching("Now Showing Movie Name.txt", "movie storage/Now Showing/", now_s[m_code-1].mv_name);
            if(search)
            {
                cout<<"\nIs this the movie you choosing ? [Yes/No] : ";
                getline(cin, is);
                system("pause");
                system("cls");
                if(is=="Yes"||is=="yes"||is=="Y"||is=="y")
                {
                    movie_sel= now_s[m_code-1].mv_name;
                    time_s();
                    sel_seat();
                }else{
                    sel_in_menu="4";
                }
            }
        }
	}
    void time_s()
    {
        while (true) {
            string is;
            bool validTime = false;

            while (!validTime) {
                cout << "Please Select a time ? [1.Morning/2.Afternoon/3.Night] : ";
                getline(cin, sel_time);

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (sel_time == "Morning" || sel_time == "morning" || sel_time == "1") {
                    sel_time = "Morning";
                    cout << sel_time << endl;
                    cout << "Is this the time you choosing ? [Yes/No] : ";
                    getline(cin, is);
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    validTime = true;
                } else if (sel_time == "Afternoon" || sel_time == "afternoon" || sel_time == "2") {
                    sel_time = "Afternoon";
                    cout << sel_time << endl;
                    cout << "Is this the time you choosing ? [Yes/No] : ";
                    getline(cin, is);
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    validTime = true;
                } else if (sel_time == "Night" || sel_time == "night" || sel_time == "3") {
                    sel_time = "Night";
                    cout << sel_time << endl;
                    cout << "\nIs this the time you choosing ? [Yes/No] : ";
                    getline(cin, is);
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    validTime = true;
                } else {
                    cout << "Invalid time selection." << endl;
                    cout << "Please enter again." << endl;
                }
                system("pause");
                system("cls");
            }

            if (is == "Yes" || is == "yes" || is == "Y" || is == "y") {
                break;
            }
        }
    }
    void sel_seat() {
        string sel_seat_id, ticket_in_file, is;
        TicketQueue tic;
        int maxticket = 30 - readTicketsFromFile(tic, movie_sel, sel_time);
        if(maxticket==0){
            cout << "The seat full ";
            sel_in_menu="4";
        }else{
            do {
                do {
                    // Prompt the user to enter the number of tickets
                    cout << "How many tickets would you like to purchase? : ";
                    cout << "Maximum available tickets: " << maxticket << endl;
                    cin >> num_ticket;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    // Check if the input is valid
                    if (cin.fail()) {
                        cin.clear();
                        cout << "Invalid input. Please enter a valid number." << endl;
                    } else if (num_ticket <= 0) {
                        cout << "Number of tickets must be greater than 0." << endl;
                    } else if (num_ticket > maxticket) {
                        cout << "Number of tickets cannot exceed the maximum available tickets." << endl;
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } while (cin.fail() || num_ticket <= 0 || num_ticket > maxticket);

                // Ask for confirmation from the user
                cout << "\n\nIs this the number of tickets you want to purchase? [Yes/No] : ";
                getline(cin, is);
                system("cls");

                // Check if the input is valid
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (is != "Yes" && is != "yes" && is != "Y" && is != "y");


            ticket = new string[num_ticket];
            tic_p = new float[num_ticket];

            for (int i = 0; i < num_ticket; i++) {
                bool check_1;
                bool check_2;
                do{
                    cout << "\n\t\t\t\t Screen" << endl;
                    cout << "    ------------------------------------------------------------------" << endl;
                    cout << "   /\t\t\t\t\t\t\t\t      \\\n";
                    cout << "  /\t\t\t\t\t\t\t\t       \\\n";
                    cout << " /\t\t\t\t\t\t\t\t        \\\n" << endl;
                    cout << "    A  [A01] [A02] [A03] [A04] [A05] [A06] [A07] [A08] [A09] [A10]     \n\n";
                    cout << "    B  [B01] [B02] [B03] [B04] [B05] [B06] [B07] [B08] [B09] [B10]     \n\n";
                    cout << "    C  [C01] [C02] [C03] [C04] [C05] [C06] [C07] [C08] [C09] [C10]     \n\n";
                    cout << "    D  [D01] [D02] [D03] [D04] [D05] [D06] [D07] [D08] [D09] [D10]     \n\n";
                    cout << "    E  [E01] [E02] [E03] [E04] [E05] [E06] [E07] [E08] [E09] [E10]     \n\n";
                    display_alre_book(tic);
                    cout << "\nPlease select a seat: ";
                    getline(cin, sel_seat_id);
                    transform(sel_seat_id.begin(), sel_seat_id.end(), sel_seat_id.begin(), ::toupper);
                    check_1 = check_seat_valid(sel_seat_id);
                    check_2 = check_seat_havent(sel_seat_id, tic);
                    if (check_1==false) {
                        cout << "The seat you entered is not in the system.\n";
                        system("pause");
                        system("cls");
                    }
                    else if (check_2==true) {
                        cout << "The seat you entered has already been booked by someone else.\n";
                        system("pause");
                        system("cls");
                    }
                } while (check_1==false || check_2==true);
                char ticket_type;
                cout << "1. Adult       RM 19.00" << endl;
                cout << "2. Children    RM 12.00" << endl;
                cout << "Please select one: ";
                cin >> ticket_type;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                while (ticket_type != '1' && ticket_type != '2') {
                    cout << "Invalid ticket type. Please select again: ";
                    cin >> ticket_type;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (ticket_type == '1' || ticket_type == 'A' || ticket_type == 'a') {
                    tic_p[i] = ticket_price_A;
                } else if (ticket_type == '2' || ticket_type == 'C' || ticket_type == 'c') {
                    tic_p[i] = ticket_price_C;
                }
                
                ticket[i] = sel_seat_id;
                ticket_file.open(("movie storage/Seat/" + movie_sel + "/" + sel_time + " " + movie_sel + ".txt").c_str(), ios::app);
                ticket_file << ticket[i] << endl;
                ticket_file.close();
                cout << ticket[i] << " book successful\n";
                ticket_in_move newTicket;
                newTicket.ticket_id = ticket[i];
                tic.enqueue(newTicket);
                system("pause");
                system("cls");
            }
            cal_total();
        }

    }

    void cal_total()
    {
    	for(int i=0; i<num_ticket; i++)
    	{
    		total_p+=tic_p [i];
		}
	}
	void n_showing()
	{
        string m_details;	
        cout<<"**************************************** "<<endl;
        cout<<"||         Now Showing Movies         || "<<endl;
        cout<<"**************************************** "<<endl;
        search_for_movies("Now Showing Movie Name.txt", "movie storage/Now Showing/", "");
	}
	void coming_s()
	{
		string cm_details;
        cout<<"\n\n";	
        cout<<"**************************************** "<<endl;
        cout<<"||            Coming Soon             || "<<endl;
        cout<<"**************************************** "<<endl;
        search_for_movies("Coming Soon Movie Name.txt", "movie storage/Coming Soon/", "");
	}
	void display_bill()
	{
        fstream bill_display("Bill & Ticket/Movie Bill.txt", ios::out);
        /////
        cout<<"======================================================="<<endl;
        cout<<"||                      BILL                         ||"<<endl;
        cout<<"======================================================="<<endl;
        cout<<"\tMovie Name : "<<movie_sel<<endl;
		cout<<"\tMovie Time : "<<sel_time<<endl;
        ///
        bill_display<<"======================================================="<<endl;
        bill_display<<"||                      BILL                         ||"<<endl;
        bill_display<<"======================================================="<<endl;
        bill_display<<"\tMovie Name : "<<movie_sel<<endl;
		bill_display<<"\tMovie Time : "<<sel_time<<endl;
        for(int i=0; i<num_ticket; i++)
		{
            cout<<"\tMovie Seat : "<<ticket[i]<<endl;
            cout<<"\tSeat Price : RM"<<fixed<<setprecision(2)<<tic_p [i]<<endl; 
            /// /
            bill_display<<"\tMovie Seat : "<<ticket[i]<<endl;
            bill_display<<"\tSeat Price : RM"<<fixed<<setprecision(2)<<tic_p [i]<<endl;
            
        }
        cout<<"-------------------------------------------------------- "<<endl;
        cout<<"Total Price				 : RM"<<fixed<<setprecision(2)<<total_p<<endl;
        ///  /
        bill_display<<"---------------------------------------------------------"<<endl;
        bill_display<<"Total Price				 : RM"<<fixed<<setprecision(2)<<total_p<<endl;
        bill_display.close();
        cout<<"\nPlease take your bill\n";
        system("pause");
        system("cls");
	}
    void ticket_generate()
	{
		fstream ticket_display("Bill & Ticket/ticket.txt", ios::out);	
		for(int i=0; i<num_ticket; i++)
		{
            cout<<"=========================================================="<<endl;
        	cout<<"\tMOVIE TICKET						   "<<endl;
        	cout<<"\tMovie Name : "<<movie_sel<<endl;
			cout<<"\tMovie Time : "<<sel_time<<endl;
			cout<<"\tMovie Seat : "<<ticket[i]<<endl;
            cout<<"\tSeat Price : RM"<<fixed<<setprecision(2)<<tic_p [i]<<endl; 
        	cout<<"=========================================================="<<endl<<endl<<endl;
            ////////////////////////
			ticket_display<<"=========================================================="<<endl;
        	ticket_display<<"\tMOVIE TICKET						   "<<endl;
        	ticket_display<<"\tMovie Name : "<<movie_sel<<endl;
			ticket_display<<"\tMovie Time : "<<sel_time<<endl;
			ticket_display<<"\tMovie Seat :	"<<ticket[i]<<endl;
            ticket_display<<"\tSeat Price : RM"<<fixed<<setprecision(2)<<tic_p [i]<<endl; 
        	ticket_display<<"=========================================================="<<endl<<endl<<endl;	
		}
        ticket_display.close();
        cout<<"\nPlease take your ticket\n";
	}
	~movie_page()
	{
		if(sel_in_menu=="Book Movie" || sel_in_menu=="book movie" || sel_in_menu=="3")
		{
			display_bill();
            ticket_generate();
			delete [] tic_p;
			delete [] ticket;
			delete [] now_s;
			delete [] c_soon;
			total_p=0;
		}
		else
		{
			delete [] now_s;
			delete [] c_soon;
		}
	}
};
void access_movie(bool discount)
{
	movie_page *movie=new movie_page;
	movie->m_menu(discount);
	cout<<"\nLoading..";
    for(int i=0;i<2;i++)
    {
        sleep(1);
    	cout<<"..";
	}
	cout<<"\n\n";
	system("cls");
	delete movie;
}
/*
//food & beverage ordering
struct Fnb_in_storage
{
    int  quantity;
    string E_sets_combo;
    double E_sets_price;
};
class FnB 
{   private:  
    Fnb_in_storage *order;
    int total_type_Fnb, set, *FnB_order, *qty;
    double total_cost;
    fstream Fnb_in_txt;
    bool discount, order_or_not;
    public: 
    FnB()
	{
		total_cost=0;
		total_type_Fnb = 0;
        order_or_not= false;
        string none;
        Fnb_in_txt.open("FnB.txt", ios::in);
        while(!Fnb_in_txt.eof())
        {
            getline(Fnb_in_txt, none);
            getline(Fnb_in_txt, none);
            total_type_Fnb++;
        }
        Fnb_in_txt.close();
        order = new Fnb_in_storage[total_type_Fnb];
        Fnb_in_txt.open("FnB.txt", ios::in);
        for(int i=0; i<total_type_Fnb; i++)
        {
            getline(Fnb_in_txt, order[i].E_sets_combo);
            Fnb_in_txt>>order[i].E_sets_price>>order[i].quantity;
            getline(Fnb_in_txt, none);
        }
        Fnb_in_txt.close();
	}
    void menu(bool dis)
    {
        discount= dis;
        string select;
        select_page:
        cout<<"==================================================="<<endl;
        cout<<"|||             F&B Order System                |||"<<endl;
        cout<<"==================================================="<<endl;
        cout<<"1.Food and Beverage Menu"<<endl; 
        cout<<"2.Order Food and Beverage"<<endl; 
        cout<<"3.Exit"<<endl; 
        cout<<"\nPlease enter your choice : ";
		getline(cin, select);
        cout<<"\nLoading..";
        for(int i=0;i<2;i++)
        {
            sleep(1);
            cout<<"..";
        }
        cout<<"\n\n";
        system("cls");
        if(select=="Food and Beverage Menu"||select=="food and beverage menu"||select=="1")
        {
            display_menu();
            goto select_page;
        }
        else if(select=="Order Food and Beverage"||select=="order food and beverage"||select=="2")
        {
            ordering();
        }
        else if(select=="Exit"||select=="exit"||select=="3")
        {}
        else
        {
            cout<<"Invalid select";
            system("pause");
            system("cls");
            goto select_page;
        }
	}
    void display_menu()
    {
        cout<<"==================================================="<<endl;
        cout<<"|||                   MENU                      |||"<<endl;
        cout<<"==================================================="<<endl;  
        for(int i=0; i<total_type_Fnb; i++)
        {
            cout<<i+1<<". "<<order[i].E_sets_combo<<endl; 
            cout<<"Price : RM "<<setprecision(2)<<order[i].E_sets_price<<endl;
            cout<<"Quantity left : "<<order[i].quantity<<endl;
        }
        system("pause");
        system("cls");
    }
	void ordering()
	{
        order_or_not=true;
        cout<<"==================================================="<<endl;
        cout<<"|||         ORDER YOUR FOOD AND BEVERAGES       |||"<<endl;
        cout<<"==================================================="<<endl;
        for(int i=0; i<total_type_Fnb; i++)
        {
            cout<<i+1<<". "<<order[i].E_sets_combo<<endl; 
        }
        cout<<"How many set you want from here : ";
        cin>>set;
        fflush(stdin);
        FnB_order= new int[set];
        qty= new int[set];
        for(int i=0; i<set; i++)
        {
            back:;
            cout<<"Set "<<i+1<<" order code : ";
            cin>>FnB_order[i];
            FnB_order[i]--;
            if(FnB_order[i]>total_type_Fnb-1||FnB_order[i]<0)
            {
                cout<<"This Set code not in menu"<<endl;
                goto back;
            }
            if(order[FnB_order[i]].quantity<=0)
            {
                cout<<"This set is sold out"<<endl;
                cout<<"Please choose other set"<<endl;
                goto back;
            }
            qty_back:;
            cout<<"Quantity of "<<order[FnB_order[i]].E_sets_combo<<" you want : ";
            cin>>qty[i];
            if(qty[i]>order[FnB_order[i]].quantity)
            {
                cout<<"The quantity you want is more then the remaining stock"<<endl;
                goto qty_back;
            }
            order[FnB_order[i]].quantity-=qty[i];
        }
        fflush(stdin);
        cal_total_cost();
        save_storage();
        system("pause");
        system("cls");
	}
    void cal_total_cost()
    {
        for(int i=0; i<set; i++)
        {
            total_cost += (order[FnB_order[i]].E_sets_price * qty[i]);
        }
        if(discount)
        {
            if(total_cost>=100&&total_cost<150)
                total_cost*=0.95;
            else if(total_cost>=150&&total_cost<200)
                total_cost*=0.9;
            else if(total_cost>=200)
                total_cost*=0.85;
        }
    }
    void save_storage()
    {
        Fnb_in_txt.open("FnB.txt", ios::out);
        for(int i=0; i<total_type_Fnb; i++)
        {
            Fnb_in_txt<<order[i].E_sets_combo<<endl<<order[i].E_sets_price<<" "<<order[i].quantity;
            if(i<total_type_Fnb-1)
            {
                Fnb_in_txt<<endl;
            }
        }
        Fnb_in_txt.close();
    }
    void display_bill()
    {
        cout<<"====================================================="<<endl;
        cout<<"|||                     BILL                      |||"<<endl;
        cout<<"====================================================="<<endl;
        for(int i=0; i<set; i++)
        {
            cout<<"Set "<<i+1<<"    : "<<order[FnB_order[i]].E_sets_combo<<endl;
            cout<<"Quantity : "<<qty[i]<<endl;
            cout<<"Price    : RM"<<fixed<<setprecision(2)<<qty[i] * order[FnB_order[i]].E_sets_price<<endl;
        }
        cout<<"-------------------------------------------------------- "<<endl;
        cout<<"Total Price				 : RM"<<fixed<<setprecision(2)<<total_cost<<endl;
        ////
        fstream bill_display("Bill & Ticket/FnB Bill.txt", ios::out);
        bill_display<<"====================================================="<<endl;
        bill_display<<"|||                     BILL                      |||"<<endl;
        bill_display<<"====================================================="<<endl;
        for(int i=0; i<set; i++)
        {
            bill_display<<"Set "<<i+1<<"    : "<<order[FnB_order[i]].E_sets_combo<<endl;
            bill_display<<"Quantity : "<<qty[i]<<endl;
            bill_display<<"Price    : RM"<<fixed<<setprecision(2)<<qty[i] * order[FnB_order[i]].E_sets_price<<endl;
        }
        bill_display<<"-------------------------------------------------------- "<<endl;
        bill_display<<"Total Price				 : RM"<<fixed<<setprecision(2)<<total_cost<<endl;
        bill_display.close();
        ////
        cout<<"====================================================="<<endl;
        cout<<"|||    THANKS FOR ORDERING WITH THE J W CINEMA    |||"<<endl;
        cout<<"====================================================="<<endl;
    }
    ~FnB()   
    {
        if(order_or_not)
        {
            display_bill();
            delete [] FnB_order;
            delete [] qty;
        }
        delete [] order;
        total_type_Fnb = 0; 
    }  
}; 
void access_FnB(bool discount)
{
    FnB *access=new FnB;
	access->menu(discount);
	cout<<"\nLoading..";
    for(int i=0;i<2;i++)
    {
        sleep(1);
    	cout<<"..";
	}
	cout<<"\n\n";
	system("cls");
	delete access;
	system("pause");
	system("cls");
}
*/
