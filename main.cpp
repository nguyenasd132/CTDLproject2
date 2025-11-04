#include <bits/stdc++.h>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void setColor(int color) {
    #ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    #endif
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

class Employee{
    public:
    string username;
    string password;
    string fullname;
    string address;
    string phone;
    string email;
    double salary;
    string position;
    string status;

    Employee() : username(""), password(""), fullname(""), address(""), phone(""), email(""),
                 salary(0.0), position(""), status("Đang làm") {}

    void displayDetails() const {
        cout << "  Họ tên: " << fullname << "\n";
        cout << "  Địa chỉ: " << address << "\n";
        cout << "  SĐT: " << phone << "\n";
        cout << "  Email: " << email << "\n";
        cout << "  Lương: " << salary << "\n";
        cout << "  Chức vụ: " << position << "\n";
        cout << "  Trạng thái: " << status << "\n";
    }
};

const string ADMIN_FILE = "Administrators.txt";
const string EMPLOYEE_FILE = "Employees.txt";
vector<Employee> employees;

bool adminLogin() {
    clearScreen();
    printTitle("ĐĂNG NHẬP ADMIN");
    int attempts = 0;
    while (attempts < 3) {
        string username, password;
        cout << "Tên đăng nhập: ";
        getline(cin, username);
        cout << "Mật khẩu: ";
        getline(cin, password);
        string u, p;
        ifstream file(ADMIN_FILE);
        while (file >> u >> p) {
            if (u == username && p == password) {
                printOk("Đăng nhập thành công!");
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

bool employeeLogin(Employee &loggedIn) {
    clearScreen();
    printTitle("ĐĂNG NHẬP EMPLOYEE");
     int attempts = 0;
    while (attempts < 3) {
        string username, password;
        cout << "Tên đăng nhập: ";
        getline(cin, username);
        cout << "Mật khẩu: ";
        getline(cin, password);
        for (Employee &e : employees) {
            if (e.username == username && e.password == password) {
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

void saveEmployeesToFile() {
    ofstream out(EMPLOYEE_FILE);
    if (!out) {
        printError("Không thể ghi file!");
        return;
    }
    for (Employee &e : employees) {
        out << e.username<< "|" << e.password <<'\n';
        ofstream userFile(e.username + ".txt");
        if (userFile) {
            userFile << e.fullname << "|" << e.address << "|"
                     << e.phone << "|" << e.email << "|"
                     << e.salary << "|" << e.position << "|"
                     << e.status << "\n";
            userFile.close();
        }
    }
    out.close();
}

void loadEmployeesFromFile() {
    employees.clear();
    ifstream in(EMPLOYEE_FILE);
    if (!in) return;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        Employee e;
        stringstream ss(line);
        getline(ss, e.username, '|');
        getline(ss, e.password, '|');
        ifstream a(e.username + ".txt");
        if (a){
            string s_salary;
            getline(a, e.fullname, '|');
            getline(a, e.address, '|');
            getline(a, e.phone, '|');
            getline(a, e.email, '|');
            getline(a, s_salary, '|');
            try {
                e.salary = s_salary.empty() ? 0.0 : stod(s_salary);
            } catch (...) {
                e.salary = 0.0;
            }
            getline(a, e.position, '|');
            getline(a, e.status, '|');
            a.close();
        }
        employees.push_back(e);
    }
    in.close();
}

void addEmployee() {
    clearScreen();
    printTitle("THÊM EMPLOYEE MỚI");
    Employee newEmp;
    newEmp.username = inputLine("Nhập Username: ");
    for (Employee &e : employees) {
        if (e.username == newEmp.username) {
            printError("Username đã tồn tại!");
            pauseConsole();
            return;
        }
    }
    newEmp.password = "111111";
    printOk("Mật khẩu mặc định: 111111");
    newEmp.fullname = inputLine("Nhập họ tên: ");
    newEmp.address = inputLine("Nhập địa chỉ: ");
    newEmp.phone = inputLine("Nhập số điện thoại: ");
    newEmp.email = inputLine("Nhập email: ");
    string s;
    s = inputLine("Nhập lương: ");
    try {
        newEmp.salary = s.empty() ? 0.0 : stod(s);
    } catch (...) {
        newEmp.salary = 0.0;
    }
    newEmp.position = inputLine("Nhập chức vụ: ");
    newEmp.status = inputLine("Nhập trạng thái (bỏ trống mặc định 'Đang làm'): ");
    if (newEmp.status.empty()) newEmp.status = "Đang làm";

    employees.push_back(newEmp);
    saveEmployeesToFile();
    printOk("Đã thêm nhân viên mới!");
    pauseConsole();
}

void removeEmployee() {
    clearScreen();
    printTitle("XÓA EMPLOYEE");
    string user = inputLine("Nhập username cần xóa: ");
    bool found = false;
    for (int i = 0; i < (int)employees.size(); ++i) {
        if (employees[i].username == user) {
            found = true;
            printOk("Đã xóa " + employees[i].fullname);
            employees.erase(employees.begin() + i);
            remove((user + ".txt").c_str());
            break;
        }
    }
    if (!found)
        printError("Không tìm thấy username!");
    else
        saveEmployeesToFile();

    pauseConsole();
}

void findEmployee() {
    clearScreen();
    printTitle("TÌM EMPLOYEE");
    string user = inputLine("Nhập username cần tìm: ");
    bool found = false;
    for (Employee &e : employees) {
        if (e.username == user) {
            cout << "\n==> Thông tin nhân viên:\n";
            e.displayDetails();
            found = true;
            break;
        }
    }
    if (!found)
        printError("Không tìm thấy nhân viên!");
    pauseConsole();
}

void updateEmployee() {
    clearScreen();
    printTitle("CẬP NHẬT THÔNG TIN NHÂN VIÊN");
    string user = inputLine("Nhập username nhân viên cần cập nhật: ");
    bool found = false;

    for (Employee &e : employees) {
        if (e.username == user) {
            found = true;
            cout << "\n==> Thông tin hiện tại:\n";
            e.displayDetails();

            cout << "\n--- Nhập thông tin mới (bỏ trống nếu không đổi) ---\n";
            string s;

            s = inputLine("Lương mới: ");
            if (!s.empty()) {
                try { e.salary = stod(s); } catch (...) { }
            }

            s = inputLine("Chức vụ mới: ");
            if (!s.empty()) e.position = s;

            s = inputLine("Trạng thái (Đang làm/Đã nghỉ): ");
            if (!s.empty()) e.status = s;

            // Thêm khả năng cập nhật thông tin cá nhân
            s = inputLine("Họ tên mới: ");
            if (!s.empty()) e.fullname = s;

            s = inputLine("Địa chỉ mới: ");
            if (!s.empty()) e.address = s;

            s = inputLine("SĐT mới: ");
            if (!s.empty()) e.phone = s;

            s = inputLine("Email mới: ");
            if (!s.empty()) e.email = s;

            saveEmployeesToFile();
            printOk("Đã cập nhật thông tin nhân viên!");
            pauseConsole();
            return;
        }
    }
    if (!found) {
        printError("Không tìm thấy nhân viên!");
        pauseConsole();
    }
}

void listAllEmployees() {
    clearScreen();
    printTitle("DANH SÁCH TẤT CẢ NHÂN VIÊN");
    if (employees.empty()) {
        printError("Chưa có nhân viên nào!");
    } else {
        int i = 1;
        for (const Employee &e : employees) {
            cout << "\n[" << i++ << "] Username: " << e.username << "\n";
            e.displayDetails();
            cout << "----------------------------------\n";
        }
    }
    pauseConsole();
}

void viewAccountInfo(){}
void changePassword(){}

void adminMenu() {
    loadEmployeesFromFile();
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
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    loadEmployeesFromFile();
    SetConsoleCP(CP_UTF8);
    #endif
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
            if (adminLogin())
            adminMenu();
        } else if (c == "2") {
            Employee emp;
            if(employeeLogin(emp))
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
