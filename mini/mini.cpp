#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <sstream>
using namespace std;

// โครงสร้างข้อมูลสำหรับพนักงาน
struct Employee
{
    string username;
    string password;
};

// โครงสร้างข้อมูลสำหรับคอนเสิร์ต
struct Concert
{
    string name;
    string date;
    int zones;
    vector<int> seatsPerZone;
    vector<double> pricesPerZone;
    vector<vector<string> > seatNumbers; // ชื่อที่นั่งในแต่ละโซน
    vector<vector<bool> > isSeatBooked; // สถานะการจองที่นั่ง
};

struct TicketPurchase {
    string concertName;
    char zone;
    int price;
};

string itemName;
int quantity;
double price;

int getZonePrice(char zone) {
    switch (zone) {
        case 'A': return 3000;
        case 'B': return 2000;
        case 'C': return 1000;
        default: return 0;
    }
}


// ฟังก์ชันสำหรับล็อกอิน
bool login(const vector<Employee> &employees, bool &isAdmin)
{
    string username, password;

    cout << "=== Login ===\n";
    cout << "กรุณากรอกชื่อผู้ใช้: ";
    cin >> username;
    cout << "กรุณากรอกรหัสผ่าน: ";
    cin >> password;

    for (vector<Employee>::const_iterator it = employees.begin(); it != employees.end(); ++it)
    {
        if (username == it->username && password == it->password)
        {
            cout << "Loginสำเร็จ!\n";
            isAdmin = (username == "admin"); // ตรวจสอบว่าเป็นแอดมินหรือไม่
            return true;
        }
    }
    cout << "ชื่อผู้ใช้หรือรหัสผ่านไม่ถูกต้อง กรุณาลองใหม่อีกครั้ง\n";
    return false;
}

// ฟังก์ชันอ่านข้อมูลพนักงานจากไฟล์
vector<Employee> loadEmployees(const string &filename)
{
    vector<Employee> employees;
    ifstream infile(filename);
    Employee emp;

    while (infile >> emp.username >> emp.password)
    {
        employees.push_back(emp);
    }
    infile.close();
    return employees;
}

// ฟังก์ชันบันทึกข้อมูลพนักงานลงไฟล์
void saveEmployees(const string &filename, const vector<Employee> &employees)
{
    ofstream outfile(filename);
    for (size_t i = 0; i < employees.size(); ++i)
    {
        outfile << employees[i].username << " " << employees[i].password << endl;
    }
    outfile.close();
}

// ฟังก์ชันเพิ่มพนักงานใหม่
void addEmployee(vector<Employee> &employees, const string &filename)
{
    Employee emp;
    cout << "\n=== เพิ่มพนักงานใหม่ ===\n";
    cout << "กรุณากรอกชื่อผู้ใช้: ";
    cin >> emp.username;
    cout << "กรุณากรอกรหัสผ่าน: ";
    cin >> emp.password;

    // ตรวจสอบว่าชื่อผู้ใช้ซ้ำหรือไม่
    for (size_t i = 0; i < employees.size(); ++i)
    {
        if (employees[i].username == emp.username)
        {
            cout << "ชื่อผู้ใช้ซ้ำ กรุณาใช้ชื่อผู้ใช้อื่น\n";
            return;
        }
    }

    employees.push_back(emp);
    saveEmployees(filename, employees); // บันทึกข้อมูลพนักงานลงไฟล์
    cout << "เพิ่มพนักงานใหม่สำเร็จ\n";
}

// ฟังก์ชันอ่านข้อมูลคอนเสิร์ตจากไฟล์
vector<Concert> loadConcerts(const string &filename)
{
    vector<Concert> concerts;
    ifstream infile(filename);
    Concert concert;

    while (infile >> concert.name >> concert.date >> concert.zones)
    {
        concert.seatsPerZone.resize(concert.zones);
        concert.pricesPerZone.resize(concert.zones);
        for (int i = 0; i < concert.zones; ++i)
        {
            infile >> concert.seatsPerZone[i];
        }
        for (int i = 0; i < concert.zones; ++i)
        {
            infile >> concert.pricesPerZone[i];
        }
        concerts.push_back(concert);
    }
    infile.close();
    return concerts;
}

