// OOPWarden.cpp 
// Ismaeel Hashimi

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;


class Credential {
public:
    Credential(const string& website, const string& username, const string& password)
        :website(website), username(username), password(password) {}

    void display() const {
        cout << "Website: " << website << ", Username: " << username << "\n";
    }

    // Getter functions

    const string& getWebsite() const {
        return website;
    }

    const string& getUsername() const {
        return username;
    }

    const string& getPassword() const {
        return password;
    }

    // Setter functions

    void setWebsite(const string& website) {
        this->website = website;
    }

    void setUsername(const string& username) {
        this->username = username;
    }
    
    void setPassword(const string& password) {
        this->password = password;
    }
private:
    string website;
    string username;
    string password;
};


class User {
public:
    User(const string& username, const string& masterPassword)
        : username(username), masterPassword(masterPassword) {}

    bool authenticate(const string& password) const {
        return password == masterPassword;
    }

    void addCredential(const string& website, const string& username, const string& password) {
        credentials.emplace(website, Credential(website, username, password));
    }

    void updateCredential(const string& website, const string& username, const string& password) {
        auto it = credentials.find(website);
        if (it != credentials.end()) {
            it->second.setUsername(username);
            it->second.setPassword(password);
        }
        else {
            cout << "Credential not found for website: " << website << endl;
        }
    }

    void deleteCredential(const string& website) {
        auto it = credentials.find(website);
        if (it != credentials.end()) {
            credentials.erase(it);
        }
        else {
            cout << "Credential not found for website: " << website << endl;
        }
    }

    void searchCredentials(const string& website) const {
        auto it = credentials.find(website);
        if (it != credentials.end()) {
            it->second.display();
        }
        else {
            cout << "Credential not found for website: " << website << endl;
        }
    }

    void displayCredentials() const {
        for (const auto& pair : credentials) {
            pair.second.display();
        }
    }

private:
    string username;
    string masterPassword;
    unordered_map<string, Credential> credentials;
};


int main()
{
    User user("myUser", "masterPassword");
    string website;
    string username;
    string password;
    int userInput;
    cout << "Enter master password: " << endl;
    cin >> password;

    if (!user.authenticate(password)) {
        cout << "Authentication failed!\n";
        return 1;
    }

    user.addCredential("example.com", "user", "password");
    user.displayCredentials();
    bool keepGoing = true;
    while (keepGoing) {
        cout << "What option do you want to select?: " << endl;
        cout << "[1] Add a credential" << endl;
        cout << "[2] Update a credential" << endl;
        cout << "[3] Delete a credential" << endl;
        cout << "[4] Check if a credential exists" << endl;
        cout << "[9] Quit program" << endl;
        cin >> userInput;
        switch (userInput) {
        case 1:
            cout << "What is the name of the website you want to add credentials for?: ";
            cin >> website;
            cout << endl;
            cout << "What is your username for this website?: ";
            cin >> username;
            cout << endl;
            cout << "What is your password for this website?: ";
            cin >> password;
            cout << endl;
            user.addCredential(website, username, password);
            break;

        case 9:
            cout << "Thank you for using OOPWarden, continue keeping your passwords safe." << endl;
            keepGoing = false;
            return -1;
        }
    }
    
    return 0;
}
