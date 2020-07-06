#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "stats.h"
//#include "search.c"
//#include "stats.c"

int scmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0') {
		i++;
	}
	if (i > 0 && s1[i] == '\0' && s2[i] == '\0') {
		return 0;
	}
	return 1;
}
void draw()
{
	printf("                  	           |----|\n");
    printf("                                   |----|\n");
    printf("	                           |----|\n");
	printf("	                           |----|\n");
	printf("                +------------------------------------------+\n");
    printf("        	|                                          |\n");
    printf("	        |    +                                 +   |\n");
    printf("	        |    |                                 |   |\n");
    printf("   		|    +------->                <--------+   |\n");
    printf("	        |                                          |\n");
	printf("    +-----------+                                          +--------------+\n");
	printf("    |           |                                          |              |\n");
	printf("    |           |                                          |              |\n");
	printf("    |           |             +--------------+             |              |\n");
	printf("    v           |                                          |              v\n");
    printf("	        |                                          |\n");
    printf("       	        +------------+---------------+-------------+\n");
    printf("        	             |               |\n");
    printf("            	             |               |\n");
    printf("                	     |               |\n");
    printf("                       	     |               |\n");
    printf("                      	     |               |\n");
    printf("                    	     |               |\n");
    printf("                    	     |               |\n");
    printf("        	 <-----------+               +---------------->\n");
}
int str_to_int(char *s)
{
	int temp[10];
	int i = 0;
	while (s[i] != '\0') {
		temp[i] = (char)(s[i] - '0');
		i++;
	}
	i--;
	int x = 0;
	int j;
	for (j = 0; j <= i; j++) {
		x = x * 10 + temp[j];
	}
	return x;
}
int main(int argc, char *argv[])
{
	if (argc == 2) {
		if (scmp(argv[1], "-h") == 0 || scmp(argv[1], "--help") == 0) {
			printf("\bhelp menu\n");
			printf("./search-cli -g/--graph FILE_PATH -s/--stats STATS_PARAMS");
			printf("(STATS_PARAMS : edges  vertices  freeman)");
			printf(":Displays statistical information for graph with `FILE_ PATH` as input file\n");
			printf("./search-cli -g/--graph FILE_PATH -sp/--shortestpath SEARCH_PARAMS -u STARTING_POINT -v TARGET_POINT:");
			printf("Displays the shortest path calculated with `SEARCH_ PARAMS` from the start point u to the end point v in the diagram with `SEARCH_ PATH` as the input file");
		} else if (scmp(argv[1], "-j") == 0){
			draw();
		} else {
			printf("Invalid instruction");
		}
	} else if (argc == 5) {
		if ((scmp(argv[1], "-g") || scmp(argv[1], "-graph") == 0) && (scmp(argv[3], "-s") == 0 || scmp(argv[3], "-stats") == 0)) {
			if (scmp(argv[4], "edges") == 0) {
				printf("%d", numberOfEdges(argv[2]));
			} else if (scmp(argv[4], "vertices") == 0) {
				printf("%d", numberOfVertices(argv[2]));
			} else if (scmp(argv[4], "freeman") == 0) {
				printf("%f", freemanNetworkCentrality(argv[2]));
			} else {
				printf("Invalid instruction");
			}
		}
	} else if (argc == 9) {
		if ((scmp(argv[1], "-g") == 0 || scmp(argv[1], "--graph") == 0) && 
		(scmp(argv[3], "-sp") == 0 || scmp(argv[3], "--shortestpath") == 0) && 
		scmp(argv[5], "-u") == 0 && 
		scmp(argv[7], "-v") == 0) {
			shortestPath(str_to_int(argv[5]), str_to_int(argv[7]), argv[4], argv[2]);
		}
	}
	return 0;
}
