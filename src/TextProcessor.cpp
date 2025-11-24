#define _CRT_SECURE_NO_WARNINGS
#include "TextProcessor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>

void TextProcessor::reverseSentences(const char* filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file!");
    }
    
    std::vector<std::string> sentences;
    std::string line;
    std::string fullText;
    
    while (std::getline(file, line)) {
        fullText += line + " ";
    }
    file.close();
    
    std::string currentSentence;
    
    for (size_t i = 0; i < fullText.length(); i++) {
        char c = fullText[i];
        currentSentence += c;
        
        if (c == '.' || c == '!' || c == '?') {
            if (!currentSentence.empty()) {
                sentences.push_back(currentSentence);
                currentSentence.clear();
            }
        }
    }
    
    if (!currentSentence.empty()) {
        sentences.push_back(currentSentence);
    }
    
    std::cout << "\n=== Text with sentences in reverse order ===" << std::endl;
    for (int i = (int)sentences.size() - 1; i >= 0; i--) {
        std::cout << sentences[i] << std::endl;
    }
}
