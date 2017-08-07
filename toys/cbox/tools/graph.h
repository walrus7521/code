#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// TODO 
//  fix topsort
//  implement netflow

//#define SIZE_RING 32
//typedef int e_v;
//#include "ring.inc"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define INV (-1)

void graph_show(int n, int p[][n], char *name);
void array_show(int n, int a[], char *name);
void topsort(int n, int a[][n]);
void test_topsort();
// is "v" reachable
void dfs_r(int n, int v, int a[][n]);
void bfs_r(int v, int n, int g[][n]);
void bfs2(int start, int n, int g[][n]);
void find_path(int start, int end, int parents[]);
void test_bfs();
int find_lowest_cost_node(int costs[], int visited[], int n);
void test_dijkstra();
int uni(int,int,int*);
int gfind(int,int*);
void test_kruskal();
//int find(int i, int par[]);
int uni(int i,int j, int par[]);
void warshall(int n, int g[][n]);
void test_warshall();
void floyd(int n, int g[][n]);
void test_floyd();
void prim(int n, int g[][n]);
void test_prim();
int graph_test();

#endif

