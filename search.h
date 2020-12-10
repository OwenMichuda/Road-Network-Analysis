/**
 * @file search.h
 * Class that holds BFS and astar search methods.
 */

#pragma once

#include <vector>
#include <queue>
#include <algorithm>

#include "vertex.h"
#include "graph.h"

using std::vector;

class Search {
    public:
        Search(Graph g) : graph(g) {}

        
        /**
         * Finds the shortest path between two vertices using BFS.
         * @return - the shortest path
         */
        vector<Vertex> BFS(Vertex start, Vertex end);

        /**
         * Finds the shortest path between two vertices using astar.
         * @return - the shortest path
         */
        vector<Vertex> astar(Vertex start, Vertex end);

    private:
        Graph graph;

        struct Node {
            Node() {}
            Node(Vertex curr, Node* prev) : current(curr), previous(prev) {}
            // bool operator!=(const Node& other) const { return current != other.current || previous != other.previous}

            Vertex current;
            Node* previous;
        };
};