// ฟังก์ชันตรวจสอบว่าคอนเสิร์ตมีอยู่แล้วหรือไม่
bool isConcertExists(const vector<Concert>& concerts, const string& name) {
    for (const auto& concert : concerts) {
        if (concert.name == name) {
            return true;
        }
    }
    return false;
}

// ฟังก์ชันบันทึกคอนเสิร์ตลงไฟล์ (บันทึกเฉพาะชื่อ)
void saveConcerts(const string& filename, const vector<Concert>& concerts) {
    ofstream file(filename.c_str(), ios::trunc); // เปิดไฟล์เพื่อลบข้อมูลเก่าและเขียนใหม่
    if (file.is_open()) {
        for (const auto& concert : concerts) {
            file << concert.name << "\n"; // บันทึกเฉพาะชื่อคอนเสิร์ต
        }
        file.close();
    } else {
        cout << "ไม่สามารถเปิดไฟล์ได้\n";
    }
}

// ฟังก์ชันเพิ่มคอนเสิร์ต
void addConcert(vector<Concert>& concerts, const string& filename) {
    Concert concert;
    cout << "\n=== เพิ่มคอนเสิร์ตใหม่ ===\n";
    cout << "กรุณากรอกชื่อคอนเสิร์ต: ";
    cin >> concert.name;

    // ตรวจสอบว่าคอนเสิร์ตมีอยู่แล้วหรือไม่
    if (isConcertExists(concerts, concert.name)) {
        cout << "คอนเสิร์ตนี้มีอยู่แล้ว กรุณาใช้ชื่อคอนเสิร์ตอื่น\n";
        return;
    }

    concerts.push_back(concert);
    saveConcerts(filename, concerts); // บันทึกข้อมูลคอนเสิร์ตลงไฟล์
    cout << "เพิ่มคอนเสิร์ตใหม่สำเร็จ\n";
}

// ฟังก์ชันลบคอนเสิร์ต
void deleteConcert() {
    vector<string> concerts;
    string concertName;
    ifstream inFile("concerts.txt");

    // อ่านข้อมูลคอนเสิร์ตจากไฟล์
    while (getline(inFile, concertName)) {
        concerts.push_back(concertName);
    }
    inFile.close();

    // แสดงคอนเสิร์ตที่มีอยู่
    cout << "คอนเสิร์ตที่มีอยู่:\n";
    for (size_t i = 0; i < concerts.size(); i++) {
        cout << i + 1 << ". " << concerts[i] << endl;
    }

    if (concerts.empty()) {
        cout << "ไม่มีคอนเสิร์ตในระบบ\n";
        return;
    }

    // ให้ผู้ใช้เลือกคอนเสิร์ตที่ต้องการลบ
    int choice;
    cout << "เลือกหมายเลขคอนเสิร์ตที่ต้องการลบ: ";
    cin >> choice;

    // ตรวจสอบความถูกต้องของการเลือก
    if (choice < 1 || choice > concerts.size()) {
        cout << "หมายเลขที่เลือกไม่ถูกต้อง\n";
        return;
    }

    // สร้างไฟล์ชั่วคราวเพื่อเขียนข้อมูลที่ไม่ต้องการ
    ofstream tempFile("temp.txt");
    for (size_t i = 0; i < concerts.size(); i++) {
        if (i + 1 != choice) { // ถ้าไม่ใช่คอนเสิร์ตที่เลือก
            tempFile << concerts[i] << endl;
        }
    }
    tempFile.close();

    // ลบไฟล์เดิมและเปลี่ยนชื่อไฟล์ชั่วคราว
    remove("concerts.txt");
    rename("temp.txt", "concerts.txt");

    cout << "ลบคอนเสิร์ต " << concerts[choice - 1] << " เรียบร้อยแล้ว\n";
}

