#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct USER{
    string username;
    string password;
}user;

void add_user(vector<USER>& users){
    ofstream data("data.txt", ios::app);
    string username;
    string password;
    cin.ignore();
    cout << "Input your account's username: " << endl;
    getline(cin,username);
    data << username << endl;
    cout << "Input a secure password for your account " << endl;
    getline(cin,password);
    data << password << endl;

    users.push_back({username, password});

    data.close();
}

USER* log_in(vector<USER>& users) {
    string username;
    cout << "Input your account's username:";
    cin >> username;
    for (auto &user: users) {
        if (user.username == username) {
            string password;
            cout << "Input the password for your account: " << endl;
            cin >> password;
            if (user.password == password) {
                return &user;
            } else {
                cout << "Inputted password is incorrect!" << endl;
                return nullptr;
            }

        }
    }
    cout << "No user with a matching username found!" << endl;
    return nullptr;

}

void read_data(vector<USER>& users){

    ifstream data("data.txt");
    string uname, passwd;

    if(!data.is_open()){
        cout << "Could not read data file!";
    }

    while(getline(data,uname) && getline(data,passwd)){
        users.push_back({uname, passwd,});
        data.ignore();
    }
    data.close();
}

int main() {
    vector<USER> users;
    read_data(users);
    USER* token = nullptr;
    int choice;
    while(true){
    cout << "Greetings dear user, would you like to: " << endl;
    cout << "1 - Create a new account "<< endl;
    cout << "2 - Log into an existing account" << endl;
    cin >> choice;

        if(choice == 1){
            add_user(users);
            read_data(users);
            continue;
        }
        else if(choice == 2){
            token = log_in(users);
            if(token != nullptr){
                break;
            }
            else{
                continue;
            }
        }
    }
        cout << "You've successfully logged in!";
    return 0;
}
