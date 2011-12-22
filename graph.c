#include "graph.h"
#include <stdlib.h>
#include <stdbool.h>

graph_t *graph_create(int node_cnt) {
	int i, j;

	graph_t *graph = (graph_t*)malloc(sizeof(graph_t));

	graph->node_cnt = node_cnt;

	graph->dists = (int**)malloc(sizeof(int*)*node_cnt);
	for (i=0;i<node_cnt;i++) {
		graph->dists[i] = (int*)malloc(sizeof(int)*node_cnt);

		for (j=0;j<node_cnt;j++) {
			graph->dists[i][j] = 0;
		}
	}

	return graph;
}

void graph_delete(graph_t *graph) {
	int i;

	for (i=0;i<graph->node_cnt;i++) free(graph->dists[i]);
	free(graph->dists);

	free(graph);
}

static int graph_depth_first_srch_real(graph_t *graph, int node, bool *visits, int *prevs, int (*cb)(graph_t *graph, int node, void *user_data), void *user_data) {
	int i;
	int res;

	visits[node] = true;
	if ((res = cb(graph, node, user_data))) return res;

	for (i=0;i<graph->node_cnt;i++) {
		if (graph->dists[node][i] && !visits[i]) {
			prevs[i] = node;
			graph_depth_first_srch_real(graph, i, visits, prevs, cb, user_data);
		}
	}

	return 0;
}

int graph_depth_first_srch(graph_t *graph, int st_node, int **prevs, int (*cb)(graph_t *graph, int node, void *user_data), void *user_data) {
	int i;

	bool *visits = (bool*)malloc(sizeof(bool)*graph->node_cnt);
	int *new_prevs = (int*)malloc(sizeof(int)*graph->node_cnt);

	for (i=0;i<graph->node_cnt;i++) {
		visits[i] = false;
		new_prevs[i] = -1;
	}

	int res = graph_depth_first_srch_real(graph, st_node, visits, new_prevs, cb, user_data);

	if (prevs) *prevs = new_prevs;
	else free(new_prevs);

	free(visits);

	return res;
}

void graph_create_spanning_tree(graph_t *graph) {
}