// ฟังก์ชันสำหรับสมัครสมาชิก
void registerMember() {
    string name, phoneNumber;

    cout << "กรุณาใส่ชื่อของคุณ: ";
    cin >> name;
    cout << "กรุณาใส่หมายเลขโทรศัพท์: ";
    cin >> phoneNumber;

    // บันทึกข้อมูลสมาชิกลงในไฟล์ members.txt
    ofstream memberFile("members.txt", ios::app);
    if (memberFile.is_open()) {
        memberFile << name << "," << phoneNumber << endl;
        memberFile.close();
        cout << "สมัครสมาชิกเรียบร้อยแล้ว!" << endl;
    } else {
        cerr << "ไม่สามารถเปิดไฟล์สำหรับบันทึกสมาชิกได้!" << endl;
    }
}

// ฟังก์ชันสำหรับเข้าสู่ระบบสมาชิก
bool loginMember() {
    string phoneNumber, line;
    bool found = false;

    cout << "กรุณาใส่หมายเลขโทรศัพท์ของคุณ: ";
    cin >> phoneNumber;

    ifstream memberFile("members.txt");
    if (!memberFile) {
        cerr << "ไม่สามารถเปิดไฟล์ข้อมูลสมาชิกได้!" << endl;
        return false;
    }

    while (getline(memberFile, line)) {
        if (line.find(phoneNumber) != string::npos) {
            found = true;
            break;
        }
    }

    memberFile.close();
    return found;
}
void loadConcerts(vector<string>& concerts) {
    ifstream concertFile("concerts.txt");
    if (!concertFile) {
        cerr << "ไม่สามารถเปิดไฟล์ concerts.txt ได้!" << endl;
        return;
    }

    string concertName;
    while (getline(concertFile, concertName)) {
        if (!concertName.empty()) { // ตรวจสอบว่าชื่อคอนเสิร์ตไม่ว่าง
            concerts.push_back(concertName);
        }
    }

    concertFile.close();
}

// ฟังก์ชันแสดงรายชื่อคอนเสิร์ต
void displayConcerts(const vector<Concert>& concerts) {
    if (concerts.empty()) {
        cout << "ไม่มีคอนเสิร์ตในระบบ\n";
        return;
    }

    cout << "\n=== รายชื่อคอนเสิร์ต ===\n";
    for (const auto& concert : concerts) {
        cout << concert.name << endl; // แสดงชื่อคอนเสิร์ต
    }
}

// ฟังก์ชันสำหรับการซื้อบัตรคอนเสิร์ต
void purchaseMemberTicket(const string& memberName) {
    vector<string> concerts;
    loadConcerts(concerts);

    if (concerts.empty()) {
        cout << "ไม่มีคอนเสิร์ตในระบบ!" << endl;
        return;
    }

    cout << "=== รายการคอนเสิร์ต ===" << endl;
    for (size_t i = 0; i < concerts.size(); ++i) {
        cout << i + 1 << ". " << concerts[i] << endl;
    }

    int choice;
    cout << "กรุณาเลือกคอนเสิร์ต (1-" << concerts.size() << "): ";
    cin >> choice;

    if (choice < 1 || choice > concerts.size()) {
        cout << "เลือกคอนเสิร์ตไม่ถูกต้อง!" << endl;
        return;
    }

    string concertName = concerts[choice - 1];

    // ให้เลือกโซน
    char zone;
    cout << "กรุณาเลือกโซน (A, B, C): ";
    cin >> zone;

    int ticketPrice = getZonePrice(zone) * 0.9; // ใช้ราคาตามโซนและลด 10%
    cout << "ซื้อบัตรคอนเสิร์ต: " << concertName << " ในโซน " << zone 
         << " ราคา: " << ticketPrice << " บาท" << endl;

    // บันทึกการขายลงไฟล์ salemem.txt
    ofstream saleMemFile("salemem.txt", ios::app);
    if (saleMemFile.is_open()) {
        saleMemFile << memberName << "," << concertName << "," << zone << "," << ticketPrice << endl;
        saleMemFile.close();
        cout << "บันทึกการขายเรียบร้อยแล้ว!" << endl;
    } else {
        cerr << "ไม่สามารถเปิดไฟล์สำหรับบันทึกการขายได้!" << endl;
    }
}

