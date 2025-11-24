// FlightManager.cpp
#include "FlightManager.h"
#include "TextProcessor.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdexcept>

// Constructor
FlightManager::FlightManager() : flights(nullptr), capacity(0), size(0) {
    std::cout << "FlightManager constructor called" << std::endl;
}

// Destructor
FlightManager::~FlightManager() {
    for (int i = 0; i < size; i++) {
        delete flights[i];
    }
    delete[] flights;
    std::cout << "FlightManager destructor called" << std::endl;
}

// Increase array capacity
void FlightManager::resize() {
    int newCapacity = (capacity == 0) ? 2 : capacity * 2;
    AEROFLOT** newFlights = new AEROFLOT*[newCapacity];
    
    for (int i = 0; i < size; i++) {
        newFlights[i] = flights[i];
    }
    
    delete[] flights;
    flights = newFlights;
    capacity = newCapacity;
}

// Sort flights by destination
void FlightManager::sortFlights() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (!(*flights[j] < *flights[j + 1])) {
                AEROFLOT* temp = flights[j];
                flights[j] = flights[j + 1];
                flights[j + 1] = temp;
            }
        }
    }
}

// Add new flight
void FlightManager::addFlight() {
    if (size >= capacity) {
        resize();
    }
    
    flights[size] = new AEROFLOT();
    std::cout << "=== Adding New Flight ===" << std::endl;
    std::cin >> *flights[size];
    size++;
    
    sortFlights();
    std::cout << "Flight added and sorted!" << std::endl;
}

// Edit existing flight
void FlightManager::editFlight() {
    if (size == 0) {
        std::cout << "No flights available for editing!" << std::endl;
        return;
    }
    
    displayAllFlights();
    
    int index;
    std::cout << "Enter flight number to edit (1-" << size << "): ";
    std::cin >> index;
    
    if (index < 1 || index > size) {
        std::cout << "Invalid number!" << std::endl;
        return;
    }
    
    std::cout << "=== Editing Flight ===" << std::endl;
    std::cin >> *flights[index - 1];
    
    sortFlights();
    std::cout << "Flight edited and sorted!" << std::endl;
}

// Delete flight
void FlightManager::deleteFlight() {
    if (size == 0) {
        std::cout << "No flights available for deletion!" << std::endl;
        return;
    }
    
    displayAllFlights();
    
    int index;
    std::cout << "Enter flight number to delete (1-" << size << "): ";
    std::cin >> index;
    
    if (index < 1 || index > size) {
        std::cout << "Invalid number!" << std::endl;
        return;
    }
    
    delete flights[index - 1];
    
    // Shift elements
    for (int i = index - 1; i < size - 1; i++) {
        flights[i] = flights[i + 1];
    }
    size--;
    
    std::cout << "Flight deleted!" << std::endl;
}

// Display all flights
void FlightManager::displayAllFlights() {
    if (size == 0) {
        std::cout << "No flights to display!" << std::endl;
        return;
    }
    
    std::cout << "\n=== All Flights ===" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << (i + 1) << ". " << *flights[i] << std::endl;
    }
}

// Search by aircraft type
void FlightManager::searchByAircraftType() {
    if (size == 0) {
        std::cout << "No flights available for search!" << std::endl;
        return;
    }
    
    char type[50];
    std::cout << "Enter aircraft type to search: ";
    std::cin >> type;
    
    bool found = false;
    std::cout << "\n=== Flights with aircraft type '" << type << "' ===" << std::endl;
    
    for (int i = 0; i < size; i++) {
        const char* currentType = flights[i]->getAircraftType();
        if (currentType && strcmp(currentType, type) == 0) {
            std::cout << "- Destination: " << flights[i]->getDestination() 
                      << ", Flight Number: " << flights[i]->getFlightNumber() << std::endl;
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "No flights found with this aircraft type!" << std::endl;
    }
}

// Process text file
void FlightManager::processTextFile() {
    char filename[100];
    std::cout << "Enter filename to process: ";
    std::cin >> filename;
    
    try {
        TextProcessor::reverseSentences(filename);
    } catch (const std::exception& e) {
        std::cout << "Error processing file: " << e.what() << std::endl;
    }
}

// Main menu
void FlightManager::runMenu() {
    int choice;
    
    do {
        std::cout << "\n=== Flight Management System ===" << std::endl;
        std::cout << "1. Add Flight" << std::endl;
        std::cout << "2. Edit Flight" << std::endl;
        std::cout << "3. Delete Flight" << std::endl;
        std::cout << "4. Display All Flights" << std::endl;
        std::cout << "5. Search by Aircraft Type" << std::endl;
        std::cout << "6. Process Text File" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose action: ";
        std::cin >> choice;
        
        try {
            switch (choice) {
                case 1:
                    addFlight();
                    break;
                case 2:
                    editFlight();
                    break;
                case 3:
                    deleteFlight();
                    break;
                case 4:
                    displayAllFlights();
                    break;
                case 5:
                    searchByAircraftType();
                    break;
                case 6:
                    processTextFile();
                    break;
                case 0:
                    std::cout << "Exiting program..." << std::endl;
                    break;
                default:
                    throw std::invalid_argument("Invalid menu choice!");
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
    } while (choice != 0);
}
