#include <iostream>
#include <memory>
#include "shared_types.h"

std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data);
std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data);

int main() {
    std::cout << "Lab 1 Variant 9\n\n";

    auto data = std::make_shared<const InputData>(InputData{
        "ligma w bread ball key fox mix mogged tree eye triangle",
        "fox"
        });

    std::cout << "Text: " << data->text << "\n";
    std::cout << "Pattern: " << data->pattern << "\n\n";

    // робота алгоритму А
    auto resultA = calculateA(data);

    auto& [positionsA, countA, comparisonsA, timeA] = *resultA;

    std::cout << "Student A (Rabin-Karp)\n";
    std::cout << "Matches found: " << countA << "\n";
    std::cout << "Positions: ";
    for (int pos : positionsA) {
        std::cout << pos << " ";
    }
    std::cout << "\nTotal comparisons: " << comparisonsA << "\n";
    std::cout << "Execution time: " << timeA << " ms\n\n";

    // робота алгоритму B (KMP)
    auto resultB = calculateB(data);
    auto& [positionsB, countB, comparisonsB, timeB] = *resultB;

    std::cout << "Student B (KMP)\n";
    std::cout << "Matches found: " << countB << "\n";
    std::cout << "Positions: ";
    for (int pos : positionsB) {
        std::cout << pos << " ";
    }
    std::cout << "\nTotal comparisons: " << comparisonsB << "\n";
    std::cout << "Execution time: " << timeB << " ms\n\n";

    return 0;
}