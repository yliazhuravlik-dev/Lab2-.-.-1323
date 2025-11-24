#include <iostream>
#include "FlightManager.h"

int main() {
    std::cout << "=== Лабораторная работа №2 ===" << std::endl;
    std::cout << "=== Система управления рейсами Аэрофлота ===" << std::endl;
    
    FlightManager manager;
    manager.runMenu();
    
    return 0;
}
