#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void merge(long long arr[], long long left, long long mid, long long right)
{
    long long l1 = mid - left + 1;
    long long l2 = right - mid;

    long long *L = new long long [l1]; 
    long long *R = new long long [l2];

    for (long long i = 0; i < l1; i++)
        L[i] = arr[left + i];

    for (long long j = 0; j < l2; j++)
        R[j] = arr[mid + 1 + j];
    
    long long i = 0;
    long long j = 0;
    long long k = left;

    while (i < l1 && j < l2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }

        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < l1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < l2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;

}

void Merge_Sort(long long arr[], long long left, long long right)
{
    if (left < right)
    {
        long long mid = left + (right - left)/2;

        Merge_Sort(arr, left, mid);
        Merge_Sort(arr, mid+1, right);

        merge(arr, left, mid, right);
    }
}

long long binary_search(long long int arr[], long long size, long long number)
{
    int left = 0, right = size-1;
    int result = -1;

    while (left <= right)
    {
        int mid = left + (right - left)/2;

        if (arr[mid] <= number)
        {
            result = arr[mid];
            left = mid+1;
        }

        else
        {
            right = mid - 1;
        }
    }

    return number - result;
}

void fill_sums_array(long long int arr[], long long size, long long weights_array[])
{
    for (long long int mask = 0; mask < (1 << size); ++mask)
    {
        long long sum = 0;
        for (long long int i = 0; i < size; ++i)
        {
            if (mask & (1 << i))
            {
                sum += weights_array[i];
            }
        }
        arr[mask] = sum;
    }
}

long kasha(char *in_)
{
    ifstream read_f(in_);
    int n;
    read_f >> n;

    long long int *left = new long long[n / 2];
    long long int *right = new long long [(n / 2 + n % 2)];
    long long total_sum = 0;

    for (int i = 0; i < n / 2; i++)
    {
        read_f >> left[i];
        total_sum += left[i];
    }

    for (int i = 0; i < (n / 2 + n % 2); i++)
    {
        read_f >> right[i];
        total_sum += right[i];
    }

    read_f.close();


    long long *leftSums = new long long [1 << (n / 2)];
    long long *rightSums = new long long [1 << (n / 2 + n % 2)];
    long long min_diff = total_sum;
    long long target = total_sum / 2;

    fill_sums_array(leftSums, n / 2, left);
    fill_sums_array(rightSums, n / 2 + n % 2, right);

    delete[] left;
    delete[] right;

    Merge_Sort(rightSums, 0, (1 << n / 2 + n % 2) - 1);

    for (long long i = 0; i < 1 << n / 2; i++)
    {
        long long left_sum = leftSums[i];
        if (left_sum <= target)
            min_diff = min(min_diff, 2 * binary_search(rightSums, 1 << (n / 2 + n % 2), target - left_sum) + total_sum % 2);
    }

    delete[] leftSums;
    delete[] rightSums;

    return min_diff;
} 


void test(char *read, char *exp)
{
    long n1, n2;

    ifstream f1(exp);
    f1 >> n1;
    f1.close();

    int start = clock();
    n2 = kasha(read);
    int finish = clock();


    float time = float(finish - start)/1000000;

    if (n1 == n2 && time <= 1)
        cout << "Test OK | time -> " << time << endl; 
    
    else if (time > 1)
        cout << "RunTime Error -> " << time << endl;

    else
        cout << "TestError " << n2 << " != " << n1 << endl;
}


int main()
{
    test("/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-3/tests/read_1.txt", "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-3/tests/exp_1.txt"); // 0
    test("/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-3/tests/read_2.txt", "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-3/tests/exp_2.txt"); // 38
    test("/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-3/tests/read_3.txt", "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-3/tests/exp_3.txt"); // 3512894
    test("/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-3/tests/read_4.txt", "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-3/tests/exp_4.txt"); // 61 не правильный тест
    test("/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-3/tests/read_5.txt", "/Users/vladislavborzyaev/Coding/ЯП/cpp-lab/cpp-lab-3/tests/exp_5.txt"); // 0

    return 0;
}
