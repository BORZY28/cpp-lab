#include <iostream>

using namespace std;

long long int sum_ar_pr(long int first, long int last)
{
    return ((first + last)*(last))/2;
}

int main()
{

    long int n;
    long long int sum, all_sum;
    long int i = 0; long int j = 0;
    long int c = 0;

    cout << "Введите число n -> ";
    cin >> n;

    all_sum = sum_ar_pr(1, n);

    long long target = all_sum/2;
    long int arr_1[n], arr_2[n];

    if (all_sum%2 == 0)
    {
        sum = 0;

        while (c < n)
        {
            if (sum + n-c <= target)
            {
                sum += n-c;
                arr_1[i] = n-c;
                i++;

            }
            else
            {
                arr_2[j] = n-c;
                j++;
            }

            c++;
        }

        cout << "YES" << endl;

        cout << i << endl;

        for (long int i = 0; i < n; i++)
        {
            if (1 <= arr_1[i] && arr_1[i] <= n)
                cout << arr_1[i] << " ";
            else
                break;
        }
            

        cout << endl;
        cout << j << endl;

        for (long int i = 0; i < n; i++)
        {
            if (1 <= arr_2[i] && arr_2[i] <= n)
                cout << arr_2[i] << " ";
            else
                break;
        }        
        
        cout << endl;
    } 

    else
    {
        cout << "NO" << endl;
    }

    return 0;
}