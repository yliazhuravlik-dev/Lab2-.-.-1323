// AEROFLOT.h
#ifndef AEROFLOT_H
#define AEROFLOT_H

#include <iostream>
#include <cstring>

class AEROFLOT {
private:
    char* destination;
    int flightNumber;
    char* aircraftType;

public:
    // Конструкторы
    AEROFLOT();
    AEROFLOT(const char* dest, int number, const char* type);
    AEROFLOT(const AEROFLOT& other);
    
    // Деструктор
    ~AEROFLOT();
    
    // Оператор присваивания
    AEROFLOT& operator=(const AEROFLOT& other);
    
    // Get-функции
    const char* getDestination() const { return destination; }
    int getFlightNumber() const { return flightNumber; }
    const char* getAircraftType() const { return aircraftType; }
    
    // Set-функции
    void setDestination(const char* dest);
    void setFlightNumber(int number) { flightNumber = number; }
    void setAircraftType(const char* type);
    
    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const AEROFLOT& flight);
    friend std::istream& operator>>(std::istream& is, AEROFLOT& flight);
    
    // Методы для сравнения (для сортировки)
    bool operator<(const AEROFLOT& other) const;
};

#endif
