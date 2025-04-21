// Algorithm HeapBottomUp(H[1...n])
// // Constructs a heap from the elements of a given array

// for i <- floor(n/2) downto 1 do:
// 	k <- i; v <- H[k]
// 	heap <- false

// 	while not heap and 2k <= n do:
// 		j <- 2k

// 		if j < n // there are 2 children
// 			if H[j] < H[j+1]:
// 				j <- j+1
// 			if v >= H[j]:
// 				heap <- true
// 			else H[k] <- H[j]; k <- j
// 	H[k] <- v

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int HeapBottomUp(int n, int *arr);

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

    HeapBottomUp(n, arr);

    printf("Final heap (array form): ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}

int HeapBottomUp(int n, int *arr)
{
    int k = 0, v = 0;
    bool heap;
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        int k = i;
        int v = arr[k];
        bool heap = false;

        while (!heap && 2 * k + 1 < n)
        {
            int j = 2 * k + 1;
            if (j + 1 < n && arr[j] < arr[j + 1])
            {
                j = j + 1;
            }

            if (v >= arr[j])
            {
                heap = true;
            }
            else
            {
                arr[k] = arr[j];
                k = j;
            }
        }
        arr[k] = v;
    }
}