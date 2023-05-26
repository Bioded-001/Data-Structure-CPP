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
    long long start_time;  // The start time of the session
    long long end_time;    // The end time of the session
    long long duration;    // The duration of the session
};

class SessionStack {
private:
    static const int MAX_SIZE = 100;  // The maximum size of the stack
    Session sessions[MAX_SIZE];       // The array to store the sessions
    int top_index;                    // The index of the top of the stack

public:
    SessionStack() : top_index(-1) {} // Constructor initializes the top index to -1

    void stack_login()  // Method to start a new session and push it onto the stack
    {
        if (top_index == MAX_SIZE - 1) {  // If the stack is full, print an error message
            std::cout << "Session stack is full.\n";
            return;
        }

        Session session;  // Create a new session
        session.start_time = get_current_time();  // Set the start time of the session to the current time
        sessions[++top_index] = session;  // Push the session onto the stack
    }

    void stack_logout()  // Method to end the current session and pop it from the stack
    {
        if (top_index == -1) {  // If the stack is empty, print an error message
            std::cout << "No active session.\n";
            return;
        }

        Session& current_session = sessions[top_index];  // Get a reference to the current session
        current_session.end_time = get_current_time();  // Set the end time of the session to the current time
        current_session.duration = current_session.end_time - current_session.start_time;  // Calculate the duration of the session
        top_index--;  // Pop the session from the stack

        std::cout << "The duration time you used is: " << current_session.duration << " seconds\n";  // Print the duration of the session
    }

private:
    long long get_current_time() const  // Method to get the current time
    {
        using namespace std::chrono;
        return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    }
}stack;
// Here is stack

// Here is selectionSort
void selectionSort(string* result, int size) {
    int i, j, min_idx;
    for (i = 0; i < size - 1; i++) {  // Iterate over each element in the array
        min_idx = i;  // Assume the current element is the smallest
        for (j = i + 1; j < size; j++) {  // Iterate over the remaining elements
            if (result[j][0] < result[min_idx][0]) {  // If a smaller element is found, update min_idx
                min_idx = j;
            }
        }
        swap(result[min_idx], result[i]);  // Swap the smallest element found with the current element
    }
}
// Here is selectionSort

// Here is hashSearch
size_t stringHash(const string& str) {
    size_t hashValue = 0;
    for (char c : str) {  // Iterate over each character in the string
        hashValue += c;  // Add the ASCII value of the character to the hash value
    }
    return hashValue;  // Return the hash value
}

void hashSearch(string& find, string* data, int dataSize, string* result, int & resultSize)
{
    // Loop through the data array and find similar strings
    for (int i = 0; i < dataSize; i++)
    {
        // Convert the current string to lowercase
        string strLower = data[i];
        transform(strLower.begin(), strLower.end(), strLower.begin(), [](unsigned char c){ return tolower(c); });

        // Generate hash value of current string
        size_t strHashVal = stringHash(strLower);

        // Compare hash values and check if the current string contains the find string as a substring
        if (strHashVal == stringHash(find) || strLower.find(find) != string::npos)
        {
            // If hash values match or the current string contains the find string, add the string to the result array
            result[resultSize] = data[i];
            resultSize++;
        }
    }
}

// Here is hashSearch
// Maximum size of the data array
const int MAX_SIZE = 100; 

// Function to search for a string in the "Now Showing" movies
void search_for_ns(string find) {
    // Open the file containing the names of the "Now Showing" movies
    ifstream movie_searching_File("Now Showing Movie Name.txt");
    // If the file cannot be opened, print an error message and return
    if (!movie_searching_File) {
        cout << "Failed to open Now Showing Movie Name.txt" << endl;
        return;
    }

    // Initialize an array to hold the movie names and a counter for the number of names
    string data[MAX_SIZE];
    int dataSize = 0;
    string line;
    // Read the movie names from the file into the array
    while (getline(movie_searching_File, line) && dataSize < MAX_SIZE) {
        data[dataSize++] = line;
    }
    // Close the file after reading
    movie_searching_File.close();

    // Initialize an array to hold the search results and a counter for the number of results
    int resultSize = 0;
    string result[MAX_SIZE];

    // Perform a hash search on the movie names using the input string
    hashSearch(find, data, dataSize, result, resultSize);
    // Sort the search results
    selectionSort(result, resultSize);

    // If any matches were found, print the details of the matching movies
    if (resultSize > 0) {
        for (int i = 0; i < resultSize; i++) {
            // Open the file containing the details of the current movie
            ifstream movie_detail_File("movie storage/Now Showing/" + result[i] + ".txt");
            // If the file can be opened, read and print its contents
            if (movie_detail_File) {
                while (getline(movie_detail_File, line)) {
                    cout << line << endl;
                }
                // Close the file after reading
                movie_detail_File.close();
                cout << endl << endl;
            }
        }
    } else {
        // If no matches were found, print a message
        cout << "No matches found." << endl;
    }
}

