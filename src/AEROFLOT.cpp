// AEROFLOT.cpp
#include "AEROFLOT.h"
#include <iostream>
#include <cstring>

// Конструктор по умолчанию
AEROFLOT::AEROFLOT() : destination(nullptr), flightNumber(0), aircraftType(nullptr) {
    std::cout << "Вызван конструктор по умолчанию для AEROFLOT" << std::endl;
}

// Конструктор с параметрами
AEROFLOT::AEROFLOT(const char* dest, int number, const char* type) : flightNumber(number) {
    destination = new char[strlen(dest) + 1];
    strcpy(destination, dest);
    
    aircraftType = new char[strlen(type) + 1];
    strcpy(aircraftType, type);
    
    std::cout << "Вызван конструктор с параметрами для AEROFLOT: " << destination << std::endl;
}

// Конструктор копирования
AEROFLOT::AEROFLOT(const AEROFLOT& other) : flightNumber(other.flightNumber) {
    destination = new char[strlen(other.destination) + 1];
    strcpy(destination, other.destination);
    
    aircraftType = new char[strlen(other.aircraftType) + 1];
    strcpy(aircraftType, other.aircraftType);
    
    std::cout << "Вызван конструктор копирования для AEROFLOT: " << destination << std::endl;
}

// Деструктор
AEROFLOT::~AEROFLOT() {
    std::cout << "Вызван деструктор для AEROFLOT: ";
    if (destination) {
        std::cout << destination;
        delete[] destination;
        destination = nullptr;
    }
    if (aircraftType) {
        delete[] aircraftType;
        aircraftType = nullptr;
    }
    std::cout << std::endl;
}

// Оператор присваивания
AEROFLOT& AEROFLOT::operator=(const AEROFLOT& other) {
    if (this != &other) {
        // Освобождаем старую память
        delete[] destination;
        delete[] aircraftType;
        
        // Копируем новые данные
        destination = new char[strlen(other.destination) + 1];
        strcpy(destination, other.destination);
        
        flightNumber = other.flightNumber;
        
        aircraftType = new char[strlen(other.aircraftType) + 1];
        strcpy(aircraftType, other.aircraftType);
    }
    return *this;
}

// Set-функции
void AEROFLOT::setDestination(const char* dest) {
    delete[] destination;
    destination = new char[strlen(dest) + 1];
    strcpy(destination, dest);
}

void AEROFLOT::setAircraftType(const char* type) {
    delete[] aircraftType;
    aircraftType = new char[strlen(type) + 1];
    strcpy(aircraftType, type);
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const AEROFLOT& flight) {
    os << "Рейс №" << flight.flightNumber 
       << " в '" << (flight.destination ? flight.destination : "null") 
       << "' на самолете '" << (flight.aircraftType ? flight.aircraftType : "null") << "'";
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
    if (destination == nullptr || other.destination == nullptr) {
        return false;
    }
    return strcmp(destination, other.destination) < 0;
}
