#include <climits>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>

struct Graph {
    int **edges;
    int size;

    Graph(int size) : size(size), edges(new int*[size]) {
        for (size_t i = 0; i < size; ++i) {
            edges[i] = new int[size];
            std::fill_n(edges[i], size, -1);
        }
    }

    void insert(int first, int second, int cost) {
        --first;
        --second;
        edges[first][second] = cost;
        edges[second][first] = cost;
    }
};

struct HeapNode {
    int vid;
    int dist;

    HeapNode(int vid, int dist) : vid(vid), dist(dist) {}
};

struct CompareHeap {
    bool operator() (const HeapNode &lhs, const HeapNode &rhs) {
        return lhs.dist > rhs.dist;
    }
};

int dijkstra(Graph &graph, int src, int dst) {
    --src;
    --dst;
    std::priority_queue<HeapNode, std::vector<HeapNode>, CompareHeap> heap;
    bool *set = new bool[graph.size]();
    int *distances = new int[graph.size];

    std::fill_n(distances, graph.size, INT_MAX);

    for (size_t i = 0; i < graph.size; ++i) {
        heap.push(HeapNode(i, INT_MAX));
    }
    heap.push(HeapNode(src, 0));

    while (!heap.empty()) {
        HeapNode min = heap.top();
        heap.pop();
        if (set[min.vid]) {
            continue;
        }

        set[min.vid] = true;
        distances[min.vid] = min.dist;

        for (size_t i = 0; i < graph.size; ++i) {
            if (!set[i] && graph.edges[min.vid][i] > 0) {
                heap.push(HeapNode(i, min.dist + graph.edges[min.vid][i]));
            }
        }
    }
    
    int result = distances[dst];

    delete[] set;
    delete[] distances;

    return result;
}


int main() {
    std::string line;
    std::istringstream sin;
    int num_nodes, num_edges;
    int node0, node1, distance;


    std::getline(std::cin, line);
    while (line != "") {
        sin.str(line);
        sin.clear();

        sin >> num_nodes >> num_edges;

        if (sin.fail()) {
            return EXIT_FAILURE;
        }

        Graph graph = Graph(num_nodes);

        for (int i = 0; i < num_edges; ++i) {
            std::getline(std::cin, line);
            sin.str(line);
            sin.clear();

            

            sin >> node0 >> node1 >> distance;
            if (sin.fail() || node0 <= 0 || node1 <= 0 || distance <= 0 || node0 > num_nodes || node1 > num_nodes || node0 == node1) {
                return EXIT_FAILURE;
            }

            graph.insert(node0, node1, distance);
        }
        std::cout << dijkstra(graph, 1, num_nodes) << std::endl;
        std::getline(std::cin, line);
    }

    return EXIT_SUCCESS;
}
