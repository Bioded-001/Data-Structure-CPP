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
#include <vector>
using namespace std;
// Stack
struct Session {
    long long start_time;  // The start time of the session
    long long end_time;    // The end time of the session
    long long duration;    // The duration of the session
};

class SessionStack {
private:
    vector<Session> sessions;  // The vector to store the sessions

public:
    SessionStack() {}  // Default constructor, the vector is automatically initialized

    void stack_login() {
        Session session;
        session.start_time = get_current_time();
        sessions.push_back(session);  // Add the session to the vector
    }

    void stack_logout() {
        if (sessions.empty()) {
            cout << "No active session.\n";
            return;
        }

        Session& current_session = sessions.back();  // Get a reference to the current session
        current_session.end_time = get_current_time();
        current_session.duration = current_session.end_time - current_session.start_time;
        sessions.pop_back();  // Remove the last session from the vector

        cout << "The duration time you used is: " << current_session.duration << " seconds\n";
    }

private:
    long long get_current_time() const {
        using namespace chrono;
        return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    }
}stack;

// Selection Sort
void selectionSort(vector<string>& result) {
    int size = result.size();
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (result[j][0] < result[min_idx][0]) {
                min_idx = j;
            }
        }
        swap(result[min_idx], result[i]);
    }
}

// Linked Queue
struct Member_st {
    string mem_name;
    string mem_phone;
    string mem_email;
    string mem_password;
    Member_st* next;
};

//LinkedQueue class
class LinkedQueue {
private:
    Member_st* front; // Points to the front of the queue
    Member_st* rear; // Points to the rear of the queue

public:
    // Constructor
    LinkedQueue() {
        front = nullptr;
        rear = nullptr;
    }

    // Destructor
    ~LinkedQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Function to check if the queue is empty
    bool isEmpty() {
        return (front == nullptr);
    }

    // Function to enqueue a member
    void enqueue(Member_st* member) {
        member->next = nullptr;

        if (isEmpty()) {
            front = rear = member;
        } else {
            rear->next = member;
            rear = member;
        }
    }

    // Function to dequeue a member
    void dequeue() {
        if (isEmpty()) {
            return;
        }

        Member_st* temp = front;

        if (front == rear) {
            front = rear = nullptr;
        } else {
            front = front->next;
        }

        delete temp;
    }

    // Function to get the front member of the queue
    Member_st* getFront() {
        if (isEmpty()) {
            return nullptr;
        }

        return front;
    }
};

// Hash Search
size_t stringHash(const string& str) {
    size_t hashValue = 0;
    for (char c : str) {
        hashValue += c;
    }
    return hashValue;
}

void hashSearch(const string& find, const vector<string>& data, vector<string>& result) {
    size_t findHash = stringHash(find);
    for (const string& str : data) {
        string strLower = str;
        transform(strLower.begin(), strLower.end(), strLower.begin(), [](unsigned char c){ return tolower(c); });

        size_t strHash = stringHash(strLower);
        if (strHash == findHash || strLower.find(find) != string::npos) {
            result.push_back(str);
        }
    }
}
bool hash_Searching(const string& find, const vector<string>& data) {
    size_t findHash = stringHash(find);
    for (const string& str : data) {
        size_t dataHash = stringHash(str);
        if (str == find && dataHash == findHash) {
            cout << "\nSearching successful\n";
            return true;
        }
    }
    cout << "\nSearching failed\n";
    return false;
}


// Function to search for movies in a specific file and directory
void search_for_movies(const string& fileName, const string& directory, const string& find) {
    ifstream movie_searching_File(fileName);
    if (!movie_searching_File) {
        cout << "Failed to open " << fileName << endl;
        return;
    }

    vector<string> data;
    string line;
    while (getline(movie_searching_File, line)) {
        data.push_back(line);
    }
    movie_searching_File.close();

    vector<string> result;
    hashSearch(find, data, result);
    selectionSort(result);

    if (!result.empty()) {
        for (const string& movie : result) {
            ifstream movie_detail_File(directory + movie + ".txt");
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


// Function to search for movies in a specific file and directory
bool movie_searching(const string& fileName, const string& directory, const string& find) {
    ifstream movie_searching_File(fileName);
    if (!movie_searching_File) {
        cout << "Failed to open " << fileName << endl;
        return false;
    }

    vector<string> data;
    string line;
    while (getline(movie_searching_File, line)) {
        data.push_back(line);
    }
    movie_searching_File.close();
    bool Searching = hash_Searching(find, data);

    if (Searching) {
        ifstream movie_detail_File(directory + find + ".txt");
        if (movie_detail_File) {
            while (getline(movie_detail_File, line)) {
                cout << line << endl;
            }
            movie_detail_File.close();
            cout << endl << endl;
        }
    } else {
        cout << "No matches found." << endl;
    }
    return Searching;
}


