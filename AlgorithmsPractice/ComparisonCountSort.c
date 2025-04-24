// ALGORITHM ComparisonCountSort(A[0...n-1])
// 	for i <- 0 to n-2 do count[i] <- 0
// 		for j <- i+1 to n-1:
// 			if A[i] < A[j] count[j]++
// 			else count[i]++

// 		for i <- 0 to n-1 do:
// 			S[count[i]] <- A[i]
// 		return S

#include <stdio.h>
#include <stdlib.h>

int *ComparisonCountSort(int n, int *arr);

int main()
{
    int n;
    printf("Enter number of elements in array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter %d space seperated integers: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int *sorted_arr = ComparisonCountSort(n, arr);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", sorted_arr[i]);
    }
    printf("\n");

    free(arr);
    free(sorted_arr);
    return 0;
}

int *ComparisonCountSort(int n, int *arr)
{
    int *count = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[j] < arr[i])
            {
                count[i]++;
            }
        }
    }

    int *result = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        result[count[i]] = arr[i];
    }

    return result;
}