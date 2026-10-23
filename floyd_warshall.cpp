#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//Driver Code Ends
void floydWarshall(vector<vector<int>> &dist) {
    int V = dist.size();
    int INF = 1e8;

    // for each intermediate vertex
    for (int k = 0; k < V; k++) {

        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++) {

            // Pick all vertices as destination
            // for the above picked source
            for (int j = 0; j < V; j++) {

                // shortest path from i to j 
                if(dist[i][k] != INF && dist[k][j]!= INF )
                    dist[i][j] = min(dist[i][j],
                                     dist[i][k] + dist[k][j]);
            }
        }
    }
}