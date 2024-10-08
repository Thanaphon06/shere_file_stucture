#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

int main() {
    string path = "../week14"; // ระบุ path ของโฟลเดอร์ที่ต้องการดู

    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            cout << entry.path().string() << endl;  
        }
    } catch (const fs::filesystem_error& e) {
        cout << "something went wrong: " << e.what() << endl;
    }
    
    string file_name;
    cout << "Enter file name : ";
    getline(cin, file_name);

    ifstream file(file_name);  // ชื่อไฟล์ที่ต้องการอ่าน
    string line;
    int w_cout = 0;

    

    if (file.is_open()) {
        while (getline(file, line) && w_cout < 25 ) {  // อ่านไฟล์ทีละบรรทัด
            cout << line << endl;
            w_cout++;

            if (w_cout == 24)
            {
                char Wait;
                
                cout << "\nPress Enter to continue";
                cin.get(Wait);
                w_cout = 0;
            }
            
            
        }
        
        file.close();  // ปิดไฟล์เมื่ออ่านเสร็จ
    } else {
        cout << "Can't open file!" << endl;
    }

}

