#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
using namespace std;

class Admin {
private:
    string username;
    string password;
public:
    Admin();
    Admin(string user, string pass);
    string getUsername();
    string getPassword();
    void setPassword(string newPass);
    bool checkLogin(const string &user, const string &pass);
    void xuatThongTin();
};
#endif
