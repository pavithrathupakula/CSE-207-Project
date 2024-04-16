#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Number of vertices in the graph
#define V 6

// Function to find the maximum flow in a graph from source to sink
int fordFulkerson(int graph[V][V], int source, int sink) {
    int u, v;

    // Create a residual graph and fill the residual graph with given capacities in the original graph as residual capacities
    int residualGraph[V][V]; // Residual graph where residualGraph[i][j] indicates residual capacity of edge from i to j

    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             residualGraph[u][v] = graph[u][v];

    int parent[V]; // This array is filled by BFS and to store path

    int maxFlow = 0;  // There is no flow initially

    // Augment the flow while there is a path from source to sink
    while (true) {
        // Create an array to indicate which vertices have been visited. This is used to prevent visiting the same vertex more than once in each iteration.
        bool visited[V];
        for (int i = 0; i < V; ++i)
            visited[i] = false;

        // Create a queue, enqueue source vertex, and mark source vertex as visited
        int queue[V];
        int front = 0, rear = 0;
        queue[rear++] = source;
        visited[source] = true;
        parent[source] = -1;

        // Standard BFS Loop
        while (front < rear) {
            u = queue[front++];

            for (v = 0; v < V; v++) {
                if (visited[v] == false && residualGraph[u][v] > 0) {
                    queue[rear++] = v;
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        // If sink is reached, no more augmenting paths are possible, so break
        if (visited[sink] == true)
            break;

        // Find minimum residual capacity of the edges along the path filled by BFS. Or we can say find the maximum flow through the path found.
        int pathFlow = INT_MAX;
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            pathFlow = pathFlow < residualGraph[u][v] ? pathFlow : residualGraph[u][v];
        }

        // Update residual capacities of the edges and reverse edges along the path
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Add path flow to overall flow
        maxFlow += pathFlow;
    }
    return maxFlow;
}
int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    int numTestCases;
    if (fscanf(file, "%d", &numTestCases) != 1) {
        fprintf(stderr, "Error reading the number of test cases\n");
        fclose(file);
        return 1;
    }

    printf("Number of test cases: %d\n", numTestCases); // Debug print

    for (int test = 0; test < numTestCases; test++) {
        int graph[V][V];

        printf("Reading graph for test case %d\n", test + 1); // Debug print

        // Read the graph data for each test case
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (fscanf(file, "%d", &graph[i][j]) != 1) {
                    fprintf(stderr, "Error reading graph data for test case %d\n", test + 1);
                    fclose(file);
                    return 1;
                }
                printf("%d ", graph[i][j]); // Debug print
            }
            printf("\n"); // Debug print
        }

        // Calculate maximum flow using the Ford-Fulkerson algorithm
        int source = 0;
        int sink = V - 1;
        int maxFlow = fordFulkerson(graph, source, sink);

        // Print the maximum flow for the current test case
        printf("Test case %d: Maximum flow from source to sink is: %d\n", test + 1, maxFlow);
    }

    fclose(file);
    return 0;
}
