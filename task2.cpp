#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function declarations
void registerUser();
bool loginUser();
bool userExists(const string& username);

int main() {
    int choice;

    while (true) {
        cout << "========================\n";
        cout << "1. Register\n2. Login\n3. Exit\nChoose an option: ";
        cin >> choice;
        cin.ignore(); // Ignore trailing newline

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    cout << "Login successful!\n";
                } else {
                    cout << "Login failed. Please try again.\n";
                }
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}

void registerUser() {
    string username, password;
    
    cout << "Enter a username: ";
    cin >> username;

    if (userExists(username)) {
        cout << "Username already exists. Please choose another.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    // Save the credentials to a file
    ofstream outFile("database.txt", ios::app);
    if (outFile.is_open()) {
        outFile << username << " " << password << "\n";
        outFile.close();
        cout << "Registration successful!\n";
    } else {
        cout << "Error opening file for registration.\n";
    }
}

bool loginUser() {
    string username, password, fileUsername, filePassword;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream inFile("database.txt");
    if (inFile.is_open()) {
        while (inFile >> fileUsername >> filePassword) {
            if (fileUsername == username && filePassword == password) {
                inFile.close();
                return true;
            }
        }
        inFile.close();
    } else {
        cout << "Error opening file for login.\n";
    }

    return false;
}

bool userExists(const string& username) {
    string fileUsername, filePassword;
    ifstream inFile("database.txt");

    if (inFile.is_open()) {
        while (inFile >> fileUsername >> filePassword) {
            if (fileUsername == username) {
                inFile.close();
                return true;
            }
        }
        inFile.close();
    }

    return false;
}
