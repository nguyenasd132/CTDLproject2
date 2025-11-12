#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "employee.h"
#include "admin.h"
using namespace std;

vector<Employee> ds;

void setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
    cout << flush;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void pauseConsole() {
    cout << "Nhấn phím enter để tiếp tục...";
    cin.get();
}

string inputLine(const string &label) {
    cout << label;
    string s;
    getline(cin,s);
    return s;
}

void printTitle(const string &title) {
    setColor(12);
    cout << "==================== " << title << " ===================="<<endl;
    setColor(7);
}


void printError(const string &msg) {
    setColor(12); // đỏ
    cout << "[Lỗi] " << msg << endl;
    setColor(7);
}

void printOk(const string &msg) {
    setColor(10); // xanh lá
    cout << "[OK] " << msg << endl;
    setColor(7);
}

void saveEmployees() {
    ofstream out("nhanvien.txt");
    for (auto &e : ds) {
        out << e.getMaNV() << " " << e.getTen() << " " << e.getNgaySinh() << " "
            << e.getPhai() << " " << e.getCapBac() << " " << e.getLuong() << " "
            << e.getSDT() << " " << e.getUsername() << " " << e.getPassword() << endl;
    }
    out.close();
}

void addEmployee() {
    string ma, ten, ns, phai, capbac, sdt, user, pass;
    long long luong;
    cout << "Nhập mã NV: "; cin >> ma;
    cin.ignore();
    cout << "Nhập tên: "; getline(cin, ten);
    cout << "Nhập ngày sinh (dd/mm/yyyy): "; getline(cin, ns);
    cout << "Nhập giới tính: "; getline(cin, phai);
    cout << "Nhập cấp bậc: "; getline(cin, capbac);
    cout << "Nhập lương: "; cin >> luong;
    cin.ignore();
    cout << "Nhap SDT: "; getline(cin, sdt);
    cout << "Nhap username: "; getline(cin, user);
    cout << "Nhap password: "; getline(cin, pass);

    ds.push_back(Employee(ma, ten, ns, phai, capbac, luong, sdt, user, pass));
    saveEmployees();
    cout << "Đã thêm NV!" << endl;
    pauseConsole();
}

void listAllEmployees() {
    for (auto &e : ds) e.xuatThongTin();
    pauseConsole();
}

void removeEmployee() {
    string ma;
    cout << "Nhập mã NV cần xóa: "; cin >> ma;
    cin.ignore();
    for (auto it = ds.begin(); it != ds.end(); ++it) {
        if (it->getMaNV() == ma) {
            ds.erase(it);
            saveEmployees();
            cout << "Đã xóa NV!" << endl;
            pauseConsole();
            return;
        }
    }
    cout << "Không tìm thấy NV!" << endl;
    pauseConsole();
}

void findEmployee() {
    string ma;
    cout << "Nhập mã NV cần tìm: "; cin >> ma;
    cin.ignore();
    for (auto &e : ds) {
        if (e.getMaNV() == ma) {
            e.xuatThongTin();
            pauseConsole();
            return;
        }
    }
    cout << "Không tìm thấy NV!" << endl;
    pauseConsole();
}

void updateEmployee() {
    string ma;
    cout << "Nhập mã NV cần cập nhập: "; cin >> ma;
    cin.ignore();
    for (auto &e : ds) {
        if (e.getMaNV() == ma) {
            string ten, ns, phai, capbac, sdt, user, pass;
            long long luong;
            cout << "Nhập tên: "; getline(cin, ten);
            cout << "Nhập ngày sinh: "; getline(cin, ns);
            cout << "Nhập giới tính: "; getline(cin, phai);
            cout << "Nhập cấp bậc: "; getline(cin, capbac);
            cout << "Nhập lương: "; cin >> luong;
            cin.ignore();
            cout << "Nhập SDT: "; getline(cin, sdt);
            cout << "Nhập username: "; getline(cin, user);
            cout << "Nhập password: "; getline(cin, pass);

            e = Employee(ma, ten, ns, phai, capbac, luong, sdt, user, pass);
            saveEmployees();
            cout << "Đã cập nhật NV!" << endl;
            pauseConsole();
            return;
        }
    }
    cout << "Không tìm thấy NV!" << endl;
    pauseConsole();
}

void changePassword(const string &username) {
    string oldPass, newPass, confirm;
    cout << "Nhập mật khẩu cũ: ";
    getline(cin, oldPass);
    for (auto &nv : ds) {
        if (nv.getUsername() == username) {
            if (nv.getPassword() != oldPass) {
                cout << "Sai mật khẩu cũ!" << endl;
                return;
            }
            cout << "Nhập mật khẩu mới: "; getline(cin, newPass);
            cout << "Nhập lại mật khẩu mới: "; getline(cin, confirm);
            if (newPass != confirm) {
                cout << "Mật khẩu xác nhận không khớp!" << endl;
                return;
            }
            nv.setPassword(newPass);
            saveEmployees();
            cout << "Đổi mật khẩu thành công!" << endl;
            pauseConsole();
            return;
        }
    }
}
const string ADMIN_FILE = "Administrators.txt";
const string EMPLOYEE_FILE = "nhanvien.txt";
vector<Employee> employees;

