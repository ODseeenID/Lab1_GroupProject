#include "shared_types.h"
#include <memory>
#include <chrono>
#include <vector>

std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data) {
    auto result = std::make_unique<Result>();
    result->count = 0;
    result->comparisons = 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    const std::string& text = data->text;
    const std::string& pattern = data->pattern;

    if (pattern.empty() || text.empty() || pattern.length() > text.length()) {
        auto end_time = std::chrono::high_resolution_clock::now();
        result->time_ms = std::chrono::duration<double, std::milli>(end_time - start_time).count();
        return result;
    }

    //Обчислення префіксної функції
    std::vector<int> lps(pattern.length(), 0);
    int len = 0;
    int i = 1;

    while (i < pattern.length()) {
        result->comparisons++;
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }

    //Пошук підрядка (KMP)
    i = 0; // індекс для тексту
    int j = 0; // індекс для підрядка
    while (i < text.length()) {
        result->comparisons++;
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        if (j == pattern.length()) {
            // Знайдено входження
            result->positions.push_back(i - j);
            result->count++;
            j = lps[j - 1];
        }
        else if (i < text.length() && pattern[j] != text[i]) {
            result->comparisons++;
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    result->time_ms = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    return result;
}