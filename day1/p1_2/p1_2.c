#include <stdio.h>

int main()
{
    FILE *input, *output;
    input = fopen("./input.txt", "r");

    int n=5;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        fscanf(input, "%d", &arr[i]);
    }
    fclose(input);

    for (int i = 1; i < n; i++)
    {
        arr[i] = arr[i] + arr[i - 1];
        printf("Prefix sum up to index %d: %d\n", i, arr[i]);
    }

    output = fopen("./output.txt", "w");
    fprintf(output, "Prefix sum array: ");
    for (int i = 0; i < n; i++)
    {
        fprintf(output, "%d ", arr[i]);
    }
    fclose(output);

    return 0;
}