// ฟังก์ชันแสดงเมนูล็อกอินเริ่มต้น
void showLoginMenu()
{
    cout << "==== Login ====\n";
    cout << "1. Login\n";
    cout << "0. ออกจากโปรแกรม\n";
    cout << "กรุณาเลือกเมนู: ";
}

// ฟังก์ชันแสดงเมนูหลัก
void showMenu(bool isAdmin)
{
    cout << "==== เมนูหลัก ====\n";
    cout << "1. ซื้อบัตรคอนเสิร์ต\n";
    cout << "2. ซื้อของที่ระลึก\n";
    cout << "3. ใบเสร็จ\n";
    cout << "4. พนักงาน\n";
    cout << "5. โปรโมชั่นสมาชิก\n";
    if (isAdmin)
    { // แสดงตัวเลือกเพิ่มพนักงานถ้าผู้ล็อกอินคือแอดมิน
        cout << "6. เพิ่มพนักงานใหม่\n";
    }
    cout << "0. ออกจากโปรแกรม\n";
    cout << "กรุณาเลือกเมนู: ";
}

void loadConcerts(Concert concerts[], int& concertCount) {
    ifstream inFile("concerts.txt");
    concertCount = 0;

    if (inFile.is_open()) {
        while (getline(inFile, concerts[concertCount].name)) {
            concertCount++;
            // เพิ่มการตรวจสอบว่า concertCount ไม่เกินขนาดที่ตั้งไว้
            if (concertCount >= 100) {
                break; // หยุดเมื่อเกินขนาดที่กำหนด
            }
        }
        inFile.close();
    } else {
        cout << "ไม่สามารถเปิดไฟล์อ่านข้อมูลคอนเสิร์ต" << endl;
    }
}


void showConcerts(const Concert concerts[], int count) {
    cout << "รายชื่อคอนเสิร์ตที่มี:" << endl;
    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ". " << concerts[i].name << endl;
    }
}

void savePurchase(const TicketPurchase &purchase) {
    ofstream saleFile("sales.txt", ios::app);
    if (saleFile.is_open()) {
        saleFile << "คอนเสิร์ต: " << purchase.concertName
                  << ", โซน: " << purchase.zone
                  << ", ราคา: " << purchase.price << " บาท" << endl;
        saleFile.close();
    } else {
        cout << "ไม่สามารถเปิดไฟล์ sales.txt" << endl;
    }
}

void displayReceipt(const TicketPurchase &purchase) {
    cout << "=== ใบเสร็จ ===" << endl;
    cout << "คอนเสิร์ต: " << purchase.concertName << endl;
    cout << "โซน: " << purchase.zone << endl;
    cout << "ราคา: " << purchase.price << " บาท" << endl;
    cout << "================" << endl;
}
void showsticket() {
    Concert concerts[100];
    int concertCount = 0;
    loadConcerts(concerts, concertCount); // โหลดข้อมูลคอนเสิร์ต
    showConcerts(concerts, concertCount); // แสดงรายการคอนเสิร์ต
    cout << "\nกด Enter เพื่อกลับไปเมนูหลัก...";
    cin.ignore();
    cin.get();
}

