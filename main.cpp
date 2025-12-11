#include "Data.h"
#include <iostream>
#include <limits>
#include <locale>

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
                    cout << "Вчерашняя дата: " << yesterday.toString() << "\n";
                    cout << "Завтрашняя дата: " << tomorrow.toString() << "\n";
                    
                    break;
                }
                    
                case 2: {
                    cout << "Введите день месяц год через пробел: ";
                    cin >> d >> m >> y;
    
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
                    cout << "Введите день месяц год через пробел: ";
                    cin >> d >> m >> y;
    
                try {
                    // Пытаемся создать дату
                    date1 = Date(d, m, y);
                    cout << "Создана дата: " << date1.toString() << endl;
        
                     // Если создание успешно, запрашиваем количество дней
                    cout << "Введите количество дней: ";
                    cin >> days;
                    clearInput();
        
                    if (days < 0) {
                        cout << "Ошибка: количество дней не может быть отрицательным!\n";
                        break;
                    }
        
                    // Вычисляем дату несколько дней назад
                    Date pastDate = date1 - days;
                    cout << "\nДата " << days << " дней назад: " << pastDate.toString() << endl;
        
                }

                catch (const exception& e) {
                // Если произошла ошибка при создании даты
                cout << "\nОшибка: " << e.what() << endl;
                cout << "Невозможно вычислить: дата " << d << "." << m << "." << y << " некорректна\n";
                }
                break;
        }
                    
                case 4: {
                    cout << "Введите день месяц год через пробел: ";
                    cin >> d >> m >> y;

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
                    cout << "\n" << string(50, '=') << "\n";
                    cout << "       РАЗНИЦА МЕЖДУ ДВУМЯ ДАТАМИ\n";
                    cout << string(50, '=') << "\n";
                    
                    cout << "Введите первую дату (день месяц год): ";
                    cin >> d >> m >> y;
                    date1 = Date(d, m, y);
                    
                    cout << "Введите вторую дату (день месяц год): ";
                    cin >> d >> m >> y;
                    date2 = Date(d, m, y);
                    
                    if (date1.isValid() && date2.isValid()) {
                        int difference = date1 - date2;  // Используем operator-
                        
                        cout << "\nДата 1: " << date1.toString() << "\n";
                        cout << "Дата 2: " << date2.toString() << "\n";
                        cout << "\nРазница в днях: " << abs(difference) << " дней\n";
                        
                        if (difference > 0) {
                            cout << date1.toString() << " на " << difference 
                                 << " дней ПОЗЖЕ чем " << date2.toString() << "\n";
                        } else if (difference < 0) {
                            cout << date1.toString() << " на " << -difference 
                                 << " дней РАНЬШЕ чем " << date2.toString() << "\n";
                        } else {
                            cout << "Даты РАВНЫ\n";
                        }
                    } else {
                        cout << "✗ Одна из дат некорректна!\n";
                    }
                    break;
                }
                    
                case 6: {
                    cout << "\n" << string(50, '=') << "\n";
                    cout << "     Проверка високосного года\n";
                    cout << string(50, '=') << "\n";
                    
                    cout << "Введите год для проверки: ";
                    cin >> y;
                    clearInput();
                    
                    bool isLeap = Date::checkLeapYear(y);
                    cout << "\nГод " << y << " - ";
                    if (isLeap) {
                        cout << y << " - високосный год\n";
                    } else {
                        cout << y << " - невисокосный год\n";
                    }
                    
                    // Создание и проверка даты 29 февраля
                    Date feb29(29, 2, y);
                    cout << "\nПроверка через создание объекта:\n";
                    cout << "Date(29, 2, " << y << ").isValid() = " 
                         << (feb29.isValid() ? "true ✓" : "false ✗") << "\n";
                    break;
                }
                    
                case 7: {
                    cout << "\n" << string(50, '=') << "\n";
                    cout << "           СРАВНЕНИЕ ДВУХ ДАТ\n";
                    cout << string(50, '=') << "\n";
                    
                    cout << "Введите первую дату (день месяц год): ";
                    cin >> d >> m >> y;
                    date1 = Date(d, m, y);
                    
                    cout << "Введите вторую дату (день месяц год): ";
                    cin >> d >> m >> y;
                    date2 = Date(d, m, y);
                    
                    if (date1.isValid() && date2.isValid()) {
                        cout << "\n" << string(40, '-') << "\n";
                        cout << "Сравнение:\n";
                        cout << string(40, '-') << "\n";
                        cout << date1.toString() << " == " << date2.toString() << " : " 
                             << (date1 == date2 ? "ДА" : "НЕТ") << "\n";
                        cout << date1.toString() << " != " << date2.toString() << " : " 
                             << (date1 != date2 ? "ДА" : "НЕТ") << "\n";
                        cout << date1.toString() << " <  " << date2.toString() << " : " 
                             << (date1 < date2 ? "ДА" : "НЕТ") << "\n";
                        cout << date1.toString() << " >  " << date2.toString() << " : " 
                             << (date1 > date2 ? "ДА" : "НЕТ") << "\n";
                        cout << date1.toString() << " <= " << date2.toString() << " : " 
                             << (date1 <= date2 ? "ДА" : "НЕТ") << "\n";
                        cout << date1.toString() << " >= " << date2.toString() << " : " 
                             << (date1 >= date2 ? "ДА" : "НЕТ") << "\n";
                        cout << string(40, '-') << "\n";
                    } else {
                        cout << "Одна из дат некорректна!\n";
                    }
                    break;
                }
                    
                case 8: {
                    cout << "\n" << string(60, '=') << "\n";
                    cout << "  ПОСЛЕДОВАТЕЛЬНОСТЬ ДАТ ВОКРУГ УКАЗАННОЙ\n";
                    cout << "      (демонстрация унарных операторов)\n";
                    cout << string(60, '=') << "\n";
                    
                    // Ввод основной даты
                    cout << "Введите центральную дату (день месяц год): ";
                    cin >> d >> m >> y;
                    clearInput();
                    
                    Date centerDate(d, m, y);
                    if (!centerDate.isValid()) {
                        cout << "✗ Некорректная дата!\n";
                        break;
                    }
                    
                    // Ввод количества дней для отображения
                    cout << "Сколько дней отобразить в каждую сторону? ";
                    cin >> days;
                    clearInput();
                    
                    if (days <= 0) {
                        cout << "✗ Количество дней должно быть положительным!\n";
                        break;
                    }
                    
                    cout << "\nЦентральная дата: " << centerDate.toString() << "\n";
                    cout << "Отображаем по " << days << " дней в каждую сторону\n";
                    cout << string(60, '-') << "\n";
                    
                    // ========== ДЕМОНСТРАЦИЯ ПОСТФИКСНОГО ДЕКРЕМЕНТА (date--) ==========
                    cout << "\n--- ДАТЫ ДО ЦЕНТРАЛЬНОЙ (используя date--) ---\n";
                    cout << "Операция: previousDate = temp--\n";
                    cout << "temp-- возвращает СТАРОЕ значение, затем уменьшает temp\n\n";
                    
                    Date temp = centerDate;  // Начинаем с центральной даты
                    
                    cout << "Начинаем с центральной даты: " << temp.toString() << "\n\n";
                    
                    for (int i = 1; i <= days; i++) {
                        Date previousDate = temp--;  // ПОСТФИКСНЫЙ ДЕКРЕМЕНТ!
                        
                        cout << "Шаг " << i << ":\n";
                        cout << "  temp-- вернул: " << previousDate.toString() << "\n";
                        cout << "  После temp-- дата стала: " << temp.toString() << "\n";
                        
                        if (i == 1) {
                            cout << " Обратите внимание: первый возврат - это центральная дата!\n";
                            cout << "    Потому что date-- сначала возвращает, потом изменяет\n";
                        }
                        cout << "\n";
                    }
                    
                    cout << "Итог после " << days << " операций date--:\n";
                    cout << "Последняя возвращенная дата: " << (centerDate - (days-1)).toString() << "\n";
                    cout << "Текущее значение temp: " << temp.toString() << "\n";
                    cout << "(на " << days << " дней меньше центральной)\n";
                    
                    // ========== ДЕМОНСТРАЦИЯ ПОСТФИКСНОГО ИНКРЕМЕНТА (date++) ==========
                    cout << "\n" << string(60, '=') << "\n";
                    cout << "\n--- ДАТЫ ПОСЛЕ ЦЕНТРАЛЬНОЙ (используя date++) ---\n";
                    cout << "Операция: nextDate = temp++\n";
                    cout << "temp++ возвращает СТАРОЕ значение, затем увеличивает temp\n\n";
                    
                    // Восстанавливаем исходную дату
                    temp = centerDate;
                    cout << "Начинаем с центральной даты: " << temp.toString() << "\n\n";
                    
                    for (int i = 1; i <= days; i++) {
                        Date nextDate = temp++;  // ПОСТФИКСНЫЙ ИНКРЕМЕНТ!
                        
                        cout << "Шаг " << i << ":\n";
                        cout << "  temp++ вернул: " << nextDate.toString() << "\n";
                        cout << "  После temp++ дата стала: " << temp.toString() << "\n";
                        
                        if (i == 1) {
                            cout << "  ⚠ Обратите внимание: первый возврат - это центральная дата!\n";
                            cout << "    Потому что date++ сначала возвращает, потом изменяет\n";
                        }
                        cout << "\n";
                    }
                    
                    cout << "Итог после " << days << " операций date++:\n";
                    cout << "Последняя возвращенная дата: " << (centerDate + (days-1)).toString() << "\n";
                    cout << "Текущее значение temp: " << temp.toString() << "\n";
                    cout << "(на " << days << " дней больше центральной)\n";
                    
                    // ========== СРАВНЕНИЕ С ПРЕФИКСНЫМИ ОПЕРАТОРАМИ ==========
                    cout << "\n" << string(60, '=') << "\n";
                    cout << "\n--- СРАВНЕНИЕ С ПРЕФИКСНЫМИ ОПЕРАТОРАМИ ---\n\n";
                    
                    // Префиксный декремент
                    temp = centerDate;
                    cout << "Префиксный декремент (--date):\n";
                    cout << "  Исходная дата: " << temp.toString() << "\n";
                    cout << "  --date вернул: " << (--temp).toString() << "\n";
                    cout << "  После операции: " << temp.toString() << "\n";
                    
                    // Префиксный инкремент
                    temp = centerDate;
                    cout << "Префиксный инкремент (++date):\n";
                    cout << "  Исходная дата: " << temp.toString() << "\n";
                    cout << "  ++date вернул: " << (++temp).toString() << "\n";
                    cout << "  После операции: " << temp.toString() << "\n";
                    
                    // ========== ВИЗУАЛИЗАЦИЯ ВСЕЙ ПОСЛЕДОВАТЕЛЬНОСТИ ==========
                    cout << "\n" << string(60, '=') << "\n";
                    cout << "\n--- ВИЗУАЛЬНАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ ---\n\n";
                    
                    cout << "Последовательность дат:\n\n";
                    
                    // Даты ДО
                    cout << "До: ";
                    for (int i = days; i >= 1; i--) {
                        cout << "←" << (centerDate - i).toString();
                    }
                    
                    // Центральная дата
                    cout << "\n     [ " << centerDate.toString() << " ]\n";
                    
                    // Даты ПОСЛЕ
                    cout << "После:";
                    for (int i = 1; i <= days; i++) {
                        cout << (centerDate + i).toString() << "→ ";
                    }
                }
                    
                case 0:
                    cout << "\n" << string(50, '=') << "\n";
                    cout << "        ВЫХОД ИЗ ПРОГРАММЫ\n";
                    cout << string(50, '=') << "\n";
                    break;
                    
                default:
                    cout << "\n⚠ Неверный выбор! Пожалуйста, выберите пункт 0-8\n";
            }
        }
        catch (const exception& e) {
            cout << "\n✗ ОШИБКА: " << e.what() << "\n";
        }
        
        if (choice != 0) {
            cout << "\n" << string(50, '=') << "\n";
            cout << "Нажмите Enter для продолжения...";
            cin.get();
        }
        
    } while(choice != 0);
    
    return 0;
}
