#include<stdio.h>
#include<stdlib.h>

void convert(int n, char* b, int pos) {
    if (pos == 0) {
        return;
    }
    convert(n / 2, b, pos - 1);
    b[16 - pos] = (n % 2) + '0';
}

int main(int argc, char* argv[]) {
    int n, i, num, cnt = 0;
    FILE *f1, *f2;
    char str[100];
    
    n = atoi(argv[1]);
    
    f1 = fopen(argv[2], "r");
    f2 = fopen(argv[3], "w");
    
    while (cnt < n && fscanf(f1, "%d", &num) == 1) {
        char bin[17];
        
        for (i = 0; i < 16; i++) {
            bin[i] = '0';
        }
        bin[16] = '\0';
        
        if (num > 0) {
            convert(num, bin, 16);
        }
        
        fprintf(f2, "The binary equivalent of %d is %s\n", num, bin);
        cnt++;
    }
    
    fclose(f1);
    fclose(f2);
    
    f2 = fopen(argv[3], "r");
    printf("Content of the first %d decimal and their equivalent binary numbers:\n", cnt);
    while (fgets(str, 100, f2)) {
        printf("%s", str);
    }
    
    fclose(f2);
    return 0;
}