// автотипизация c++11

#include <iostream>
#include <memory>
using namespace std;

void automatic()
{
    int answer1 = 2;   // явно int
    cout << answer1 << endl;
    
    auto answer2 = 3;  // не явно int
    cout << answer2 << endl;
}

// умные указатели С++11

void demonstrate_unique_ptr() {
    std::cout << "\n=== Начало демонстрации unique_ptr ===\n";
    
    // 2. Создание unique_ptr через make_unique
    auto res1 = make_unique<int>(2);
    
    // 3. Попытка копирования (ошибка компиляции)
    // std::unique_ptr<int> res2 = res1; // Ошибка! unique_ptr нельзя копировать
    
    // 4. Перемещение владения
    std::cout << "\nПеред перемещением:\n";
    std::unique_ptr<int> res2 = std::move(res1); // Владение переходит от res1 к res2
    
    std::cout << "После перемещения:\n";
    if (!res1) {
        std::cout << "res1 теперь пуст\n";
    }
    
    // 5. Освобождение ресурса вручную
    std::cout << "\nОсвобождаем res2 вручную:\n";
    res2.reset(); // Явное освобождение ресурса
    if (!res2) {
        std::cout << "res2 теперь пуст\n";
    }
    
    // 6. Создание нового ресурса в существующий unique_ptr
    std::cout << "\nСоздаем новый ресурс в res2:\n";
    res2 = std::make_unique<int>(3);
    
    std::cout << "\n=== Конец области видимости функции ===\n";
    // Все unique_ptr автоматически освободят свои ресурсы при выходе из области видимости
    
}

// лямбда функция

void lyambda()
{   // Захват переменных по значению ([=]) и по ссылке ([&])
    int x = 10;
    auto increment = [&x]() {x++;}; // Захват по ссылке
    increment();
    std::cout << "x после инкремента: " << x << "\n";
}

// вариативный шаблон

template<typename... Args> // Определяем шаблон с переменным числом аргументов
void print(Args... args) { 
    ((std::cout << args << " "), ...); // Используем fold expression, чтобы вывести все аргументы через пробел
    std::cout << std::endl;
}

int main() {
    automatic();
    demonstrate_unique_ptr();
    lyambda();
    print(1, 2.5, "Hello", 'A');

    return 0;
}
