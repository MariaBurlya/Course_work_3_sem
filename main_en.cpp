#include "Date.cpp"
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printMenu() {
    cout << "Choose an action you want to perform: \n";
    cout << "1. Display today's, yesterday's and tomorrow's dates\n";
    cout << "2. Create and verify an entered date\n";
    cout << "3. Date X days ago\n";
    cout << "4. Date in X days\n";
    cout << "5. Difference in days between two dates\n";
    cout << "6. Check if a year is leap\n";
    cout << "7. Compare two dates\n";
    cout << "8. Sequence of dates around specified date\n";
    cout << "0. Exit\n";
    cout << "Select option: ";
}

int main() {
    
    int choice;
    Date date1, date2;
    int d, m, y, days;
    
    do {
        printMenu();
        cin >> choice;
        clearInput();
        
        try {
            switch(choice) {
                case 1: {                    
                    Date today = Date::today();
                    Date yesterday = today;
                    Date tomorrow = today;

                    --yesterday;
                    ++tomorrow;
    
                    cout << "Today:     " << today.toString() << "\n";
                    cout << "Yesterday: " << yesterday.toString() << "\n";
                    cout << "Tomorrow:  " << tomorrow.toString() << "\n";
                    
                    break;
                }
                    
                case 2: {
                    cout << "Enter date (day month year): ";
                    cin >> d >> m >> y;
                    clearInput();
    
                    try {
                        date1 = Date(d, m, y);
                        cout << "Date: " << date1.toString() << endl;
                    }
                    catch (const exception& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 3: {
                    cout << "Enter date (day month year): ";
                    cin >> d >> m >> y;
                    clearInput(); 
    
                    try {
                        date1 = Date(d, m, y);
                        cout << "Created date: " << date1.toString() << endl;
        
                        cout << "Enter number of days: ";
                        cin >> days;
                        clearInput();
        
                        if (days < 0) {
                            cout << "Error: number of days cannot be negative!\n";
                            break;
                        }
        
                        Date pastDate = date1 - days;
                        cout << "\nDate " << days << " days ago: " << pastDate.toString() << endl;
                    }
                    catch (const exception& e) {
                        cout << "\nError: " << e.what() << endl;
                        cout << "Cannot calculate: date " << d << "." << m << "." << y << " is invalid\n";
                    }
                    break;
                }
                    
                case 4: {
                    cout << "Enter date (day month year): ";
                    cin >> d >> m >> y;
                    clearInput();

                    try {
                        date1 = Date(d, m, y);
                        cout << "Created date: " << date1.toString() << endl;

                        cout << "Enter number of days: ";
                        cin >> days;
                        clearInput();

                        if (days < 0) {
                            cout << "Error: number of days cannot be negative!\n";
                            break;
                        }

                        Date futureDate = date1 + days;
                        cout << "\nDate in " << days << " days: " << futureDate.toString() << "\n";
                    }
                    catch(const exception& e) {
                        cout << "\nError: " << e.what() << endl;
                        cout << "Cannot calculate: date " << d << "." << m << "." << y << " is invalid\n";
                    }
                    break;
                }
                    
                case 5: {
                    try {
                        cout << "Enter first date (day month year): ";
                        cin >> d >> m >> y;
                        clearInput();
                        Date date1(d, m, y);
        
                        cout << "Enter second date (day month year): ";
                        cin >> d >> m >> y;
                        clearInput(); 
                        Date date2(d, m, y);
        
                        cout << "Difference between dates: " << abs(date1 - date2) << " days\n";
                    }
                    catch (const exception& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 6: {
                    cout << "Enter year: ";
                    if (cin >> y) {
                        if (y < 0) {
                            cout << "Error: year cannot be negative!\n";
                        } else {
                            cout << "Year " << y << " is " 
                            << (Date::checkLeapYear(y) ? "leap" : "not leap") 
                            << endl;
                        }
                    } else {
                        cout << "Input error\n";
                    }
                    clearInput();
                    break;
                }
                    
                case 7: {    
                    try {
                        cout << "Enter first date (day month year): ";
                        cin >> d >> m >> y;
                        clearInput(); 
                        Date date1(d, m, y);
        
                        cout << "Enter second date (day month year): ";
                        cin >> d >> m >> y;
                        clearInput(); 
                        Date date2(d, m, y);
        
                        if (date1 == date2) {
                            cout << "Dates are equal: " << date1.toString() << endl;
                        }
                        else if (date1 < date2) {
                            cout << date1.toString() << " is earlier than " << date2.toString() << endl;
                        }
                        else {
                            cout << date1.toString() << " is later than " << date2.toString() << endl;
                        }
                    }
                    catch (const exception& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 8: {  
                    try {
                        cout << "Enter date (day month year): ";
                        cin >> d >> m >> y;
                        clearInput(); 
                        Date date(d, m, y);
        
                        cout << "Enter number of days: ";
                        cin >> days;
                        clearInput();
        
                        if (days <= 0) {
                            cout << "Error: number of days must be positive!\n";
                            break;
                        }
        
                        cout << "\nOriginal date: " << date.toString() << endl;
        
                        cout << "\nDates backward (using date--):\n";
                        Date tempBack = date;
                        for (int i = 0; i < days; i++) {
                            Date result = tempBack--;
                            cout << "Step " << i+1 << ": " << result.toString() << endl;
                        }
                        cout << "Result: " << (date - days).toString() << endl;
        
                        cout << "\nDates forward (using date++):\n";
                        Date tempForward = date;
                        for (int i = 0; i < days; i++) {
                            Date result = tempForward++;
                            cout << "Step " << i+1 << ": " << result.toString() << endl;
                        }
                        cout << "Result: " << (date + days).toString() << endl;
                    }
                    catch (const exception& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 0:
                    cout << "You have exited the program\n";
                    break;
                    
                default:
                    cout << "\nInvalid choice! Select option 0-8\n";
            }
        }
        catch (const exception& e) {
            cout << "\nError: " << e.what() << "\n";
        }
        
        if (choice != 0) {
            cout << "Press Enter to continue...";
            cin.get();
        }
        
    } while(choice != 0);
    
    return 0;
}
