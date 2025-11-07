#include "AEROFLOT.h"        // Подключаем заголовочный файл с объявлением класса
#include <iostream>          // Для работы с вводом-выводом (cout, cin)
#include <cstring>           // Для работы со строками C-style (strcpy, strlen)

// Конструктор по умолчанию - создает объект с пустыми значениями
AEROFLOT::AEROFLOT() : destination(nullptr), flightNumber(0), aircraftType(nullptr) {
    // Выводим сообщение о создании объекта для отслеживания работы программы
    std::cout << "Вызван конструктор по умолчанию для AEROFLOT" << std::endl;
}

// Конструктор с параметрами - создает объект с заданными значениями
AEROFLOT::AEROFLOT(const char* dest, int number, const char* type) {
    // Выделяем динамическую память для строки назначения
    destination = new char[strlen(dest) + 1];  // +1 для нулевого терминатора
    strcpy(destination, dest);                 // Копируем строку в выделенную память
    
    flightNumber = number;                     // Присваиваем номер рейса
    
    // Выделяем динамическую память для типа самолета
    aircraftType = new char[strlen(type) + 1]; // +1 для нулевого терминатора
    strcpy(aircraftType, type);                // Копируем строку в выделенную память
    
    // Сообщаем о создании объекта с параметрами
    std::cout << "Вызван конструктор с параметрами для AEROFLOT: " << destination << std::endl;
}

// Конструктор копирования - создает копию существующего объекта
AEROFLOT::AEROFLOT(const AEROFLOT& other) {
    // Выделяем новую память для назначения и копируем данные
    destination = new char[strlen(other.destination) + 1];
    strcpy(destination, other.destination);
    
    // Копируем числовое поле
    flightNumber = other.flightNumber;
    
    // Выделяем новую память для типа самолета и копируем данные
    aircraftType = new char[strlen(other.aircraftType) + 1];
    strcpy(aircraftType, other.aircraftType);
    
    // Сообщаем о создании копии объекта
    std::cout << "Вызван конструктор копирования для AEROFLOT: " << destination << std::endl;
}

// Деструктор - освобождает ресурсы при уничтожении объекта
AEROFLOT::~AEROFLOT() {
    std::cout << "Вызван деструктор для AEROFLOT: ";
    if (destination) {                         // Проверяем, что указатель не нулевой
        std::cout << destination;              // Выводим название для информации
        delete[] destination;                  // Освобождаем память, выделенную под назначение
    }
    if (aircraftType) {                        // Проверяем, что указатель не нулевой
        delete[] aircraftType;                 // Освобождаем память, выделенную под тип самолета
    }
    std::cout << std::endl;                    // Переход на новую строку после вывода
}

// Оператор присваивания - позволяет присвоить один объект другому
AEROFLOT& AEROFLOT::operator=(const AEROFLOT& other) {
    if (this != &other) {                      // Проверяем, что это не присваивание самому себе
        // Освобождаем старую память
        delete[] destination;
        delete[] aircraftType;
        
        // Выделяем новую память и копируем данные из другого объекта
        destination = new char[strlen(other.destination) + 1];
        strcpy(destination, other.destination);
        
        // Копируем числовое поле
        flightNumber = other.flightNumber;
        
        // Выделяем новую память и копируем данные из другого объекта
        aircraftType = new char[strlen(other.aircraftType) + 1];
        strcpy(aircraftType, other.aircraftType);
    }
    return *this;                              // Возвращаем ссылку на текущий объект
}

// Set-функция для установки пункта назначения
void AEROFLOT::setDestination(const char* dest) {
    delete[] destination;                      // Освобождаем старую память
    destination = new char[strlen(dest) + 1];  // Выделяем новую память
    strcpy(destination, dest);                 // Копируем новую строку
}

// Set-функция для установки типа самолета
void AEROFLOT::setAircraftType(const char* type) {
    delete[] aircraftType;                     // Освобождаем старую память
    aircraftType = new char[strlen(type) + 1]; // Выделяем новую память
    strcpy(aircraftType, type);                // Копируем новую строку
}

// Перегрузка оператора вывода - для красивого вывода объекта в поток
std::ostream& operator<<(std::ostream& os, const AEROFLOT& flight) {
    // Форматируем вывод информации о рейсе
    os << "Рейс №" << flight.flightNumber 
       << " в '" << flight.destination 
       << "' на самолете '" << flight.aircraftType << "'";
    return os;                                 // Возвращаем поток для цепочки операций
}

// Перегрузка оператора ввода - для ввода данных объекта из потока
std::istream& operator>>(std::istream& is, AEROFLOT& flight) {
    char buffer[100];                          // Временный буфер для ввода строк
    
    std::cout << "Введите пункт назначения: ";
    is >> buffer;                              // Читаем строку в буфер
    flight.setDestination(buffer);             // Устанавливаем значение через set-функцию
    
    std::cout << "Введите номер рейса: ";
    is >> flight.flightNumber;                 // Читаем номер рейса напрямую в поле
    
    std::cout << "Введите тип самолета: ";
    is >> buffer;                              // Читаем строку в буфер
    flight.setAircraftType(buffer);            // Устанавливаем значение через set-функцию
    
    return is;                                 // Возвращаем поток для цепочки операций
}

// Оператор сравнения "меньше" - для сортировки объектов по названию пункта назначения
bool AEROFLOT::operator<(const AEROFLOT& other) const {
    // Сравниваем строки назначения лексикографически
    return strcmp(destination, other.destination) < 0;
}
