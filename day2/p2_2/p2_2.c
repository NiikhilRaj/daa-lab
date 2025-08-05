#include <stdio.h>
#include <stdlib.h>


int calculategcd(int a, int b) {
    if (a < b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if (b == 0)
        return a;
    return calculategcd(b, a % b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        printf("Error opening input file.\n");
        return 1;
    }
    FILE *fout = fopen(argv[2], "w");
    if (!fout) {
        printf("Error opening output file.\n");
        fclose(fin);
        return 1;
    }

    int a, b;
    while (fscanf(fin, "%d %d", &a, &b) == 2) {
        int result = calculategcd(a, b);
        fprintf(fout, "The GCD of %d and %d is %d\n", a, b, result);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}