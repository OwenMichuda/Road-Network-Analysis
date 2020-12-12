#include "../cs225/catch/catch.hpp"

#include "../edge.h"
#include "../random.h"
#include "../graph.h"
#include "../search.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::ifstream connections;
std::ifstream vertices;
Graph graph(true, false);

TEST_CASE("Sanity Check", "[weight=1]") {
  REQUIRE(1 + 1 == 2);
}

TEST_CASE("CSV Graph Constructor", "[weight=1]") {
  Graph g("tests/test_connections.csv", "tests/test_vertices.csv", true);

  vector<Vertex> vertices = g.getVertices();

  vector<Vertex> correct;
  correct.push_back(Vertex(5,5329,3621));
  correct.push_back(Vertex(4,2359,4124));
  correct.push_back(Vertex(3,1245,8231));
  correct.push_back(Vertex(2,7234,6923));
  correct.push_back(Vertex(1,3486,1292));
  correct.push_back(Vertex(0,1000,592));

  SECTION("Vertices correctness") {
    REQUIRE(!vertices.empty());
    REQUIRE(correct.size() == vertices.size());
    REQUIRE(correct == vertices);
  }

  vector<Edge> edges = g.getEdges();

  vector<Edge> correct_edges;
  correct_edges.push_back(Edge(Vertex(5,5329,3621), Vertex(3,1245,8231), 19, ""));
  correct_edges.push_back(Edge(Vertex(4,2359,4124), Vertex(5,5329,3621), 11, ""));
  correct_edges.push_back(Edge(Vertex(4,2359,4124), Vertex(0,1000,592), 50, ""));
  correct_edges.push_back(Edge(Vertex(3,1245,8231), Vertex(4,2359,4124), 1, ""));
  correct_edges.push_back(Edge(Vertex(2,7234,6923), Vertex(3,1245,8231), 16, ""));
  correct_edges.push_back(Edge(Vertex(1,3486,1292), Vertex(2,7234,6923), 4, ""));
  correct_edges.push_back(Edge(Vertex(0,1000,592), Vertex(1,3486,1292), 20, ""));

  SECTION("Edges correctness") {
    REQUIRE(!edges.empty());
    REQUIRE(correct_edges.size() == edges.size());
    REQUIRE(edges[0].getWeight() == 19);
    for (Edge e : edges) {
      REQUIRE(e.dest.getIndex() != -1);
      REQUIRE(e.source.getIndex() != -1);
    }
  }
}

TEST_CASE("BFS finds shortest path", "[weight=1]") {
  Graph graph(false);
  for (int i = 0; i < 9; i++) {
    Vertex v = Vertex(i);
    graph.insertVertex(v);
  }

  graph.insertEdge(Vertex(0), Vertex(1));
  graph.insertEdge(Vertex(0), Vertex(2));
  graph.insertEdge(Vertex(1), Vertex(3));
  graph.insertEdge(Vertex(1), Vertex(4));
  graph.insertEdge(Vertex(2), Vertex(3));
  graph.insertEdge(Vertex(3), Vertex(4));
  graph.insertEdge(Vertex(3), Vertex(5));
  graph.insertEdge(Vertex(3), Vertex(7));
  graph.insertEdge(Vertex(4), Vertex(6));
  graph.insertEdge(Vertex(5), Vertex(8));
  graph.insertEdge(Vertex(5), Vertex(6));
  graph.insertEdge(Vertex(6), Vertex(8));
  graph.insertEdge(Vertex(7), Vertex(8));

  Search search(graph);
  vector<Vertex> path = {Vertex(0), Vertex(2), Vertex(3), Vertex(5), Vertex(8)};

  REQUIRE(path == search.BFS(Vertex(0), Vertex(8)));
}

