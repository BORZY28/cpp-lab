#ifndef BANK_HPP
#define BANK_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

// Класс клиента
class Customer {
    std::string login;
    std::string password;
    std::string data[5];
    std::string id_str;
    std::string check_all;
    std::string check_log;
    std::string check_pas;    

public:
    long id;
    std::string first_name;
    std::string last_name;

    Customer();
    ~Customer();

    void set_login(char* file);
    void set_password();
    void set_id(char* file);
    void set_last_name();
    void set_first_name();
    void get_last_name();
    void get_first_name();
    void authentication(std::string login, std::string password, char* file);
    std::string return_data(size_t i);
};

// Базовый класс для банковского счета
class BankAccount {
protected:
    std::string user_id;
    std::string type;
    std::string balance;
    std::string creation_time_utc;
    time_t now;
    tm* ltm;
    std::string check_all;
    std::string data[5];

public:
    BankAccount();
    virtual ~BankAccount();

    void set_id(Customer& client);
    void set_balance(std::string summ);
    virtual std::string get_user_id();
    virtual std::string get_type();
    void set_creation_time();
    virtual std::string get_balance();
    virtual std::string get_data(size_t i);
    virtual void create_acc(char* file) = 0;
    virtual void input_data(char* file) = 0;
};

// Сберегательный счет
class SavingAccount : public BankAccount {
    std::string procent;

public:
    SavingAccount(std::string save_procent);
    ~SavingAccount();

    std::string get_procent();
    void set_data();
    void input_data(char* file);
    void create_acc(char* file);

    friend std::ostream& operator<<(std::ostream& os, const SavingAccount& account);
};

// Расчетный счет
class CheckingAccount : public BankAccount {
public:
    CheckingAccount();
    ~CheckingAccount();

    void set_data();
    void input_data(char* file);
    void create_acc(char* file);
};

// Транзакции
class Transaction {
    float balance_1, balance_2;

public:
    Transaction();
    ~Transaction();

    virtual void withdraw(CheckingAccount* account, float summ, char* file);
    virtual void withdraw(SavingAccount* account, float summ, char* file);
    virtual void deposit(CheckingAccount* account, float summ, char* file);
    virtual void deposit(SavingAccount* account, float summ, char* file);
    virtual void writing_logs(SavingAccount* account, char* file);
    virtual void writing_logs(CheckingAccount* account, char* file);
    virtual void get_logs(SavingAccount* account, char* file);
    virtual void get_logs(CheckingAccount* account, char* file);
};

#endif // BANK_HPP