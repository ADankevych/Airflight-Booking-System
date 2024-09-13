#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

struct Record {
    string date;
    string flightNumber;
    int row;
    int column;
    int price;
    bool available = true;
};

map<string, map<string, map<int, map<int, Record>>>> recordsMap;

class Parser {
public:
    static void parseRecord() {
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
            string date = line.substr(0, position);
            string lineRemainder = line.substr(position + 1);

            position = lineRemainder.find(' ');
            string flightNumber = lineRemainder.substr(0, position);
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

                for (int column = startColumn; column <= endColumn; ++column) {
                    Record record;
                    record.date = date;
                    record.flightNumber = flightNumber;
                    record.row = row;
                    record.column = column;
                    record.price = price;
                    record.available = true;
                    recordsMap[date][flightNumber][row][column] = record;
                }
            }
        }
    };

};


class Passenger {
public:
    string name;
    map<string, map<string, map<int, map<int, Record>>> > personalRecords;


};


class Airflight {
public:
    static void checkAvailability(string &option) {
        size_t position = option.find(' ');
        string date = option.substr(0, position);
        string flightNumber = option.substr(position + 1, option.size() - 1);

        for (const auto &row : recordsMap[date][flightNumber]) {
            for (const auto &column : row.second) {
                if (column.second.available) {
                    char c = 'A' + row.first;
                    cout << column.first << c << " " << column.second.price << "$ available" << endl;
                }
            }
        }
    }


};

/*
class Record {
public:
    //string date;
    //string flightNumber;
    map<string, map<string, map<int, map<int, Record>>>> rowColumnPrice;
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
            //record.date = line.substr(0, position);
            string date = line.substr(0, position);
            string lineRemainder = line.substr(position + 1);

            position = lineRemainder.find(' ');
            //record.flightNumber = lineRemainder.substr(0, position);
            string flightNumber = lineRemainder.substr(0, position);
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
                    record.rowColumnPrice [date][flightNumber][row][i] = price;
                    record.rowColumnPrice [date][flightNumber][row][i] = price;
                    cout << "row " << row << " column " << i << " price " << price << "\n";
                }
            }
        }
    }
};

class Passenger : public Record {
public:
    string name;
    map<int, Record> personalRecords;


    void bookTicket(string &option) {
        size_t position = option.find(' ');
        string data = option.substr(0, position);
        string flightNumber = option.substr(position + 1, option.size() - 1);

        cout << flightNumber << endl;
        cout << data << endl;


    }
};

map <int, Passenger> passengers; // int - ID

class Airflight {
public:
    static void checkAvailability(string &option) {
        size_t position = option.find(' ');
        string data = option.substr(0, position);
        string flightNumber = option.substr(position + 1, option.size() - 1);



    }
};*/

int main() {
    cout << "Welcome to air-flight booking system!" << endl
         << "Please select an option:" << endl
         << "Check seat availability (check)" << endl
         << "Book a ticket (book)" << endl
         << "Return a ticket (return)" << endl
         << "View booked tickets (view)" << endl
         << "Exit (exit)" << endl;

    Parser::parseRecord();

    string option;
    size_t position;
    string newOption;
    string functionOption;

    while (option != "exit") {
        getline(cin, option);

        position = option.find(' ');
        newOption = option.substr(0, position);
        functionOption = option.substr(position + 1, option.size() - 1);

        if (newOption == "check") {
            cout << "Enter the seat number: ";
            Airflight::checkAvailability(functionOption);
        } else if (newOption == "book") {
            cout << "Enter the passenger name: ";
        } else if (newOption == "return") {
            cout << "Enter the passenger name: ";
        } else if (newOption == "view") {
            cout << "Enter the passenger name: ";
        } else if (newOption == "exit") {
            cout << "Goodbye!";
        } else {
            cout << "Invalid option!" << endl;
        }
    }
    return 0;
}
