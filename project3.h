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
    void login() {
        login_pa:
        int mem_status = 0;
        string none;
        string login_c;
        string log_password, log_phone;
        system("cls");
        cout << "________________________________________________________________" << endl;
        cout << "\t\t || THE - J W - CINEMA || \t\t" << endl;
        cout << "                          [  LOGIN  ]                           " << endl;
        cout << "________________________________________________________________" << endl;
        cout << "Login by : " << endl;
        cout << "1. Name " << endl;
        cout << "2. Phone number " << endl;
        cout << "\nPlease enter your choice : ";
        getline(cin, login_c);
        if (login_c == "1") {
            cout << "\nPlease enter your member name : ";
            getline(cin, log_name);
            cout << "\nPlease enter password : ";
            getline(cin, log_password);
            //log_password = computeHash(log_password); // Encrypt the password
        }
        else if (login_c == "2") {
            cout << "\nPlease enter your member phone number : ";
            getline(cin, log_phone);
            cout << "\nPlease enter password : ";
            getline(cin, log_password);
            //log_password = computeHash(log_password); // Encrypt the password
        }
        else {
            cout << "Sorry, this is an invalid option. Please try again. " << endl;
            system("pause");
            goto login_pa;
        }
        cout << "\nLoading..";
        for (int i = 0; i < 2; i++) {
            sleep(1);
            cout << "..";
        }
        cout << "\n\n";
        LinkedQueue memberQueue; // Create a LinkedQueue object to store member information
        readMembersFromFile(memberQueue); // Read member information from the file and populate the queue

        Member_st* frontMember = memberQueue.getFront();

        while (frontMember != nullptr) {
            if ((login_c == "1" && log_name == frontMember->mem_name) ||
                (login_c == "2" && log_phone == frontMember->mem_phone)) {
                
                if (log_password == frontMember->mem_password) {
                    log_name = frontMember->mem_name; //to display name when successful log in
                    mem_status = 1;
                    break;
                } else {
                    mem_status = 2;
                    break;
                }
            }
            
            frontMember = frontMember->next;
        }

        if (mem_status == 1) {
            mem_status = 1;
            cout << "\nLogin successful." << endl;
            cout << "Welcome, " << log_name << endl;
            access = true;
        }
        else if (mem_status == 2) {
            mem_status = 2;
            cout << "\nSorry, password entered is wrong. " << endl;
        }
        else {
            mem_status = 0;
            cout << "\nSorry, member not found. " << endl;
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

        do {
            system("cls");
            string user_s;
            string movie_name;

            cout << "Welcome, " << log_name << endl;
            cout << ".............................. M E N U .............................." << endl;
            cout << "1. View movies" << endl;
            /*cout<<"2. Order snack & beverages"<<endl;*/
            cout << "2. Search movies for Coming Soon" << endl;
            cout << "3. Search movies for Now Showing" << endl;
            cout << "4. Edit Personal Detail" << endl;
            //cout<<"5. Recommendation"<<endl;
            cout << "5. Exit" << endl;
            cout << "\nPlease enter your selection: ";
            cin >> user_s;
            fflush(stdin);

            cout << "\nLoading...";
            for (int i = 0; i < 2; i++) {
                sleep(1);
                cout << "..";
            }
            cout << "\n\n";
            system("cls");
            fflush(stdin);
            if (user_s == "1")
                access_movie(true);
            /*else if(user_s=="2")
                access_FnB(true);*/
            else if (user_s == "2") {
                cout << "\nWhat is the movie name you want to search?" << endl;
                getline(cin, movie_name);
                search_for_movies("Coming Soon Movie Name.txt", "movie storage/Coming Soon/", movie_name);
                system("pause");
                system("cls");
            }
            else if (user_s == "3") {
                cout << "\nWhat is the movie name you want to search?" << endl;
                getline(cin, movie_name);
                search_for_movies("Now Showing Movie Name.txt", "movie storage/Now Showing/", movie_name);
                system("pause");
                system("cls");
            }
            else if (user_s == "4") {
                if (data_edit) {
                    data_edit = edit_member();
                }
                else {
                    cout << "\nUser, you have just edited your Personal Detail recently.\n";
                    cout << "\nYou can only edit your data next time you log in.\n";
                }
            }
            /*else if(user_s=="5")
                recommendation();*/
            else if (user_s == "5")
                break;
            else {
                cout << "Invalid selection! Please select again." << endl;
                system("pause");
            }

            cout << "\nDo you want to continue in user mode? [Y/N]: ";
            cin >> conti_or_not;
            fflush(stdin);
        } while (toupper(conti_or_not) == 'Y');

        stack.stack_logout();
    }
    bool edit_member() {
        bool change = false;
        string mem_name, mem_phone, mem_email, mem_password;
        LinkedQueue memberQueue; // Create a LinkedQueue object to store member information
        readMembersFromFile(memberQueue); // Read member information from the file and populate the queue

        do {
            cout << "----------------Edit Member Information----------------" << endl;
            // Key in old information
            cout << "Please enter your old member name: ";
            getline(cin, mem_name);
            if (log_name != mem_name) {
                cout << "\nThis is not your own member name!\n";
                cout << "\nPlease enter your own member name!\n";
                system("pause");
                system("cls");
            }
        } while (log_name != mem_name);

        cout << "Please enter your old member phone number: ";
        getline(cin, mem_phone);
        cout << "Please enter your old member email: ";
        getline(cin, mem_email);
        cout << "Please enter your old member password: ";
        getline(cin, mem_password);
        //mem_password = computeHash(mem_password); // Encrypt the password

        // Check and update member information
        Member_st* frontMember = memberQueue.getFront();

        while (frontMember != nullptr) {
            if (mem_name == frontMember->mem_name && mem_phone == frontMember->mem_phone &&
                mem_email == frontMember->mem_email && mem_password == frontMember->mem_password) {

                // Key in new information
                cout << "\nPlease enter your new member name: ";
                getline(cin, frontMember->mem_name);
                cout << "Please enter your new member phone number: ";
                getline(cin, frontMember->mem_phone);
                cout << "Please enter your new member email: ";
                getline(cin, frontMember->mem_email);
                cout << "Please enter your new member password: ";
                getline(cin, frontMember->mem_password);

                // Update the member information
                change = true;
                break;
            }

            frontMember = frontMember->next;
        }

        if (change) {
            // Write updated member information to the file
            ofstream outFile("members.txt");
            frontMember = memberQueue.getFront();
            
            while (frontMember != nullptr) {
                outFile << frontMember->mem_name << endl;
                outFile << frontMember->mem_phone << endl;
                outFile << frontMember->mem_email << endl;
                outFile << frontMember->mem_password << endl;
                outFile << endl;

                frontMember = frontMember->next;
            }
            outFile.close();

            cout << "\nNew data inserted. Edit successful.";
        } else {
            cout << "These are wrong old member information" << endl;
        }

        cout << endl;
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
void mem_setdata() {
    system("cls");
    fflush(stdin);
    LinkedQueue memberQueue; // Create a LinkedQueue object to store member information
    readMembersFromFile(memberQueue); // Read member information from the file and populate the queue
    cout << "\n \" The J W Cinema -- Your first choice cinema \" " << endl;
    cout << "\n   ~ Welcome to join us as a member ! ~ " << endl;
    cout << "\n----------------[  Member Registration Form  ]----------------" << endl;
    cout << "\n   if you want to return to the home page, enter return " << endl;

    while (true) {
        cout << "\nYour name: ";
        getline(cin, cus.mem_name);
        if (cus.mem_name == "return") {
            break;
        }
        if (cus.mem_name.empty()) {
            cout << "\nYou must enter the username to register";
            continue;
        }

        // Check for duplicate name
        Member_st* frontMember = memberQueue.getFront();
        bool isNameTaken = false;
        while (frontMember != nullptr) {
            if (cus.mem_name == frontMember->mem_name) {
                cout << "\nThis name is already taken. Please choose a different name.";
                isNameTaken = true;
                break;
            }
            frontMember = frontMember->next;
        }
        if (isNameTaken) {
            continue;
        }

        cout << "\nYour phone number: ";
        getline(cin, cus.mem_phone);
        if (cus.mem_phone == "return") {
            break;
        }
        if (cus.mem_phone.empty()) {
            cout << "\nYou must enter the phone number to register";
            continue;
        }

        cout << "\nYour email: ";
        getline(cin, cus.mem_email);
        if (cus.mem_email == "return") {
            break;
        }
        if (cus.mem_email.empty()) {
            cout << "\nYou must enter your email to register";
            continue;
        }

        // Check for duplicate email
        frontMember = memberQueue.getFront();
        bool isEmailRegistered = false;
        while (frontMember != nullptr) {
            if (cus.mem_email == frontMember->mem_email) {
                cout << "\nThis email is already registered. Please choose a different email.";
                isEmailRegistered = true;
                break;
            }
            frontMember = frontMember->next;
        }
        if (isEmailRegistered) {
            continue;
        }

        cout << "\nPlease create a password for your account: ";
        getline(cin, cus.mem_password);
        if (cus.mem_password == "return") {
            break;
        }
        if (cus.mem_password.empty()) {
            cout << "\nYou must enter your account password to register";
            continue;
        }

        if (!(cus.mem_name).empty() && !(cus.mem_phone).empty() && !(cus.mem_email).empty() && !(cus.mem_password).empty()) {
            //cus.mem_password = computeHash(cus.mem_password); // Encrypt the password
            fstream cusfile("members.txt", ios::app);
            if (cusfile.fail()) {
                cout << "Failed to open file." << endl;
            } else {
                cusfile << cus.mem_name << endl << cus.mem_phone << endl << cus.mem_email << endl << cus.mem_password << endl << endl;
                cout << "\n\nRegister successful! " << endl;
            }
            cusfile.close();
            break;
        }
    }
}


