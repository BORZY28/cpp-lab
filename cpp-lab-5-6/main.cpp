#include "bank.cpp"

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
        catch(std::invalid_argument)
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
        catch(std::invalid_argument)
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

    cout << "prod. Yato\n";


    // Цикл главного меню
    while (flag)
    {
        Customer client;

        string login, password = "";

        flag = false; 


        cout << "Введите 1, чтобы зарегистрировать пользователя\nВведите 2, чтобы войти в аккаунт\nВведите 0, чтобы завершить сеанс\n";
        cin >> step;


        // Регистрация нового пользователя
        if (step == 1)
        {
            registration(client, "users.txt");
            flag = true;

            cout << "Ваши данные:" << endl;

            for (size_t i = 1; i < 5; i++)
                cout << client.return_data(i) << endl;
        }

        // Вход в аккаунт
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

                    client.authentication(login, password, "users.txt");
                    
                    // дальше работаем с клиентом, данные в него записались

                    cout << "Вы зашли, как пользователь: " << client.return_data(1) << ' ' << client.return_data(2) << endl;

                    bool count_1, exist_1, count_2, exist_2, account_flag = 0;
                    while(!account_flag)
                    {
                        size_t account_step = 10;

                        SavingAccount saving_account("12"), *saving_acc; saving_account.set_id(client);
                        saving_acc = &saving_account;
                        
                        CheckingAccount checking_account, *check_acc; checking_account.set_id(client);
                        check_acc = &checking_account;
                        
                        saving_acc->set_data();
                        check_acc ->set_data();
                        
                        //check
                        /*
                        cout << saving_acc->get_data(0) << ';' << saving_acc->get_data(1)
                             << ';' << saving_acc->get_data(2) << ';' << saving_acc->get_data(3)
                             << ';' << saving_acc->get_data(4) << endl;

                        cout << check_acc->get_data(0) << ';' << check_acc->get_data(1)
                             << ';' << check_acc->get_data(2) << ';' << check_acc->get_data(3)
                             << ';' << check_acc->get_data(4) << endl;
                        */
                        //check
                        

                        // Попытка получить данные сберегательного счёта
                        try { saving_acc->input_data("accounts.txt"); count_1 = true; exist_1 = true; }

                        // Обработка ошибок при отсутствии счета или данных о счетах в принципе
                        //
                        catch(std::invalid_argument)
                        {
                            cout << "|      У вас нет сберегательного счёта       |";
                            count_1 = false;
                            exist_1 = false;
                        }
                        catch(std::out_of_range)
                        {
                            cout << "|       У вас нет сберегательного счёта        |";
                            count_1 = false;
                            exist_1 = false;
                        }
                        //
 
                        // Попытка получить данные текущего счёта
                        try { check_acc->input_data("accounts.txt"); count_2 = true; exist_2 = true; }

                        // Обработка ошибок при отсутствии счета или данных о счетах в принципе
                        //
                        catch(std::invalid_argument)
                        {
                            cout << "|      У вас нет текущего счёта       |" << endl;
                            count_2 = false;
                            exist_2 = false;
                        }
                        catch(std::out_of_range)
                        {
                            cout << "|      У вас нет текущего счёта       |" << endl;
                            count_2 = false;
                            exist_2 = false;
                        }
                        //
                        
                        if (!count_1)
                        {
                            account_step = 10;

                            cout << "Предлагаем создать сберегательный счёт\nВведите 1, чтобы создать счёт | 2, чтобы игнорировать\n";
 
                            while (!count_1)
                            {
                                cin >> account_step;

                                if (account_step == 1) 
                                {
                                    
                                    saving_acc->create_acc("accounts.txt");
                                    cout << "Ваш сберегательный счёт создан\n";
                                    cout << saving_account;
                                    count_1 = true;
                                    exist_1 = true;
                                }

                                else if (account_step == 2) { count_1 = true; exist_1 = false; cout << "Счёт не создан" << endl; }

                                else 
                                {
                                    cout << "Введены недопустимые символы\nПовторите ввод\n"; 
                                    cout << "Введите 1, чтобы создать счёт\n2 чтобы игнорировать\n";
                                }
                            }

                        }
       
                        if (!count_2) 
                        {
                            account_step = 10;

                            cout << "Предлагаем создать текущий счёт\nВведите 1, чтобы создать счёт | 2, чтобы игнорировать\n";

                            while (!count_2)
                            {
                                cin >> account_step;

                                if (account_step == 1) 
                                {
                                    check_acc->create_acc("accounts.txt");
                                    cout << "Ваш текущий счёт создан\n";
                                    cout << "Владелец счёта: " << client.return_data(1) << ' ' << client.return_data(2) << endl;
                                    cout << "Cчёт создан: " << check_acc->get_data(3) << endl;
                                    cout << "Баланс: " << check_acc->get_data(4) << endl;
                                    count_2 = true;
                                    exist_2 = true;
                                }

                                else if (account_step == 2) {count_2 = true; exist_2 = false; cout << "Счёт не создан" << endl; }

                                else
                                {
                                    cout << "Введены недопустимые символы\nПовторите ввод\n"; 
                                    cout << "Введите 1, чтобы создать счёт\n2 чтобы игнорировать\n";
                                }
                            }
                        }
                        bool flag_trans = false;

                        while (!flag_trans)
                        {
                            size_t acc_step = 10;
                            size_t acc_type = 10;
                            Transaction trans;
                            if (exist_1 && exist_2)
                            {
                                cout << "Вам доступны Сберегательный и текущий счёт" << endl;
                                cout << "Cберегательный счёт: Баланс: " << saving_acc->get_data(4) << endl;
                                cout << "Текущий счёт: Баланс: " << check_acc->get_data(4) << endl;
                                cout << "Чтобы совершить операции введите номер из меню" << endl;
                                cout << "1. Внести деньги\n2. Снять деньги\n3. Просмотреть историю счета\n0. Чтобы выйти\n";
                                cin >> acc_step;
                                if (acc_step == 1) 
                                {
                                    float summ = 0;
                                    cout << "Введите 1, чтобы выбрать Сберегательный счёт, 2, чтобы выбрать Текущий счёт\n";
                                    cin >> acc_type;
                                    cout << "Введите сумму -> ";
                                    cin >> summ;

                                    if (acc_type == 1) {trans.deposit(saving_acc, summ, "accounts.txt"); trans.writing_logs(saving_acc, "logs.txt");}

                                    else if (acc_type == 2) {trans.deposit(check_acc, summ, "accounts.txt"); trans.writing_logs(check_acc, "logs.txt");}
                                }

                                else if (acc_step == 2)
                                {
                                    cout << "Введите 1, чтобы выбрать Сберегательный счёт, 2, чтобы выбрать Текущий счёт\n";
                                    cin >> acc_type;
                                    float summ = 0;
                                    cout << "Введите сумму -> ";
                                    cin >> summ;

                                    if (acc_type == 1) {trans.withdraw(saving_acc, summ, "accounts.txt"); trans.writing_logs(saving_acc, "logs.txt");}

                                    else if (acc_type == 2) {trans.withdraw(check_acc, summ, "accounts.txt"); trans.writing_logs(check_acc, "logs.txt");}
                                }

                                else if (acc_step == 3)
                                {
                                    cout << "Введите 1, чтобы выбрать Сберегательный счёт, 2, чтобы выбрать Текущий счёт\n";
                                    cin >> acc_type;
                                    if (acc_type == 1) {trans.get_logs(saving_acc, "logs.txt");}
                                    else if (acc_type == 2) {trans.get_logs(check_acc, "logs.txt");}
                                }

                                else flag_trans = true;

                                
                            }

                            else if (exist_1)
                            {
                                cout << "Вам доступен только Сберегательный счёт" << endl;
                                cout << "Cберегательный счёт: Баланс: " << saving_acc->get_data(4) << endl;
                                cout << "Чтобы совершить операции введите номер из меню" << endl;
                                cout << "1. Внести деньги\n2. Снять деньги\n3.Просмотреть историю счета\n";
                                cin >> acc_step;
                                if (acc_step == 1) 
                                {
                                    float summ = 0;
                                    cout << "Введите сумму -> ";
                                    cin >> summ;
                                    trans.deposit(saving_acc, summ, "accounts.txt"); trans.writing_logs(saving_acc, "logs.txt");
                                }

                                else if (acc_step == 2)
                                {

                                    float summ = 0;
                                    cout << "Введите сумму -> ";
                                    cin >> summ;
                                    trans.withdraw(saving_acc, summ, "accounts.txt"); trans.writing_logs(saving_acc, "logs.txt");
                                }

                                else if (acc_step == 3)
                                {
                                    trans.get_logs(saving_acc, "logs.txt");
                                }

                                else flag_trans = true;
                            }

                            else if (exist_2)
                            {
                                cout << "Вам доступен только Текущий счёт" << endl;
                                cout << "Текущий счёт: Баланс: " << check_acc->get_data(4) << endl;
                                cout << "Чтобы совершить операции введите номер из меню" << endl;
                                cout << "1. Внести деньги\n2. Снять деньги\n3.Просмотреть историю счета";

                                cin >> acc_step;
                                if (acc_step == 1) 
                                {
                                    float summ = 0;
                                    cout << "Введите сумму -> ";
                                    cin >> summ;
                                    trans.deposit(check_acc, summ, "accounts.txt"); trans.writing_logs(check_acc, "logs.txt");
                                }

                                else if (acc_step == 2)
                                {

                                    float summ = 0;
                                    cout << "Введите сумму -> ";
                                    cin >> summ;
                                    trans.withdraw(check_acc, summ, "accounts.txt"); trans.writing_logs(check_acc, "logs.txt");
                                }

                                else if (acc_step == 3)
                                {
                                    trans.get_logs(check_acc, "logs.txt");
                                }

                                else flag_trans = true;
                            }
                            else if (exist_1 && !exist_2) {flag_trans = true;}
                            cout << "Выполнено\n";
                        } 
                        account_flag = true;
                    }
                    flag = true;
                }

                // Обработка ошибок при аутантификации
                catch(std::invalid_argument)
                {
                    cout << "Неправильный логин или пароль" << endl << "Повторите ввод" << endl;
                    flag = false;
                }

                catch(std::out_of_range)
                {
                    cout << "Нет зарегистрированных пользователей" << endl;
                    flag = true;
                }

                
            } 
        }   
    
        else if (step == 0)
            flag = false;
    }
    cout << "До встречи" << endl;
    
    return 0;
}