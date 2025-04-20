#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int a[], int n);
void swap(int *a, int *b);

int main()
{
    int n;
    int a[100];

    printf("Enter the size of array: ");
    scanf("%d", &n);

    printf("Enter %d values: \n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    clock_t start, end;
    start = clock();
    bubbleSort(a, n);
    end = clock();

    double time = (double)((end - start) / CLOCKS_PER_SEC);
    printf("time taken = %lf\n", time);
    printf("Sorted array: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}

void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j + 1] < a[j])
            {
                swap(&(a[j]), &(a[j + 1]));
            }
        }
    }
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}