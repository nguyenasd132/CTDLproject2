#include "employee.h"

Employee::Employee() {
    maNV = "0000";
    ten = "Unknown";
    ngaysinh = "01/01/2000";
    phai = "None";
    capbac = "NhanVien";
    luong = 0;
    sdt = "0000000000";
    username = "none";
    password = "none";
}

Employee::Employee(string ma, string t, string ns, string gt, string cb, long long l, string sdt, string user, string pass) {
    maNV = ma;
    ten = t;
    ngaysinh = ns;
    phai = gt;
    capbac = cb;
    luong = l;
    this->sdt = sdt;
    username = user;
    password = pass;
}

string Employee::getMaNV() { return maNV; }
string Employee::getTen() { return ten; }
string Employee::getNgaySinh() { return ngaysinh; }
string Employee::getPhai() { return phai; }
string Employee::getCapBac() { return capbac; }
long long Employee::getLuong() { return luong; }
string Employee::getSDT() { return sdt; }
string Employee::getUsername() { return username; }
string Employee::getPassword() { return password; }

void Employee::setPassword(string newPass) { password = newPass; }

void Employee::xuatThongTin() {
    cout << "---------------------------------" << endl;
    cout << "Ma NV: " << maNV << endl;
    cout << "Ten: " << ten << endl;
    cout << "Ngay sinh: " << ngaysinh << endl;
    cout << "Phai: " << phai << endl;
    cout << "Cap bac: " << capbac << endl;
    cout << "Luong: " << luong << endl;
    cout << "SDT: " << sdt << endl;
    cout << "Username: " << username << endl;
    cout << "---------------------------------" << endl;
}
