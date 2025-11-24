// TextProcessor.cpp
#include "TextProcessor.h"        // Подключаем заголовочный файл нашего класса
#include <iostream>               // Для ввода/вывода (std::cout, std::cin)
#include <fstream>                // Для работы с файлами (std::ifstream)
#include <string>                 // Для работы со строками std::string
#include <vector>                 // Для использования контейнера vector (хотя в требованиях сказано не использовать STL, но для простоты демонстрации)
#include <cstring>                // Для функций работы со строками в стиле C
#include <stdexcept>              // Для исключений (std::runtime_error)

// Реализация статического метода для обращения порядка предложений в файле
void TextProcessor::reverseSentences(const char* filename) {
    // Создаем объект для чтения файла
    std::ifstream file(filename);
    
    // Проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        // Если файл не открылся, бросаем исключение с сообщением об ошибке
        throw std::runtime_error("Не удалось открыть файл!");
    }
    
    // Создаем вектор для хранения предложений
    std::vector<std::string> sentences;
    // Строка для временного хранения каждой строки файла
    std::string line;
    // Строка для объединения всего текста из файла
    std::string text;
    
    // Читаем файл построчно до конца
    while (std::getline(file, line)) {
        // Добавляем каждую прочитанную строку в общий текст
        // + " " добавляем пробел для разделения строк
        text += line + " ";
    }
    // Закрываем файл после чтения
    file.close();
    
    // Временная строка для накопления текущего предложения
    std::string sentence;
    // Проходим по каждому символу в тексте
    for (char c : text) {
        // Добавляем текущий символ к предложению
        sentence += c;
        // Проверяем, является ли символ концом предложения (., !, ?)
        if (c == '.' || c == '!' || c == '?') {
            // Проверяем, что предложение не пустое
            if (!sentence.empty()) {
                // Добавляем завершенное предложение в вектор
                sentences.push_back(sentence);
                // Очищаем временную строку для следующего предложения
                sentence.clear();
            }
        }
    }
    
    // Добавляем последнее предложение, если оно не закончилось точкой
    // но содержит текст (на случай если файл не заканчивается точкой)
    if (!sentence.empty()) {
        sentences.push_back(sentence);
    }
    
    // Выводим заголовок для результатов
    std::cout << "\n=== Текст с предложениями в обратном порядке ===" << std::endl;
    
    // Выводим предложения в обратном порядке
    // Начинаем с последнего предложения (size-1) и идем до первого (0)
    for (int i = sentences.size() - 1; i >= 0; i--) {
        // Выводим каждое предложение на новой строке
        std::cout << sentences[i] << std::endl;
    }
}

// Дополнительный метод для обработки текста без использования STL (альтернативная версия)
void TextProcessor::processTextWithoutSTL(const char* filename) {
    // Открываем файл для чтения
    std::ifstream file(filename);
    
    // Проверка успешности открытия файла
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка открытия файла!");
    }
    
    // Определяем максимальное количество предложений
    const int MAX_SENTENCES = 100;
    // Массив для хранения предложений (вместо vector)
    char* sentences[MAX_SENTENCES];
    // Счетчик предложений
    int sentenceCount = 0;
    
    // Буфер для чтения текста
    char buffer[1000];
    // Общий текст файла
    char fullText[5000] = "";
    
    // Читаем файл построчно
    while (file.getline(buffer, sizeof(buffer))) {
        // Добавляем каждую строку в общий текст
        strcat(fullText, buffer);
        strcat(fullText, " "); // Добавляем пробел между строками
    }
    
    // Закрываем файл
    file.close();
    
    // Указатель для разбиения текста на предложения
    char* context = nullptr;
    // Разбиваем текст на предложения по разделителям .!?
    char* token = strtok_s(fullText, ".!?", &context);
    
    // Обрабатываем все предложения
    while (token != nullptr && sentenceCount < MAX_SENTENCES) {
        // Выделяем память для текущего предложения
        sentences[sentenceCount] = new char[strlen(token) + 2]; // +2 для точки и нуль-терминатора
        // Копируем предложение
        strcpy(sentences[sentenceCount], token);
        // Добавляем точку в конец
        strcat(sentences[sentenceCount], ".");
        // Увеличиваем счетчик
        sentenceCount++;
        // Получаем следующее предложение
        token = strtok_s(nullptr, ".!?", &context);
    }
    
    // Выводим предложения в обратном порядке
    std::cout << "\n=== Обработанный текст (без STL) ===" << std::endl;
    for (int i = sentenceCount - 1; i >= 0; i--) {
        std::cout << sentences[i] << std::endl;
        // Освобождаем память
        delete[] sentences[i];
    }
}
