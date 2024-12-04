#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

// класс клиент, имеющий характерстики: id, логин, пароль, фамилия, имя. 
class Customer
{
    string login;
    string password;
    string data[5];
    string id_str;

    string check_all;
    string check_log;
    string check_pas;    
    
    public:

        long id;
        string first_name;
        string last_name;

        Customer()
        {
            login = "";
            password = "";
            string data[5] = {"", "", "", "", ""};
            first_name = "";
            last_name = "";
            id_str = "";
            id = -1;
        }
        ~Customer(){} //он есть

        void set_login(char * file)
        {
            size_t count = 0;
            cin >> login;
            ifstream f_users(file);

            if (f_users.peek() != EOF)
            while(getline(f_users, check_log, ';'))
            {
                if (count%5 == 3)
                    if (check_log == login) 
                    {
                        throw (check_log == login);
                    }

                count ++;
            }

            data[3] = login;
        }

        void set_password()
        {
            cin >> password;
            data[4] = password;
        }

        void set_id(char * file)
        {
            ifstream f_users(file);

            if (f_users.peek() != EOF)
            {
                while(getline(f_users, id_str))
                {
                    id += 1;
                }
            }

            data[0] = to_string(id + 1);
            f_users.close();
        }   
            
        void set_last_name()
        {   
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

        void set_first_name()
        {   
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

        void get_last_name()
        {
            cout << "Фамилия клиента -> " << data[1];
        }

        void get_first_name()
        {
            cout << "Имя клиента -> " << data[2];
        }

        void autantification(string login, string password, char * file)
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

        string return_data(size_t i)

        {
            return data[i];
        }
};

class BankAccount{
    
    protected:
        string user_id;
        string type;
        string balance;
        string creation_time_utc;
        time_t now;
        tm *ltm;
        string check_all;
        string data[5];

    public:

        BankAccount()
        {
            string data[5] = {"", "", "", "", ""};   // {user id; account type; procent/"nothing" ; date of creation; balance}
            user_id = "";
            type = "";
            balance = "0";
            now = time(0);
            ltm = localtime(&now);
            check_all = "";
        }
        ~BankAccount(){}

        void set_id(Customer& client) { user_id = client.return_data(0); }
        

        virtual string get_user_id() {return user_id;}
        virtual string get_type()    {return type;}

        void set_creation_time()
        {
            ltm = localtime(&now);
            stringstream creation_time_utc_stream;
            creation_time_utc_stream << ltm->tm_mday << ' ' << 1 + ltm->tm_mon << ' ' << 1900 + ltm->tm_year;
            
            getline(creation_time_utc_stream, creation_time_utc); //return UTC date 

            creation_time_utc_stream.clear();
        }
       
        virtual string get_balance() {return balance;}
        virtual string get_data(size_t i) { return data[i]; }

        // virtual void set_data() = 0;

        virtual void create_acc(char * file) = 0;
            
        virtual void input_data(char * file) = 0;    
};

class SavingAccount : public BankAccount{
    string procent;
    public:

        SavingAccount(string save_procent) {type = "0"; procent = save_procent;}
        ~SavingAccount() {}

        string get_procent() {return procent;}

        

        void set_data() 
        {
            data[0] = user_id; 
            data[1] = type; 
            data[2] = procent; 
            data[3] = creation_time_utc;
            data[4] = balance;
        }

        void input_data(char * file)
        {
            ifstream f_accounts(file);

            bool flag = false;

            if (f_accounts.peek() != EOF)
            {
                
                string check_id; 
                string check_type;
                string check_procent;
                string check_date;
                string check_balance;

                size_t count = 0;
                while(getline(f_accounts, check_all, ';'))
                {

                    if (count%6 == 0)      {check_id      = check_all;}
                    else if (count%6 == 1) {check_type    = check_all;}
                    else if (count%6 == 2) {check_procent = check_all;}
                    else if (count%6 == 3) {check_date    = check_all;}
                    else if (count%6 == 4) {check_balance = check_all;}


                    if ((check_id == user_id) && (check_type == type) && (count%6 == 5))
                    {   
                        
                        data[0] = check_id;
                        data[1] = check_type;
                        data[2] = check_procent;
                        data[3] = check_date;
                        data[4] = check_balance;
                        flag = true;
                        break;
                    }
                    count ++;
                    count %= 6;
                }
                f_accounts.close();

                if (!flag) {throw std::invalid_argument("Customer has not SavingAccount"); }
            }

            else {throw std::out_of_range("No data");}
        }
        
        void create_acc(char * file) 
        {
            ofstream f_accounts(file, ios::app);
            
            set_creation_time();

            set_data();

            f_accounts << data[0] << ';' << data[1] 
                    << ';' << data[2] << ';' << data[3]
                    << ';' << data[4] << ";\n;";
            f_accounts.close();
        };
};

class CheckingAccount : public BankAccount{

    public:
        CheckingAccount() {type = "1";}
        ~CheckingAccount() {};

        void set_data() 
        {
            data[0] = user_id; 
            data[1] = type; 

            data[3] = creation_time_utc;
            data[4] = balance;
        }

        void input_data(char * file)
        {
            ifstream f_accounts(file);

            bool flag = false;

            if (f_accounts.peek() != EOF)
            {
                string check_id; 
                string check_type;
                string check_date;
                string check_balance;

                size_t count = 0;
                while(getline(f_accounts, check_all, ';'))
                {

                    if (count%6 == 0)      {check_id      = check_all;}
                    else if (count%6 == 1) {check_type    = check_all;}
                    else if (count%6 == 3) {check_date    = check_all;}
                    else if (count%6 == 4) {check_balance = check_all;}


                    if ((check_id == user_id) && (check_type == type) && (count%6 == 5))
                    {
                        data[0] = check_id;
                        data[1] = check_type;

                        data[3] = check_date;
                        data[4] = check_balance;
                        flag = true;
                        break;
                    }
                    count ++;
                    count %= 6;
                }
                f_accounts.close();

                if (!flag) {throw std::invalid_argument("Customer has not CheckingAccount");}
            }

            else {throw std::out_of_range("No data");}
        }

        void create_acc(char * file) 
        {
            ofstream f_accounts(file, ios::app);

            set_creation_time();
            
            set_data();

            f_accounts << data[0] << ';' << data[1] 
                    << ';'  << ';' << data[3]
                    << ';' << data[4] << ";\n;";
            f_accounts.close();
        };
};

class Transaction{
    void withdraw(CheckingAccount& account, float summ) {}
    void withdraw  (SavingAccount& account, float summ) {}

    void deposit (CheckingAccount& account, float summ) {}
    void deposit   (SavingAccount& account, float summ) {}

    virtual void writing_logs(char * file) = 0; 
};