#include "bank.hpp"

using namespace std;
// Реализация методов класса Customer
Customer::Customer() {
    login = "";
    password = "";
    std::string data[5] = {"", "", "", "", ""};
    first_name = "";
    last_name = "";
    id_str = "";
    id = -1;
}

Customer::~Customer() {}

void Customer::set_login(char* file) {
    size_t count = 0;
    std::cin >> login;
    std::ifstream f_users(file);
    if (f_users.peek() != EOF) {
        while (getline(f_users, check_log, ';')) {
            if (count % 5 == 3)
                if (check_log == login) {
                    throw (check_log == login);
                }
            count++;
        }
    }
    data[3] = login;
}

void Customer::set_password() {
    std::cin >> password;
    data[4] = password;
}

void Customer::set_id(char* file) {
    std::ifstream f_users(file);
    if (f_users.peek() != EOF) {
        while (getline(f_users, id_str)) {
            id += 1;
        }
    }
    data[0] = std::to_string(id + 1);
    f_users.close();
}

void Customer::set_last_name(){   
    cin >> last_name;
    for (size_t i = 0; i < last_name.length(); i++)
    {
        if (isdigit(last_name[i]) || ispunct(last_name[i]) || isspace(last_name[i]))
        {
            throw (std::invalid_argument("Недопустимые символы\n"));
        }
    }
    data[1] = last_name;
}

void Customer::set_first_name(){   
    cin >> first_name;
    for (size_t i = 0; i < first_name.length(); i++)
    {
        if (isdigit(first_name[i]) || ispunct(first_name[i]) || isspace(first_name[i]))
        {
            throw (std::invalid_argument("Недопустимые символы\n"));;
        }
    }
    data[2] = first_name;
}
void Customer::get_last_name() {cout << "Фамилия клиента -> " << data[1];}

void Customer::get_first_name() {cout << "Имя клиента -> " << data[2];}

void Customer::authentication(string login, string password, char * file)
{
    string str_data = "";
    string str_data_count = "";
    size_t count_log = 0;
    size_t count_pas = 0;
    bool flag = false;
    ifstream f_users(file);

    if (f_users.peek() != EOF)            // проверка логина и пароля в строке, если не находим в файле, то выкидывание ошибки по средствам флага
    {
        while(getline(f_users, check_all, ';'))
        {
            id = (count_log/5);
            
            if (count_log%5 == 3)
                check_log = check_all;

            else if (count_pas%5 == 4)
                check_pas = check_all;
            
            if (check_log == login && check_pas == password && count_log == count_pas)
            {
                flag = true;
                break;
            }

            count_log ++;
            count_pas ++; 
        }


    
        if (!flag)
            throw std::invalid_argument("Wrong login or password");
    }

    else
        throw std::out_of_range("No data");

    f_users.seekg(0, ios::beg);

    for (size_t i = 0; i <= id; ++i)
    {
        getline(f_users, str_data_count);

        if (i == id)
            str_data = str_data_count;
    }
            
    f_users.close();

    stringstream user_data;
    user_data << str_data;
    
    size_t i = 0;
    while (getline(user_data, str_data, ';'))
    {   
        data[i] = str_data;
        ++i;
    }

    user_data.clear();
}

std::string Customer::return_data(size_t i) {return data[i];}

// Реализация методов BankAccount
BankAccount::BankAccount() {
    std::string data[5] = {"", "", "", "", ""};
    user_id = "";
    type = "";
    balance = "0";
    now = time(0);
    ltm = localtime(&now);
    check_all = "";
}

BankAccount::~BankAccount() {}

void BankAccount::set_id(Customer& client) {
    user_id = client.return_data(0);
}

void BankAccount::set_balance(std::string summ) {
    balance = summ;
}

std::string BankAccount::get_user_id() {
    return user_id;
}

std::string BankAccount::get_type() {
    return type;
}

void BankAccount::set_creation_time() {
    ltm = localtime(&now);
    std::stringstream creation_time_utc_stream;
    creation_time_utc_stream << ltm->tm_mday << ' ' << 1 + ltm->tm_mon << ' ' << 1900 + ltm->tm_year;

    getline(creation_time_utc_stream, creation_time_utc); // Сохраняем дату в строку
    creation_time_utc_stream.clear();
}

