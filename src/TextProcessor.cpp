#include "TextProcessor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>

// Безопасная версия с использованием string вместо небезопасных функций
void TextProcessor::reverseSentences(const char* filename) {
    // Создаем объект для чтения файла
    std::ifstream file(filename);
    
    // Проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл!");
    }
    
    // Вектор для хранения предложений
    std::vector<std::string> sentences;
    std::string line;
    std::string fullText;
    
    // Читаем файл построчно
    while (std::getline(file, line)) {
        fullText += line + " ";  // Используем безопасный оператор += для string
    }
    file.close();
    
    std::string currentSentence;
    
    // Обрабатываем каждый символ текста
    for (size_t i = 0; i < fullText.length(); i++) {
        char c = fullText[i];
        currentSentence += c;
        
        // Проверяем конец предложения
        if (c == '.' || c == '!' || c == '?') {
            if (!currentSentence.empty()) {
                sentences.push_back(currentSentence);
                currentSentence.clear();
            }
        }
    }
    
    // Добавляем последнее предложение, если оно есть
    if (!currentSentence.empty()) {
        sentences.push_back(currentSentence);
    }
    
    // Выводим результат
    std::cout << "\n=== Текст с предложениями в обратном порядке ===" << std::endl;
    for (int i = sentences.size() - 1; i >= 0; i--) {
        std::cout << sentences[i] << std::endl;
    }
}

// Альтернативная версия без STL с безопасными функциями
void TextProcessor::processTextWithoutSTL(const char* filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка открытия файла!");
    }
    
    const int MAX_SENTENCES = 100;
    const int BUFFER_SIZE = 1000;
    char* sentences[MAX_SENTENCES];
    int sentenceCount = 0;
    
    // Используем безопасное чтение
    char buffer[BUFFER_SIZE];
    std::string fullText;
    
    // Безопасное чтение файла
    while (file.getline(buffer, BUFFER_SIZE)) {
        fullText += buffer;
        fullText += " ";
    }
    file.close();
    
    // Обрабатываем предложения безопасно
    size_t start = 0;
    size_t end = 0;
    
    while (end < fullText.length() && sentenceCount < MAX_SENTENCES) {
        // Ищем конец предложения
        end = fullText.find_first_of(".!?", start);
        if (end == std::string::npos) {
            end = fullText.length();
        } else {
            end++; // Включаем конечный символ
        }
        
        // Извлекаем предложение
        std::string sentence = fullText.substr(start, end - start);
        if (!sentence.empty()) {
            // Безопасное копирование с выделением точного количества памяти
            sentences[sentenceCount] = new char[sentence.length() + 1];
            // Используем безопасное копирование
            #ifdef _MSC_VER
            strcpy_s(sentences[sentenceCount], sentence.length() + 1, sentence.c_str());
            #else
            strncpy(sentences[sentenceCount], sentence.c_str(), sentence.length());
            sentences[sentenceCount][sentence.length()] = '\0';
            #endif
            sentenceCount++;
        }
        
        start = end;
        if (start >= fullText.length()) break;
    }
    
    // Выводим результат
    std::cout << "\n=== Обработанный текст ===" << std::endl;
    for (int i = sentenceCount - 1; i >= 0; i--) {
        std::cout << sentences[i] << std::endl;
        delete[] sentences[i];
    }
}
