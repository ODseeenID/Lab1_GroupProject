#include "shared_types.h"
#include <memory>
#include <chrono>

// Алгоритм Рабіна-Карпа 
std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data) {
    auto result = std::make_unique<Result>();
    result->count = 0;
    result->comparisons = 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    const std::string& txt = data->text;
    const std::string& pat = data->pattern;
    int n = txt.length();
    int m = pat.length();

    //перевірка на коректність вхідних даних 
    if (m == 0 || m > n) {
        auto end_time = std::chrono::high_resolution_clock::now();
        result->time_ms = std::chrono::duration<double, std::milli>(end_time - start_time).count();
        return result;
    }

    const int d = 256;
    const int q = 1000000007; 
    long long h = 1;

    // h = d^(m-1) % q
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    long long p = 0; //хеш підрядка 
    long long t = 0; // Хеш поточного вікна тексту

    // початкові хеші
    for (int i = 0; i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Зсув вікна тексту
    for (int i = 0; i <= n - m; i++) {
        result->comparisons++; 

        if (p == t) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                result->comparisons++; 
                if (txt[i + j] != pat[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                result->positions.push_back(i);
                result->count++;
            }
        }

        if (i < n - m) {
            t = (d * (t - txt[i] * h) + txt[i + m]) % q;
            if (t < 0) {
                t = (t + q);
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    result->time_ms = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    return result;
}