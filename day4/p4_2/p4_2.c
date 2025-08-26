#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int comparison_count = 0;

void quickSort(int arr[], int low, int high) {
	if (low < high) {
		int pivot = arr[high];
		int i = (low - 1);
		for (int j = low; j < high; j++) {
			comparison_count++;
			if (arr[j] < pivot) {
				i++;
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
		int temp = arr[i + 1];
		arr[i + 1] = arr[high];
		arr[high] = temp;
		int pi = i + 1;
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int readDataFromFile(const char* filename, int arr[]) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Error: Could not open file %s\n", filename);
		return -1;
	}
	int count = 0;
	while (fscanf(file, "%d", &arr[count]) == 1 && count < 1000) {
		count++;
	}
	fclose(file);
	return count;
}

void writeDataToFile(const char* filename, int arr[], int size) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error: Could not create file %s\n", filename);
		return;
	}
	for (int i = 0; i < size; i++) {
		fprintf(file, "%d ", arr[i]);
	}
	fprintf(file, "\n");
	fclose(file);
}

void displayArray(int arr[], int size, int limit) {
	int display_count = (size < limit) ? size : limit;
	for (int i = 0; i < display_count; i++) {
		printf("%d ", arr[i]);
	}
	if (size > limit) {
		printf("... (showing first %d elements)", limit);
	}
	printf("\n");
}

void processData(const char* inputFile, const char* outputFile, const char* dataType) {
	int arr[1000];
	int original[1000];
	int size = readDataFromFile(inputFile, arr);
	if (size == -1) {
		return;
	}
	printf("\nProcessing %s Data...\n", dataType);
	printf("Number of elements: %d\n", size);
	for (int i = 0; i < size; i++) {
		original[i] = arr[i];
	}
	printf("Before Sorting: ");
	displayArray(original, size, 20);
	comparison_count = 0;
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	quickSort(arr, 0, size - 1);
	clock_gettime(CLOCK_MONOTONIC, &end);
	long long execution_time = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
	printf("After Sorting: ");
	displayArray(arr, size, 20);
	writeDataToFile(outputFile, arr, size);
	printf("Number of Comparisons: %d\n", comparison_count);
	printf("Execution Time: %lld nanoseconds\n", execution_time);
	printf("Data sorted and saved to %s\n", outputFile);
}

int main() {
	int choice;
	printf("MAIN MENU (QUICK SORT)\n");
	printf("1. Ascending Data\n");
	printf("2. Descending Data\n");
	printf("3. Random Data\n");
	printf("4. ERROR (EXIT)\n");
	while (1) {
		printf("\nEnter option: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				processData("inAsce.dat", "outQuickAsce.dat", "Ascending");
				break;
			case 2:
				processData("inDesc.dat", "outQuickDesc.dat", "Descending");
				break;
			case 3:
				processData("inRand.dat", "outQuickRand.dat", "Random");
				break;
			case 4:
				printf("Exiting...\n");
				exit(0);
			default:
				printf("Invalid option! Please enter 1-4.\n");
		}
	}
	return 0;
}
