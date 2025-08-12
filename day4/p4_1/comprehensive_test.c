#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int comparison_count = 0;

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    
    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Merge the temporary arrays back into arr[left..right]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    
    while (i < n1 && j < n2) {
        comparison_count++; // Count comparison
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void generateAscendingData(const char* filename, int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create file %s\n", filename);
        return;
    }
    
    for (int i = 1; i <= size; i++) {
        fprintf(file, "%d ", i * 10);
    }
    fprintf(file, "\n");
    fclose(file);
}

void generateDescendingData(const char* filename, int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create file %s\n", filename);
        return;
    }
    
    for (int i = size; i >= 1; i--) {
        fprintf(file, "%d ", i * 10);
    }
    fprintf(file, "\n");
    fclose(file);
}

void generateRandomData(const char* filename, int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create file %s\n", filename);
        return;
    }
    
    // Create array with numbers 1 to size
    int* numbers = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        numbers[i] = (i + 1) * 10;
    }
    
    // Shuffle the array using Fisher-Yates algorithm
    srand(42); // Fixed seed for reproducible results
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
    
    // Write to file
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", numbers[i]);
    }
    fprintf(file, "\n");
    
    free(numbers);
    fclose(file);
}

int readDataFromFile(const char* filename, int** arr) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return -1;
    }
    
    // Count numbers in file first
    int count = 0;
    int temp;
    while (fscanf(file, "%d", &temp) == 1) {
        count++;
    }
    
    // Allocate memory
    *arr = malloc(count * sizeof(int));
    if (*arr == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return -1;
    }
    
    // Read data again
    rewind(file);
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d", &(*arr)[i]);
    }
    
    fclose(file);
    return count;
}

long long testMergeSort(const char* inputFile, const char* outputFile, const char* dataType, int size) {
    int* arr;
    
    // Read data from file
    int actualSize = readDataFromFile(inputFile, &arr);
    if (actualSize == -1) {
        return -1;
    }
    
    printf("Testing %s data with %d elements...\n", dataType, actualSize);
    
    // Reset comparison counter
    comparison_count = 0;
    
    // Measure execution time
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Perform merge sort
    mergeSort(arr, 0, actualSize - 1);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    // Calculate execution time in nanoseconds
    long long execution_time = (end.tv_sec - start.tv_sec) * 1000000000LL + 
                              (end.tv_nsec - start.tv_nsec);
    
    // Write sorted data to output file
    FILE* outFile = fopen(outputFile, "w");
    if (outFile != NULL) {
        for (int i = 0; i < actualSize; i++) {
            fprintf(outFile, "%d ", arr[i]);
        }
        fprintf(outFile, "\n");
        fclose(outFile);
    }
    
    printf("  Comparisons: %d, Time: %lld ns\n", comparison_count, execution_time);
    
    free(arr);
    return execution_time;
}

int main() {
    FILE* resultFile = fopen("merge_sort_results.txt", "w");
    if (resultFile == NULL) {
        printf("Error: Could not create results file\n");
        return 1;
    }
    
    // Write header
    fprintf(resultFile, "MERGE SORT PERFORMANCE ANALYSIS\n");
    fprintf(resultFile, "================================\n");
    fprintf(resultFile, "Test conducted on: %s", __DATE__);
    fprintf(resultFile, "\n\n");
    fprintf(resultFile, "%-12s %-8s %-12s %-15s\n", "Data Type", "Size", "Comparisons", "Time (ns)");
    fprintf(resultFile, "%-12s %-8s %-12s %-15s\n", "---------", "----", "-----------", "---------");
    
    printf("MERGE SORT COMPREHENSIVE TESTING\n");
    printf("=================================\n\n");
    
    // Test sizes
    int sizes[] = {350, 5000, 10000};
    char* sizeNames[] = {"Default", "5K", "10K"};
    char* dataTypes[] = {"Ascending", "Descending", "Random"};
    
    for (int s = 0; s < 3; s++) {
        int size = sizes[s];
        printf("Testing with %s (%d elements):\n", sizeNames[s], size);
        printf("------------------------------\n");
        
        // Generate data files for current size
        char ascFile[50], descFile[50], randFile[50];
        sprintf(ascFile, "inAsce_%d.dat", size);
        sprintf(descFile, "inDesc_%d.dat", size);
        sprintf(randFile, "inRand_%d.dat", size);
        
        generateAscendingData(ascFile, size);
        generateDescendingData(descFile, size);
        generateRandomData(randFile, size);
        
        // Test each data type
        char* inputFiles[] = {ascFile, descFile, randFile};
        char* outputFiles[3];
        char ascOut[50], descOut[50], randOut[50];
        sprintf(ascOut, "outMergeAsce_%d.dat", size);
        sprintf(descOut, "outMergeDesc_%d.dat", size);
        sprintf(randOut, "outMergeRand_%d.dat", size);
        outputFiles[0] = ascOut;
        outputFiles[1] = descOut;
        outputFiles[2] = randOut;
        
        for (int t = 0; t < 3; t++) {
            long long time = testMergeSort(inputFiles[t], outputFiles[t], dataTypes[t], size);
            if (time != -1) {
                fprintf(resultFile, "%-12s %-8s %-12d %-15lld\n", 
                       dataTypes[t], sizeNames[s], comparison_count, time);
            }
        }
        printf("\n");
    }
    
    // Write summary statistics
    fprintf(resultFile, "\n\nSUMMARY:\n");
    fprintf(resultFile, "--------\n");
    fprintf(resultFile, "• Merge Sort has O(n log n) time complexity\n");
    fprintf(resultFile, "• Random data typically requires more comparisons than sorted data\n");
    fprintf(resultFile, "• Execution time increases with data size\n");
    fprintf(resultFile, "• Algorithm is stable and works well for all input patterns\n");
    
    fclose(resultFile);
    
    printf("Testing completed! Results saved to 'merge_sort_results.txt'\n");
    printf("Generated files:\n");
    printf("- Input files: inAsce_*.dat, inDesc_*.dat, inRand_*.dat\n");
    printf("- Output files: outMergeAsce_*.dat, outMergeDesc_*.dat, outMergeRand_*.dat\n");
    printf("- Results file: merge_sort_results.txt\n");
    
    return 0;
}
