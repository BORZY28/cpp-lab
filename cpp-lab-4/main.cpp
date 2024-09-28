#include <iostream>
#include "kasha.lib"
#include <fstream>
#include <time.h>

using namespace std;

void test(long int n, char *name_out, char *name_exp)
    {
        int start = clock();
        kasha(n, name_out);
        int finish = clock();

        float time = float(finish - start)/1000000;

        string s1, s2, s;

        ifstream f_1(name_exp);
        
        while (getline(f_1, s))
        {
            s1 += s;
        }

        f_1.close();

        ifstream f_2(name_out);

        while (getline(f_2, s))
        {
            s2 += s;
        }
        
        f_2.close();

        if (time <= 1.0 && s1 == s2)
            cout << "Test OK | time -> " << time<< endl;
        
        else if (time > 1.0)
            cout << "RunTime Error | time -> " << time<< endl;

        else
            cout << "Test Error exp != out | time -> " << time << endl;
    }   

int main()
{
    test(17237842, "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-4/tests/out_1.txt", "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-4/tests/exp_1.txt");
    test(10000,    "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-4/tests/out_2.txt", "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-4/tests/exp_2.txt");
    test(99999,    "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-4/tests/out_3.txt", "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-4/tests/exp_3.txt");
    test(10000000, "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-4/tests/out_4.txt", "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-4/tests/exp_4.txt");
    test(37263,    "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-4/tests/out_5.txt", "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-4/tests/exp_5.txt");

    return 0;

}