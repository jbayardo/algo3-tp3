#ifndef STATISTICS_H
#include <list>
#include <map>
#include <chrono>
#include <fstream>
#include <string>

#ifdef _NOEXCEPT
#define noexcept _NOEXCEPT
#endif

class Value;
class Counter;
class Timer;

typedef std::size_t Number;
typedef long Time;

/***********************************************************************************************************************
 * Statistics
 **********************************************************************************************************************/
class Statistics {
    friend class Value;
    friend class Counter;
    friend class Timer;
public:
    static Statistics &getInstance() {
        static Statistics instance;
        return instance;
    }

    void dump(std::string file) const {
        std::fstream output(file, std::ios_base::out);

        for (auto &keypair : this->values) {
            output << keypair.first << "\t\t\t" << keypair.second << std::endl;
        }

        for (auto &keypair : this->series) {
            output << keypair.first << "\t\t\t";

            for (auto number = keypair.second.begin(); number != keypair.second.end(); ++number) {
                if (number != keypair.second.begin()) {
                    output << ",";
                }

                output << *number;
            }

            output << std::endl;
        }

        for (auto &keypair : this->timers) {
            output << keypair.first << "\t\t\t";

            for (auto number = keypair.second.begin(); number != keypair.second.end(); ++number) {
                if (number != keypair.second.begin()) {
                    output << ",";
                }

                output << *number;
            }

            output << std::endl;
        }

        output.close();
    }
private:
    Statistics() { }
    Statistics(Statistics const &) = delete;
    void operator=(Statistics const &) = delete;

    std::map<std::string, Number> values;
    std::map<std::string, std::list<Number>> series;
    std::map<std::string, std::list<Time>> timers;
};

/***********************************************************************************************************************
 * Value
 **********************************************************************************************************************/
class Value {
public:
    Value(std::string iName)
            : name(iName), value(Statistics::getInstance().values[name]) { };

    std::string inline getName() const {
        return this->name;
    }

    operator Number() const {
        return this->value;
    }

    Value &operator+=(const Value &m) {
        this->value += m.value;
        return *this;
    };

    Value &operator-=(const Value &m) {
        this->value -= m.value;
        return *this;
    };

    Value &operator++() {
        ++this->value;
        return *this;
    };

    Value &operator--() {
        --this->value;
        return *this;
    };

    template<typename T>
    Value &operator+=(const T &m) {
        this->value += m;
        return *this;
    }

    template<typename T>
    Value &operator-=(const T &m) {
        this->value -= m;
        return *this;
    }

    ~Value() { }
private:
    std::string name;
    Number &value;
};

/***********************************************************************************************************************
 * Counter
 **********************************************************************************************************************/
class Counter {
public:
    Counter(std::string iName)
            : name(iName), serie(Statistics::getInstance().series[iName]) { };

    std::string inline getName() const {
        return this->name;
    }

    operator Number() const {
        return this->value;
    }

    Counter &operator+=(const Counter &m) {
        this->value += m.value;
        return *this;
    };

    Counter &operator-=(const Counter &m) {
        this->value -= m.value;
        return *this;
    };

    Counter &operator++() {
        ++this->value;
        return *this;
    };

    Counter &operator--() {
        --this->value;
        return *this;
    };

    template<typename T>
    Counter &operator+=(const T &m) {
        this->value += m;
        return *this;
    }

    template<typename T>
    Counter &operator-=(const T &m) {
        this->value -= m;
        return *this;
    }

    ~Counter() {
        serie.push_back(value);
    }
private:
    std::string name;
    std::list<Number> &serie;
    Number value;
};

/***********************************************************************************************************************
 * Timer
 **********************************************************************************************************************/
class Timer {
public:
    Timer(std::string iName)
            : name(iName), timers(Statistics::getInstance().timers[name]),
              start(std::chrono::steady_clock::now()), end(std::chrono::steady_clock::now()), stopped(false) { }

    std::string inline getName() const {
        return this->name;
    }

    void stop() throw(std::runtime_error) {
        if (!stopped) {
            end = std::chrono::steady_clock::now();
            stopped = true;
        } else {
            throw std::runtime_error("Tried to double stop timer");
        }
    }

    void mark() throw(std::runtime_error) {
        if (!stopped) {
            end = std::chrono::steady_clock::now();
            timers.push_back(std::chrono::duration_cast<std::chrono::microseconds>(this->end - this->start).count());
            start = end;
            stopped = true;
        } else {
            throw std::runtime_error("Tried to double stop timer");
        }
    }

    ~Timer() {
        if (!stopped) {
            end = std::chrono::steady_clock::now();
        }

        timers.push_back(std::chrono::duration_cast<std::chrono::microseconds>(this->end - this->start).count());
    }
private:
    std::string name;
    std::list<Time> &timers;

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
    bool stopped;
};

#define STATISTICS_H
#endif //STATISTICS_H
