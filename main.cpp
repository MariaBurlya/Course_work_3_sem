#include "Data.cpp"
#include <iostream>
#include <locale>

using namespace std;

void displayMenu() {
    cout << "\n=== МЕНЮ РАБОТЫ С ДАТАМИ ===" << endl;
    cout << "1. Показать текущую дату" << endl;
    cout << "2. Создать новую дату" << endl;
    cout << "3. Узнать дату через X дней" << endl;
    cout << "4. Узнать дату X дней назад" << endl;
    cout << "5. Вычислить разницу между датами" << endl;
    cout << "6. Проверить существование даты (29 февраля)" << endl;
    cout << "7. Сравнить две даты" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

void createDateInteractive() {
    try {
        int d, m, y;
        cout << "Введите день: ";
        cin >> d;
        cout << "Введите месяц: ";
        cin >> m;
        cout << "Введите год: ";
        cin >> y;
        
        Date userDate(d, m, y);
        cout << "Создана дата: ";
        userDate.print();
        cout << endl;
        
        // Дополнительная информация
        cout << "Это " << (Date::isLeapYear(y) ? "високосный" : "невисокосный") << " год" << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void calculateFutureDate() {
    try {
        Date today = Date::today();
        cout << "Сегодня: ";
        today.print();
        cout << endl;
        
        int days;
        cout << "Введите количество дней: ";
        cin >> days;
        
        Date future = today + days;
        cout << "Через " << days << " дней будет: ";
        future.print();
        cout << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void compareDates() {
    try {
        cout << "Введите первую дату:" << endl;
        int d1, m1, y1;
        cout << "День: "; cin >> d1;
        cout << "Месяц: "; cin >> m1;
        cout << "Год: "; cin >> y1;
        Date date1(d1, m1, y1);
        
        cout << "Введите вторую дату:" << endl;
        int d2, m2, y2;
        cout << "День: "; cin >> d2;
        cout << "Месяц: "; cin >> m2;
        cout << "Год: "; cin >> y2;
        Date date2(d2, m2, y2);
        
        cout << "\nРезультаты сравнения:" << endl;
        cout << "Дата 1: "; date1.print(); cout << endl;
        cout << "Дата 2: "; date2.print(); cout << endl;
        
        if (date1 == date2) {
            cout << "Даты одинаковые" << endl;
        } else if (date1 < date2) {
            cout << "Первая дата раньше второй" << endl;
        } else {
            cout << "Первая дата позже второй" << endl;
        }
        
        cout << "Разница в днях: " << date1.daysBetween(date2) << " дней" << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void testLeapYear() {
    int year;
    cout << "Введите год для проверки 29 февраля: ";
    cin >> year;
    
    try {
        Date leapTest(29, 2, year);
        cout << "29 февраля " << year << " года существует!" << endl;
        cout << year << " - високосный год" << endl;
    }
    catch (const invalid_argument& e) {
        cout << "29 февраля " << year << " года НЕ существует!" << endl;
        cout << year << " - невисокосный год" << endl;
    }
}

int main() {

    setlocale(LC_ALL, "rus");
    
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                Date today = Date::today();
                cout << "Сегодняшняя дата: ";
                today.print();
                cout << endl;
                break;
            }
            case 2:
                createDateInteractive();
                break;
            case 3:
                calculateFutureDate();
                break;
            case 4: {
                Date today = Date::today();
                cout << "Сегодня: ";
                today.print();
                cout << endl;
                
                int days;
                cout << "Введите количество дней: ";
                cin >> days;
                
                Date past = today - days;
                cout << days << " дней назад было: ";
                past.print();
                cout << endl;
                break;
            }
            case 5: {
                try {
                    cout << "Введите первую дату:" << endl;
                    int d1, m1, y1;
                    cout << "День: "; cin >> d1;
                    cout << "Месяц: "; cin >> m1;
                    cout << "Год: "; cin >> y1;
                    Date date1(d1, m1, y1);
                    
                    cout << "Введите вторую дату:" << endl;
                    int d2, m2, y2;
                    cout << "День: "; cin >> d2;
                    cout << "Месяц: "; cin >> m2;
                    cout << "Год: "; cin >> y2;
                    Date date2(d2, m2, y2);
                    
                    int difference = date1.daysBetween(date2);
                    cout << "\nРазница между датами: " << difference << " дней" << endl;
                }
                catch (const invalid_argument& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            }
            case 6:
                testLeapYear();
                break;
            case 7:
                compareDates();
                break;
            case 0:
                cout << "Выход из программы..." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
        
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}
