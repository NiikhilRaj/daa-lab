#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
} ITEM;

void swap(ITEM *a, ITEM *b) {
    ITEM temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(ITEM arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    
    if (l < n && arr[l].profit_weight_ratio < arr[largest].profit_weight_ratio)
        largest = l;
    if (r < n && arr[r].profit_weight_ratio < arr[largest].profit_weight_ratio)
        largest = r;
    
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(ITEM arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    for (int i = n-1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    
    ITEM *items = (ITEM*)malloc(n * sizeof(ITEM));
    
    for (int i = 0; i < n; i++) {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }
    
    float capacity;
    printf("Enter the capacity of knapsack:");
    scanf("%f", &capacity);
    
    heapSort(items, n);
    
    float max_profit = 0.0;
    float *amount_taken = (float*)calloc(n, sizeof(float));
    float remaining_capacity = capacity;
    
    for (int i = 0; i < n && remaining_capacity > 0; i++) {
        if (items[i].item_weight <= remaining_capacity) {
            amount_taken[i] = 1.0;
            max_profit += items[i].item_profit;
            remaining_capacity -= items[i].item_weight;
        } else {
            amount_taken[i] = remaining_capacity / items[i].item_weight;
            max_profit += items[i].item_profit * amount_taken[i];
            remaining_capacity = 0;
        }
    }
    
    printf("Item No    profit    Weight     Amount to be taken\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-10f %-10f %-10f\n", 
               items[i].item_id, items[i].item_profit, 
               items[i].item_weight, amount_taken[i]);
    }
    printf("Maximum profit: %f\n", max_profit);
    
    free(items);
    free(amount_taken);
    return 0;
}