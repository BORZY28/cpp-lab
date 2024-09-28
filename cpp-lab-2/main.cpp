#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;


int pow(int x, int n)
{   
    if (n == 0) return 1;

    int k = x;
    for (int i = 0; i < n-1; i++)
    {
        x = x*k;
    }

    return x;
}

long int d_f(long int x)
{
    if (x <= 1) return 1;
    else return x * d_f(x-2);
}

long double t(long double x)
{   
    int k;
    long double answer1 = 0; long double answer2 = 0;

    for(int k = 0; k <= 10; k++)
    {
        answer1 += (pow(x, 2*k+1)) / (d_f(2*k + 1));
        answer2 += (pow(x, 2*k)) / (d_f(2*k));
    }

    return answer1 / answer2;
}

long double f(double y)
{
    return (7 * t(0.25) + 2 * t(1+y)) / (6 - t(pow(y, 2) -1));
}


void test(double x, long double y)
{
    int start = clock();
    long double k = f(x) - y;
    int finish = clock();

    if (abs(k) < 0.00000000000001 && float(finish - start)/1000 <= 1.0)
    {
        cout << "Test OK " << float(finish - start) / 1000 << endl;
    } 

    else 
    {
        cout << "Error" << endl;
    }
}

int main()
{   
    long double y;

    test(1, 0.687421307804035);
    test(87, -0.024176524540420);
    test(23451, -0.000085299502823);
    test(23450, -0.000085299502823);
    test(87654, -0.000022818079422);


    return 0;
}

// int main()
// {
//     double y;
//     cin >> y;
//     cout << f(y) << endl;
//     cout << fixed << setprecision(6) << f(y) << endl;
    
    
// }
