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
 * Complete the 'lengthOfLongestSubstring' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int lengthOfLongestSubstring(char *s)
{
    int len = strlen(s);
    if (len == 0)
    {
        return 0;
    }

    int max_substr_len = 0;
    for (int i = 0; i < len; i++)
    {
        int seen[128] = {0};
        int count = 0;

        for (int j = i; j < len; j++)
        {
            if (seen[(int)s[j]])
            {
                break;
            }
            seen[(int)s[j]] = 1;
            count++;

            if (count > max_substr_len)
            {
                max_substr_len = count;
            }
        }
    }
    return max_substr_len;
}
// {
//     int len = strlen(s);
//     int max_substr_len = 0;
//     for (int i = 0; i < len; i++)
//     {
//         char key = s[i];
//         int count = 1;
//         for (int j = i + 1; j < len; j++)
//         {
//             if (key != s[j])
//             {
//                 count++;
//             }
//             if (count > max_substr_len)
//             {
//                 max_substr_len = count;
//                 printf("%d", max_substr_len);
//             }
//             else
//             {
//                 break;
//             }
//         }
//     }
//     return max_substr_len;
// }

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    // Function to find the length of the longest substring without repeating characters

    // Read the input string

    char *s = readline();

    // Invoke the function and store the result

    int result = lengthOfLongestSubstring(s);

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
