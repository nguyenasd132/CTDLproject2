#include "admin.h"

Admin::Admin() {
    username = "admin";
    password = "admin";
}

Admin::Admin(string user, string pass) {
    username = user;
    password = pass;
}

string Admin::getUsername() { return username; }
string Admin::getPassword() { return password; }

void Admin::setPassword(string newPass) { password = newPass; }

bool Admin::checkLogin(const string &user, const string &pass) {
    return (username == user && password == pass);
}

void Admin::xuatThongTin() {
    cout << "===============================" << endl;
    cout << "Admin username: " << username << endl;
    cout << "===============================" << endl;
}