void purchaseTicket() {
    Concert concerts[100];
    int concertCount = 0;
    loadConcerts(concerts, concertCount);
    showConcerts(concerts, concertCount);

    int concertChoice;
    cout << "เลือกคอนเสิร์ต (หมายเลข): ";
    cin >> concertChoice;

    if (concertChoice < 1 || concertChoice > concertCount) {
        cout << "หมายเลขคอนเสิร์ตไม่ถูกต้อง" << endl;
        return;
    }

    char zone;
    cout << "เลือกโซน (A, B, C): ";
    cin >> zone;

    int price = getZonePrice(zone);
    if (price == 0) {
        cout << "โซนไม่ถูกต้อง" << endl;
        return;
    }

    TicketPurchase purchase; // สร้างตัวแปรเพื่อเก็บข้อมูลการซื้อ
    purchase.concertName = concerts[concertChoice - 1].name; // ชื่อคอนเสิร์ต
    purchase.zone = zone; // โซนที่เลือก
    purchase.price = price; // ราคาตั๋ว

    savePurchase(purchase); // บันทึกข้อมูลการซื้อ
    displayReceipt(purchase); // แสดงใบเสร็จ
}


void purchaseMerchandise() {
    int choice;
    int quantity;
    int price;
    string itemName;
    ofstream saleFile;

    saleFile.open("sale.txt", ios::app); // เปิดไฟล์ใบเสร็จเพื่อเพิ่มข้อมูล

    if (!saleFile) {
        cout << "ไม่สามารถเปิดไฟล์ใบเสร็จได้" << endl;
        return;
    }

    cout << "เมนูซื้อของที่ระลึก:" << endl;
    cout << "1. เสื้อ (300 บาท)" << endl;
    cout << "2. รูป (100 บาท)" << endl;
    cout << "3. ป้ายไฟ (100 บาท)" << endl;
    cout << "4. พวงกุญแจ (50 บาท)" << endl;
    cout << "กรุณาเลือกสินค้า (1-4): ";
    cin >> choice;

    switch (choice) {
        case 1:
            itemName = "เสื้อ";
            price = 300;
            break;
        case 2:
            itemName = "รูป";
            price = 100;
            break;
        case 3:
            itemName = "ป้ายไฟ";
            price = 100;
            break;
        case 4:
            itemName = "พวงกุญแจ";
            price = 50;
            break;
        default:
            cout << "เลือกไม่ถูกต้อง" << endl;
            saleFile.close();
            return;
    }

    cout << "กรุณากรอกจำนวน: ";
    cin >> quantity;

    // คำนวณราคารวม
    int totalPrice = price * quantity;
    cout << "ราคารวมสำหรับ " << quantity << " " << itemName << " คือ " << totalPrice << " บาท" << endl;

    // บันทึกข้อมูลลงในใบเสร็จ
    saleFile << "ซื้อ " << quantity << " " << itemName << " ราคารวม " << totalPrice << " บาท" << endl;

    saleFile.close(); // ปิดไฟล์ใบเสร็จ
    cout << "การซื้อเสร็จสิ้น ขอบคุณ!" << endl;
}

// ฟังก์ชันสำหรับแสดงใบเสร็จ
void showReceipt() {
    string line;

    ifstream salesFile("sales.txt");
    ifstream merchandiseFile("sale.txt");

    cout << "=== ใบเสร็จ ===" << endl;

    // แสดงข้อมูลการซื้อจาก sales.txt
    cout << "ข้อมูลการซื้อบัตร:" << endl;
    if (salesFile.is_open()) {
        while (getline(salesFile, line)) {
            cout << line << endl;
        }
        salesFile.close();
    } else {
        cout << "ไม่สามารถเปิดไฟล์ sales.txt ได้" << endl;
    }

    // แสดงข้อมูลการซื้อของที่ระลึกจาก sale.txt
    cout << "\nข้อมูลการซื้อของที่ระลึก:" << endl;
    if (merchandiseFile.is_open()) {
        while (getline(merchandiseFile, line)) {
            cout << line << endl;
        }
        merchandiseFile.close();
    } else {
        cout << "ไม่สามารถเปิดไฟล์ sale.txt ได้" << endl;
    }
    cout << "=================" << endl;
}

