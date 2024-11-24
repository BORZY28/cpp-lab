#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
                    throw (isdigit(last_name[i]) || ispunct(last_name[i]) || isspace(last_name[i]));
                }
            }
            data[1] = last_name;

        }

        void get_last_name()
        {
            cout << "Фамилия клиента -> " << data[1];
        }

        void set_first_name()
        {   
            cin >> first_name;
            for (size_t i = 0; i < first_name.length(); i++)
            {
                if (isdigit(first_name[i]) || ispunct(first_name[i]) || isspace(first_name[i]))
                {
                    throw (isdigit(first_name[i]) || ispunct(first_name[i]) || isspace(first_name[i]));
                }
            }
            data[2] = first_name;
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
                    throw "Wrong login or password";
            }

            else
                throw "No data";

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
        float balance;
        size_t user_id;
};

class SavingAccount : public BankAccount{
    string creation_date;
    int procent;
};

class CheckingAccount : public BankAccount{

};

class Transaction{

};

void registration(Customer& client, char * file)
{
    bool flag = 0;

    while(!flag)
    {
        try
        {
            cout << "Введите логин -> ";;   
            client.set_login(file);
            flag = 1;
        }
        catch(bool error)
        {
            cout << "Данный логин занят" << endl << "Повторите ввод" << endl;
            flag = 0;
        }
    }


    flag = 0;

    cout << "Введите пароль -> ";
    client.set_password(); 
    
    while(!flag)
    {
        try
        {
            cout << "Введите свою фамилию -> ";
            client.set_last_name();
            flag = 1;
        }
        catch(bool error)
        {
            cout << "Введены недопустимые символы" << endl << "Повторите ввод фамилии" << endl;
            flag = 0;
        }
    }

    flag = 0;

    while(!flag)
    {
        try
        {
            cout << "Введите своё имя -> ";   
            client.set_first_name();
            flag = 1;
        }
        catch(bool error)
        {
            
            cout << "Введены недопустимые символы" << endl << "Повторите ввод" << endl;
            flag = 0;
        }
    }

    client.set_id(file);

    ofstream f_users(file, ios::app);
    for (size_t i = 0; i < 5; ++i)
    {
        f_users << client.return_data(i) << ';';
    }

    f_users << "\n";
    f_users.close();
};


int main()
{
    
    string login, password = "";

    bool flag = true;
    size_t step = 10;

    cout << "Салам, какашка\n";

    while (flag)
    {
        Customer client;

        string login, password = "";

        flag = false; 

        cout << "Введите 1, чтобы зарегистрировать пользователя\nВведите 2, чтобы войти в аккаунт\nВведите 0, чтобы завершить сеанс\n";
        cin >> step;

        if (step == 1)
        {
            registration(client, "users.txt");
            flag = true;

            cout << "Ваши данные:" << endl;

            for (size_t i = 1; i < 5; i++)
                cout << client.return_data(i) << endl;
        }

        else if(step == 2)
        {

            while(!flag)
            {
                try
                {
                    cout << "Введите свой логин -> ";
                    cin >> login;

                    cout << "Введите свой пароль -> ";
                    cin >> password;

                    // зависает после ввода логина и пароля: порешали

                    client.autantification(login, password, "users.txt");
                    flag = true;

                    // дальше работаем с клиентом, данные в него записались
                }


                catch(char const*)
                {
                    cout << "Неправильный логин или пароль" << endl << "Повторите ввод" << endl;
                    flag = false;
                }
            } 

            cout << "Вы зашли, как пользователь: " << client.return_data(1) << ' ' << client.return_data(2) << endl;
        }   
        
    
        else if (step == 0)
            flag = false;

        client.~Customer();
    }
    
    return 0;
}