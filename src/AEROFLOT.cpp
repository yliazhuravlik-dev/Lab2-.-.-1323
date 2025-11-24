// AEROFLOT.cpp
#define _CRT_SECURE_NO_WARNINGS  // ОТКЛЮЧАЕМ ПРЕДУПРЕЖДЕНИЯ О БЕЗОПАСНОСТИ
#include "AEROFLOT.h"
#include <iostream>
#include <cstring>

// Безопасное копирование строки
void safeStringCopy(char*& dest, const char* src) {
    if (dest) {
        delete[] dest;
        dest = nullptr;
    }
    if (src) {
        dest = new char[strlen(src) + 1];
        strcpy(dest, src);  // Теперь безопасно, т.к. выделили нужный размер
    }
}

// Конструктор по умолчанию
AEROFLOT::AEROFLOT() : destination(nullptr), flightNumber(0), aircraftType(nullptr) {
    std::cout << "Вызван конструктор по умолчанию для AEROFLOT" << std::endl;
}

// Конструктор с параметрами
AEROFLOT::AEROFLOT(const char* dest, int number, const char* type) : flightNumber(number) {
    safeStringCopy(destination, dest);
    safeStringCopy(aircraftType, type);
    std::cout << "Вызван конструктор с параметрами для AEROFLOT" << std::endl;
}

// Конструктор копирования
AEROFLOT::AEROFLOT(const AEROFLOT& other) : flightNumber(other.flightNumber) {
    safeStringCopy(destination, other.destination);
    safeStringCopy(aircraftType, other.aircraftType);
    std::cout << "Вызван конструктор копирования для AEROFLOT" << std::endl;
}

// Деструктор
AEROFLOT::~AEROFLOT() {
    std::cout << "Вызван деструктор для AEROFLOT" << std::endl;
    delete[] destination;
    delete[] aircraftType;
}

// Оператор присваивания
AEROFLOT& AEROFLOT::operator=(const AEROFLOT& other) {
    if (this != &other) {
        flightNumber = other.flightNumber;
        safeStringCopy(destination, other.destination);
        safeStringCopy(aircraftType, other.aircraftType);
    }
    return *this;
}

// Set-функции
void AEROFLOT::setDestination(const char* dest) {
    safeStringCopy(destination, dest);
}

void AEROFLOT::setAircraftType(const char* type) {
    safeStringCopy(aircraftType, type);
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const AEROFLOT& flight) {
    os << "Рейс №" << flight.flightNumber;
    if (flight.destination) {
        os << " в '" << flight.destination << "'";
    } else {
        os << " в 'неизвестно'";
    }
    if (flight.aircraftType) {
        os << " на самолете '" << flight.aircraftType << "'";
    } else {
        os << " на самолете 'неизвестно'";
    }
    return os;
}

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& is, AEROFLOT& flight) {
    char buffer[100];
    
    std::cout << "Введите пункт назначения: ";
    is >> buffer;
    flight.setDestination(buffer);
    
    std::cout << "Введите номер рейса: ";
    is >> flight.flightNumber;
    
    std::cout << "Введите тип самолета: ";
    is >> buffer;
    flight.setAircraftType(buffer);
    
    return is;
}

// Оператор сравнения для сортировки
bool AEROFLOT::operator<(const AEROFLOT& other) const {
    if (!destination || !other.destination) {
        return false;
    }
    return strcmp(destination, other.destination) < 0;
}
