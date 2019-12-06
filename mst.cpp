#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

struct Edge {
    int src;
    int dst;
    int cost;

    Edge(int src, int dst, int cost) : src(src), dst(dst), cost(cost) {}

    bool operator< (const Edge &other) const {
        return cost < other.cost;
    }
};

int find_set(int *set, int target) {
    
    if (target == set[target]) {
        return target;
    }

    set[target] = find_set(set, set[target]);
    return set[target];
}

void union_set(int *set, int u, int v) {
    int parent_u = find_set(set, u);
    int parent_v = find_set(set, v);

    set[parent_u] = parent_v;
}


int mst(int size, std::vector<Edge> &edges) {
    int *disjoint_set = new int[size];

    int result_cost = 0;

    for (int i = 0; i < size; ++i) {
        disjoint_set[i] = i;
    }

    std::sort(edges.begin(), edges.end());

    for (std::vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
        if (find_set(disjoint_set, it->src - 1) != find_set(disjoint_set, it->dst - 1)) {
            union_set(disjoint_set, it->src - 1, it->dst - 1);
            result_cost += it->cost;
        }
    }

    delete[] disjoint_set;

    return result_cost;
}

int main() {
    std::string line;
    std::istringstream sin;
    std::vector<Edge> edges;
    int num_cities, num_city_pairs;
    int city0, city1, cost;

    std::getline(std::cin, line);
    while (line != "") {
        sin.str(line);
        sin.clear();

        sin >> num_cities >> num_city_pairs;

        if (sin.fail()) {
            return EXIT_FAILURE;
        }

        for (int i = 0; i < num_city_pairs; ++i) {
            std::getline(std::cin, line);
            sin.str(line);
            sin.clear();

            sin >> city0 >> city1 >> cost;
            if (sin.fail() || city0 <= 0 || city1 <= 0 || cost <= 0 || city0 > num_cities || city1 > num_cities || city0 == city1) {
                return EXIT_FAILURE;
            }

            edges.push_back(Edge(city0, city1, cost));
        }
        std::cout << mst(num_cities, edges) << std::endl;
        edges.clear();
        std::getline(std::cin, line);
    }

    return EXIT_SUCCESS;
}
