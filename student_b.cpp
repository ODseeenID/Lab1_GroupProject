#include "shared_types.h"
#include <memory>

// Заглушка для алгоритму КМП
std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data) {
    return std::make_unique<Result>();
}