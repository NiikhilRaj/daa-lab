#include <stdio.h>

int main()
{
    FILE *fp1, *fp2;
    fp1 = fopen("./input.txt", "r");
    fp2 = fopen("./output.txt", "w");

    int n = 10;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        fscanf(fp1, "%d", &arr[i]);
    }
    fclose(fp1);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                // swap
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    fprintf(fp2, "Second largest element: %d", arr[n - 2]);
    fprintf(fp2, "\nSecond smallest element: %d", arr[1]);
    fclose(fp2);

    return 0;
}