#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <cstring> 
#include <fstream>
#include <unistd.h>
#include <ctime>
#include <cctype>
#include <chrono>
#include <vector>
//#include <openssl/sha.h>
//#include <sstream>
using namespace std;
const float ticket_price_A=19, ticket_price_C=12; // ticket_price
const vector<string> seat_id = {
    "A01", "A02", "A03", "A04", "A05", "A06", "A07", "A08", "A09", "A10",
    "B01", "B02", "B03", "B04", "B05", "B06", "B07", "B08", "B09", "B10",
    "C01", "C02", "C03", "C04", "C05", "C06", "C07", "C08", "C09", "C10",
    "D01", "D02", "D03", "D04", "D05", "D06", "D07", "D08", "D09", "D10",
    "E01", "E02", "E03", "E04", "E05", "E06", "E07", "E08", "E09", "E10"
};
struct movies{
	string mv_name;
};
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
struct ticket_in_move {
    string ticket_id;
    ticket_in_move* next;
};


class TicketQueue {
private:
    ticket_in_move* front;
    ticket_in_move* rear;

public:
    TicketQueue() {
        front = nullptr;
        rear = nullptr;
    }

    ~TicketQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(const ticket_in_move& item) {
        ticket_in_move* newTicket = new ticket_in_move;
        newTicket->ticket_id = item.ticket_id;
        newTicket->next = nullptr;

        if (isEmpty()) {
            front = rear = newTicket;
        } else {
            rear->next = newTicket;
            rear = newTicket;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            return;
        }

        ticket_in_move* temp = front;

        if (front == rear) {
            front = rear = nullptr;
        } else {
            front = front->next;
        }

        delete temp;
    }

    ticket_in_move* getFront() const {
        if (isEmpty()) {
            return nullptr;
        }
        return front;
    }
};

struct Member_st {
    string mem_name;
    string mem_phone;
    string mem_email;
    string mem_password;
    Member_st* next;
};

class LinkedQueue {
private:
    Member_st* front; // Points to the front of the queue
    Member_st* rear; // Points to the rear of the queue

public:
    LinkedQueue() {
        front = nullptr;
        rear = nullptr;
    }

    ~LinkedQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(Member_st* member) {
        member->next = nullptr;

        if (isEmpty()) {
            front = rear = member;
        } else {
            rear->next = member;
            rear = rear->next;
        }
    }

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

    Member_st* getFront() {
        if (isEmpty()) {
            return nullptr;
        }

        return front;
    }
};

int readTicketsFromFile(TicketQueue& queue, const string& movie_sel, const string& sel_time) {
    ifstream ticket_file(("movie storage/Seat/" + movie_sel + "/" + sel_time + " " + movie_sel + ".txt").c_str());
    string ticket_id;
    int maxticket = 0;
    if (!ticket_file) {
        cout << "Error in opening ticket file." << endl;
    }

    while (getline(ticket_file, ticket_id)) {
        ticket_in_move newTicket;
        newTicket.ticket_id = ticket_id;
        queue.enqueue(newTicket);
        maxticket++;
    }

    ticket_file.close();
    return maxticket;
}

void readMembersFromFile(LinkedQueue& queue) {
    ifstream memberFile("members.txt");
    
    if (!memberFile) {
        cout << "Error in opening members.txt" << endl;
        return;
    }
    
    string name, phone, email, password, none;
    
    while (getline(memberFile, name)) {
        getline(memberFile, phone);
        getline(memberFile, email);
        getline(memberFile, password);
        getline(memberFile, none);
        
        Member_st* member = new Member_st;
        member->mem_name = name;
        member->mem_phone = phone;
        member->mem_email = email;
        member->mem_password = password;
        member->next = nullptr;
        
        queue.enqueue(member);
    }
    
    memberFile.close();
}
bool check_seat_valid(string sel_seat_id){
    for (const string& str : seat_id) {
        if (sel_seat_id == str) {
            return true;
        }
    }
    return false;
}
bool check_seat_havent(const string& sel_seat_id, const TicketQueue& tic) {
    ticket_in_move* current = tic.getFront();
    while (current != nullptr) {
        if (!current->ticket_id.empty()) {
            if (sel_seat_id == current->ticket_id) {
                return true;
            }
        }
        current = current->next;
    }
    return false;
}

// Hash Search
size_t stringHash(const string& str) {
    size_t hashValue = 0;
    for (char c : str) {
        hashValue += c;
    }
    return hashValue;
}

// Function to compute SHA-256 hash of a string
/*
string computeHash(const string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.length());
    SHA256_Final(hash, &sha256);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << hex << static_cast<int>(hash[i]);
    }
    return ss.str();
}
*/

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
        if (dataHash == findHash) {
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


