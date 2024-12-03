#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *handle_input(char **all_reports)
{
    FILE *fptr = fopen("input.txt", "r");
    if (fptr == NULL)
    {
        return NULL;
    }

    char *lineptr = malloc(sizeof(char) * 200);
    char *input_array_char = (char *)malloc(20 * sizeof(char));

    int count = 0;
    while (fgets(input_array_char, 200, fptr) > 0)
    {
        char *copy = (char *)malloc(sizeof(char) * (strlen(input_array_char) + 1));
        strcpy(copy, input_array_char);
        all_reports[count] = copy;
        // printf("%s\n", copy);
        count++;
    }
    fclose(fptr);
    return NULL;
}

int *report_from_char_to_int(char *report_char)
{
    int size = ((strlen(report_char) + 1) / 3) + 1;
    int *report_int = (int *)malloc(size * sizeof(int));

    report_int[0] = atoi(strtok(report_char, " "));
    for (int i = 1; i < size; i++)
    {
        report_int[i] = atoi(strtok(NULL, " "));
    }
    report_int[size] = 0;
    return report_int;
}

void print_report(int *report)
{
    printf("Report: ");
    for (int i = 0; report[i] != 0; i++)
    {
        printf("%d - ", report[i]);
    }
    printf("\n");
}

int ascending(int *report)
{
    int is_correct = 1;

    for (int i = 1; report[i] > 0; i++)
    {
        if (report[i - 1] > report[i])
        {
            is_correct = 0;
        }
    }
    return is_correct;
}

int decending(int *report)
{
    int is_correct = 1;

    for (int i = 1; report[i] > 0; i++)
    {
        if (report[i - 1] < report[i])
        {
            is_correct = 0;
        }
    }
    return is_correct;
}

int check_distances(int ascdesc, int *report)
{
    // ascdesc: 1 = ascending & 2 = decending
    int is_correct = 1;
    if (ascdesc == 1)
    {
        for (int i = 1; report[i] != 0; i++)
        {
            if ((report[i] - report[i - 1]) > 3 || (report[i] - report[i - 1]) <= 0)
            {
                is_correct = 0;
            }
        }
    }
    if (ascdesc == 2)
    {
        for (int i = 1; report[i] != 0; i++)
        {
            if ((report[i - 1] - report[i]) > 3 || (report[i - 1] - report[i]) <= 0)
            {
                is_correct = 0;
            }
        }
    }
    return is_correct;
}

int *remove_one(int *report, int index_to_remove)
{
    int *short_report = (int *)malloc(8 * sizeof(int));

    int i = 0;
    while (report[i] != 0)
    {
        if (i < index_to_remove)
        {
            short_report[i] = report[i];
        }
        if (i > index_to_remove)
        {
            short_report[i - 1] = report[i];
        }
        i++;
    }
    short_report[i - 1] = 0;
    // printf("short rep\n");
    // print_report(short_report);
    // printf("\n");
    return short_report;
}

int safe_counter(char **all_reports, int safe_count)
{
    handle_input(all_reports);
    for (int i = 0; i < 1000; i++)
    {
        int *report = report_from_char_to_int(all_reports[i]);
        if (ascending(report) == 1)
        {
            safe_count = safe_count + check_distances(1, report);
        }
        if (decending(report) == 1)
        {
            safe_count = safe_count + check_distances(2, report);
        }
    }
    return safe_count;
}

int is_safe(int *report)
{
    if (ascending(report) == 1)
    {
        return check_distances(1, report);
    }
    else if (decending(report) == 1)
    {
        return check_distances(2, report);
    }
    else
    {
        return 0;
    }
}

int main()
{
    /*  PART ONE
        char **all_reports = (char **)malloc(1000 * (sizeof(char)*20));
        int safe_count = 0;
        printf("Nmber of safe reports:\n%d", safe_counter(all_reports, safe_count));
    */

    char **all_reports = (char **)malloc(1000 * (sizeof(char) * 10));
    int safe_count = 0;
    handle_input(all_reports);
    for (int i = 0; i < 1000; i++)
    {
        int *report = report_from_char_to_int(all_reports[i]);
        if (is_safe(report) == 1)
        {
            safe_count++;
        }
        else
        {
            for (int j = 0; report[j] != 0; j++)
            {
                if (is_safe(remove_one(report, j)) == 1)
                {
                    safe_count++;
                    break;
                }
            }
        }
    }
    printf("Number of safe reports: %d", safe_count);

}

/* #################################
   ########### TESTING #############
   #################################

    int test_report_a[] = {2, 8, 5, 6, 0};
    int test_report_d[] = {10, 7, 4, 1, 0};

    printf("ascending\n");
    printf("sorted: %d\n", ascending(test_report_a));
    printf("distances: %d\n", check_distances(1, test_report_a));

    printf("\ndescending\n");
    printf("sorted: %d\n", decending(test_report_d));
    printf("distances: %d\n", check_distances(2, test_report_d));
    printf("\n\n");



    int test_report_a[] = {2, 4, 7, 6, 0};
    if (is_safe(test_report_a) == 1) printf("It is safe\n");
    else {
        for (int i = 0; test_report_a[i] != 0; i++) {
            printf("Result of safe: %d\n", is_safe(remove_one(test_report_a, i)));
        }
    }

    printf("incorrect\n");
    print_report(test_report_a);
    printf("sorted: %d\n", ascending(test_report_a));
    printf("distances: %d\n", check_distances(1, test_report_a));
    int *new_test_report_a = remove_one(test_report_a, 1);

    printf("correct\n");
    print_report(new_test_report_a);
    printf("sorted: %d\n", ascending(new_test_report_a));
    printf("distances: %d\n", check_distances(1, new_test_report_a));
*/