// Реализация дека(двухсторонняя очередь)
#include <iostream>

using namespace std;

template<class Type>
class Deque {
    Type* data;                                             // Массив
    size_t size;                                            // Размер массива

    public:
        Deque() {data = nullptr; size = 0;}                 // конуструктор
        ~Deque(){delete[] data;}                            // деструктор

                                                            // добавление элемента в начало очереди
        void front_push(Type type){                    
            size += 1;
            Type* tmp = new Type [size];

            if (data){
                for (size_t i = 0; i < size-1; ++i){
                    tmp[i+1] = data[i];
                }
            }
 
            tmp[0] = type;
            if (data) delete[] data;
            data = tmp;
        }
                                                            // добавление клиента в конец очереди
        void back_push(Type type) {                   
            size += 1;
            Type* tmp = new Type [size];
            
            if (data) {
                for (size_t i = 0; i < size-1; ++i){
                    tmp[i] = data[i];
                }
            }
            tmp[size-1] = type;

            if (data) delete[] data;
            data = tmp;
        }
                                                            // удаление элемента из начала очереди
        Type front_pop() 
        {
            if (size == 0) throw runtime_error("Deque is empty!");

            Type type = data[0]; // Запоминаем первый элемент
            size -= 1;

            if (size == 0) 
            {
                delete[] data;
                data = nullptr;
                return type;
            }

            Type* tmp = new Type[size];
            for (size_t i = 0; i < size; ++i) {
                tmp[i] = data[i + 1];
            }

            delete[] data;
            data = tmp;
            return type;
        }
                                                            // удаление элемента из конца очереди
        Type back_pop() 
        {
            if (size == 0) throw runtime_error("Deque is empty!");

            Type type = data[size - 1];
            size -= 1;
            Type* tmp = new Type[size];

            for (size_t i = 0; i < size; ++i) {
                tmp[i] = data[i];
            }

            delete[] data;
            data = tmp;
            return type;
        }
                                                            // возврат кол-ва элементов в очереди
        size_t size_()
        {
            return size;
        }

        template <class U>
        friend std::ostream& operator<<(std::ostream& os, const Deque<U>& deque);
};

template <class U>
std::ostream& operator<<(std::ostream& os, const Deque<U>& deque) 
{
    if (deque.size == 0) 
        os << "Deque is empty!";
    else
    {
        os << '[';
        for (size_t i = 0; i < deque.size; ++i) 
        {
            os << deque.data[i];
            if (i < deque.size - 1)
                os << ", ";
            else
                os << ']';
        }
    }
    return os;
}


int main() 
{
    Deque<std::string>array;
    array.back_push("Slava");
    cout << array << endl;
    array.front_push("Egor");
    cout << array << endl;
    array.back_push("Dima");
    cout << array << endl;
    array.front_pop();
    cout << array << endl;
    cout << array.size_() << endl; 

    return 0;
}
