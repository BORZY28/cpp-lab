#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// класс клиент, имеющий характерстики: id, логин, пароль, фамилия, имя. 
class Customer{
    string login;
    string password;
    string data[5];
    
    int id;


    public:

        string first_name;
        string last_name;

        Customer()
        {
            login = "";
            password = "";
            string data[5] = {"", "", "", "", ""};
            first_name = "";
            last_name = "";
        }
        ~Customer(){};

        void set_login()
        {
            cout << "Введите логин: ";
            cin >> login;
            data[3] = login;
        }

        void set_password()
        {
            cout << "Введите пароль: ";
            cin >> password;
            data[4] = password;
        }         

        void set_id(){}

        void registration()
        {


            set_login();
            set_password();
            set_last_name();
            set_first_name();
            set_id();

            cout << data[0] << " " << data[1] << " " << data[2] << " " << data[3] << " " << data[4] << endl;

        }

        void set_last_name()
        {   
            bool flag = false;

            while (!flag)
            {

                flag = true;

                cout << "Введите свою фамилию -> ";
                cin >> last_name;

                for (size_t i = 0; i < last_name.length(); i++)
                {
                    if (isdigit(last_name[i]) || ispunct(last_name[i]) || isspace(last_name[i]))
                    {
                        cout << "Недопустимые символы\nПовторите ввод\n";
                        flag = false;
                        break;
                    }
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
            bool flag = false;

            while (!flag)
            {
                flag = true;

                cout << "Введите своё имя -> ";
                cin >> first_name;

                for (size_t i = 0; i < first_name.length(); i++)
                {
                    if (isdigit(first_name[i]) || ispunct(first_name[i]) || isspace(first_name[i]))
                    {
                        flag = false;
                    }
                }
            } 

            data[2] = first_name;
        }

        void get_first_name()
        {
            cout << "Имя клиента -> " << data[2];
        }

        string * return_data()
        {
            return data;
        }
};

class BankAccount{

};

class SavingAccount : public BankAccount{

};

class CheckingAccount : public BankAccount{

};

class Transaction{

};



int main()
{
    Customer client;

    client.registration();
    for (size_t i = 0; i < 5; i++)
    {
        cout << *(client.return_data() + i) << endl;
    }

    return 0;
}