// TextProcessor.h
#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

class TextProcessor {
public:
    // Статический метод для обращения порядка предложений в файле
    static void reverseSentences(const char* filename);
    
    // Альтернативный метод без использования STL контейнеров
    static void processTextWithoutSTL(const char* filename);
};

#endif
