// FlightManager.cpp
#include "FlightManager.h"
#include "TextProcessor.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdexcept>

// Конструктор
FlightManager::FlightManager() : flights(nullptr), capacity(0), size(0) {
    std::cout << "Вызван конструктор FlightManager" << std::endl;
}

// Деструктор
FlightManager::~FlightManager() {
    for (int i = 0; i < size; i++) {
        delete flights[i];
    }
    delete[] flights;
    std::cout << "Вызван деструктор FlightManager" << std::endl;
}

// Увеличение емкости массива
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

// Сортировка рейсов
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

// Добавление рейса
void FlightManager::addFlight() {
    if (size >= capacity) {
        resize();
    }
    
    flights[size] = new AEROFLOT();
    std::cin >> *flights[size];
    size++;
    
    sortFlights();
    std::cout << "Рейс добавлен и отсортирован!" << std::endl;
}

// Редактирование рейса
void FlightManager::editFlight() {
    if (size == 0) {
        std::cout << "Нет рейсов для редактирования!" << std::endl;
        return;
    }
    
    displayAllFlights();
    
    int index;
    std::cout << "Введите номер рейса для редактирования (1-" << size << "): ";
    std::cin >> index;
    
    if (index < 1 || index > size) {
        std::cout << "Неверный номер!" << std::endl;
        return;
    }
    
    std::cout << "Редактирование рейса:" << std::endl;
    std::cin >> *flights[index - 1];
    
    sortFlights();
    std::cout << "Рейс отредактирован и отсортирован!" << std::endl;
}

// Удаление рейса
void FlightManager::deleteFlight() {
    if (size == 0) {
        std::cout << "Нет рейсов для удаления!" << std::endl;
        return;
    }
    
    displayAllFlights();
    
    int index;
    std::cout << "Введите номер рейса для удаления (1-" << size << "): ";
    std::cin >> index;
    
    if (index < 1 || index > size) {
        std::cout << "Неверный номер!" << std::endl;
        return;
    }
    
    delete flights[index - 1];
    
    // Сдвигаем элементы
    for (int i = index - 1; i < size - 1; i++) {
        flights[i] = flights[i + 1];
    }
    size--;
    
    std::cout << "Рейс удален!" << std::endl;
}

// Показать все рейсы
void FlightManager::displayAllFlights() {
    if (size == 0) {
        std::cout << "Нет рейсов для отображения!" << std::endl;
        return;
    }
    
    std::cout << "\n=== Все рейсы ===" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << (i + 1) << ". " << *flights[i] << std::endl;
    }
}

// Поиск по типу самолета
void FlightManager::searchByAircraftType() {
    if (size == 0) {
        std::cout << "Нет рейсов для поиска!" << std::endl;
        return;
    }
    
    char type[50];
    std::cout << "Введите тип самолета для поиска: ";
    std::cin >> type;
    
    bool found = false;
    std::cout << "\n=== Рейсы с типом самолета '" << type << "' ===" << std::endl;
    
    for (int i = 0; i < size; i++) {
        const char* currentType = flights[i]->getAircraftType();
        if (currentType && strcmp(currentType, type) == 0) {
            std::cout << "- Пункт назначения: " << flights[i]->getDestination() 
                      << ", Номер рейса: " << flights[i]->getFlightNumber() << std::endl;
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "Рейсов с таким типом самолета не найдено!" << std::endl;
    }
}

// Обработка текстового файла
void FlightManager::processTextFile() {
    char filename[100];
    std::cout << "Введите имя файла для обработки: ";
    std::cin >> filename;
    
    try {
        TextProcessor::reverseSentences(filename);
    } catch (const std::exception& e) {
        std::cout << "Ошибка при обработке файла: " << e.what() << std::endl;
    }
}

// Главное меню
void FlightManager::runMenu() {
    int choice;
    
    do {
        std::cout << "\n=== Меню управления рейсами ===" << std::endl;
        std::cout << "1. Добавить рейс" << std::endl;
        std::cout << "2. Редактировать рейс" << std::endl;
        std::cout << "3. Удалить рейс" << std::endl;
        std::cout << "4. Показать все рейсы" << std::endl;
        std::cout << "5. Поиск по типу самолета" << std::endl;
        std::cout << "6. Обработать текст из файла" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите действие: ";
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
                    std::cout << "Выход из программы..." << std::endl;
                    break;
                default:
                    throw std::invalid_argument("Неверный выбор меню!");
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
        
    } while (choice != 0);
}
