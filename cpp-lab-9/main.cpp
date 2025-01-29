#include <iostream>

// template<typename Type>
// Type sum(const Type* array, size_t len)
// {
//     Type answer = 0;

//     for (size_t i = 0; i < len; ++i) 
//     {
//         answer += array[i];
//     }

//     return answer;
// }

// std::string sum(const std::string* array, size_t len)
// {
//     std::string answer = "";

//     for (size_t i = 0; i < len; ++i) 
//     {
//         answer += array[i];
//     }

//     return answer;
// }


template<typename Type>
std::pair<Type, Type> min_max(const Type* array, size_t len)
{
    Type min = array[0];
    Type max = array[0];

    for (size_t i = 0; i < len; ++i) 
    {
        min > array[i] ? min = array[i] : min = min;
        max < array[i] ? max = array[i] : max = max;
    }

    return std::pair<Type, Type>(min, max);
}

int main()
{
    int arr[4] = {0, 1, 2, 3};
    float arr_[3] = {0.1, 0.345, 123.001};
    double _arr[3] = {0.123, 123.1, 4};
    // char _arr_[2] = {'C', 'B'};
    // std::string _arr[2] = {"123", "21"};

    auto [s, d] = min_max(arr, 4);
    auto [s_, d_] = min_max(arr_, 3);
    auto [_s, _d] = min_max(_arr, 3);

    std::cout <<  s << ' ' << d << '\n';
    std::cout << s_ << ' ' << d_ << '\n';
    std::cout << _s << ' ' << _d << '\n';

    return 0;
}