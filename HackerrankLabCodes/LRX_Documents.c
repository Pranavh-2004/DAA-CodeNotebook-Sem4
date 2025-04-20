#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline();

/*
 * Complete the 'canTransform' function below.
 *
 * The function is expected to return a BOOLEAN.
 * The function accepts following parameters:
 *  1. STRING start
 *  2. STRING end
 */

bool canTransform(char *start, char *end)
{
    if (strcmp(start, end) == 0)
    {
        return true;
    }
    for (int i = 0; i < strlen(start) - 1; i++)
    {
        if (start[i] == 'X' && start[i + 1] == 'L')
        {
            start[i] = 'L';
            start[i + 1] = 'X';
        }
        if (strcmp(start, end) == 0)
        {
            return true;
        }
        if (start[i] == 'R' && start[i + 1] == 'X')
        {
            start[i] = 'X';
            start[i + 1] = 'R';
        }
        if (strcmp(start, end) == 0)
        {
            return true;
        }
    }
    return false;
}

/*
bool canTransform(char *start, char *end)
{
    if (strcmp(start, end) == 0)
    {
        return true;
    }
    else
    {
        for (int i = 0; i < strlen(start) - 1; i++)
        {
            if (start[i] == 'X' && start[i + 1] == 'L')
            {
                start[i] = 'L';
                start[i + 1] = 'X';
            }
        }
        canTransform(start, end);

        for (int i = 0; i < strlen(start) - 1; i++)
        {
            if (start[i] == 'X' && start[i + 1] == 'L')
            {
                start[i] = 'L';
                start[i + 1] = 'X';
            }
        }
        canTransform(start, end);
    }
    return 0;
}
*/

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    // Function to check if transformation is possible

    // Read the input strings

    char *start = readline();

    char *end = readline();

    // Invoke the function to check transformation possibility

    bool result = canTransform(start, end);

    // Print the result

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char *readline()
{
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char *data = malloc(alloc_length);

    while (true)
    {
        char *cursor = data + data_length;
        char *line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line)
        {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n')
        {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data)
        {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n')
    {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data)
        {
            data = '\0';
        }
    }
    else
    {
        data = realloc(data, data_length + 1);

        if (!data)
        {
            data = '\0';
        }
        else
        {
            data[data_length] = '\0';
        }
    }

    return data;
}
