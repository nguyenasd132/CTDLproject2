#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string maNV;
    string ten;
    string ngaysinh;
    string phai;
    string capbac;
    long long luong;
    string sdt;
    string username;
    string password;
public:
    Employee();
    Employee(string ma, string t, string ns, string gt, string cb, long long l, string sdt, string user, string pass);

    string getMaNV();
    string getTen();
    string getNgaySinh();
    string getPhai();
    string getCapBac();
    long long getLuong();
    string getSDT();
    string getUsername();
    string getPassword();

    void setPassword(string newPass);
    void xuatThongTin();
};

#endif
