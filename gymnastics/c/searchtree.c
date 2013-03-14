#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _Node {
    struct _Node* l;
    struct _Node* r;
    void* data;
} Node;

typedef struct {
    Node* root;
    int (*cmp)(void*, void*);
} Tree;

Node* make_node(void* data)
{
    Node* res = (Node*)malloc(sizeof(Node));
    res->data = data;
    res->l = res->r = NULL;
    return res;
}

Tree* make_tree(void* root_val, int (*cmp)(void*, void*))
{
    Tree* res = (Tree*)malloc(sizeof(Tree));
    res->root = make_node(root_val);
    res->cmp = cmp;
    return res;
}

Node* node_find(Node* n, void* val, int (*cmp)(void*, void*))
{
    int compared = cmp(n->data, val);
    if (compared == 0) {
        return n;
    } else if (compared < 0) { /* n->data is smaller than val */
        if (n->r) {
            return node_find(n->r, val, cmp);
        }
    } else { /* (compared > 0) */
        if (n->l) {
            return node_find(n->l, val, cmp);
        }
    }
    return NULL;
}

Node* tree_find(Tree* t, void* val)
{
    return node_find(t->root, val, t->cmp);
}

void node_insert(Node* n, Node* new_el, int (*cmp)(void*, void*))
{
    int compared = cmp(n->data, new_el->data);
    if (compared == 0) { /* when equal, always add to the left child */
        if (!n->l) {
            n->l = new_el;
            return;
        }
        compared = cmp(n->l->data, new_el->data);
        if (compared == 0) {
            node_insert(n->l, new_el, cmp);
        } else if (compared < 0) { /* n->l < new_el */
            new_el->l = n->l;
        } else if (compared > 0) {
            new_el->r = n->l;
        }
        n->l = new_el;
    } else if (compared < 0) {
        if (n->r) {
            node_insert(n->r, new_el, cmp);
        } else {
            n->r = new_el;
        }
    } else { /* (compared > 0) */
        if (n->l) {
            node_insert(n->l, new_el, cmp);
        } else {
            n->l = new_el;
        }
    }
}

void tree_insert(Tree* t, void* val)
{
    Node* n = make_node(val);
    if (t->root->data) {
        node_insert(t->root, n, t->cmp);
    } else {
        t->root->data = val;
    }
}

int tree_count(Tree* t, void* val)
{
    Node* n = tree_find(t, val);
    int count = 0;
    if (n == NULL) {
        return 0;
    }
    count = 1;
    while (n->l && t->cmp(n->l->data, val) == 0) {
        count++;
        n = n->l;
    }
    return count;
}

int cmp_long(void* a, void* b)
{
    return (int)((long)a - (long)b);
}

int main(void)
{
    int size = 32;
    int i;
    Tree* t = make_tree(NULL, cmp_long);
    long which;
    long val;

    srand(time(NULL));

    for (i = 0; i < size; i++) {
        val = rand() % 100;
        printf("%ld ", val);
        tree_insert(t, (void*)val);
    }

    printf("\nWhich kind of element do you want to count? ");
    scanf("%ld", &which);
    printf("Looking for %ld ...\n", which);
    printf("%d occurrences\n", tree_count(t, (void*)which));
    
    return 0; 
}

