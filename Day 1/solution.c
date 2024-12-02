#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// INPUT FILE
void *handle_input(int *input_array_int1, int *input_array_int2)
{
    FILE *fptr = fopen("input.txt", "r");
    if (fptr == NULL)
    {
        return NULL;
    }
    
    char *lineptr = malloc(sizeof(char) * 200);
    char *input_array_char = (char *)malloc(5 * sizeof(char));

    int count = 0;
    while (fgets(input_array_char, 200, fptr) > 0)
    {
        char *copy = (char *)malloc(sizeof(char) * (strlen(input_array_char) + 1));
        strcpy(copy, input_array_char);
        input_array_int1[count] = atoi(strtok(input_array_char, "   "));
        input_array_int2[count] = atoi(strtok(NULL, "   "));
        count++;
    }
    fclose(fptr);
    return NULL;
}

void swap(int *array, int first_index, int second_index)
{
    int tmp = array[first_index];
    array[first_index] = array[second_index];
    array[second_index] = tmp;
}

void insertion_sort(int *array, int length)
{
    for (int i = 1; i < length; i++)
    {
        for (int j = i; j > 0 && array[j] < array[j - 1]; j--)
        {
            swap(array, j, j - 1);
        }
    }
}

int check_sort(int *array, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            printf("\n\nSort failed\n\n");
            return 0;
        }
    }
    printf("\n\nSort successful!\n\n");
    return 1;
}

/* PART ONE
int main() {
    int *input_array_int1 = (int *)malloc(1000 * sizeof(int));
    int *input_array_int2 = (int *)malloc(1000 * sizeof(int));
    handle_input(input_array_int1, input_array_int2);
    insertion_sort(input_array_int1, 1000);
    insertion_sort(input_array_int2, 1000);
    // check_sort(input_array_int1, 1000);

    int tot_dist = 0;
    for (int i = 0; i < 1000; i++) {
        tot_dist = tot_dist + abs(input_array_int1[i] - input_array_int2[i]);
    }
    printf("Total distance: %d\n", tot_dist);
}
*/

int main () {
    
}