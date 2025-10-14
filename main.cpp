#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen() {
    system("cls");
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

void printError(const string &tx) {
    setColor(12);
    cout << "[Lỗi] " << tx << "\n";
    setColor(7);
}


void printOk(const string &tx) {
    setColor(10);
    cout << "[OK] " << tx << "\n";
    setColor(7);
}

void addEmployee(){}      
void removeEmployee(){}
void findEmployee(){}
void updateEmployee(){}   
void listAllEmployees(){}  

void viewAccountInfo(){}
void changePassword(){}   

void adminMenu() {
    while (true) {
        clearScreen();
        printTitle("MENU ADMIN");
        cout << "1. Thêm Employee\n";
        cout << "2. Xóa Employee\n";
        cout << "3. Tìm Employee\n";
        cout << "4. Cập nhật Employee\n";
        cout << "5. Hiển thị tất cả Employee\n";
        cout << "6. Thoát\n";
        cout << "\nChọn: ";
        string ch;
        getline(cin, ch);
         if (ch == "1") {
            addEmployee();
        } else if (ch == "2") {
            removeEmployee();
        } else if (ch == "3") {
            findEmployee();
        } else if (ch == "4") {
            updateEmployee();
        } else if (ch == "5") {
            listAllEmployees();
        } else if (ch == "6") {
            break;
        } else {
            printError("Lựa chọn không hợp lệ!");
            pauseConsole();
        }
    }
}

void employeeMenu() {
    while (true) {
        clearScreen();
        printTitle("MENU EMPLOYEE");
        cout << "1. Xem thông tin tài khoản\n";
        cout << "2. Đổi mật khẩu\n";
        cout << "3. Thoát\n\nChọn: ";
        string ch;
        getline(cin, ch);
        if (ch == "3") {
            break;
        } else {
            printError("Chức năng này chưa được triển khai.");
            pauseConsole();
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
   // clearScreen();
    while (true) {
        clearScreen();
        printTitle("QUẢN LÝ NHÂN SỰ - PROJECT 2");
        cout << "1. Đăng nhập Admin\n";
        cout << "2. Đăng nhập Employee\n";
        cout << "3. Thoát\n\nChọn: ";
        string c;
        getline(cin, c);
        if (c == "1") {
            adminMenu();
        } else if (c == "2") {
            employeeMenu();
        } else if (c == "3") {
            clearScreen();
            setColor(10);
            cout << "Tạm biệt!\n";
            setColor(7);
            break;
        } else {
            printError("Lựa chọn không hợp lệ!");
            pauseConsole();
        }
    }
    return 0;
}
