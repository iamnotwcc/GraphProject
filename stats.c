#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
//#include "search.h"

//int flag_edges[500000][500000] = {0};			//边的标记 

int numberOfEdges(char name[])
{
	FILE *fp = fopen(name, "r");
	if (fp == NULL) {
		printf("Failed to open teh file\n");
	}
	int m, n, weight;				//两个顶点和权重 
	while (fscanf(fp, "%d %d %d", &m, &n, &weight) != EOF) {
		num_edges++;
	}
	fclose(fp);
	return num_edges;
}

int numberOfVertices(char name[])
{
	FILE *fp = fopen(name, "r");
	if (fp == NULL) {
		printf("Failed to open the file\n");
	}
	int m, n, weight;
	while (fscanf(fp, "%d %d %d", &m, &n, &weight) != EOF) {
		if (flag_vertices[m] == 0) {
			flag_vertices[m] = 1;
			num_vertices++;
		}
		if (flag_vertices[n] == 0) {
			flag_vertices[n] = 1;
			num_vertices++;
		}
	}
	fclose(fp);
	return num_vertices;
}

float freemanNetworkCentrality(char name[])
{
	int s = 0;
	if (num_vertices == 0) {
		s = numberOfVertices(name);
	} else {
		s = num_vertices;
	}
	int m, n, weight;				//两个顶点和权重 
	FILE *fp = fopen(name, "r");
	if (fp == NULL) {
		printf("Failed to open teh file\n");
	}
	while (fscanf(fp, "%d %d %d", &m, &n, &weight) != EOF) {
		flag_vertices_import[m]++;
		flag_vertices_import[n]++;
		if (flag_vertices_import[m] > max_vertices_import) {
			max_vertices_import = flag_vertices_import[m];
		}
		if (flag_vertices_import[n] > max_vertices_import) {
			max_vertices_import = flag_vertices_import[n];
		}
	}
	int sum = 0;
	int i;
	for (i = 0; i < 500000; i++) {
		if (flag_vertices[i] == 1) {
			sum += max_vertices_import - flag_vertices_import[i];
		}
	}
	return ((float)sum / (s - 1) / (s - 2));
}
//float closenessCentrality(char name[], int node)
//{
//	int N = 0;
//	if (num_vertices == 0) {
//		N = numberOfVertices(name);
//	} else {
//		N = num_vertices;
//	}
//	int path_length = 0;		//Dijkstra
//	CreateAdj(name);
//	Dijkstra(node);
//	int count = N;
//	float result = 0;
//	for (int i = 0; count != 0; i++) {
//		if (flag[i] == 1 && dist[i] != INF) {
//			int num = 0;
//			int temp = i;
//			while (path[temp] != -1) {
//				num++;
//				temp = path[temp];
//			}
//			result += (float)1 / num;
//		}
//	}
//	return result;
//}
