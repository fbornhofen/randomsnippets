#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EXAMPLE_N 32 

/* heap */

typedef int heap_data_t;
typedef struct {
    heap_data_t* data;
    int size;
    int capacity;  
} Heap;

Heap* make_heap(int capacity)
{
    Heap* res = malloc(sizeof(Heap));
    res->size = 0;
    res->capacity = capacity + 1;
    res->data = (int*)malloc(res->capacity * sizeof(heap_data_t));
    res->data[0] = 0xDEADBEEF;
    return res;
}

void heap_destroy(Heap* h) 
{
    free(h->data);
    free(h);
}

void heap_swap(Heap* h, int idx1, int idx2)
{
    heap_data_t tmp = h->data[idx1];
    h->data[idx1] = h->data[idx2];
    h->data[idx2] = tmp;
}

void heap_sink(Heap* h, int idx)
{
    int branch = 0;
    if (2*idx <= h->size && 
            h->data[2*idx] < h->data[idx]) {
        if (2*idx+1 <= h->size && 
                h->data[2*idx+1] < h->data[2*idx]) {
            branch = 2*idx+1;
        } else {
            branch = 2*idx;
        }
    } else {
        if (2*idx+1 <= h->size && 
                h->data[2*idx+1] < h->data[idx]) {
            branch = 2*idx+1;
        }
    }
    if (branch) {
        heap_swap(h, idx, branch);
        heap_sink(h, branch);
    }
}

void heap_bubble(Heap* h, int idx)
{
    if (idx <= 1) {
        return;
    }
    if (h->data[idx] < h->data[idx/2]) {
        heap_swap(h, idx, idx/2);
        heap_bubble(h, idx/2);
    }
}

heap_data_t heap_pop(Heap* h)
{
    heap_data_t res;
    if (h->size == 0) {
        exit(-10); 
    }
    res = h->data[1]; 
    heap_swap(h, 1, h->size);
    h->size--;
    heap_sink(h, 1);
    return res;
}

void heap_push(Heap* h, heap_data_t item)
{
    if (h->size == h->capacity) {
        fprintf(stderr, 
                "heap can hold no more than %d elements.\n", 
                h->capacity);
        exit(-11);
    }
    h->size++;
    h->data[h->size] = item;
    heap_bubble(h, h->size);
}

void heap_print(Heap* h)
{
    int i;
    printf("[");
    for (i = 1; i <= h->size; i++) {
        printf("%d ", h->data[i]);
    }
    printf("]\n");
}

/* binary search */

int binary_search(heap_data_t val, heap_data_t* array, int l, int r)
{
    int m = (l+r) / 2;
    if (array[m] == val) {
        return m;
    }
    if (l >= r) {
        return -1;
    }
    if (val < array[m]) {
        return binary_search(val, array, l, m);
    } else {
        return binary_search(val, array, m+1, r);
    }
}

int main(void)
{
    Heap* h = make_heap(EXAMPLE_N);
    heap_data_t* array = (heap_data_t*)malloc(EXAMPLE_N*sizeof(heap_data_t));
    int i;
    int val;
    srand(time(0));
    for (i = 0; i < EXAMPLE_N; i++) {
        heap_push(h, rand() % 100);
    }
    heap_print(h);
    for (i = 0; i < EXAMPLE_N; i++) {
        array[i] = heap_pop(h);
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("search for a value in the now sorted array:\n");
    scanf("%d", &val);
    printf("%d is at pos %d\n", 
        val, 
        binary_search(val, array, 0, EXAMPLE_N-1));
    free(array);
    return 0;
}

