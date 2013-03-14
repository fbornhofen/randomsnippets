#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_VERTICES 8
#define MAX_EDGES MAX_VERTICES*MAX_VERTICES 
#define DIST_MAX 9999

#define UNVISITED 0
#define SEEN 1
#define VISITED 2

/* Queue */

typedef struct {
    int size;
    int capacity;
    void* data[MAX_EDGES];
    int head;
    int tail;
} Queue;

Queue* make_queue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->capacity = MAX_EDGES;
    q->size = 0;
    q->head = q->tail = 0;
    return q;
}

void queue_destroy(Queue* q)
{
    free(q);
}

int queue_enqueue(Queue* q, void* item)
{
    if (q->size == q->capacity) {
        return 0;
    }
    q->data[q->tail] = item;
    q->tail = (q->tail+1) % q->capacity;
    q->size++;
    return 1;
}

void* queue_dequeue(Queue* q)
{
    if (q->size == 0) {
        return NULL;
    }
    void* res = q->data[q->head];
    q->head = (q->head+1) % q->capacity;
    q->size--;
    return res;
}

/* Graph */

struct _Edge;

typedef struct {
    int label;
    struct _Edge* edges[MAX_EDGES];
    int n_edges;
    int mark;
    int distance;
} Vertex;

typedef struct _Edge {
    Vertex* v1;
    Vertex* v2;
    int weight;
} Edge;

Vertex* make_vertex(int label)
{
    Vertex* v = (Vertex*)malloc(sizeof(Vertex));
    v->n_edges = 0;
    v->mark = UNVISITED;
    v->distance = DIST_MAX;
    v->label = label;
    return v;
}

void vertex_add_edge(Vertex* v, Edge* e)
{
    v->edges[v->n_edges++] = e;
}

Edge* make_edge(Vertex* v1, Vertex* v2, int weight)
{
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->v1 = v1;
    e->v2 = v2;
    e->weight = weight;
    vertex_add_edge(v1, e);
    vertex_add_edge(v2, e);
    return e; 
}

Vertex* edge_opposite(Edge* e, Vertex* v)
{
    if (e->v1 == v) {
        return e->v2;
    } else if (e->v2 == v) {
        return e->v1;
    } else {
        return NULL;
    }
}


/*
 * BFS traversal of a graph to find the shortest distance
 * between two Vertices. 
 * Yes, it's slower than Dijkstra :).
 */
int distance(Vertex* from, Vertex* to)
{
    int i;
    Queue* q = make_queue();
    Vertex* v1, *v2;
    Edge* e;
    from->distance = 0;
    queue_enqueue(q, from);

    while (q->size > 0) {
        v1 = queue_dequeue(q);
        for (i = 0; i < v1->n_edges; i++) {
            e = v1->edges[i];
            v2 = edge_opposite(e, v1);
            if (v2->mark != VISITED) {
                if (v2->mark != SEEN) {
                    queue_enqueue(q, v2);
                    v2->mark = SEEN;
                }
                if (v2->distance > v1->distance + e->weight) {
                    v2->distance = v1->distance + e->weight;
                }
            }
        }
        v1->mark = VISITED;
        printf("visited v%d (%d)\n", v1->label, v1->distance);
    }
    queue_destroy(q);
    return to->distance;
}

int main(int argc, char** argv)
{
    Vertex* v1, *v2, *v3, *v4, *v5, *v6;
    Edge* e12, *e13, *e16, *e23, *e24, *e34, *e36, *e45, *e56;
    long i;
    Queue* q = make_queue();
   
    /* Sample graph from: http://upload.wikimedia.org/wikipedia/commons/5/57/Dijkstra_Animation.gif */
    v1 = make_vertex(1);
    v2 = make_vertex(2);
    v3 = make_vertex(3);
    v4 = make_vertex(4);
    v5 = make_vertex(5);
    v6 = make_vertex(6);

    e12 = make_edge(v1, v2, 7);
    e13 = make_edge(v1, v3, 9);
    e16 = make_edge(v1, v6, 14);
    e23 = make_edge(v2, v3, 10);
    e24 = make_edge(v2, v4, 15);
    e34 = make_edge(v3, v4, 11);
    e36 = make_edge(v3, v6, 2);
    e45 = make_edge(v4, v5, 6);
    e56 = make_edge(v5, v6, 9);

    printf("Distance between v1 and v5 is %d\n",
        distance(v1, v5)); 

    return 0;
}

