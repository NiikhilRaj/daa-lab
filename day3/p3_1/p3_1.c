#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    FILE *inp = fopen("input.txt", "r");
    int n;
    fscanf(inp, "%d", &n);
    int copy = n;
    int arr[n];
    while (copy > 0) {
        int num;
        if (fscanf(inp, "%d", &num) != 1) {
            break;
        }
        arr[copy - 1] = num;
        copy--;
    }
    fclose(inp);


    clock_t start, end;
    double cpu_time_used;
    start = clock();
    insertionSort(arr, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by insertionSort: %f seconds\n", cpu_time_used);

    FILE *out = fopen("output.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(out, "%d\n", arr[i]);
    }
    fclose(out);
    return 0;
}