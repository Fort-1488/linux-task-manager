#include <iostream>
#include <iomanip>     // Подключаем магию форматирования вывода
#include <algorithm>
#include "ProcessReader.hpp"

int main() {
    ProcessReader reader;
    std::vector<ProcessInfo> list = reader.getAllProcesses();

    std::cout << "Найдено процессов: " << list.size() << "\n\n";

    // Рисуем красивую и ровную шапку таблицы
    // std::left заставляет текст прижиматься к левому краю
    // std::setw(X) задает фиксированную ширину столбца в X символов
    std::cout << std::left << std::setw(8)  << "PID" 
              << std::left << std::setw(35) << "NAME" 
              << std::left << std::setw(15) << "MEMORY (Kb)" << "\n";
              
    std::cout << "---------------------------------------------------------\n";

    // Выведем первые 20 процессов для теста
    size_t limit = std::min(list.size(), static_cast<size_t>(20));
    for (size_t i = 0; i < limit; ++i) {
        
        // Если имя слишком длинное (больше 32 символов), обрежем его, чтобы не ломать таблицу
        std::string displayName = list[i].name;
        if (displayName.length() > 32) {
            displayName = displayName.substr(0, 29) + "...";
        }

        // Выводим строки в строго фиксированные по ширине ячейки
        std::cout << std::left << std::setw(8)  << list[i].pid 
                  << std::left << std::setw(35) << displayName 
                  << std::left << std::setw(15) << list[i].memorykb << "\n";
    }

    return 0;
}
