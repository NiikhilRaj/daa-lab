#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparisons = 0;

void insertionSort(int arr[], int n) {
    int i, key, j;
    comparisons = 0;
    
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            comparisons++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        
        if (j >= 0) {
            comparisons++;
        }
        
        arr[j + 1] = key;
    }
}

int readFromFile(const char* filename, int arr[], int maxSize) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return -1;
    }
    
    int count = 0;
    while (count < maxSize && fscanf(file, "%d", &arr[count]) == 1) {
        count++;
    }
    
    fclose(file);
    return count;
}

void writeToFile(const char* filename, int arr[], int n) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot create file %s\n", filename);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
        if ((i + 1) % 10 == 0) { 
            fprintf(file, "\n");
        }
    }
    
    fclose(file);
}

void displayFileContent(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }
    
    int num;
    int count = 0;
    while (fscanf(file, "%d", &num) == 1) {
        printf("%d ", num);
        count++;
        if (count % 15 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    
    fclose(file);
}

const char* determineScenario(int n, int actualComparisons) {
    int bestCase = n - 1;
    
    int worstCase = (n * (n - 1)) / 2;
    
    int avgCase = worstCase / 4;
    
    if (actualComparisons <= bestCase + (bestCase * 0.1)) {
        return "Best Case";
    } else if (actualComparisons >= worstCase - (worstCase * 0.1)) {
        return "Worst Case";
    } else {
        return "Average Case";
    }
}

void createSampleFiles() {
    FILE* file = fopen("inAsce.dat", "w");
    if (file != NULL) {
        for (int i = 10; i <= 4000; i += 10) {
            fprintf(file, "%d ", i);
            if ((i / 10) % 10 == 0) fprintf(file, "\n");
        }
        fclose(file);
    }
    
    file = fopen("inDesc.dat", "w");
    if (file != NULL) {
        for (int i = 4000; i >= 10; i -= 10) {
            fprintf(file, "%d ", i);
            if ((4010 - i) / 10 % 10 == 0) fprintf(file, "\n");
        }
        fclose(file);
    }
    
    file = fopen("inRand.dat", "w");
    if (file != NULL) {
        int random_data[] = {55, 66, 33, 11, 44, 88, 22, 77, 99, 15, 
                           234, 123, 456, 789, 321, 654, 987, 147, 258, 369,
                           500, 400, 300, 200, 100, 600, 700, 800, 900, 150,
                           275, 425, 575, 325, 475, 625, 175, 725, 875, 125};
        
        for (int i = 0; i < 40; i++) {
            fprintf(file, "%d ", random_data[i % 40]);
            if ((i + 1) % 10 == 0) fprintf(file, "\n");
        }
        
        for (int i = 1000; i < 1360; i += 3) {
            fprintf(file, "%d ", i);
            if ((i - 997) % 30 == 0) fprintf(file, "\n");
        }
        
        fclose(file);
    }
}

int main() {
    int choice;
    int arr[1000]; 
    int n; 
    const char* inputFile;
    const char* outputFile;
    
    printf("Creating sample input files...\n");
    createSampleFiles();
    printf("Sample files created successfully!\n\n");
    
    do {
        // Display menu
        printf("        MAIN MENU (INSERTION SORT)        \n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. ERROR (EXIT)\n");
        printf("Enter option: ");
        scanf("%d", &choice);
        printf("\n");
        
        switch (choice) {
            case 1:
                inputFile = "inAsce.dat";
                outputFile = "outInsAsce.dat";
                printf("Processing Ascending Data...\n");
                break;
                
            case 2:
                inputFile = "inDesc.dat";
                outputFile = "outInsDesc.dat";
                printf("Processing Descending Data...\n");
                break;
                
            case 3:
                inputFile = "inRand.dat";
                outputFile = "outInsRand.dat";
                printf("Processing Random Data...\n");
                break;
                
            case 4:
                printf("Exiting program...\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please select 1-4.\n\n");
                continue;
        }
        
        n = readFromFile(inputFile, arr, 1000);
        if (n == -1) {
            printf("Failed to read from file. Please check if file exists.\n\n");
            continue;
        }
        
        printf("Number of elements read: %d\n\n", n);
        
        printf("Before Sorting:\n");
        printf("Content of the input file (%s):\n", inputFile);
        displayFileContent(inputFile);
        printf("\n");
        
        insertionSort(arr, n);
        
        writeToFile(outputFile, arr, n);
        
        printf("After Sorting:\n");
        printf("Content of the output file (%s):\n", outputFile);
        displayFileContent(outputFile);
        printf("\n");
        
        printf("           SORTING STATISTICS              \n");
        printf("Number of Comparisons: %d\n", comparisons);
        printf("Actual Scenario: %s\n", determineScenario(n, comparisons));
        
        printf("Press Enter to continue...");
        getchar(); 
        getchar(); 
        printf("\n");
        
    } while (choice != 4);
    
    return 0;
}