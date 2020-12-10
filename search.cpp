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

        queue.pop();
    }

    vector<Vertex> path;
    while(current != NULL) {
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
    vector<Vertex> visited;
    std::priority_queue<Node*, std::vector<Node*>, NodeComparison> queue;

    Node* startNode = new Node(start, NULL, 0, heuristic(start, end));

    queue.push(startNode);
    visited.push_back(start);

    Node* current;
    while(!queue.empty()) {
        current = queue.top();

        if (current->current == end) {
            break;
        }

        for (Vertex neighbor : graph.getAdjacent(current->current)) {
            if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                double cost = current->cost + graph.getEdgeWeight(current->current, neighbor);
                double priority = cost + heuristic(neighbor, end);

                queue.push(new Node(neighbor, current, cost, priority));
                visited.push_back(neighbor);
            }
        }

        queue.pop();
    }

    vector<Vertex> path;
    while(current != NULL) {
        path.push_back(current->current);
        current = current->previous;
    } 
    std::reverse(path.begin(), path.end());

    return path;
}

/** Helper function to compute the heuristic for astar. */
double Search::heuristic(Vertex current, Vertex end) {
    double x = end.getX() - current.getX();
    double y = end.getY() - current.getY();

    double distance = sqrt(pow(x, 2) + pow(y, 2));
    return distance;
}