#pragma once
#include <iostream>
#include <string>

using namespace std;

class v_Client {
private:
    string mail;
    string password;
    string userName;
    float score;

public:
    v_Client() : mail(""), password(""), userName(""), score(0) {}

    v_Client(string mail, string password, string userName)
        : mail(mail), password(password), userName(userName), score(0) {}

    virtual ~v_Client() {}

    virtual bool setUserName(string userName) {
        if (userName.size() > 3) {
            this->userName = userName;
            return true;
        }
        else {
            cout << "User name length must be bigger than 3\n";
            return false;
        }
    }

    virtual bool changePassword(string password1) {
        if (password1.size() > 5) {
            this->password = password1;
            return true;
        }
        else {
            cout << "Password length must be bigger than 5\n";
            return false;
        }
    }

    string getPassword() {
        return password;
    }

    string getUserName() {
        return userName;
    }
    string getEmail() {
        return mail;
    }
    int getScore() {
        return score;
    }
};