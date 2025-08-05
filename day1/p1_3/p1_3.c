#include <stdio.h>

int main() {
    FILE *input, *output;
    input = fopen("./input.txt", "r");
    int n;
    fscanf(input, "%d", &n);
    int arr[n];
    for(int i=0;i<n;i++) fscanf(input, "%d", &arr[i]);
    fclose(input);

    output = fopen("./output.txt", "w");
    fprintf(output, "The content of the array: ");
    for(int i=0;i<n;i++) fprintf(output, "%d ", arr[i]);
    fprintf(output, "\n");

    int dup=0;
    int freq[n];
    for(int i=0;i<n;i++) freq[i]=0;
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            if(arr[i]==arr[j] && freq[j]==0) {
                dup++;
                freq[j]=1;
            }
        }
    }
    fprintf(output, "Total number of duplicate values = %d\n", dup);

    int max=0, most=arr[0];
    for(int i=0;i<n;i++) {
        int count=1;
        for(int j=i+1;j<n;j++) {
            if(arr[i]==arr[j]) count++;
        }
        if(count>max) { max=count; most=arr[i]; }
    }
    fprintf(output, "The most repeating element in the array = %d\n", most);
    fclose(output);
    return 0;
}
