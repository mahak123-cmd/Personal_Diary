#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Entry {
    string title;
    string date;
    string content;
};

vector<Entry> diary;
string password = "1234";

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d", ltm);
    return string(date);
}

bool authenticate() {
    string inputPassword;
    cout << "Enter password to access the diary: ";
    cin >> inputPassword;
    return inputPassword == password;
}

void createEntry() {
    Entry newEntry;
    cin.ignore();
    cout << "Enter title: ";
    getline(cin, newEntry.title);
    newEntry.date = getCurrentDate();
    cout << "Enter your journal entry (type END on a new line to finish):\n";
    string line;
    while (true) {
        getline(cin, line);
        if (line == "END") break;
        newEntry.content += line + "\n";
    }
    diary.push_back(newEntry);
    cout << "Entry saved successfully!\n";
}

void viewEntries() {
    if (diary.empty()) {
        cout << "No diary entries found.\n";
        return;
    }
    for (size_t i = 0; i < diary.size(); i++) {
        cout << "\n" << i + 1 << ". " << diary[i].title << " (" << diary[i].date << ")\n";
    }
}

void readEntry() {
    int index;
    viewEntries();
    cout << "Enter entry number to read: ";
    cin >> index;
    if (index > 0 && index <= diary.size()) {
        cout << "\nTitle: " << diary[index - 1].title << "\nDate: " << diary[index - 1].date << "\n";
        cout << "Content:\n" << diary[index - 1].content << "\n";
    } else {
        cout << "Invalid entry number!\n";
    }
}

void saveToFile() {
    ofstream file("diary.txt");
    for (const auto &entry : diary) {
        file << entry.title << "\n" << entry.date << "\n" << entry.content << "---\n";
    }
    file.close();
    cout << "Diary saved to file successfully!\n";
}

void loadFromFile() {
    ifstream file("diary.txt");
    if (!file) return;
    diary.clear();
    Entry entry;
    string line;
    while (getline(file, entry.title) && getline(file, entry.date)) {
        entry.content = "";
        while (getline(file, line) && line != "---") {
            entry.content += line + "\n";
        }
        diary.push_back(entry);
    }
    file.close();
}

int main() {
    if (!authenticate()) {
        cout << "Incorrect password. Access denied!\n";
        return 0;
    }
    
    loadFromFile();
    int choice;
    do {
        cout << "\nPersonal Diary Menu:";
        cout << "\n1. Create Entry\n2. View Entries\n3. Read Entry\n4. Save and Exit\nChoose an option: ";
        cin >> choice;
        
        switch (choice) {
            case 1: createEntry(); break;
            case 2: viewEntries(); break;
            case 3: readEntry(); break;
            case 4: saveToFile(); cout << "Exiting diary.\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
    
    return 0;
}
