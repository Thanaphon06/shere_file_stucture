#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
int Menu();
void AddStudent(string FN);
void DisplayStudent(string FN);
void ReportGread(string FN);
    int main()
    {
    const string Filename = "student.dat";
    ifstream InFile;
    ofstream OutFile;
    int c;
    do {
   system("cls"); // เคลียหน้าจอ command ด้วยคำสั่ง cls
    c = Menu();

    switch(c)
    {
        case 1 : AddStudent(Filename); break;
        case 2 : DisplayStudent(Filename); break;  
        case 3 : ReportGread(Filename); break; 
    }
    } while(c != 0);
        cout << "Exit program." << endl;
        return(0);
    }
    int Menu()
    {
        string line(25,'=');
        int Choose;
        cout << "Program Add-Display Student Data\n";
        cout << line << endl;
        cout << ": Main Menu :\n";
        cout << line << endl;
        cout << ": 0 - Exit :\n";
        cout << ": 1 - Add Student :\n";
        cout << ": 2 - Display Student :\n";
        cout << ": 3 - Report Gread :\n";
        cout << line << endl;
        cout << " Enter choose : ";
        cin >> Choose;
        return(Choose);
    }

    void AddStudent(string FN){
        // open file for write and append
        ofstream OutFile(FN.c_str(), ios_base::out | ios_base::app);
        if (OutFile.is_open()) {

        string Id, Name;
        int gread;
        cout << "\n Add Student \n";
        cout << "Enter id : ";
        cin >> Id;
        cout << "Enter name : ";
        cin >> Name;
        cout << "Enter Greada : ";
        cin >> gread;
        // write data to file student.dat
        OutFile << Id << " " << Name <<  " " << gread << endl;
        OutFile.close();
        char wa;
        cin.get(wa);
        cout << "\nSaved already ,Press Enter to continue";
        cin.get(wa);
        
        }
        else cout << "File could not opened." << endl;
    }
    void DisplayStudent(string FN){
        ifstream InFile(FN.c_str(), ios_base::in); // open file for read
        if (InFile.is_open()) {
        string Id, Name;
        string line(30,'=');
        int n = 0;
        cout << "\nList Student\n";
        cout << line << endl;
        cout << " No. Id Name \n";
        cout << line << endl;
        // read data from file student.dat
        InFile >> Id >> Name;
        while (!InFile.eof()) {
            n = n + 1;
            cout << right << setw(3) << n << " : ";
            cout << left << setw(6) << Id;
            cout << " " << Name << endl;
            
            InFile >> Id >> Name;
        }
        InFile.close();
        char Wait;
        cin.get(Wait);
        cout << "\nPress Enter to continue";
        cin.get(Wait);
        }else cout << "File could not opened." << endl;
}

void ReportGread(string FN){
        ifstream InFile(FN.c_str(), ios_base::in); // open file for read
        if (InFile.is_open()) {
        string Id, Name;
        string line(30,'=');
        int n = 0 , gread;
        cout << "\nList Student\n";
        cout << line << endl;
        cout << " No. Id Name Gread \n";
        cout << line << endl;
        // read data from file student.dat
        InFile >> Id >> Name >> gread;
        while (!InFile.eof()) {
            n = n + 1;
            cout << right << setw(3) << n << " : ";
            cout << left  << Id;
            cout << " " << setw(3) << Name ;
            cout << " " << gread << endl;
            
            InFile >> Id >> Name >> gread;
        }
        InFile.close();
        char Wait;
        cin.get(Wait);
        cout << "\nPress Enter to continue";
        cin.get(Wait);
        }else cout << "File could not opened." << endl;
}