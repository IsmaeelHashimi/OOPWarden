// OOPWarden.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

    string password;
    cout << "Enter master password: " << endl;
    cin >> password;

    if (!user.authenticate(password)) {
        cout << "Authentication failed!\n";
        return 1;
    }

    user.addCredential("example.com", "user", "password");
    user.displayCredentials();

    return 0;
}
