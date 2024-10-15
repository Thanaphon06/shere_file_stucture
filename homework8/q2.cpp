#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {

    ifstream Infile;
    ofstream OutFile;
    bool inWord = false;  
    
    string text, yaimak;

    cout << "Enter file name (.txt) : ";
    getline(cin, yaimak);
    
    int wordCount = 0, sentenceCount = 0;
    
    // สร้างไฟล์ที่มีข้อความลงไป
    OutFile.open(yaimak.c_str());
        cout << "Enter a paragraph: ";
        getline(cin, text);  
        OutFile << text;
        cout << endl;
    OutFile.close(); //เปิดแล้วต้องปิด
    
    Infile.open(yaimak.c_str());// เปิดไฟล์เพื่ออ่านข้อมูล

    char c;
    while (Infile.get(c)) {  //ฟังชั่น get(c) คือการนับทีละตัวในไฟล์แล้วคืนค่า true false
   
        if (isspace(c)) {  
            if (inWord) {
                wordCount++;
                inWord = false;  
            }
        } else {
            inWord = true;  
        }

        // นับประโยค
        if (c == '.' || c == '?' || c == '!') {
            sentenceCount++;
        }
    }
    
    if (inWord) {
        wordCount++;
    }

    Infile.close();  

    cout << "Number of words: " << wordCount << endl;
    cout << "Number of sentences: " << sentenceCount << endl;

}
