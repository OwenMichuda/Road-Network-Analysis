#include <search.h>

/**
 * Finds the shortest path between two vertices using BFS.
 * @return - the shortest path
 */
vector<Vertex> Search::BFS(Vertex start, Vertex end) {
    /* vector<Vertex> visited;
    std::queue<std::pair<Vertex*, std::pair<>>> queue;

    queue.push(std::pair<>(&start, NULL);
    visited.push_back(start);

    std::pair<Vertex*, Vertex*> current_node;
    while(!queue.empty()) {
        current_node = queue.front();

        if (*current_node.first == end) {
            break;
        }

        for (Vertex neighbor : getAdjacent(*current_node.first)) {
            if (std::find(neighbor, visited) == visited.end()) {
                queue.push(std::pair<>(&neighbor, current_node.first));
                visited.push_back(neighbor);
            }
        }
    }

    vector<Vertex> path;
    while (current_node != NULL) {
        path.push_back
    } */

}

/**
 * Finds the shortest path between two vertices using astar.
 * @return - the shortest path
 */
vector<Vertex> Search::astar(Vertex start, Vertex end) {

}