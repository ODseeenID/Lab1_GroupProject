#include "shared_types.h"
#include <memory>

// Заглушка для алгоритму Рабіна-Карпа
std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data) {
    return std::make_unique<Result>();
}