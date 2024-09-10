#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "Welcome to air-flight booking system!" << endl
         << "Please select an option:" << endl
         << "Check seat availability (check)" << endl
         << "Book a ticket (book)" << endl
         << "Return a ticket (return)" << endl
         << "View booked tickets (view)" << endl;

    string option;
    getline(cin, option);

    string newOption = "";

    for (int i = 0; i < option.length(); i++){
        if (option[i] != ' '){
            newOption += option[i];
        } else {
            break;
        }
    }

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

    return 0;
}
