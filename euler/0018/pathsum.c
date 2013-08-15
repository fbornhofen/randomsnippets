#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 255

typedef struct {
    int n;
    int sum;
} PathNode;

void process_row(PathNode** ns, int dim, int row)
{
    int i;
    for (i = 0; i <= dim; ++i) {
        if (ns[row+1][i].sum < ns[row+1][i].n + ns[row][i].sum) {
            ns[row+1][i].sum = ns[row+1][i].n + ns[row][i].sum;
        }
        if (ns[row+1][i+1].sum < ns[row+1][i+1].n + ns[row][i].sum) {
            ns[row+1][i+1].sum = ns[row+1][i+1].n + ns[row][i].sum;
        }
    }
}

int max_path_sum(PathNode** ns, int dim)
{
    int i;
    int max = 0;
    for (i = 0; i < dim-1; ++i) {
        process_row(ns, dim, i);
    }
    for (i = 0; i < dim; ++i) {
        if (max < ns[dim-1][i].sum) {
            max = ns[dim-1][i].sum;
        }
    }
    return max;
}

int main()
{
    FILE *f = fopen("numbers.txt", "r");
    size_t linelen = 0;
    char* line = NULL;
    char* tok;
    int linecount = 0;
    PathNode* path_nodes[DIM];
    for (; !feof(f) && linecount < DIM; ++linecount) {
        int colcount = 0;
        path_nodes[linecount] = malloc(DIM*sizeof(PathNode));
        getline(&line, &linelen, f);
        if (strlen(line) == 0) {
            break;
        }
        for (tok = strtok(line, " ");
             tok && colcount < DIM;
             tok = strtok(NULL, " "), ++colcount) {
            path_nodes[linecount][colcount].n = atoi(tok);
            path_nodes[linecount][colcount].sum = 0;
        }
    }
    free(line);
    path_nodes[0][0].sum = path_nodes[0][0].n;
    printf("%d\n", max_path_sum(path_nodes, linecount));
    while (linecount--) {
        free(path_nodes[linecount]);
    }
    return 0;
}
