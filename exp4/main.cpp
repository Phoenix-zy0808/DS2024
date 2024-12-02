#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <list>
#include <stack>

class Graph {
private:
    int V; // 顶点数
    std::vector<std::vector<std::pair<int, int>>> adj; // 邻接表

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w, int weight) {
        adj[v].push_back({w, weight}); // 添加边及其权重
    }

    void BFS(int s);
    void DFS(int s);
    void Dijkstra(int src);
    void Prim();
};

void Graph::BFS(int s) {
    std::vector<bool> visited(V, false);
    std::queue<int> queue;

    visited[s] = true;
    queue.push(s);

    while (!queue.empty()) {
        s = queue.front();
        std::cout << s << " ";
        queue.pop();

        for (const auto& edge : adj[s]) {
            int v = edge.first;
            if (!visited[v]) {
                visited[v] = true;
                queue.push(v);
            }
        }
    }
}

void Graph::DFS(int s) {
    std::vector<bool> visited(V, false);
    std::stack<int> stack;

    stack.push(s);

    while (!stack.empty()) {
        s = stack.top();
        stack.pop();

        if (!visited[s]) {
            std::cout << s << " ";
            visited[s] = true;
        }

        for (const auto& edge : adj[s]) {
            int v = edge.first;
            if (!visited[v]) {
                stack.push(v);
            }
        }
    }
}

void Graph::Dijkstra(int src) {
    std::vector<int> dist(V, INT_MAX);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::vector<bool> visited(V, false);

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    std::cout << "Vertex Distance from Source\n";
    for (int i = 0; i < V; ++i)
        std::cout << i << " \t\t " << dist[i] << std::endl;
}

void Graph::Prim() {
    std::vector<int> parent(V);
    std::vector<int> key(V, INT_MAX);
    std::vector<bool> inMST(V, false);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        int minWeight = INT_MAX;

        // 找到不在MST中的最小权重顶点
        for (int v = 0; v < V; ++v) {
            if (!inMST[v] && key[v] < minWeight) {
                minWeight = key[v];
                u = v;
            }
        }

        inMST[u] = true;

        // 更新相邻顶点的权重
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (!inMST[v] && key[u] != INT_MAX && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    std::cout << "Edge \t Weight\n";
    for (int i = 1; i < V; ++i)
        std::cout << parent[i] << " - " << i << " \t" << key[i] << std::endl;
}

int main() {
    Graph g(5);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 4);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 5);

    std::cout << "BFS (starting from vertex 0):\n";
    g.BFS(0);

    std::cout << "\nDFS (starting from vertex 0):\n";
    g.DFS(0);

    std::cout << "\nDijkstra's Algorithm (starting from vertex 0):\n";
    g.Dijkstra(0);

    std::cout << "\nPrim's Algorithm:\n";
    g.Prim();

    return 0;
}
