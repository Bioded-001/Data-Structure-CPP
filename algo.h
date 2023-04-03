#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring> 
#include<fstream>
#include<unistd.h>
#include<ctime>
#include<cctype>
#include <stack>
#include <chrono>
using namespace std;
// Here is stack
struct Session {
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
    std::chrono::seconds duration;
};
std::stack<Session> session_stack;
void stack_login()
{
    Session session;
    session.start_time = std::chrono::system_clock::now();
    session_stack.push(session);
}
void stack_logout()
{
    Session& current_session = session_stack.top();
    current_session.end_time = std::chrono::system_clock::now();
    current_session.duration = std::chrono::duration_cast<std::chrono::seconds>(current_session.end_time - current_session.start_time);
    session_stack.pop();
    std::cout << "The duration time you use is : " << current_session.duration.count() << " seconds\n";
}
// Here is stack
// Here is selectionSort
void selectionSort(vector<string>& result) {
    int n = result.size();
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (result[j][0] < result[min_idx][0]) {
                min_idx = j;
            }
        }
        swap(result[min_idx], result[i]);
    }
}
// Here is selectionSort
// Here is hashSearch
void hashSearch(string& find, vector<string>& data, vector<string>& result)
{
    // Initialize hash function
    std::hash<std::string> strHash;

    // Convert the find string to lowercase
    transform(find.begin(), find.end(), find.begin(), [](unsigned char c){ return tolower(c); });

    // Loop through the data array and find similar strings
    for (const auto& str : data)
    {
        // Convert the current string to lowercase
        string strLower = str;
        transform(strLower.begin(), strLower.end(), strLower.begin(), [](unsigned char c){ return tolower(c); });

        // Generate hash value of current string
        size_t strHashVal = strHash(strLower);

        // Compare hash values and check if the current string contains the find string as a substring
        if (strHashVal == strHash(find) || strLower.find(find) != string::npos)
        {
            // If hash values match or the current string contains the find string, add the string to the result vector
            result.push_back(str);
        }
    }
}
// Here is 

void search_for_ns(string find)
{
    // Test data
    fstream movie_searching_File;
    movie_searching_File.open("Now Showing Movie Name.txt", ios::in);
    vector<string> movie_names;
    string line;
    while (getline(movie_searching_File, line)) {
        movie_names.push_back(line);
    }
    movie_searching_File.close();
    vector<string> result;
    string movie_detail;
    // Search for similar strings using hash search algorithm
    hashSearch(find, movie_names, result);
    selectionSort(result);
    // Display the result
    if (!result.empty())
    {
        for (const auto& str : result)
        {
            movie_searching_File.open(("movie storage/Now Showing/" + str + ".txt").c_str(), ios::in);
            do{
                getline(movie_searching_File, movie_detail);
                cout<<movie_detail<<endl;
            }while(!movie_searching_File.eof());
            cout<<endl<<endl;
            movie_searching_File.close();
        }
    }
    else
    {
        cout << "No found." << endl;
    }
    
}

void search_for_cs(string find)
{
    // Test data
    fstream movie_searching_File;
    movie_searching_File.open("Coming Soon Movie Name.txt", ios::in);
    vector<string> movie_names;
    string line;
    while (getline(movie_searching_File, line)) {
        movie_names.push_back(line);
    }
    movie_searching_File.close();
    vector<string> result;
    string movie_detail;
    // Search for similar strings using hash search algorithm
    hashSearch(find, movie_names, result);
    selectionSort(result);

    // Display the result
    if (!result.empty())
    {
        for (const auto& str : result)
        {
            movie_searching_File.open(("movie storage/Coming Soon/" + str + ".txt").c_str(), ios::in);
            do{
                getline(movie_searching_File, movie_detail);
                cout<<movie_detail<<endl;
            }while(!movie_searching_File.eof());
            cout<<endl<<endl;
            movie_searching_File.close();
        }
    }
    else
    {
        cout << "No found." << endl;
    }
    
}

bool movie_searching_for_now_showing(string movie_searching_name)
{
    bool Searching;
    string movie_name, movie_detail;
	fstream movie_searching_File;
    movie_searching_File.open("Now Showing Movie Name.txt", ios::in);
    do{
        getline(movie_searching_File, movie_name);
        if(movie_searching_name==movie_name)
        {
            cout<<"\nSearching successful\n";
            Searching= true;
            break;
        }
        if(movie_searching_File.eof()&&movie_searching_name!=movie_name)
        {
            cout<<"\nSearching failed\n";
            Searching= false;
            break;
        }
    }while(!movie_searching_File.eof());
    movie_searching_File.close();
    if(Searching)
    {
        movie_searching_File.open(("movie storage/Now Showing/" + movie_searching_name + ".txt").c_str(), ios::in);
        do{
            getline(movie_searching_File, movie_detail);
            cout<<movie_detail<<endl;
        }while(!movie_searching_File.eof());
        movie_searching_File.close();
    }
    return Searching;
}
bool movie_searching_for_coming_soon(string movie_searching_name)
{
    bool Searching;
    string movie_name, movie_detail;
	fstream movie_searching_File;
    movie_searching_File.open("Coming Soon Movie Name.txt", ios::in);
    do{
        getline(movie_searching_File, movie_name);
        if(movie_searching_name==movie_name)
        {
            cout<<"\nSearching successful\n";
            Searching= true;
            break;
        }
        if(movie_searching_File.eof()&&movie_searching_name!=movie_name)
        {
            cout<<"\nSearching failed\n";
            Searching= false;
            break;
        }
    }while(!movie_searching_File.eof());
    movie_searching_File.close();
    if(Searching)
    {
        movie_searching_File.open(("movie storage/Coming Soon/" + movie_searching_name + ".txt").c_str(), ios::in);
        do{
            getline(movie_searching_File, movie_detail);
            cout<<movie_detail<<endl;
        }while(!movie_searching_File.eof());
        movie_searching_File.close();
    }
    return Searching;
}
