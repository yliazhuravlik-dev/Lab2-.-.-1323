// FlightManager.cpp
#include "FlightManager.h"
#include <iostream>
#include <cstring>
#include <algorithm>

// Конструктор класса FlightManager
FlightManager::FlightManager() : flights(nullptr), capacity(0), size(0) {
    // Инициализация указателя на массив рейсов как nullptr
    // capacity (емкость) = 0 - массив еще не выделен
    // size (размер) = 0 - нет элементов в массиве
    std::cout << "Вызван конструктор FlightManager" << std::endl;
}

// Деструктор класса FlightManager
FlightManager::~FlightManager() {
    // Цикл для удаления всех объектов AEROFLOT в массиве
    for (int i = 0; i < size; i++) {
        delete flights[i];  // Освобождение памяти для каждого рейса
    }
    delete[] flights;  // Освобождение памяти для массива указателей
    std::cout << "Вызван деструктор FlightManager" << std::endl;
}

// Метод для увеличения размера динамического массива
void FlightManager::resize() {
    // Вычисление новой емкости: если массив пустой - 2, иначе удваиваем
    int newCapacity = (capacity == 0) ? 2 : capacity * 2;
    
    // Выделение памяти для нового массива указателей
    AEROFLOT** newFlights = new AEROFLOT*[newCapacity];
    
    // Копирование существующих указателей в новый массив
    for (int i = 0; i < size; i++) {
        newFlights[i] = flights[i];  // Переносим указатели
    }
    
    // Освобождение памяти старого массива
    delete[] flights;
    
    // Обновление указателя на новый массив
    flights = newFlights;
    
    // Обновление емкости
    capacity = newCapacity;
}

// Метод для сортировки рейсов по названию пункта назначения
void FlightManager::sortFlights() {
    // Реализация пузырьковой сортировки
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Сравнение двух соседних рейсов с помощью перегруженного оператора <
            if (!(*flights[j] < *flights[j + 1])) {
                // Если текущий рейс "больше" следующего, меняем их местами
                std::swap(flights[j], flights[j + 1]);
            }
        }
    }
}

// Метод для добавления нового рейса
void FlightManager::addFlight() {
    // Проверка необходимости увеличения размера массива
    if (size >= capacity) {
        resize();  // Увеличиваем массив если нужно
    }
    
    // Создание нового объекта AEROFLOT в динамической памяти
    flights[size] = new AEROFLOT();
    
    // Ввод данных рейса с помощью перегруженного оператора >>
    std::cin >> *flights[size];
    
    // Увеличение счетчика элементов
    size++;
    
    // Сортировка массива после добавления нового элемента
    sortFlights();
    
    std::cout << "Рейс добавлен и отсортирован!" << std::endl;
}

// Метод для редактирования существующего рейса
void FlightManager::editFlight() {
    // Проверка наличия рейсов для редактирования
    if (size == 0) {
        std::cout << "Нет рейсов для редактирования!" << std::endl;
        return;  // Выход если массив пустой
    }
    
    // Отображение всех рейсов для выбора
    displayAllFlights();
    
    int index;
    // Запрос номера рейса для редактирования
    std::cout << "Введите номер рейса для редактирования (1-" << size << "): ";
    std::cin >> index;
    
    // Проверка корректности введенного индекса
    if (index < 1 || index > size) {
        std::cout << "Неверный номер!" << std::endl;
        return;  // Выход при неверном индексе
    }
    
    // Редактирование выбранного рейса
    std::cout << "Редактирование рейса:" << std::endl;
    std::cin >> *flights[index - 1];  // index-1 потому что пользователь видит с 1, а массив с 0
    
    // Повторная сортировка после изменения данных
    sortFlights();
    std::cout << "Рейс отредактирован и отсортирован!" << std::endl;
}