bool adminLogin() {
    clearScreen();
    printTitle("ĐĂNG NHẬP ADMIN");
    int attempts = 0;
    string username, password;
    while (attempts < 3) {
        cout << "Tên đăng nhập: ";
        getline(cin, username);
        cout << "Mật khẩu: ";
        getline(cin, password);
        ifstream file(ADMIN_FILE);
        string u, p;
        while (file >> u >> p) {
            Admin admin(u, p);
            if (admin.checkLogin(username, password)) {
                printOk("Đăng nhập thành công!");
                pauseConsole();
                return true;
            }
        }
        attempts++;
        printError("Sai tên đăng nhập hoặc mật khẩu!");
        if (attempts == 3) {
            printError("Bạn đã nhập sai 3 lần. Hệ thống thoát!");
            pauseConsole();
            return false;
        }
    }
    return false;
}

bool employeeLogin(Employee &loggedIn) {
    clearScreen();
    printTitle("ĐĂNG NHẬP EMPLOYEE");
     int attempts = 0;
    while (attempts < 3) {
        string user, pass;
        cout << "Tên đăng nhập: ";
        getline(cin, user);
        cout << "Mật khẩu: ";
        getline(cin, pass);
        for (Employee &e : ds) {
            if (e.getUsername() == user && e.getPassword() == pass) {
                printOk("Đăng nhập thành công!");
                loggedIn = e;
                pauseConsole();
                return true;
            }
        }
        attempts++;
        printError("Sai tên đăng nhập hoặc mật khẩu!");
        if(attempts == 3) {
            printError("Bạn đã nhập sai 3 lần. Hệ thống thoát!");
            pauseConsole();
            return false;
        }
    }
    return false;
}

void adminMenu() {
    while (true) {
        clearScreen();
        printTitle("MENU ADMIN");
        cout << "1. Thêm Employee\n";
        cout << "2. Xóa Employee\n";
        cout << "3. Tìm Employee\n";
        cout << "4. Cập nhật Employee\n";
        cout << "5. Hiển thị tất cả Employee\n";
        cout << "6. Đăng xuất\n";
        cout << "Chọn: ";
        string ch;
        getline(cin, ch);
        if (ch == "1") addEmployee();
        else if (ch == "2") removeEmployee();
        else if (ch == "3") findEmployee();
        else if (ch == "4") updateEmployee();
        else if (ch == "5") listAllEmployees();
        else if (ch == "6") break;
        else {
            cout << "Lựa chọn không hợp lệ!" << endl;
            pauseConsole();
        }
    }
}

void employeeMenu(const string &username) {
    while (true) {
        clearScreen();
        printTitle("MENU EMPLOYEE");
        cout << "1. Xem thông tin\n";
        cout << "2. Đổi mật khẩu\n";
        cout << "3. Đăng xuất\n";
        cout << "Chọn: ";
        string ch; getline(cin, ch);
        if (ch == "1") {
            for (auto &nv : ds) if (nv.getUsername() == username) nv.xuatThongTin();
            pauseConsole();
        }
        else if (ch == "2") changePassword(username);
        else if (ch == "3") break;
        else {
            cout << "Lựa chọn không hợp lệ!" << endl;
            pauseConsole();
        }
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    ifstream input("nhanvien.txt");
    if (input.is_open()) {
        string ma, ten, ngaysinh, phai, capbac, sdt, user, pass;
        long long luong;
        while (input >> ma >> ten >> ngaysinh >> phai >> capbac >> luong >> sdt >> user >> pass) {
            ds.push_back(Employee(ma, ten, ngaysinh, phai, capbac, luong, sdt, user, pass));
        }
        input.close();
    }
    while (true) {
        clearScreen();
        printTitle("QUẢN LÝ NHÂN SỰ - PROJECT 2");
        cout << "1. Đăng nhập Admin\n";
        cout << "2. Đăng nhập Employee\n";
        cout << "3. Thoát\n\nChọn: ";
        string c;
        getline(cin, c);
        if (c == "1") {
            if (adminLogin()) {
                adminMenu();
            }
        } 
        else if (c == "2") {
            Employee emp;
            if (employeeLogin(emp)) {
                employeeMenu(emp.getUsername());
            }
        } 
        else if (c == "3") {
            clearScreen();
            setColor(10);
            cout << "Tạm biệt!\n";
            setColor(7);
            break;
        } 
        else {
            printError("Lựa chọn không hợp lệ!");
            pauseConsole();
        }
    }
    return 0;
}
