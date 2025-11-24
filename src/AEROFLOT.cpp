// AEROFLOT.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "AEROFLOT.h"
#include <iostream>
#include <cstring>

// Safe string copy function
void safeStringCopy(char*& dest, const char* src) {
    if (dest) {
        delete[] dest;
        dest = nullptr;
    }
    if (src) {
        dest = new char[strlen(src) + 1];
        strcpy(dest, src);
    }
}

// Default constructor
AEROFLOT::AEROFLOT() : destination(nullptr), flightNumber(0), aircraftType(nullptr) {
    std::cout << "Default constructor called for AEROFLOT" << std::endl;
}

// Parameterized constructor
AEROFLOT::AEROFLOT(const char* dest, int number, const char* type) : flightNumber(number) {
    safeStringCopy(destination, dest);
    safeStringCopy(aircraftType, type);
    std::cout << "Parameterized constructor called for AEROFLOT" << std::endl;
}

// Copy constructor
AEROFLOT::AEROFLOT(const AEROFLOT& other) : flightNumber(other.flightNumber) {
    safeStringCopy(destination, other.destination);
    safeStringCopy(aircraftType, other.aircraftType);
    std::cout << "Copy constructor called for AEROFLOT" << std::endl;
}

// Destructor
AEROFLOT::~AEROFLOT() {
    std::cout << "Destructor called for AEROFLOT" << std::endl;
    delete[] destination;
    delete[] aircraftType;
}

// Assignment operator
AEROFLOT& AEROFLOT::operator=(const AEROFLOT& other) {
    if (this != &other) {
        flightNumber = other.flightNumber;
        safeStringCopy(destination, other.destination);
        safeStringCopy(aircraftType, other.aircraftType);
    }
    return *this;
}

// Set functions
void AEROFLOT::setDestination(const char* dest) {
    safeStringCopy(destination, dest);
}

void AEROFLOT::setAircraftType(const char* type) {
    safeStringCopy(aircraftType, type);
}

// Output operator overload
std::ostream& operator<<(std::ostream& os, const AEROFLOT& flight) {
    os << "Flight No" << flight.flightNumber;
    if (flight.destination) {
        os << " to '" << flight.destination << "'";
    } else {
        os << " to 'unknown'";
    }
    if (flight.aircraftType) {
        os << " on aircraft '" << flight.aircraftType << "'";
    } else {
        os << " on aircraft 'unknown'";
    }
    return os;
}

// Input operator overload
std::istream& operator>>(std::istream& is, AEROFLOT& flight) {
    char buffer[100];
    
    std::cout << "Enter destination: ";
    is >> buffer;
    flight.setDestination(buffer);
    
    std::cout << "Enter flight number: ";
    is >> flight.flightNumber;
    
    std::cout << "Enter aircraft type: ";
    is >> buffer;
    flight.setAircraftType(buffer);
    
    return is;
}

// Comparison operator for sorting
bool AEROFLOT::operator<(const AEROFLOT& other) const {
    if (!destination || !other.destination) {
        return false;
    }
    return strcmp(destination, other.destination) < 0;
}
