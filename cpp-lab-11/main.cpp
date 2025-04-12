// g++ main.cpp -std=c++17 -o main - !!!компиляция!!! не забыть, инчане не скомпилится
#include <iostream>
#include <vector>
#include <deque>
#include <iterator> // для копирования

int main() {
    // Создаем и заполняем вектор
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Копируем данные из vector в deque
    std::deque<int> deq;
    std::copy(vec.begin(), vec.end(), std::back_inserter(deq));

    // Вывод содержимого deque
    std::cout << "Deque после копирования из vector: ";
    for (int val : deq)
        std::cout << val << " ";
    std::cout << std::endl;

    // Копируем данные обратно из deque в vector
    std::vector<int> vec2;
    std::copy(deq.begin(), deq.end(), std::back_inserter(vec2));

    // Вывод нового вектора
    std::cout << "Vector после копирования из deque: ";
    for (int val : vec2)
        std::cout << val << " ";
    std::cout << std::endl;
 
    return 0;
}