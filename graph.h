#pragma once

typedef struct {
	int **dists;
	int node_cnt;
} graph_t;

extern graph_t *graph_create(int size);
extern void graph_delete(graph_t *graph);
extern int graph_depth_first_search(graph_t *graph, int st_node, int **prevs, int (*cb)(graph_t *graph, int node, void *user_data), void *user_data);
