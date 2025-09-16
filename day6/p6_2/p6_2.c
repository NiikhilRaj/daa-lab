#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SYMBOL {
    char alphabet;
    int frequency;
    struct SYMBOL* left;
    struct SYMBOL* right;
} SYMBOL;

typedef struct {
    SYMBOL** array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (SYMBOL**)malloc(capacity * sizeof(SYMBOL*));
    return heap;
}

void swap(SYMBOL** a, SYMBOL** b) {
    SYMBOL* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if (left < heap->size && heap->array[left]->frequency < heap->array[smallest]->frequency)
        smallest = left;
    
    if (right < heap->size && heap->array[right]->frequency < heap->array[smallest]->frequency)
        smallest = right;
    
    if (smallest != idx) {
        swap(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

int isSizeOne(MinHeap* heap) {
    return (heap->size == 1);
}

SYMBOL* extractMin(MinHeap* heap) {
    SYMBOL* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    --heap->size;
    minHeapify(heap, 0);
    return temp;
}

void insertMinHeap(MinHeap* heap, SYMBOL* node) {
    ++heap->size;
    int i = heap->size - 1;
    
    while (i && node->frequency < heap->array[(i - 1) / 2]->frequency) {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = node;
}

void buildMinHeap(MinHeap* heap) {
    int n = heap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(heap, i);
}

SYMBOL* createNode(char alphabet, int frequency) {
    SYMBOL* node = (SYMBOL*)malloc(sizeof(SYMBOL));
    node->alphabet = alphabet;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

SYMBOL* buildHuffmanTree(char alphabets[], int frequencies[], int size) {
    SYMBOL *left, *right, *top;
    
    MinHeap* heap = createMinHeap(size);
    
    for (int i = 0; i < size; ++i) {
        heap->array[i] = createNode(alphabets[i], frequencies[i]);
    }
    heap->size = size;
    buildMinHeap(heap);
    
    while (!isSizeOne(heap)) {
        left = extractMin(heap);
        right = extractMin(heap);
        
        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        
        insertMinHeap(heap, top);
    }
    
    return extractMin(heap);
}

void inOrderTraversal(SYMBOL* root) {
    if (root) {
        inOrderTraversal(root->left);
        if (root->alphabet != '$') {
            printf("%c  ", root->alphabet);
        }
        inOrderTraversal(root->right);
    }
}

int main() {
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);
    
    char* alphabets = (char*)malloc(n * sizeof(char));
    int* frequencies = (int*)malloc(n * sizeof(int));
    
    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++) {
        scanf(" %c", &alphabets[i]);
    }
    
    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &frequencies[i]);
    }
    
    SYMBOL* root = buildHuffmanTree(alphabets, frequencies, n);
    
    printf("In-order traversal of the tree (Huffman): ");
    inOrderTraversal(root);
    printf("\n");
    
    free(alphabets);
    free(frequencies);
    return 0;
}