TEST_CASE("astar finds shortest path", "[weight=1]") {
  Graph graph(true, false);
  Search search(graph);

  graph.insertVertex(Vertex(0, 0, 0));
  graph.insertVertex(Vertex(1, 2, 1));
  graph.insertVertex(Vertex(2, 1, 3));
  graph.insertVertex(Vertex(3, 3, 3));

  graph.insertEdge(Vertex(0, 0, 0), Vertex(1, 2, 1));
  graph.setEdgeWeight(Vertex(0, 0, 0), Vertex(1, 2, 1), 2.2361);

  graph.insertEdge(Vertex(0, 0, 0), Vertex(2, 1, 3));
  graph.setEdgeWeight(Vertex(0, 0, 0), Vertex(2, 1, 3), 3.1623);

  graph.insertEdge(Vertex(1, 2, 1), Vertex(3, 3, 3));
  graph.setEdgeWeight(Vertex(1, 2, 1), Vertex(3, 3, 3), 2.2361);

  graph.insertEdge(Vertex(2, 1, 3), Vertex(3, 3, 3));
  graph.setEdgeWeight(Vertex(2, 1, 3), Vertex(3, 3, 3), 2);

  REQUIRE(graph.getAdjacent(Vertex(0, 0, 0)).size() == 2);

  SECTION("Simple Graph") {
    vector<Vertex> path = {Vertex(0, 0, 0), Vertex(1, 2, 1), Vertex(3, 3, 3)};
    REQUIRE(path == search.astar(Vertex(0, 0, 0), Vertex(3, 3, 3)));
  }

  graph.insertVertex(Vertex(4, 4, 2));
  graph.insertVertex(Vertex(5, 4, 5));
  graph.insertVertex(Vertex(6, 2, 5));

  graph.insertEdge(Vertex(1, 2, 1), Vertex(4, 4, 2));
  graph.setEdgeWeight(Vertex(1, 2, 1), Vertex(4, 4, 2), 2.2361);

  graph.insertEdge(Vertex(3, 3, 3), Vertex(5, 4, 5));
  graph.setEdgeWeight(Vertex(3, 3, 3), Vertex(5, 4, 5), 2.2361);

  graph.insertEdge(Vertex(2, 1, 3), Vertex(6, 2, 5));
  graph.setEdgeWeight(Vertex(2, 1, 3), Vertex(6, 2, 5), 2.2361);

  graph.insertEdge(Vertex(6, 2, 5), Vertex(5, 4, 5));
  graph.setEdgeWeight(Vertex(6, 2, 5), Vertex(5, 4, 5), 2);

  graph.insertEdge(Vertex(4, 4, 2), Vertex(5, 4, 5));
  graph.setEdgeWeight(Vertex(4, 4, 2), Vertex(5, 4, 5), 3);

  REQUIRE(graph.getEdges().size() == 9);

  SECTION("More Complex Graph") {
    vector<Vertex> path = {Vertex(0, 0, 0), Vertex(1, 2, 1), Vertex(3, 3, 3), Vertex(5, 4, 5)};
    REQUIRE(path == search.astar(Vertex(0, 0, 0), Vertex(5, 4, 5)));
  }
}

TEST_CASE("Test search methods on graph from file") {
  Graph g("tests/test_connections.csv", "tests/test_vertices.csv", true);
  Search search(g);

  vector<Vertex> vertices = g.getVertices();
  REQUIRE(vertices.size() > 0);

  Vertex start = vertices[0];
  Vertex end = vertices[4];

  vector<Vertex> correct;

  correct.push_back(Vertex(5,5329,3621));
  correct.push_back(Vertex(3,1245,8231));
  correct.push_back(Vertex(2,7234,6923));
  correct.push_back(Vertex(1,3486,1292));

  REQUIRE(search.BFS(start, end) == correct);
  REQUIRE(search.astar(start, end) != correct);
}

TEST_CASE("Testing on our actual data") {
  string connections_file = "sampledata/oldenburg_road_network.csv";
	string vertices_file = "sampledata/OL_road_coords.csv";
	
	Graph g(connections_file, vertices_file, true);
  Search search(g);

  vector<Vertex> vertices = g.getVertices();
  REQUIRE(vertices.size() > 0);

  Vertex start = vertices[7];
  Vertex end = vertices[40];

  vector<Vertex> correct;

  correct.push_back(Vertex(5,5329,3621));
  correct.push_back(Vertex(3,1245,8231));
  correct.push_back(Vertex(2,7234,6923));
  correct.push_back(Vertex(1,3486,1292));

  //REQUIRE(search.BFS(start, end) == correct);
  REQUIRE(search.astar(start, end) == correct);
}