// ฟังก์ชันสำหรับบันทึกการขาย
void recordSale() {
    string itemName;
    int quantity;
    double price;
    string employeeName;

    cout << "กรุณาใส่ชื่อพนักงาน: ";
    cin >> employeeName;  // ใช้ cin แทน getline
    
    cout << "กรุณาใส่ชื่อสินค้าที่ขาย: ";
    cin >> itemName;  // ใช้ cin แทน getline
    
    cout << "กรุณาใส่จำนวนสินค้าที่ขาย: ";
    cin >> quantity;
    
    cout << "กรุณาใส่ราคา: ";
    cin >> price;
    
    // บันทึกข้อมูลการขายลงในไฟล์ emsale.txt
    ofstream saleFile("emsale.txt", ios::app); // เปิดไฟล์ในโหมด append
    if (saleFile.is_open()) {
        saleFile << employeeName << "," << itemName << "," << quantity << "," << price << endl;
        saleFile.close();
        cout << "บันทึกการขายเรียบร้อยแล้ว!" << endl;
    } else {
        cerr << "ไม่สามารถเปิดไฟล์สำหรับบันทึกการขายได้!" << endl;
    }
}

// ฟังก์ชันสำหรับแสดงข้อมูลการขาย
void displaySales() {
    ifstream saleFile("emsale.txt"); // เปิดไฟล์ emsale.txt เพื่ออ่านข้อมูล
    if (!saleFile) {
        cerr << "ไม่สามารถเปิดไฟล์ข้อมูลการขายได้!" << endl;
        return;
    }

    string line;
    cout << "=== รายการขาย ===" << endl;
    cout << "ชื่อพนักงาน\tชื่อสินค้า\tจำนวน\tราคา" << endl;

    while (getline(saleFile, line)) { // อ่านข้อมูลแต่ละบรรทัดจากไฟล์
        istringstream ss(line); // เปลี่ยนเป็น istringstream
        string employeeName, itemName;
        int quantity;
        double price;

        // แยกข้อมูลจากบรรทัด
        if (getline(ss, employeeName, ',') && getline(ss, itemName, ',') && ss >> quantity && ss.ignore() && ss >> price) {
            cout << employeeName << "\t        " << itemName << "\t" << quantity << "\t" << price << endl;
        } else {
            cerr << "ข้อมูลไม่ถูกต้องในบรรทัด: " << line << endl;
        }
    }

    saleFile.close();
}

void buyConcertTicket(vector<Concert> &concerts) // เปลี่ยนจาก const เป็น reference
{
    int choice;
    int concertCount = 0;

    do {
        cout << "\n=== ซื้อบัตรคอนเสิร์ต ===\n";
        cout << "1. แสดงคอนเสิร์ต\n";
        cout << "2. ซื้อบัตร\n";
        cout << "0. กลับเมนูหลัก\n";
        cout << "กรุณาเลือกเมนู: ";
        cin >> choice;

        switch (choice) {
            case 1:
                showsticket();
                break;
            case 2:
                purchaseTicket(); // เรียกฟังก์ชันซื้อบัตร
                break;
            case 0:
                cout << "กลับสู่เมนูหลัก\n";
                break;
            default:
                cout << "เลือกไม่ถูกต้อง กรุณาลองใหม่\n";
        }
    } while (choice != 0);
}


// ฟังก์ชันสำหรับพนักงาน
void staffMenu(vector<Concert> &concerts, const string &filename)
{
    int choice;
    do
    {
        cout << "\n=== เมนูพนักงาน ===\n";
        cout << "1. คอนเสิร์ต\n";
        cout << "2. บันทึกการขาย\n";
        cout << "3. แสดงการขาย\n";
        cout << "0. กลับ\n";
        cout << "กรุณาเลือกเมนู: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            int concertChoice;
            do
            {
                cout << "\n=== เมนูคอนเสิร์ต ===\n";
                cout << "1. เพิ่มคอนเสิร์ต\n";
                cout << "2. ลบคอนเสิร์ต\n";
                cout << "0. กลับ\n";
                cout << "กรุณาเลือกเมนู: ";
                cin >> concertChoice;

                switch (concertChoice)
                {
                case 1:
                    addConcert(concerts, filename);
                    break;
                case 2:
                    deleteConcert(); // เรียกฟังก์ชันลบคอนเสิร์ต
                    break;
                case 0:
                    break;
                default:
                    cout << "เลือกไม่ถูกต้อง กรุณาลองใหม่\n";
                }
            } while (concertChoice != 0);
            break;
        case 2: 
            recordSale();
            break;
        case 3: 
            displaySales();
            break;
        case 0:
            break;
        default:
            cout << "เลือกไม่ถูกต้อง กรุณาลองใหม่\n";
        }
    } while (choice != 0);
}

