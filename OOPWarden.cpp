// OOPWarden.cpp 
// Ismaeel Hashimi

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
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

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& pair : credentials) {
                const Credential& credential = pair.second;
                file << credential.getWebsite() << ','
                    << credential.getUsername() << ','
                    << credential.getPassword() << '\n';
            }
            file.close();
        }
        else {
            cerr << "Unable to open file for writing.";
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string website, username, password;
                getline(ss, website, ',');
                getline(ss, username, ',');
                getline(ss, password, ',');
                addCredential(website, username, password);
            }
            file.close();
        }
        else {
            cerr << "Unable to open file for reading: ";
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
    string userFilename = "save";
    int userInput;
    cout << "Enter master password: " << endl;
    cin >> password;
    cout << endl;
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
        cout << "[5] Display all websites and usernames" << endl;
        cout << "[6] Save credentials to a file" << endl;
        cout << "[7] Load credentials from file" << endl;
        cout << "[9] Quit program" << endl;
        cin >> userInput;
        cout << endl;
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
            cout << "Successfully added!" << endl << endl;
            break;
        case 2:
            cout << "What is the name of the website you want to change update the credentials to?: ";
            cin >> website;
            cout << endl;
            cout << "What is the new username you want for this website?: ";
            cin >> username;
            cout << endl;
            cout << "What is the new password you want for this website?: ";
            cin >> password;
            cout << endl;
            user.updateCredential(website, username, password);
            cout << "Successfully updated!" << endl << endl;
            break;
        case 3:
            cout << "What is the name of the website credentials you wish to delete?: ";
            cin >> website;
            user.deleteCredential(website);
            cout << "Successfully deleted " << website << "'s credentials!" << endl << endl;
            break;

        case 4:
            cout << "For what website do you wish to check if credentials exist for?: ";
            cin >> website;
            cout << endl << endl;
            user.searchCredentials(website);
            break;

        case 5:
            user.displayCredentials();
            cout << endl;
            break;

        case 6:
            user.saveToFile(userFilename);
            cout << "Successfully saved credentials to file!" << endl;
            break;
            
        case 7:
            user.loadFromFile(userFilename);
            cout << "Successfully loaded credentials from file!" << endl;
            break;

        case 9:
            cout << "Thank you for using OOPWarden, continue keeping your passwords safe." << endl;
            keepGoing = false;
            return -1;
        }
    }
    
    return 0;
}
