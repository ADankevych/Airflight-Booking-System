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
    string name = "";
    int ID;
};

map<string, map<string, map<int, map<int, Record>>>> recordsMap;
int previousID = 0;

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
private:
    string name;
    map<string, map<string, map<int, map<int, Record>>>> personalRecords;

public:

    Passenger() = default;

    explicit Passenger(string &name) {
        this->name = name;
    }

    explicit Passenger(map<string, map<string, map<int, map<int, Record>>>> &personalRecords) {
        this->personalRecords = personalRecords;
    }

    void setName(string &newName) {
        this->name = newName;
    }

    void bookTicket(string &option) {
        size_t position = option.find(' ');

        string date = option.substr(0, position);
        string lineRemainder = option.substr(position + 1);

        position = lineRemainder.find(' ');
        string flightNumber = lineRemainder.substr(0, position);
        lineRemainder = lineRemainder.substr(position + 1);

        position = lineRemainder.find(' ');
        string rowColumn = lineRemainder.substr(0, position);
        string name = lineRemainder.substr(position + 1, lineRemainder.size() - 1);
        setName(name);

        char c = rowColumn[rowColumn.size() - 1];
        int row = c - 'A' + 1;
        int column = stoi(rowColumn.substr(0, rowColumn.size() - 2 - name.size()));

        if (recordsMap[date][flightNumber][row][column].available && recordsMap[date][flightNumber][row][column].price != 0) {
            recordsMap[date][flightNumber][row][column].available = false;
            recordsMap[date][flightNumber][row][column].name = name;
            recordsMap[date][flightNumber][row][column].ID = previousID + 1;
            previousID++;
            personalRecords[date][flightNumber][row][column] = recordsMap[date][flightNumber][row][column];

            cout << recordsMap[date][flightNumber][row][column].name << ", ticket booked successfully!" << endl;
            cout << "Your ticket ID is: " << recordsMap[date][flightNumber][row][column].ID << ". Your ticket price is: "
            << recordsMap[date][flightNumber][row][column].price << "$" << ". Your seat is: " << column << " "
            << row << ". Your flight number is: " << flightNumber << ". Your flight date is: " << date << endl;
        } else {
            cout << "The seat is not available!" << endl;
        }
    }

    void returnTicket(string &option) {
        size_t position = option.find(' ');
        int ID = stoi(option.substr(0, position));

        for ( auto &date : recordsMap) {
            for ( auto &flight : date.second) {
                for (auto &row: flight.second) {
                    for (auto &column: row.second) {
                        if (column.second.ID == ID) {
                            column.second.available = true;
                            column.second.name = "";
                            column.second.ID = 0;
                            personalRecords[date.first][flight.first][row.first][column.first] = column.second;
                            cout << "Ticket returned successfully!" << endl
                                 << "Your ticket ID is: " << column.second.ID << ". Your ticket price is: "
                                 << column.second.price << "$" << ". Your seat is: " << column.first << " "
                                 << row.first << ". Your flight number is: " << flight.first << ". Your flight date is: "
                                 << date.first << endl;
                            return;
                        }
                    }
                }
            }
        }
    }


    void viewBookedTickets(string &option) {
        size_t position = option.find(' ');
        string optionType  = option.substr(0, position);
        string lineRemainder = option.substr(position + 1 , option.size() - 1);

        if (optionType == "username") {
            for (auto &date : recordsMap) {
                for (auto &flight : date.second) {
                    for (auto &row : flight.second) {
                        for (auto &column : row.second) {
                            if (column.second.name == lineRemainder) {
                                cout << "Name is: " << column.second.name << ". Ticket ID is: "
                                     << column.second.ID << ". Ticket price is: "
                                     << column.second.price << "$" << ". Seat is: " << column.first << " "
                                     << row.first << ". Flight number is: " << flight.first << ". Flight date is: "
                                     << date.first << endl;
                            }
                        }
                    }
                }
            }
        } else if (optionType == "flight") {
            for (auto &date : recordsMap) {
                for (auto &flight : date.second) {
                    if (flight.first == lineRemainder) {
                        for (auto &row : flight.second) {
                            for (auto &column : row.second) {
                                if (column.second.name != "") {
                                    cout << "Name is: " << column.second.name << ". Ticket ID is: "
                                         << column.second.ID << ". Ticket price is: "
                                         << column.second.price << "$" << ". Seat is: " << column.first << " "
                                         << row.first << ". Flight number is: " << flight.first << ". Flight date is: "
                                         << date.first << endl;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            for (auto &date : recordsMap) {
                for (auto &flight: date.second) {
                    for (auto &row: flight.second) {
                        for (auto &column: row.second) {
                            if (column.second.ID == stoi(optionType)) {
                                cout << "Name is: " << column.second.name << ". Ticket ID is: "
                                     << column.second.ID << ". Ticket price is: "
                                     << column.second.price << "$" << ". Seat is: " << column.first << " "
                                     << row.first << ". Flight number is: " << flight.first << ". Flight date is: "
                                     << date.first << endl;
                            }
                        }
                    }
                }
            }
        }
    }

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
                    char c = 'A' - 1 + row.first;
                    cout << column.first << c << " " << column.second.price << "$ available" << endl;
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
            Airflight::checkAvailability(functionOption);
        } else if (newOption == "book") {
            Passenger passenger(functionOption);
            passenger.bookTicket(functionOption);
        } else if (newOption == "return") {
            Passenger().returnTicket(functionOption);
        } else if (newOption == "view") {
            Passenger().viewBookedTickets(functionOption);
        } else if (newOption == "exit") {
            cout << "Goodbye!";
        } else {
            cout << "Invalid option!" << endl;
        }
    }
    return 0;
}
