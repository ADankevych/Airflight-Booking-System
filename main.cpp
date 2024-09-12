#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class Record {
public:
    string date;
    string flightNumber;
    map<int, map<int, int>> rowColumnPrice;
};

Record record;

class Parser {
public:
    static void parseRecord(){
        const char *path = "/Users/anastasia_d/CLionProjects/Airflight-Booking-System/records";
        fstream records(path);
        if (!records.is_open()) {
            cout << "Could not open file." << endl;
            return;
        }

        string line;

        while (getline(records, line)) {
            size_t position;

            position = line.find(' ');
            record.date = line.substr(0, position);
            string lineRemainder = line.substr(position + 1);

            position = lineRemainder.find(' ');
            record.flightNumber = lineRemainder.substr(0, position);
            lineRemainder = lineRemainder.substr(position + 1);

            position = lineRemainder.find(' ');
            int row = stoi(lineRemainder.substr(0, position));
            lineRemainder = lineRemainder.substr(position + 1);

            while ((position = lineRemainder.find(' ')) != string::npos) {
                string currentLine = lineRemainder.substr(0, position);
                size_t dash = currentLine.find('-');
                int startColumn = stoi(currentLine.substr(0, dash));
                int endColumn = stoi(currentLine.substr(dash + 1));

                lineRemainder = lineRemainder.substr(position + 1);

                position = lineRemainder.find(' ');
                string dollar = lineRemainder.substr(0, position);
                int price = stoi(dollar.substr(0, dollar.size() - 1));

                lineRemainder = lineRemainder.substr(position + 1);

                for (int i = startColumn; i <= endColumn; ++i) {
                    record.rowColumnPrice[row][i] = price;
                }
            }
        }
    }
};

int main() {
    cout << "Welcome to air-flight booking system!" << endl
         << "Please select an option:" << endl
         << "Check seat availability (check)" << endl
         << "Book a ticket (book)" << endl
         << "Return a ticket (return)" << endl
         << "View booked tickets (view)" << endl;

    string option;
    getline(cin, option);

    size_t position = option.find(' ');
    string newOption = option.substr(0, position);

    if (newOption == "check"){
        cout << "Enter the seat number: ";
    } else if (newOption == "book") {
        cout << "Enter the passenger name: ";
    } else if (newOption == "return") {
        cout << "Enter the passenger name: ";
    } else if (newOption == "view") {
        cout << "Enter the passenger name: ";
    } else {
        cout << "Invalid option!" << endl;
    }

    Parser::parseRecord();

    return 0;
}
