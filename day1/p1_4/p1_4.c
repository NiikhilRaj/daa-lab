#include <stdio.h>

void EXCHANGE(int *p, int *q) {
    int t = *p;
    *p = *q;
    *q = t;
}

void ROTATE_RIGHT(int *a, int n) {
    for(int i=n-1;i>0;i--) {
        EXCHANGE(&a[i], &a[i-1]);
    }
}

int main() {
    FILE *input, *output;
    input = fopen("./input.txt", "r");
    int n;
    fscanf(input, "%d", &n);
    int arr[n];
    for(int i=0;i<n;i++) fscanf(input, "%d", &arr[i]);
    fclose(input);

    output = fopen("./output.txt", "w");
    fprintf(output, "Before ROTATE: ");
    for(int i=0;i<n;i++) fprintf(output, "%d ", arr[i]);
    fprintf(output, "\n");

    ROTATE_RIGHT(arr, 5);

    fprintf(output, "After ROTATE: ");
    for(int i=0;i<n;i++) fprintf(output, "%d ", arr[i]);
    fprintf(output, "\n");
    fclose(output);
    return 0;
}
