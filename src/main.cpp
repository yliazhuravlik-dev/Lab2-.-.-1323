#include <iostream>
#include "FlightManager.h"

int main() {
    std::cout << "=== Laboratory Work #2 ===" << std::endl;
    std::cout << "=== AEROFLOT Flight Management System ===" << std::endl;
    
    FlightManager manager;
    manager.runMenu();
    
    return 0;
}
