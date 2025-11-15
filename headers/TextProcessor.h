#ifndef TEXTPROCESSOR_H  // Защита от повторного включения файла
#define TEXTPROCESSOR_H  // Определение макроса для этого файла

#include <fstream>       // Для работы с файловыми потоками (ifstream, ofstream)
#include <string>        // Для использования класса string

class TextProcessor {    // Объявление класса для обработки текста
public:
    // Статический метод для обращения порядка предложений в файле
    // static - метод можно вызывать без создания объекта класса
    // const char* filename - параметр: путь к файлу для обработки
    static void reverseSentences(const char* filename);
};

#endif // TEXTPROCESSOR_H // Конец защитного блока
