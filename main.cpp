#include "Date.cpp"
#include <iostream>
#include <limits>
#include <locale>
#include <cmath>

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printMenu() {
    cout << "Выберите действие, которое вы хотите совершить: \n";
    cout << "1. Вывести сегодняшнюю, вчерашнюю и завтрашнюю даты\n";
    cout << "2. Создать и проверить введенную дату\n";
    cout << "3. Дата X дней назад\n";
    cout << "4. Дата через X дней\n";
    cout << "5. Разница в днях между двумя датами\n";
    cout << "6. Проверить был ли год високосным\n";
    cout << "7. Сравнить две даты\n";
    cout << "8. Последовательность дат вокруг указанной\n";
    cout << "0. Выход\n";
    cout << "Выберите пункт: ";
}

int main() {
    
    setlocale(LC_ALL, "rus");

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
    
                    cout << "Сегодняшняя дата:    " << today.toString() << "\n";
                    cout << "Вчерашняя дата:      " << yesterday.toString() << "\n";
                    cout << "Завтрашняя дата:     " << tomorrow.toString() << "\n";
                    
                    break;
                }
                    
                case 2: {
                    cout << "Введите дату (день месяц год): ";
                    cin >> d >> m >> y;
                    clearInput();
    
                    try {
                        date1 = Date(d, m, y);
                        cout << "Дата: " << date1.toString() << endl;
                    }
                    catch (const exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 3: {
                    cout << "Введите дату (день месяц год): ";
                    cin >> d >> m >> y;
                    clearInput(); 
    
                    try {
                        date1 = Date(d, m, y);
                        cout << "Создана дата: " << date1.toString() << endl;
        
                        cout << "Введите количество дней: ";
                        cin >> days;
                        clearInput();
        
                        if (days < 0) {
                            cout << "Ошибка: количество дней не может быть отрицательным!\n";
                            break;
                        }
        
                        Date pastDate = date1 - days;
                        cout << "\nДата " << days << " дней назад: " << pastDate.toString() << endl;
                    }
                    catch (const exception& e) {
                        cout << "\nОшибка: " << e.what() << endl;
                        cout << "Невозможно вычислить: дата " << d << "." << m << "." << y << " некорректна\n";
                    }
                    break;
                }
                    
                case 4: {
                    cout << "Введите дату (день месяц год): ";
                    cin >> d >> m >> y;
                    clearInput();

                    try {
                        date1 = Date(d, m, y);
                        cout << "Создана дата: " << date1.toString() << endl;

                        cout << "Введите количество дней: ";
                        cin >> days;
                        clearInput();

                        if (days < 0) {
                            cout << "Ошибка: количество дней не может быть отрицательным!\n";
                            break;
                        }

                        Date futureDate = date1 + days;
                        cout << "\nДата через " << days << " дней: " << futureDate.toString() << "\n";
                    }
                    catch(const exception& e) {
                        cout << "\nОшибка: " << e.what() << endl;
                        cout << "Невозможно вычислить: дата " << d << "." << m << "." << y << " некорректна\n";
                    }
                    break;
                }
                    
                case 5: {
                    try {
                        cout << "Введите первую дату (день месяц год): ";
                        cin >> d >> m >> y;
                        clearInput();
                        Date date1(d, m, y);
        
                        cout << "Введите вторую дату (день месяц год): ";
                        cin >> d >> m >> y;
                        clearInput(); 
                        Date date2(d, m, y);
        
                        cout << "Разница между датами: " << abs(date1 - date2) << " дней\n";
                    }
                    catch (const exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 6: {
                    cout << "Введите год: ";
                    if (cin >> y) {
                        if (y < 0) {
                            cout << "Ошибка: год не может быть отрицательным!\n";
                        } else {
                            cout << "Год " << y << " - " 
                            << (Date::checkLeapYear(y) ? "високосный" : "невисокосный") 
                            << endl;
                        }
                    } else {
                        cout << "Ошибка ввода\n";
                    }
                    clearInput();
                    break;
                }
                    
                case 7: {    
                    try {
                        cout << "Введите первую дату (день месяц год): ";
                        cin >> d >> m >> y;
                        clearInput(); 
                        Date date1(d, m, y);
        
                        cout << "Введите вторую дату (день месяц год): ";
                        cin >> d >> m >> y;
                        clearInput(); 
                        Date date2(d, m, y);
        
                        if (date1 == date2) {
                            cout << "Даты одинаковы: " << date1.toString() << endl;
                        }
                        else if (date1 < date2) {
                            cout << date1.toString() << " была раньше чем " << date2.toString() << endl;
                        }
                        else {
                            cout << date1.toString() << " была позже чем " << date2.toString() << endl;
                        }
                    }
                    catch (const exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 8: {  
                    try {
                        cout << "Введите дату (день месяц год): ";
                        cin >> d >> m >> y;
                        clearInput(); 
                        Date date(d, m, y);
        
                        cout << "Введите количество дней: ";
                        cin >> days;
                        clearInput();
        
                        if (days <= 0) {
                            cout << "Ошибка: количество дней должно быть положительным!\n";
                            break;
                        }
        
                        cout << "\nИсходная дата: " << date.toString() << endl;
        
                        cout << "\nДаты назад (используя date--):\n";
                        Date tempBack = date;
                        for (int i = 0; i < days; i++) {
                            Date result = tempBack--;
                            cout << "Шаг " << i+1 << ": " << result.toString() << endl;
                        }
                        cout << "Итог: " << (date - days).toString() << endl;
        
                        cout << "\nДаты вперед (используя date++):\n";
                        Date tempForward = date;
                        for (int i = 0; i < days; i++) {
                            Date result = tempForward++;
                            cout << "Шаг " << i+1 << ": " << result.toString() << endl;
                        }
                        cout << "Итог: " << (date + days).toString() << endl;
                    }
                    catch (const exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 0:
                    cout << "Вы вышли из программы\n";
                    break;
                    
                default:
                    cout << "\nНеверный выбор! Выберите пункт 0-8\n";
            }
        }
        catch (const exception& e) {
            cout << "\nОшибка: " << e.what() << "\n";
        }
        
        if (choice != 0) {
            cout << "Нажмите Enter для продолжения...";
            cin.get();
        }
        
    } while(choice != 0);
    
    return 0;
}
