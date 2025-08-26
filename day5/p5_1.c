#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char name[50];
    int age;
    int height;
    int weight;
};

void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct person heap[], int n, int i) {
    int smallest = i, l = 2*i+1, r = 2*i+2;
    if (l < n && heap[l].age < heap[smallest].age) smallest = l;
    if (r < n && heap[r].age < heap[smallest].age) smallest = r;
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

void maxHeapify(struct person heap[], int n, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if (l < n && heap[l].weight > heap[largest].weight) largest = l;
    if (r < n && heap[r].weight > heap[largest].weight) largest = r;
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, n, largest);
    }
}

void buildMinHeap(struct person heap[], int n) {
    for (int i = n/2-1; i >= 0; i--)
        minHeapify(heap, n, i);
}

void buildMaxHeap(struct person heap[], int n) {
    for (int i = n/2-1; i >= 0; i--)
        maxHeapify(heap, n, i);
}

void display(struct person heap[], int n) {
    printf("Id Name Age Height Weight\n");
    for (int i = 0; i < n; i++)
        printf("%d %s %d %d %d\n", heap[i].id, heap[i].name, heap[i].age, heap[i].height, heap[i].weight);
}

int main() {
    struct person *arr = NULL;
    int n = 0, heapType = 0, choice;
    char filename[100];
    while (1) {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n2. Create a Min-heap based on the age\n3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n5. Insert a new person into the Min-heap\n6. Delete the oldest person\n7. Exit\n");
        printf("Enter option: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter filename: ");
            scanf("%s", filename);
            FILE *fp = fopen(filename, "r");
            if (!fp) { printf("File not found!\n"); continue; }
            fscanf(fp, "%d", &n);
            arr = (struct person*)malloc(n * sizeof(struct person));
            for (int i = 0; i < n; i++)
                fscanf(fp, "%d %s %d %d %d", &arr[i].id, arr[i].name, &arr[i].age, &arr[i].height, &arr[i].weight);
            fclose(fp);
            buildMinHeap(arr, n);
            heapType = 1;
            printf("Data loaded and min-heap created based on age.\n");
            display(arr, n);
        } else if (choice == 2) {
            if (!arr) { printf("Load data first.\n"); continue; }
            buildMinHeap(arr, n);
            heapType = 1;
            printf("Min-heap created based on age.\n");
        } else if (choice == 3) {
            if (!arr) { printf("Load data first.\n"); continue; }
            buildMaxHeap(arr, n);
            heapType = 2;
            printf("Max-heap created based on weight.\n");
        } else if (choice == 4) {
            if (!arr || heapType != 1) { printf("Create min-heap first.\n"); continue; }
            printf("Weight of youngest student: %.2f kg\n", arr[0].weight * 0.453592);
        } else if (choice == 5) {
            if (!arr || heapType != 1) { printf("Create min-heap first.\n"); continue; }
            arr = realloc(arr, (n+1)*sizeof(struct person));
            printf("Enter id name age height weight: ");
            scanf("%d %s %d %d %d", &arr[n].id, arr[n].name, &arr[n].age, &arr[n].height, &arr[n].weight);
            int i = n++;
            while (i && arr[(i-1)/2].age > arr[i].age) {
                swap(&arr[i], &arr[(i-1)/2]);
                i = (i-1)/2;
            }
            printf("Person inserted into min-heap.\n");
        } else if (choice == 6) {
            if (!arr || heapType != 1) { printf("Create min-heap first.\n"); continue; }
            if (n == 0) { printf("Heap is empty.\n"); continue; }
            printf("Deleted person: %d %s %d %d %d\n", arr[0].id, arr[0].name, arr[0].age, arr[0].height, arr[0].weight);
            arr[0] = arr[--n];
            minHeapify(arr, n, 0);
        } else if (choice == 7) {
            free(arr);
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
    return 0;
}