std::string BankAccount::get_balance() {
    return balance;
}

std::string BankAccount::get_data(size_t i) {
    if (i >= 0 && i < 5) {
        return data[i];
    }
    throw std::out_of_range("Invalid data index");
}

// Реализация методов SavingAccount
SavingAccount::SavingAccount(std::string save_procent) {
    type = "0"; // Сберегательный счет
    procent = save_procent;
}

SavingAccount::~SavingAccount() {}

std::string SavingAccount::get_procent() {
    return procent;
}

void SavingAccount::set_data() {
    data[0] = user_id;
    data[1] = type;
    data[2] = procent;
    data[3] = creation_time_utc;
    data[4] = balance;
}

void SavingAccount::input_data(char* file) {
    std::ifstream f_accounts(file);

    if (!f_accounts.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    bool flag = false;
    if (f_accounts.peek() != EOF) {
        std::string check_id, check_type, check_procent, check_date, check_balance;
        size_t count = 0;

        while (getline(f_accounts, check_all, ';')) {
            if (count % 6 == 0) check_id = check_all;
            else if (count % 6 == 1) check_type = check_all;
            else if (count % 6 == 2) check_procent = check_all;
            else if (count % 6 == 3) check_date = check_all;
            else if (count % 6 == 4) check_balance = check_all;

            if ((check_id == user_id) && (check_type == type) && (count % 6 == 5)) {
                data[0] = check_id;
                data[1] = check_type;
                data[2] = check_procent;
                data[3] = check_date;
                data[4] = check_balance;
                flag = true;
                break;
            }
            count++;
            count %= 6;
        }
        f_accounts.close();

        if (!flag) {
            throw std::invalid_argument("Customer has no SavingAccount");
        }
    } else {
        throw std::out_of_range("No data available");
    }
}

void SavingAccount::create_acc(char* file) {
    std::ofstream f_accounts(file, std::ios::app);

    if (!f_accounts.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    set_creation_time();
    set_data();

    f_accounts << data[0] << ';' << data[1] << ';' << data[2] << ';'
               << data[3] << ';' << data[4] << ";\n";
    f_accounts.close();
}

// Реализация перегрузки оператора <<
std::ostream& operator<<(std::ostream& os, const SavingAccount& account) {
    os << "Saving Account Details:\n";
    os << "User ID: " << account.user_id << "\n";
    os << "Account Type: " << " (Saving Account)\n";
    os << "Procent: " << account.procent << "%\n";
    os << "Creation Date: " << account.creation_time_utc << "\n";
    os << "Balance: " << account.balance << "\n";
    return os;
}

// Реализация методов CheckingAccount
CheckingAccount::CheckingAccount() {
    type = "1"; // Расчетный счет
}

CheckingAccount::~CheckingAccount() {}

void CheckingAccount::set_data() {
    data[0] = user_id;
    data[1] = type;
    data[3] = creation_time_utc;
    data[4] = balance;
}

void CheckingAccount::input_data(char* file) {
    std::ifstream f_accounts(file);

    if (!f_accounts.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    bool flag = false;
    if (f_accounts.peek() != EOF) {
        std::string check_id, check_type, check_date, check_balance;
        size_t count = 0;

        while (getline(f_accounts, check_all, ';')) {
            if (count % 6 == 0) check_id = check_all;
            else if (count % 6 == 1) check_type = check_all;
            else if (count % 6 == 3) check_date = check_all;
            else if (count % 6 == 4) check_balance = check_all;

            if ((check_id == user_id) && (check_type == type) && (count % 6 == 5)) {
                data[0] = check_id;
                data[1] = check_type;
                data[3] = check_date;
                data[4] = check_balance;
                flag = true;
                break;
            }
            count++;
            count %= 6;
        }
        f_accounts.close();

        if (!flag) {
            throw std::invalid_argument("Customer has no CheckingAccount");
        }
    } else {
        throw std::out_of_range("No data available");
    }
}

void CheckingAccount::create_acc(char* file) {
    std::ofstream f_accounts(file, std::ios::app);

    if (!f_accounts.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    set_creation_time();
    set_data();

    f_accounts << data[0] << ';' << data[1] << ';' << ';'
               << data[3] << ';' << data[4] << ";\n";
    f_accounts.close();
}

// Реализация методов Transaction
Transaction::Transaction() {
    balance_1 = 0;
    balance_2 = 0;
}

Transaction::~Transaction() {}

// ---------------------------------------------
// Метод для снятия средств с расчетного счета
// ---------------------------------------------
void Transaction::withdraw(CheckingAccount* account, float summ, char* file) {
    if (summ <= 0) {
        throw std::invalid_argument("Invalid argument, summ <= 0 | waiting summ > 0");
    }

    // Получаем баланс с расчетного счета
    std::string check_all, check_id, check_type;
    float balance;
    std::string str_balance = "";
    std::stringstream balance_stream;
    balance_stream << account->get_data(4);
    balance_stream >> balance;
    balance_1 = balance;
    balance_stream.clear();

    if (summ > balance) {
        throw std::out_of_range("No money");
    }

    balance -= summ;
    balance_2 = balance;

    // Обновляем баланс на расчетном счете
    balance_stream << balance;
    balance_stream >> str_balance;
    balance_stream.clear();
    account->set_balance(str_balance);
    account->set_data();

    size_t count = 0;
    size_t len_f = 0;
    bool flag_id = false, flag_type = false;
    size_t balance_flag = 0;
    check_id = account->get_data(0);
    check_type = account->get_data(1);

    std::fstream f_accounts(file);
    while (getline(f_accounts, check_all, ';')) {
        if (count % 6 == 0 && check_id == check_all) flag_id = true;
        if (count % 6 == 1 && check_type == check_all && flag_id) flag_type = true;
        if (count % 6 == 4 && flag_id && flag_type) balance_flag = count;
        if (count % 6 == 5) flag_id = false, flag_type = false;
        count++;
    }
    f_accounts.close();

    len_f = count;
    count = 0;
    std::string* arr_f = new std::string[len_f];

    std::fstream f_accounts_1(file);
    while (getline(f_accounts_1, check_all, ';')) {
        arr_f[count] = check_all;
        count++;
    }
    f_accounts_1.close();
    remove(file);

    arr_f[balance_flag] = str_balance;

    std::ofstream f_accounts_2(file);
    for (size_t i = 0; i < count - 1; i += 6) {
        f_accounts_2 << arr_f[i] << ';' << arr_f[i + 1]
                     << ';' << arr_f[i + 2] << ';' << arr_f[i + 3]
                     << ';' << arr_f[i + 4] << ";\n;";
    }
    f_accounts_2.close();
    delete[] arr_f;
}

// ---------------------------------------------
// Метод для снятия средств с сберегательного счета
// ---------------------------------------------
void Transaction::withdraw(SavingAccount* account, float summ, char* file) {
    if (summ <= 0) {
        throw std::invalid_argument("Invalid argument, summ <= 0 | waiting summ > 0");
    }

    // Получаем баланс с сберегательного счета
    std::string check_all, check_id, check_type;
    float balance;
    std::string str_balance = "";
    std::stringstream balance_stream;
    balance_stream << account->get_data(4);
    balance_stream >> balance;
    balance_1 = balance;
    balance_stream.clear();

    if (summ > balance) {
        throw std::out_of_range("No money");
    }

    balance -= summ;
    balance_2 = balance;

    // Обновляем баланс на сберегательном счете
    balance_stream << balance;
    balance_stream >> str_balance;
    balance_stream.clear();
    account->set_balance(str_balance);
    account->set_data();

    // Обновляем данные в файле
    size_t count = 0;
    size_t len_f = 0;
    bool flag_id = false, flag_type = false;
    size_t balance_flag = 0;
    check_id = account->get_data(0);
    check_type = account->get_data(1);

    std::fstream f_accounts(file);
    while (getline(f_accounts, check_all, ';')) {
        if (count % 6 == 0 && check_id == check_all) flag_id = true;
        if (count % 6 == 1 && check_type == check_all && flag_id) flag_type = true;
        if (count % 6 == 4 && flag_id && flag_type) balance_flag = count;
        if (count % 6 == 5) flag_id = false, flag_type = false;
        count++;
    }
    f_accounts.close();

    len_f = count;
    count = 0;
    std::string* arr_f = new std::string[len_f];

    std::fstream f_accounts_1(file);
    while (getline(f_accounts_1, check_all, ';')) {
        arr_f[count] = check_all;
        count++;
    }
    f_accounts_1.close();
    remove(file);

    arr_f[balance_flag] = str_balance;

    std::ofstream f_accounts_2(file);
    for (size_t i = 0; i < count - 1; i += 6) {
        f_accounts_2 << arr_f[i] << ';' << arr_f[i + 1]
                     << ';' << arr_f[i + 2] << ';' << arr_f[i + 3]
                     << ';' << arr_f[i + 4] << ";\n;";
    }
    f_accounts_2.close();
    delete[] arr_f;
}

// ---------------------------------------------
// Метод для пополнения расчетного счета
// ---------------------------------------------
void Transaction::deposit(CheckingAccount* account, float summ, char* file) {
    if (summ <= 0) {
        throw std::invalid_argument("Invalid argument, summ <= 0 | waiting summ > 0");
    }

    // Получаем баланс с расчетного счета
    std::string check_all, check_id, check_type;
    float balance;
    std::string str_balance = "";
    std::stringstream balance_stream;
    balance_stream << account->get_data(4);
    balance_stream >> balance;
    balance_1 = balance;
    balance_stream.clear();

    balance += summ;
    balance_2 = balance;

    // Обновляем баланс на расчетном счете
    balance_stream << balance;
    balance_stream >> str_balance;
    balance_stream.clear();
    account->set_balance(str_balance);
    account->set_data();

    // Обновляем данные в файле
    size_t count = 0;
    size_t len_f = 0;
    bool flag_id = false, flag_type = false;
    size_t balance_flag = 0;
    check_id = account->get_data(0);
    check_type = account->get_data(1);

    std::fstream f_accounts(file);
    while (getline(f_accounts, check_all, ';')) {
        if (count % 6 == 0 && check_id == check_all) flag_id = true;
        if (count % 6 == 1 && check_type == check_all && flag_id) flag_type = true;
        if (count % 6 == 4 && flag_id && flag_type) balance_flag = count;
        if (count % 6 == 5) flag_id = false, flag_type = false;
        count++;
    }
    f_accounts.close();

    len_f = count;
    count = 0;
    std::string* arr_f = new std::string[len_f];

    std::fstream f_accounts_1(file);
    while (getline(f_accounts_1, check_all, ';')) {
        arr_f[count] = check_all;
        count++;
    }
    f_accounts_1.close();
    remove(file);

    arr_f[balance_flag] = str_balance;

    std::ofstream f_accounts_2(file);
    for (size_t i = 0; i < count - 1; i += 6) {
        f_accounts_2 << arr_f[i] << ';' << arr_f[i + 1]
                     << ';' << arr_f[i + 2] << ';' << arr_f[i + 3]
                     << ';' << arr_f[i + 4] << ";\n;";
    }
    f_accounts_2.close();
    delete[] arr_f;
}

// ---------------------------------------------
// Метод для пополнения сберегательного счета
// ---------------------------------------------
void Transaction::deposit(SavingAccount* account, float summ, char* file) {
    if (summ <= 0) {
        throw std::invalid_argument("Invalid argument, summ <= 0 | waiting summ > 0");
    }

    // Получаем баланс с сберегательного счета
    std::string check_all, check_id, check_type;
    float balance;
    std::string str_balance = "";
    std::stringstream balance_stream;
    balance_stream << account->get_data(4);
    balance_stream >> balance;
    balance_1 = balance;
    balance_stream.clear();

    balance += summ;
    balance_2 = balance;

    // Обновляем баланс на сберегательном счете
    balance_stream << balance;
    balance_stream >> str_balance;
    balance_stream.clear();
    account->set_balance(str_balance);
    account->set_data();

    // Обновляем данные в файле
    size_t count = 0;
    size_t len_f = 0;
    bool flag_id = false, flag_type = false;
    size_t balance_flag = 0;
    check_id = account->get_data(0);
    check_type = account->get_data(1);

    std::fstream f_accounts(file);
    while (getline(f_accounts, check_all, ';')) {
        if (count % 6 == 0 && check_id == check_all) flag_id = true;
        if (count % 6 == 1 && check_type == check_all && flag_id) flag_type = true;
        if (count % 6 == 4 && flag_id && flag_type) balance_flag = count;
        if (count % 6 == 5) flag_id = false, flag_type = false;
        count++;
    }
    f_accounts.close();

    len_f = count;
    count = 0;
    std::string* arr_f = new std::string[len_f];

    std::fstream f_accounts_1(file);
    while (getline(f_accounts_1, check_all, ';')) {
        arr_f[count] = check_all;
        count++;
    }
    f_accounts_1.close();
    remove(file);

    arr_f[balance_flag] = str_balance;

    std::ofstream f_accounts_2(file);
    for (size_t i = 0; i < count - 1; i += 6) {
        f_accounts_2 << arr_f[i] << ';' << arr_f[i + 1]
                     << ';' << arr_f[i + 2] << ';' << arr_f[i + 3]
                     << ';' << arr_f[i + 4] << ";\n";
    }
    f_accounts_2.close();
    delete[] arr_f;
}

void Transaction::writing_logs(SavingAccount * account, char * file) {
    fstream f_logs(file, ios::app);
    f_logs << account->get_data(0) << ';' << account->get_data(1) << ';' << balance_1 << ';' << balance_2 << ';' << "\n" << ';';
    f_logs.close();
}; 
void Transaction::writing_logs(CheckingAccount * account, char * file) 
{
    fstream f_logs(file, ios::app);
    f_logs << account->get_data(0) << ';' << account->get_data(1) << ';' << balance_1 << ';' << balance_2 << ';' << "\n" << ';';
    f_logs.close();
}; 

void Transaction::get_logs(SavingAccount* account, char * file)
{

    string check_all;
    size_t c = 0, count = 0;
    bool id_flag = false;
    bool type_flag = false;
    fstream f_logs(file);
    if (f_logs.peek() != EOF)
    {
        while (getline(f_logs, check_all, ';'))
        {
            if (count%5 == 0 && check_all == account->get_data(0)) {id_flag = true; c++;}
            if (count%5 == 1 && check_all == account->get_data(1)) {type_flag = true; c++;}

            if (count%5 == 2 && id_flag && type_flag) {cout << check_all << " -> "; c++;}
            if (count%5 == 3 && id_flag && type_flag) {cout << check_all << endl; c++;}
            if (count%5 == 4) {id_flag = false; type_flag = false;}
            
            count ++;
        }          
        if (c == 0) throw std::out_of_range("No data");      

    }

    else
        throw std::out_of_range("No data");
}
void Transaction::get_logs(CheckingAccount * account, char * file)
{

    string check_all;
    size_t c = 0, count = 0;
    bool id_flag = false;
    bool type_flag = false;
    fstream f_logs(file);
    if (f_logs.peek() != EOF)
    {
        while (getline(f_logs, check_all, ';'))
        {
            if (count%5 == 0 && check_all == account->get_data(0)) {id_flag = true; c++;}
            if (count%5 == 1 && check_all == account->get_data(1)) {type_flag = true; c++;}

            if (count%5 == 2 && id_flag && type_flag) {cout << check_all << " -> "; c++;}
            if (count%5 == 3 && id_flag && type_flag) {cout << check_all << endl; c++;}
            if (count%5 == 4) {id_flag = false; type_flag = false;}
            
            count ++;
        }          
        if (c == 0) throw std::out_of_range("No data");      

    }

    else
        throw std::out_of_range("No data");
}
