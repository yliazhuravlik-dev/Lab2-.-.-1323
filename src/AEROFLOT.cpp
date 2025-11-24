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
    if (dest) {
        destination = new char[strlen(dest) + 1];
        strcpy(destination, dest);
    } else {
        destination = nullptr;
    }
    
    if (type) {
        aircraftType = new char[strlen(type) + 1];
        strcpy(aircraftType, type);
    } else {
        aircraftType = nullptr;
    }
    
    std::cout << "Вызван конструктор с параметрами для AEROFLOT" << std::endl;
}

// Конструктор копирования
AEROFLOT::AEROFLOT(const AEROFLOT& other) : flightNumber(other.flightNumber) {
    if (other.destination) {
        destination = new char[strlen(other.destination) + 1];
        strcpy(destination, other.destination);
    } else {
        destination = nullptr;
    }
    
    if (other.aircraftType) {
        aircraftType = new char[strlen(other.aircraftType) + 1];
        strcpy(aircraftType, other.aircraftType);
    } else {
        aircraftType = nullptr;
    }
    
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
        // Освобождаем старую память
        delete[] destination;
        delete[] aircraftType;
        
        // Копируем новые данные
        if (other.destination) {
            destination = new char[strlen(other.destination) + 1];
            strcpy(destination, other.destination);
        } else {
            destination = nullptr;
        }
        
        flightNumber = other.flightNumber;
        
        if (other.aircraftType) {
            aircraftType = new char[strlen(other.aircraftType) + 1];
            strcpy(aircraftType, other.aircraftType);
        } else {
            aircraftType = nullptr;
        }
    }
    return *this;
}

// Set-функции
void AEROFLOT::setDestination(const char* dest) {
    delete[] destination;
    if (dest) {
        destination = new char[strlen(dest) + 1];
        strcpy(destination, dest);
    } else {
        destination = nullptr;
    }
}

void AEROFLOT::setAircraftType(const char* type) {
    delete[] aircraftType;
    if (type) {
        aircraftType = new char[strlen(type) + 1];
        strcpy(aircraftType, type);
    } else {
        aircraftType = nullptr;
    }
}

// Перегрузка оператора вывода (РЕАЛИЗАЦИЯ)
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

// Перегрузка оператора ввода (РЕАЛИЗАЦИЯ)
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
