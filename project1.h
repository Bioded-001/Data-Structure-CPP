#include "algo.h"

class Movie_management
{
    protected:
    	fstream movies_file;
        string movie_name;
        int n,c;
        movies  *now_s, *c_soon;
    public:
    Movie_management(){

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
    void delete_coming_soon_movie() {
        fflush(stdin);
        string movie_name_in_txt;
        fstream new_movies_file;
        int m_code;
        cout << "\n==============================================================";
        cout << "\n||                 Delete Coming Soon Movie                 ||";
        cout << "\n==============================================================";
        cout << "\n";

        int i;
        for (i = 0; i < c; i++) {
            cout << i + 1 << " " << c_soon[i].mv_name << endl;
        }
        cout << i + 1 << " " << "Back To Menu" << endl;
        cout << "\nPlease enter the movie code you want to delete: ";
        cin >> m_code;
        cout << "\nLoading..";
        for (int i = 0; i < 2; i++) {
            sleep(1);
            cout << "..";
        }
        cout << "\n\n";
        system("pause");

        if (cin.fail()) {
            m_code = 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (m_code > c || m_code < 1) {
            cout << "Invalid choice!" << endl;
            cout << "Please enter again" << endl;
            system("pause");
            system("cls");
            delete_coming_soon_movie();
        } else if (m_code == c + 1) {
            return;
        } else {
            string movie_name = c_soon[m_code - 1].mv_name;
            bool searching = movie_searching("Coming Soon Movie Name.txt", "movie storage/Coming Soon/", movie_name);
            if (searching) {
                fstream movies_file("Coming Soon Movie Name.txt", ios::out);
                for (i = 0; i < c; i++) {
                    if (c_soon[i].mv_name != movie_name) {
                        movies_file << c_soon[i].mv_name << endl;
                    }
                }
                movies_file.close();
                cout << "Movie name deleted successfully" << endl;
                sleep(1);
                remove(("movie storage/Coming Soon/" + movie_name + ".txt").c_str());
                cout << "Movie slot deleted successfully" << endl;
            }
            sleep(1);
            char sel;
            cout << "\nDo you want to continue deleting? [Y/N] ";
            cin >> sel;
            sleep(1);
            system("cls");
            if (sel == 'Y' || sel == 'y') {
                delete_coming_soon_movie();
            }
        }
    }

    void delete_now_showing_movie() {
        fflush(stdin);
        int m_code;
        cout << "\n==============================================================";
        cout << "\n||                  Delete Now Showing Movie                ||";
        cout << "\n==============================================================";
        cout << "\n";

        int i;
        for (i = 0; i < n; i++) {
            cout << i + 1 << " " << now_s[i].mv_name << endl;
        }
        cout << i + 1 << " " << "Back To Menu" << endl;
        cout << "\nPlease enter the movie code you want to delete: ";
        cin >> m_code;
        cout << "\nLoading..";
        for (int i = 0; i < 2; i++) {
            sleep(1);
            cout << "..";
        }
        cout << "\n\n";
        system("pause");

        if (cin.fail()) {
            m_code = 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (m_code > n || m_code < 1) {
            cout << "Invalid choice!" << endl;
            cout << "Please enter again" << endl;
            system("pause");
            system("cls");
            delete_now_showing_movie();
        } else if (m_code == n + 1) {
            return;
        } else {
            string movie_name = now_s[m_code - 1].mv_name;
            bool searching = movie_searching("Now Showing Movie Name.txt", "movie storage/Now Showing/", movie_name);
            if (searching) {
                fstream movies_file("Now Showing Movie Name.txt", ios::out);
                for (i = 0; i < n; i++) {
                    if (now_s[i].mv_name != movie_name) {
                        movies_file << now_s[i].mv_name << endl;
                    }
                }
                movies_file.close();
                cout << "Movie name deleted successfully" << endl;
                sleep(1);
                remove(("movie storage/Now Showing/" + movie_name + ".txt").c_str());
                remove(("movie storage/Seat/" + movie_name).c_str());
                cout << "Movie slot deleted successfully" << endl;
            }
            sleep(1);
            char sel;
            cout << "\nDo you want to continue deleting? [Y/N] ";
            cin >> sel;
            sleep(1);
            system("cls");
            if (sel == 'Y' || sel == 'y') {
                delete_now_showing_movie();
            }
        }
    }
    void remove_seat() {
        fflush(stdin);
        int m_code;
        cout << "\n==============================================================";
        cout << "\n||                    Remove  Movie  Seat                   ||";
        cout << "\n==============================================================";
        cout << "\n";

        int i;
        for (i = 0; i < n; i++) {
            cout << i + 1 << " " << now_s[i].mv_name << endl;
        }
        cout << i + 1 << " " << "Back To Menu" << endl;
        cout << "\nPlease enter the movie code you want to remove the seat: ";
        cin >> m_code;
        cout << "\nLoading..";
        for (int i = 0; i < 2; i++) {
            sleep(1);
            cout << "..";
        }
        cout << "\n\n";
        system("pause");

        if (cin.fail()) {
            m_code = 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (m_code > n || m_code < 1) {
            cout << "Invalid choice!" << endl;
            cout << "Please enter again" << endl;
            system("pause");
            system("cls");
            remove_seat();
        } else if (m_code == n + 1) {
            return;
        } else {
            string movie_name = now_s[m_code - 1].mv_name;
            bool searching = movie_searching("Now Showing Movie Name.txt", "movie storage/Now Showing/", movie_name);
            if (searching) {
                fstream morning(("movie storage/Seat/" + movie_name + "/Morning " + movie_name + ".txt").c_str(), ios::out);
                fstream afternoon(("movie storage/Seat/" + movie_name + "/Afternoon " + movie_name + ".txt").c_str(), ios::out);
                fstream night(("movie storage/Seat/" + movie_name + "/Night " + movie_name + ".txt").c_str(), ios::out);
                morning.close();
                afternoon.close();
                night.close();
                cout << "Movie seat removed successfully" << endl;
            }
            sleep(1);
            char sel;
            cout << "\nDo you want to continue remove seat? [Y/N] ";
            cin >> sel;
            sleep(1);
            system("cls");
            if (sel == 'Y' || sel == 'y') {
                remove_seat();
            }
        }
    }



};