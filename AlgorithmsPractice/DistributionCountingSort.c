// ALGORITHM DistSort(A[0...n-1], l, u)
// // Sorts an array of integers from a limited range by distribution counting

// 	for j <- 0 to u-l do:
// 		D[j] <- 0 // initialize frequencies

// 	for i <- 0 to n-l do:
// 		D[A[i]-l] <- D[A[i]-l]+1 // compute frequencies

// 	for j <- n-1 downto 0 do:
// 		j <- A[i]-l
// 		S[D[j]-1] <- A[i]
// 		D[j] <- D[j]-1

// 	return S

#include <stdio.h>
#include <stdlib.h>

int *DistributionCountingSort(int n, int *arr, int upper, int lower);

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

    int u, l;
    printf("Enter upper bound: ");
    scanf("%d", &u);
    printf("Enter lower bound: ");
    scanf("%d", &l);

    int *sorted_arr = DistributionCountingSort(n, arr, u, l);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", sorted_arr[i]);
    }
    printf("\n");

    free(arr);
    free(sorted_arr);
    return 0;

    return 0;
}

int *DistributionCountingSort(int n, int *arr, int upper, int lower)
{
    int range = upper - lower + 1;
    int *dist = (int *)calloc(range, sizeof(int));
    int *result = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        dist[arr[i] - lower]++;
    }

    for (int i = 1; i < range; i++)
    {
        dist[i] += dist[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int index = arr[i] - lower;
        result[dist[index] - 1] = arr[i];
        dist[index]--;
    }

    free(dist);
    return result;
}