// Метод для удаления рейса
void FlightManager::deleteFlight() {
    // Проверка наличия рейсов для удаления
    if (size == 0) {
        std::cout << "Нет рейсов для удаления!" << std::endl;
        return;
    }
    
    // Отображение всех рейсов для выбора
    displayAllFlights();
    
    int index;
    // Запрос номера рейса для удаления
    std::cout << "Введите номер рейса для удаления (1-" << size << "): ";
    std::cin >> index;
    
    // Проверка корректности введенного индекса
    if (index < 1 || index > size) {
        std::cout << "Неверный номер!" << std::endl;
        return;
    }
    
    // Удаление объекта рейса из памяти
    delete flights[index - 1];
    
    // Сдвиг элементов массива для заполнения пустого места
    for (int i = index - 1; i < size - 1; i++) {
        flights[i] = flights[i + 1];  // Перемещаем указатели
    }
    
    // Уменьшение счетчика элементов
    size--;
    
    std::cout << "Рейс удален!" << std::endl;
}

// Метод для отображения всех рейсов
void FlightManager::displayAllFlights() {
    // Проверка наличия рейсов
    if (size == 0) {
        std::cout << "Нет рейсов для отображения!" << std::endl;
        return;
    }
    
    // Вывод заголовка
    std::cout << "\n=== Все рейсы ===" << std::endl;
    
    // Цикл по всем рейсам
    for (int i = 0; i < size; i++) {
        // Вывод номера и информации о рейсе с помощью перегруженного оператора <<
        std::cout << (i + 1) << ". " << *flights[i] << std::endl;
    }
}

// Метод для поиска рейсов по типу самолета
void FlightManager::searchByAircraftType() {
    // Проверка наличия рейсов для поиска
    if (size == 0) {
        std::cout << "Нет рейсов для поиска!" << std::endl;
        return;
    }
    
    char type[50];
    // Запрос типа самолета для поиска
    std::cout << "Введите тип самолета для поиска: ";
    std::cin >> type;
    
    bool found = false;  // Флаг для отслеживания найденных рейсов
    
    // Вывод заголовка результатов поиска
    std::cout << "\n=== Рейсы с типом самолета '" << type << "' ===" << std::endl;
    
    // Цикл по всем рейсам для поиска совпадений
    for (int i = 0; i < size; i++) {
        // Сравнение типа самолета текущего рейса с искомым
        if (strcmp(flights[i]->getAircraftType(), type) == 0) {
            // Вывод информации о найденном рейсе
            std::cout << "- Пункт назначения: " << flights[i]->getDestination() 
                      << ", Номер рейса: " << flights[i]->getFlightNumber() << std::endl;
            found = true;  // Устанавливаем флаг что найден хотя бы один рейс
        }
    }
    
    // Сообщение если рейсы не найдены
    if (!found) {
        std::cout << "Рейсов с таким типом самолета не найдено!" << std::endl;
    }
}

// Метод для запуска основного меню программы
void FlightManager::runMenu() {
    int choice;  // Переменная для хранения выбора пользователя
    
    // Основной цикл меню
    do {
        // Отображение меню
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
        
        // Обработка выбора пользователя с обработкой исключений
        try {
            switch (choice) {
                case 1:
                    addFlight();      // Добавление рейса
                    break;
                case 2:
                    editFlight();     // Редактирование рейса
                    break;
                case 3:
                    deleteFlight();   // Удаление рейса
                    break;
                case 4:
                    displayAllFlights();  // Показать все рейсы
                    break;
                case 5:
                    searchByAircraftType();  // Поиск по типу самолета
                    break;
                case 6:
                    // Вызов функции обработки текстового файла
                    processTextFile();
                    break;
                case 0:
                    std::cout << "Выход из программы..." << std::endl;
                    break;
                default:
                    // Генерация исключения при неверном выборе
                    throw std::invalid_argument("Неверный выбор меню!");
            }
        } catch (const std::exception& e) {
            // Обработка исключений
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
        
    } while (choice != 0);  // Цикл продолжается пока не выбран выход
}
