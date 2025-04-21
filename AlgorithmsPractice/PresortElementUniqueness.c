// ALGORITHM PresortElementUniqueness(A[0...n-1])

// 	sort array A
// 	for i <- 0 to n-2 do:
// 		if A[i] = A[i+1] return false
// 	return true

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool PresortElementUniqueness(int n, int *arr);

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

    bool result = PresortElementUniqueness(n, arr);

    if (result == true)
    {
        printf("Array has unique elements");
    }
    else
    {
        printf("Array has one/many duplicate elements");
    }

    free(arr);
    return 0;
}

int comp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

bool PresortElementUniqueness(int n, int *arr)
{
    qsort(arr, n, sizeof(int), comp);

    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] == arr[i + 1])
        {
            return false;
        }
    }
    return true;
}