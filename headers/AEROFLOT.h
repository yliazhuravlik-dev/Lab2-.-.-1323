// AEROFLOT.h
#ifndef AEROFLOT_H  // Защита от повторного включения файла
#define AEROFLOT_H  // Если AEROFLOT_H не определен, определяем его

#include <iostream>  // Для работы с потоками ввода/вывода (std::cout, std::cin)
#include <cstring>   // Для работы со строками в стиле C (strcpy, strlen)

class AEROFLOT {     // Объявление класса AEROFLOT
private:             // Секция приватных членов класса (доступны только внутри класса)
    char* destination;    // Указатель на строку - пункт назначения рейса
    int flightNumber;     // Целое число - номер рейса
    char* aircraftType;   // Указатель на строку - тип самолета

public:              // Секция публичных членов класса (доступны извне)
    // Конструкторы - специальные методы для создания объектов
    AEROFLOT();                              // Конструктор по умолчанию (без параметров)
    AEROFLOT(const char* dest, int number, const char* type);  // Конструктор с параметрами
    AEROFLOT(const AEROFLOT& other);        // Конструктор копирования
    
    // Деструктор - специальный метод для очистки памяти при уничтожении объекта
    ~AEROFLOT();
    
    // Оператор присваивания - для копирования данных из одного объекта в другой
    AEROFLOT& operator=(const AEROFLOT& other);
    
    // Get-функции - методы для чтения приватных полей (геттеры)
    const char* getDestination() const { return destination; }   // Возвращает пункт назначения
    int getFlightNumber() const { return flightNumber; }         // Возвращает номер рейса
    const char* getAircraftType() const { return aircraftType; } // Возвращает тип самолета
    
    // Set-функции - методы для установки значений приватных полей (сеттеры)
    void setDestination(const char* dest);    // Устанавливает пункт назначения
    void setFlightNumber(int number) { flightNumber = number; }  // Устанавливает номер рейса
    void setAircraftType(const char* type);   // Устанавливает тип самолета
    
    // Перегрузка операторов ввода/вывода - для удобной работы с потоками
    friend std::ostream& operator<<(std::ostream& os, const AEROFLOT& flight);  // Вывод в поток
    friend std::istream& operator>>(std::istream& is, AEROFLOT& flight);        // Ввод из потока
    
    // Методы для сравнения (для сортировки)
    bool operator<(const AEROFLOT& other) const;  // Оператор меньше для сортировки по алфавиту
};

#endif  // Конец защиты от повторного включения
