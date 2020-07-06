#ifndef _STATS_H_
#define _STATS_H_

int flag_vertices[500000] = {0};				//点的标记 
int flag_vertices_import[500000] = {0};			//点的连接个数 
int num_vertices = 0;
int num_edges = 0;
int max_vertices_import = 0;

int numberOfEdges(char name[]);
int numberOfVertices(char name[]);
float freemanNetworkCentrality(char name[]);
//float closenessCentrality(char name[], int node);

#endif
