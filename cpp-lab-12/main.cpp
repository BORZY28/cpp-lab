#include <iostream>
#include <list>
#include <string>
#include <ctime>

// ============================
// Структура события
// ============================
struct Event {
    std::string name;
    std::time_t timestamp;  // UNIX-время
};

// ============================
// Пользовательский итератор
// ============================
class IntervalIterator {
public:
    using Iterator = std::list<Event>::iterator;

    IntervalIterator(Iterator current, Iterator end, std::time_t from, std::time_t to)
        : it(current), end_it(end), from_time(from), to_time(to) {
        skipInvalid();
    }

    Event& operator*() { return *it; }
    IntervalIterator& operator++() {
        ++it;
        skipInvalid();
        return *this;
    }

    bool operator!=(const IntervalIterator& other) const {
        return it != other.it;
    }

private:
    Iterator it, end_it;
    std::time_t from_time, to_time;

    void skipInvalid() {
        while (it != end_it && (it->timestamp < from_time || it->timestamp > to_time)) {
            ++it;
        }
    }
};

// ============================
// Диапазон для range-based for
// ============================
class IntervalRange {
public:
    IntervalRange(std::list<Event>& events, std::time_t from, std::time_t to)
        : events(events), from_time(from), to_time(to) {}

    IntervalIterator begin() { return IntervalIterator(events.begin(), events.end(), from_time, to_time); }
    IntervalIterator end() { return IntervalIterator(events.end(), events.end(), from_time, to_time); }

private:
    std::list<Event>& events;
    std::time_t from_time, to_time;
};

// ============================
// Утилита для вывода времени
// ============================
std::string timeToStr(std::time_t t) {
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
    return buf;
}

// ============================
// Демонстрация работы
// ============================
int main() {
    std::list<Event> events = {
        {"Событие A", 1672531200},  // 2023-01-01
        {"Событие B", 1673481600},  // 2023-01-12
        {"Событие C", 1674000000},  // 2023-01-18
        {"Событие D", 1677628800}   // 2023-03-01
    };

    // Интервал: 2023-01-10 — 2023-01-31
    std::time_t from = 1673308800;  // 2023-01-10
    std::time_t to   = 1675123200;  // 2023-01-31

    IntervalRange filtered(events, from, to);

    std::cout << "События в интервале:\n";
    for (const auto& e : filtered) {
        std::cout << "- " << e.name << " (" << timeToStr(e.timestamp) << ")\n";
    }

    return 0;
}