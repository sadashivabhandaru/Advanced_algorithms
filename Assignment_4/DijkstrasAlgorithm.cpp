#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int node, weight;
};

void dijkstra(vector<vector<Edge>>& graph, int src, int dest, int V) {
    vector<int> dist(V, INF);
    vector<int> parent(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto& edge : graph[u]) {
            int v = edge.node, weight = edge.weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[dest] == INF) {
        cout << "No path exists from " << char('A' + src) << " to " << char('A' + dest) << ".\n";
        return;
    }

    cout << "Shortest Path from " << char('A' + src) << " to " << char('A' + dest) << ": ";
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) 
        path.push_back(v);
    for (int i = path.size() - 1; i >= 0; i--) 
        cout << char('A' + path[i]) << " ";
    cout << "\nCost: " << dist[dest] << endl;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<Edge>> graph(V);

    cout << "Enter edges in format (source destination weight), e.g., A B 10:\n";
    for (int i = 0; i < E; i++) {
        char u, v;
        int w;
        cin >> u >> v >> w;
        graph[u - 'A'].push_back({v - 'A', w});
        graph[v - 'A'].push_back({u - 'A', w});
    }

    char src, dest;
    cout << "Enter start node (A-" << char('A' + V - 1) << "): ";
    cin >> src;
    cout << "Enter end node (A-" << char('A' + V - 1) << "): ";
    cin >> dest;

    dijkstra(graph, src - 'A', dest - 'A', V);

    return 0;
}
