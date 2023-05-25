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
#include <chrono>
using namespace std;
// Here is stack
struct Session {
    long long start_time;
    long long end_time;
    long long duration;
};

class SessionStack {
private:
    static const int MAX_SIZE = 100;
    Session sessions[MAX_SIZE];
    int top_index;

public:
    SessionStack() : top_index(-1) {}

    void stack_login()
    {
        if (top_index == MAX_SIZE - 1) {
            std::cout << "Session stack is full.\n";
            return;
        }

        Session session;
        session.start_time = get_current_time();
        sessions[++top_index] = session;
    }

    void stack_logout()
    {
        if (top_index == -1) {
            std::cout << "No active session.\n";
            return;
        }

        Session& current_session = sessions[top_index];
        current_session.end_time = get_current_time();
        current_session.duration = current_session.end_time - current_session.start_time;
        top_index--;

        std::cout << "The duration time you used is: " << current_session.duration << " seconds\n";
    }

private:
    long long get_current_time() const
    {
        using namespace std::chrono;
        return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    }
}stack;
// Here is stack
// Here is selectionSort
void selectionSort(string* result, int size) {
    int i, j, min_idx;
    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < size; j++) {
            if (result[j][0] < result[min_idx][0]) {
                min_idx = j;
            }
        }
        swap(result[min_idx], result[i]);
    }
}

// Here is selectionSort
// Here is hashSearch
void hashSearch(string& find, string* data, int dataSize, string* result, int & resultSize)
{
    // Initialize hash function
    std::hash<std::string> strHash;

    // Convert the find string to lowercase
    transform(find.begin(), find.end(), find.begin(), [](unsigned char c){ return tolower(c); });

    // Loop through the data array and find similar strings
    for (int i = 0; i < dataSize; i++)
    {
        // Convert the current string to lowercase
        string strLower = data[i];
        transform(strLower.begin(), strLower.end(), strLower.begin(), [](unsigned char c){ return tolower(c); });

        // Generate hash value of current string
        size_t strHashVal = strHash(strLower);

        // Compare hash values and check if the current string contains the find string as a substring
        if (strHashVal == strHash(find) || strLower.find(find) != string::npos)
        {
            // If hash values match or the current string contains the find string, add the string to the result array
            result[resultSize] = data[i];
            resultSize++;
        }
    }
}

// Here is hashSearch
const int MAX_SIZE = 100; 


void search_for_ns(string& find) {
    ifstream movie_searching_File("Now Showing Movie Name.txt");
    if (!movie_searching_File) {
        cout << "Failed to open Now Showing Movie Name.txt" << endl;
        return;
    }

    string data[MAX_SIZE];
    int dataSize = 0;
    string line;
    while (getline(movie_searching_File, line) && dataSize < MAX_SIZE) {
        data[dataSize++] = line;
    }
    movie_searching_File.close();

    int resultSize = 0;
    string result[MAX_SIZE];

    hashSearch(find, data, dataSize, result, resultSize);
    selectionSort(result, resultSize);

    if (resultSize > 0) {
        for (int i = 0; i < resultSize; i++) {
            ifstream movie_detail_File("movie storage/Now Showing/" + result[i] + ".txt");
            if (movie_detail_File) {
                while (getline(movie_detail_File, line)) {
                    cout << line << endl;
                }
                movie_detail_File.close();
                cout << endl << endl;
            }
        }
    } else {
        cout << "No matches found." << endl;
    }
}

void search_for_cs(string& find) {
    ifstream movie_searching_File("Coming Soon Movie Name.txt");
    if (!movie_searching_File) {
        cout << "Failed to open Coming Soon Movie Name.txt" << endl;
        return;
    }

    string data[MAX_SIZE];
    int dataSize = 0;
    string line;
    while (getline(movie_searching_File, line) && dataSize < MAX_SIZE) {
        data[dataSize++] = line;
    }
    movie_searching_File.close();

    int resultSize = 0;
    string result[MAX_SIZE];

    hashSearch(find, data, dataSize, result, resultSize);
    selectionSort(result, resultSize);

    if (resultSize > 0) {
        for (int i = 0; i < resultSize; i++) {
            ifstream movie_detail_File("movie storage/Coming Soon/" + result[i] + ".txt");
            if (movie_detail_File) {
                while (getline(movie_detail_File, line)) {
                    cout << line << endl;
                }
                movie_detail_File.close();
                cout << endl << endl;
            }
        }
    } else {
        cout << "No matches found." << endl;
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