// Function to search for a string in the "Coming Soon" movies
// This function works the same way as the search_for_ns function, but it reads from a different file
void search_for_cs(string find) {
    // Open the file containing the names of the "Coming Soon" movies
    ifstream movie_searching_File("Coming Soon Movie Name.txt");
    // If the file cannot be opened, print an error message and return
    if (!movie_searching_File) {
        cout << "Failed to open Coming Soon Movie Name.txt" << endl;
        return;
    }

    // Initialize an array to hold the movie names and a counter for the number of names
    string data[MAX_SIZE];
    int dataSize = 0;
    string line;
    // Read the movie names from the file into the array
    while (getline(movie_searching_File, line) && dataSize < MAX_SIZE) {
        data[dataSize++] = line;
    }
    // Close the file after reading
    movie_searching_File.close();

    // Initialize an array to hold the search results and a counter for the number of results
    int resultSize = 0;
    string result[MAX_SIZE];

    // Perform a hash search on the movie names using the input string
    hashSearch(find, data, dataSize, result, resultSize);
    // Sort the search results
    selectionSort(result, resultSize);

    // If any matches were found```cpp
    // If any matches were found, print the details of the matching movies
    if (resultSize > 0) {
        for (int i = 0; i < resultSize; i++) {
            // Open the file containing the details of the current movie
            ifstream movie_detail_File("movie storage/Coming Soon/" + result[i] + ".txt");
            // If the file can be opened, read and print its contents
            if (movie_detail_File) {
                while (getline(movie_detail_File, line)) {
                    cout << line << endl;
                }
                // Close the file after reading
                movie_detail_File.close();
                cout << endl << endl;
            }
        }
    } else {
        // If no matches were found, print a message
        cout << "No matches found." << endl;
    }
}

// Function to search for a specific movie in the "Now Showing" list
bool movie_searching_for_now_showing(string movie_searching_name)
{
    // Initialize a boolean variable to indicate whether the movie was found
    bool Searching;
    string movie_name, movie_detail;
    // Open the file containing the names of the "Now Showing" movies
    fstream movie_searching_File;
    movie_searching_File.open("Now Showing Movie Name.txt", ios::in);
    // Loop until the end of the file is reached
    do{
        // Read a movie name from the file
        getline(movie_searching_File, movie_name);
        // If the movie name matches the input string, print a success message, set Searching to true, and break the loop
        if(movie_searching_name==movie_name)
        {
            cout<<"\nSearching successful\n";
            Searching= true;
            break;
        }
        // If the end of the file is reached and the movie name does not match the input string, print a failure message and set Searching to false
        if(movie_searching_File.eof()&&movie_searching_name!=movie_name)
        {
            cout<<"\nSearching failed\n";
            Searching= false;
            break;
        }
    }while(!movie_searching_File.eof());
    // Close the file after reading
    movie_searching_File.close();
    // If the movie was found, open the file containing its details and print them
    if(Searching)
    {
        movie_searching_File.open(("movie storage/Now Showing/" + movie_searching_name + ".txt").c_str(), ios::in);
        do{
            getline(movie_searching_File, movie_detail);
            cout<<movie_detail<<endl;
        }while(!movie_searching_File.eof());
        movie_searching_File.close();
    }
    // Return whether the movie was found
    return Searching;
}

// Function to search for a specific movie in the "Coming Soon" list
// This function works the same way as the movie_searching_for_now_showing function, but it reads from a different file and directory
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
