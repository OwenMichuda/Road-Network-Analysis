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
Graph g(true, false);

void load_files() {
  std::string connections_file = "connections_test_data.csv";
  std::string vertices_file = "vertices_test_data.csv";
  connections.open(connections_file);
  vertices.open(vertices_file);

  g.insertVertex(Vertex(0, 1000, 592));
  g.insertVertex(Vertex(1,3486,1292));
  g.insertVertex(Vertex(2,7234,6923));
  g.insertVertex(Vertex(3,1245,8231));
  g.insertVertex(Vertex(4,2359,4124));
  g.insertVertex(Vertex(5,5329,3621));
  g.insertVertex(Vertex(6,6438,7631));
  g.insertVertex(Vertex(7,4591,7131));
  g.insertVertex(Vertex(8,1888,4120));

  g.insertEdge(Vertex(0, 1000, 592), Vertex(2,7234, 6923));
  g.insertEdge(Vertex(0, 1000, 592), Vertex(4,2359,4124));
  g.insertEdge(Vertex(1,3486,1292), Vertex(6,6438,7631));
  g.insertEdge(Vertex(1,3486,1292), Vertex(8,1888,4120));
  g.insertEdge(Vertex(4,2359,4124), Vertex(0, 1000, 592));
  g.insertEdge(Vertex(5,5329,3621), Vertex(1,3486,1292));
  g.insertEdge(Vertex(5,5329,3621), Vertex(3,1245,8231));
  g.insertEdge(Vertex(6,6438,7631), Vertex(5,5329,3621));
  g.insertEdge(Vertex(6,6438,7631), Vertex(7,4591,7131));
}

TEST_CASE("Sanity Check", "[weight=1]") {
  REQUIRE(1 + 1 == 2);
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
  vector<Vertex> path = {Vertex(0), Vertex(2), Vertex(3), Vertex(7), Vertex(8)};

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
  graph.insertEdge(Vertex(0, 0, 0), Vertex(2, 1, 3));
  graph.insertEdge(Vertex(1, 2, 1), Vertex(3, 3, 3));
  graph.insertEdge(Vertex(2, 1, 3), Vertex(3, 3, 3));


  SECTION("Simple Graph") {
    vector<Vertex> path = {Vertex(0, 0, 0), Vertex(1, 2, 1), Vertex(3, 3, 3)};
    REQUIRE(path == search.astar(Vertex(0, 0, 0), Vertex(3, 3, 3)));
  }
}