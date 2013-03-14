#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long q_item_t;

typedef struct {
    q_item_t* items;
    long size;
    long capacity;    
    long head;
    long tail;
} Queue;

Queue* make_queue(long capacity)
{
    Queue* res = (Queue*)malloc(sizeof(Queue));
    res->items = (q_item_t*)malloc(capacity*sizeof(q_item_t));
    res->size = 0;
    res->head = 0;
    res->tail = 0;
    res->capacity = capacity;
}

int queue_enqueue(Queue* q, q_item_t item)
{
    if (q->size == q->capacity) {
        return 0;
    }
    q->size++;
    q->items[q->tail] = item;
    q->tail = (q->tail + 1) % q->capacity;
    return 1;
}

q_item_t queue_dequeue(Queue* q)
{
    q_item_t res;
    if (q->size == 0) {
        exit(-1);
    }
    q->size--;
    res = q->items[q->head];
    q->head = (q->head + 1) % q->capacity;
    return res;
}

void queue_destroy(Queue* q)
{
    free(q->items);
    free(q);
}

void radix_sort(Queue* q)
{
    Queue* q0 = make_queue(q->capacity);
    Queue* q1 = make_queue(q->capacity);

    int key_len = sizeof(q_item_t) * 8;
    int i, j;
    int n_items = q->size;
    q_item_t cur;
    
    for (i = 0; i < key_len; i++) {
        while (q->size) {
            cur = queue_dequeue(q);
            if (cur & (1<<i)) {
                queue_enqueue(q1, cur);
            } else {
                queue_enqueue(q0, cur);
            }
        }
        while (q0->size) {
            queue_enqueue(q, queue_dequeue(q0));
        }
        while (q1->size) {
            queue_enqueue(q, queue_dequeue(q1));
        }
    }

    queue_destroy(q0);
    queue_destroy(q1);
}


int main(void)
{
    Queue* q = make_queue(1024);
    int i;
    int n_elems = 32;
    q_item_t tmp;
    
    srand(time(0));
    for (i = 0; i < n_elems; i++) {
        tmp = rand() % 100;
        queue_enqueue(q, tmp);
        printf("%ld ", tmp);
    }
    printf("\n");
    
    radix_sort(q);

    for (i = 0; i < n_elems; i++) {
        printf("%ld ", queue_dequeue(q));
    }
    printf("\n");
    queue_destroy(q);

    return 0;
}

