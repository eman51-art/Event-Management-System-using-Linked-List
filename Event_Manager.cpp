#include <iostream>
#include <string>
#include <limits>  // for numeric_limits
#include <regex>

using namespace std;

// ================= Node class =================
class Node {
public:
    string eventName;   // Event name
    string eventDate;   // Event date
    Node* next;         // Pointer to next node

    Node(string name, string date) {
        eventName = name;
        eventDate = date;
        next = nullptr;
    }
};

// ================ SingleLinkedList class ================
class SingleLinkedList {
public:
    Node* head = nullptr;

    // Add event at the end
    void addevent(string s, string d) {
        Node* newnode = new Node(s, d);
        if(head == nullptr) {
            head = newnode;
            return;
        }
        Node* temp = head;
        while(temp->next != nullptr) temp = temp->next;
        temp->next = newnode;
    }

    // View all events
    void seeevent() {
        if(head == nullptr) {
            cout << "No events found.\n";
            return;
        }
        Node* temp = head;
        while(temp != nullptr) {
            cout << temp->eventName << " at " << temp->eventDate << "\n";
            temp = temp->next;
        }
        cout << "Event list finished.\n";
    }

    // Search event by substring in name
    void searchevent(string search) {
        if(head == nullptr) {
            cout << "No events found.\n";
            return;
        }
        Node* temp = head;
        bool found = false;
        while(temp != nullptr) {
            if(temp->eventName.find(search) != string::npos) {
                cout << "Found: " << temp->eventName << " at " << temp->eventDate << "\n";
                found = true;
            }
            temp = temp->next;
        }
        if(!found) cout << "No event found containing: " << search << "\n";
    }

    // Delete event by position
    void deleteEvent(int pos) {
        if(head == nullptr) {
            cout << "No events to delete.\n";
            return;
        }
        if(pos == 1) { Node* t = head; head = head->next; delete t; return; }

        Node* temp = head;
        for(int i=1; i<pos-1 && temp!=nullptr; i++) temp = temp->next;

        if(temp == nullptr || temp->next == nullptr) {
            cout << "Invalid position!\n";
            return;
        }

        Node* t = temp->next;
        temp->next = t->next;
        delete t;
    }

    // Update event by name
    void updateEvent(string oldEvent, string newEvent) {
        if(head == nullptr) { cout<<"No events found!\n"; return; }
        Node* temp = head;
        bool found = false;
        while(temp != nullptr) {
            if(temp->eventName.find(oldEvent) != string::npos) {
                temp->eventName = newEvent;
                found = true;
                break;
            }
            temp = temp->next;
        }
        if(!found) cout<<"No event exists: "<<oldEvent<<"\n";
    }

    // Validate date format YYYY-MM-DD
    bool isValidDate(string date){
        string pattern = "^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$";
        regex r(pattern);
        return regex_match(date, r);
    }

    // Search events by date
    void searchByDate(string date) {
        if (!isValidDate(date)) {
            cout << "Invalid date. Please enter in YYYY-MM-DD format.\n";
            return;
        }

        Node* temp = head;
        bool found = false;

        while (temp != nullptr) {
            if (temp->eventDate == date) {
                found = true;
                cout << "Event found:\n";
                cout << "Name: " << temp->eventName << " at Date: " << temp->eventDate << "\n";
            }
            temp = temp->next;
        }

        if (!found) {
            cout << "No events found on this date.\n";
        }
    }
};

// ================= Main function =================
int main() {
    SingleLinkedList l;
    int choice = 0;
    string name, oldName, newName, date;
    int pos;

    while(choice != 7) {
        cout << "\n--- Event Manager Menu ---\n";
        cout << "1. Add Event\n2. Delete Event\n3. Update Event\n4. View Events\n5. Search Event by Name\n6. Search Event by Date\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush newline

        switch(choice) {
            case 1:
                cout << "Enter your event name: ";
                getline(cin, name);

                cout << "Enter date of event (YYYY-MM-DD): ";
                getline(cin, date);

                while(!l.isValidDate(date)) {
                    cout << "Enter correct date (YYYY-MM-DD): ";
                    getline(cin, date);
                }

                l.addevent(name, date);
                cout << "Event added!\n";
                break;

            case 2:
                l.seeevent();
                cout << "Enter position of event to delete: ";
                cin >> pos;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                l.deleteEvent(pos);
                break;

            case 3:
                cout << "Enter event name to update: ";
                getline(cin, oldName);
                cout << "Enter new event name: ";
                getline(cin, newName);
                l.updateEvent(oldName, newName);
                break;

            case 4:
                l.seeevent();
                break;

            case 5:
                cout << "Enter search string: ";
                getline(cin, name);
                l.searchevent(name);
                break;

            case 6:
                cout << "Enter date to search (YYYY-MM-DD): ";
                getline(cin, date);
                l.searchByDate(date);
                break;

            case 7:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
