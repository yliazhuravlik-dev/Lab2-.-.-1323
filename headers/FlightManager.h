#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H

#include "AEROFLOT.h"

class FlightManager {
private:
    AEROFLOT** flights;
    int capacity;
    int size;

    void resize();
    void sortFlights();

public:
    FlightManager();
    ~FlightManager();
    
    void addFlight();
    void editFlight();
    void deleteFlight();
    void displayAllFlights();
    void searchByAircraftType();
    void processTextFile();
    void runMenu();
};

#endif