// ฟังก์ชันสำหรับเมนูโปรโมชั่นสมาชิก
void memberPromotionsMenu() {
    int choice;

    do {
        cout << "=== เมนูโปรโมชั่นสมาชิก ===" << endl;
        cout << "1. สมัครสมาชิก" << endl;
        cout << "2. เข้าสู่ระบบ" << endl;
        cout << "3. ซื้อบัตรราคาสมาชิก" << endl;
        cout << "0. กลับ" << endl;
        cout << "กรุณาเลือกเมนู: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerMember();
                break;
            case 2:
                if (loginMember()) {
                    cout << "เข้าสู่ระบบสมาชิกเรียบร้อย!" << endl;
                } else {
                    cout << "หมายเลขโทรศัพท์ไม่ถูกต้อง!" << endl;
                }
                break;
            case 3:
                //purchaseMemberTicket(memberName);
                break;
            case 0:
                cout << "กลับไปยังเมนูหลัก" << endl;
                break;
            default:
                cout << "กรุณาเลือกเมนูที่ถูกต้อง!" << endl;
                break;
        }
    } while (choice != 0);
}

// ฟังก์ชันหลัก
int main()
{
    const string filename = "employees.txt"; // ชื่อไฟล์สำหรับเก็บข้อมูลพนักงาน
    const string concertsFilename = "concerts.txt";
    vector<Concert> concerts = loadConcerts(concertsFilename);
    vector<Employee> employees = loadEmployees(filename); // อ่านข้อมูลพนักงานจากไฟล์

    
    int choice;
    bool loggedIn = false;
    bool isAdmin = false; // ตัวแปรบอกสถานะว่าผู้ล็อกอินเป็นแอดมินหรือไม่

    // แสดงเมนูล็อกอินเริ่มต้น
    do
    {
        showLoginMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            loggedIn = login(employees, isAdmin); // พยายามล็อกอินและตรวจสอบสถานะแอดมิน
            if (!loggedIn)
            {
                cout << "กรุณาลองใหม่\n";
            }
            break;
        case 0:
            cout << "ออกจากโปรแกรม\n";
            return 0;
        default:
            cout << "เลือกไม่ถูกต้อง กรุณาลองใหม่อีกครั้ง\n";
        }
    } while (!loggedIn); // ล็อกอินสำเร็จถึงจะออกจากลูปนี้ได้
        cout << "ล็อกอินสำเร็จ! ยินดีต้อนรับ\n";

    do
    {
        showMenu(isAdmin);
        cin >> choice;

        switch (choice)
        {
        case 1:
            buyConcertTicket(concerts); // ส่งข้อมูลคอนเสิร์ตเข้าไปในฟังก์ชันซื้อบัตร
            break;
        case 2:
            purchaseMerchandise();
            break;
        case 3:
            showReceipt();
            break;
        case 4:
            staffMenu(concerts, concertsFilename); // ส่ง concerts และ filename เข้าไปใน staffMenu
            break;
        case 5:
            memberPromotionsMenu();
            break;
        case 6:
            if (isAdmin)
            {
                addEmployee(employees, filename); // เรียกฟังก์ชันเพิ่มพนักงานใหม่
            }
            else
            {
                cout << "คุณไม่มีสิทธิ์เข้าถึงเมนูนี้\n";
            }
            break;
        case 0:
            cout << "ออกจากโปรแกรม\n";
            break;
        default:
            cout << "เลือกไม่ถูกต้อง กรุณาลองใหม่อีกครั้ง\n";
        }
    } while (choice != 0);

    return 0;
}