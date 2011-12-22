#include <stdio.h>
#include "graph.h"
#include <stdlib.h>

static graph_t *input() {
	int i;
	FILE *fin = NULL;
	int node_cnt;
	char buf[1024];
	int j;
	graph_t *graph = NULL;
	char *buf_pos, *new_buf_pos;

	if (!(fin = fopen("graph_data.txt", "r"))) goto err;

	if (fscanf(fin, "%d", &node_cnt) != 1) goto err;
	graph = graph_create(node_cnt);

	while (fgets(buf, sizeof(buf), fin)) {
		buf_pos = buf;

		i = strtol(buf_pos, &new_buf_pos, 10);
		if (buf_pos == new_buf_pos) continue;
		buf_pos = new_buf_pos;

		while (1) {
			j = strtol(buf_pos, &new_buf_pos, 10);
			if (buf_pos == new_buf_pos) break;
			buf_pos = new_buf_pos;

			graph->dists[i][j] = 1;
		}
	}

	fclose(fin);
	return graph;

err:
	if (fin) fclose(fin);
	if (graph) graph_delete(graph);
	return NULL;
}

static int depth_first_srch_visit(graph_t *graph, int node, void *user_data) {
	printf("%d ", node);
	return 0;
}

static void print_path(int *prevs, int node) {
	int prev = prevs[node];
	if (prev != -1) print_path(prevs, prev);

	printf("%d ", node);
}

void process(graph_t *graph) {
	int i;
	int *prevs;

	static const int st_node = 0;

	graph_depth_first_srch(graph, st_node, &prevs, depth_first_srch_visit, NULL);
	putchar('\n');

	int ed_node;
	while (scanf("%d", &ed_node) == 1 && ed_node != -1) {
		print_path(prevs, ed_node);
		putchar('\n');
	}

	for (i=0;i<graph->node_cnt;i++) {
		if (prevs[i] == -1) continue;
		printf("(%d %d) ", prevs[i], i);
	}
	putchar('\n');

	free(prevs);
}

void finalize(graph_t *graph) {
	graph_delete(graph);
}

int main(void) {
	graph_t *graph;

	if (!(graph = input())) return -1;
	process(graph);
	finalize(graph);

	return 0;
}
