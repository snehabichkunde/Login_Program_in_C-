#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std; 

class User {
public:
    User(const string& username, const string& password)
        : username(username), password(password) {}

    const string& getUsername() const {
        return username;
    }

    const string& getPassword() const {
        return password;
    }

private:
    string username;
    string password;
};

class UserManager {
public:
    UserManager() {
        loadUsers();
    }

    bool login() {
        string username, password;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        for (const User& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                cout << "Login successful. Welcome, " << username << "!" << endl;
                return true;
            }
        }

        cout << "Login failed. Invalid username or password." << endl;
        return false;
    }

    void createUser() {
        string username, password;
        cout << "Create a new account\n";
        cout << "Username: ";
        cin >> username;

        if (isUsernameTaken(username)) {
            cout << "Username is already taken. Choose a different one." << endl;
            return;
        }

        cout << "Password: ";
        cin >> password;

        User newUser(username, password);
        users.push_back(newUser);
        saveUsers();
        cout << "Account created successfully." << endl;
    }

private:
    vector<User> users;

    void loadUsers() {
        loadUsernames("usernames.txt");
        loadPasswords("passwords.txt");
    }

    void loadUsernames(const string& usernameFile) {
        ifstream file(usernameFile);
        if (!file) {
            return;
        }

        string username;
        while (file >> username) {
            User user(username, "");
            users.push_back(user);
        }

        file.close();
    }

    void loadPasswords(const string& passwordFile) {
        ifstream file(passwordFile);
        if (!file) {
            return;
        }

        for (size_t i = 0; i < users.size(); i++) {
            string password;
            if (file >> password) {
                users[i] = User(users[i].getUsername(), password);
            }
        }

        file.close();
    }

    void saveUsers() {
        saveUsernames("usernames.txt");
        savePasswords("passwords.txt");
    }

    void saveUsernames(const string& usernameFile) {
        ofstream file(usernameFile);
        if (!file) {
            cerr << "Error: Unable to save usernames." << endl;
            return;
        }

        for (const User& user : users) {
            file << user.getUsername() << '\n';
        }

        file.close();
    }

    void savePasswords(const string& passwordFile) {
        ofstream file(passwordFile);
        if (!file) {
            cerr << "Error: Unable to save passwords." << endl;
            return;
        }

        for (const User& user : users) {
            file << user.getPassword() << '\n';
        }

        file.close();
    }

    bool isUsernameTaken(const string& username) {
        for (const User& user : users) {
            if (user.getUsername() == username) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    UserManager userManager;
    int choice;

    while (true) {
        cout << "Choose an option:\n";
        cout << "1. Login\n";
        cout << "2. Create an account\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                userManager.login();
                break;
            case 2:
                userManager.createUser();
                break;
            case 3:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cerr << "Invalid choice. Please choose a valid option." << endl;
        }
    }

    return 0;
}
