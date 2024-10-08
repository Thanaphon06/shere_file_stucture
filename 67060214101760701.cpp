#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

pair<string, string> convertDate(const string& date) {
    int day, month, year;
    char delimiter;

    stringstream ss(date);
    ss >> day >> delimiter >> month >> delimiter >> year;

    vector<string> months = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    string format1 = months[month - 1] + " " + to_string(day) + ", " + to_string(year);
    string format2 = to_string(day) + " " + months[month - 1].substr(0, 3) + " " + to_string(year);

    return make_pair(format1, format2);
}

int main() {
    string inputDate;
    cout << " Input Date(dd/mm/yyyy) (dd/mm/yyyy): ";
    cin >> inputDate;

    auto [format1, format2] = convertDate(inputDate);

    cout << "Format 1: " << format1 << endl;
    cout << "Format 2: " << format2 << endl;

    return 0;
}
