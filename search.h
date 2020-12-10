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
        Search(Graph& g) : graph(g) {}

        
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

        /** Helper function to compute the heuristic for astar. */
        double heuristic(Vertex current, Vertex end);

        struct Node {
            Node() {}
            Node(Vertex curr, Node* prev) : current(curr), previous(prev) {}
            Node(Vertex curr, Node* prev, double c, double p) : current(curr), previous(prev),
             cost(c), priority(p) {}

            Vertex current;
            Node* previous;
            double cost;
            double priority;
        };

        /** Predicate for priority queue */
        struct NodeComparison {
            bool operator()(const Node& lhs, const Node& rhs) const {
                return lhs.priority < rhs.priority;
            }
        };
};