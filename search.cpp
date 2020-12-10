#include "search.h"

/**
 * Finds the shortest path between two vertices using BFS.
 * @return - the shortest path
 */
vector<Vertex> Search::BFS(Vertex start, Vertex end) {
    vector<Vertex> visited;
    std::queue<Node*> queue;

    Node* startNode = new Node(start, NULL);

    queue.push(startNode);
    visited.push_back(start);

    Node* current;
    while(!queue.empty()) {
        current = queue.front();

        if (current->current == end) {
            break;
        }

        for (Vertex neighbor : graph.getAdjacent(current->current)) {
            if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                queue.push(new Node(neighbor, current));
                visited.push_back(neighbor);
            }
        }
    }

    vector<Vertex> path;
    while (current != NULL) {
        path.push_back(current->current);
        current = current->previous;
    } 
    std::reverse(path.begin(), path.end());

    return path;
}

/**
 * Finds the shortest path between two vertices using astar.
 * @return - the shortest path
 */
vector<Vertex> Search::astar(Vertex start, Vertex end) {

}