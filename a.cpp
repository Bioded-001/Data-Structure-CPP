#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

// Member structure
struct Member_st {
    string mem_name;
    string mem_phone;
    string mem_email;
    string mem_password;
    Member_st* next;
};

// Linked Queue class
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

void view_member() {
    int i = 1;
    string none;
    const int nameWidth = 20;
    ifstream cusfile("members.txt");
    if (cusfile.fail()) {
        cout << "File opening failed.\n";
    } else {
        LinkedQueue memberQueue; // Create a LinkedQueue object to store member information
        Member_st cus;
        while (!cusfile.eof()) {
            getline(cusfile, cus.mem_name);
            getline(cusfile, cus.mem_phone);
            getline(cusfile, cus.mem_email);
            getline(cusfile, cus.mem_password);
            getline(cusfile, none);
            if (!cusfile.eof()) {
                Member_st* newMember = new Member_st;
                newMember->mem_name = cus.mem_name;
                newMember->mem_phone = cus.mem_phone;
                newMember->mem_email = cus.mem_email;
                newMember->mem_password = cus.mem_password;
                memberQueue.enqueue(newMember); // Enqueue member
                i++;
            }
        }

        cusfile.close();

        // Display the member information from the queue
        if (memberQueue.isEmpty()) {
            cout << "No member information available." << endl;
        } else {
            cout << "-----------------------------------------------------------------------------------Member Information-----------------------------------------------------------------------------------" << endl;
            while (!memberQueue.isEmpty()) {
                Member_st* member = memberQueue.getFront();
                memberQueue.dequeue();
                cout << i << ". Member Name : " << left << setw(nameWidth) << member->mem_name;
                cout << "| Member Phone Number : " << left << setw(nameWidth) << member->mem_phone;
                cout << "| Member Email : " << left << setw(nameWidth) << member->mem_email;
                cout << "| Member Password : " << member->mem_password << endl;
                delete member;
                i++;
            }
        }
    }
}

int main() {
    view_member();

    return 0;
}
