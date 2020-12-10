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

TEST_CASE("BFS finds a valid path", "[weight=1]") {
  load_files();
  Search s(g);
  vector<Vertex> v = g.getVertices();
  vector<Vertex> path = s.BFS(v[0], v[5]);
  REQUIRE(!path.empty());
  REQUIRE(path[0].getX() == v[0].getX());
  REQUIRE(path[0].getY() == v[0].getY());
  REQUIRE(path[path.size() - 1].getX() == v[5].getX());
  REQUIRE(path[path.size() - 1].getY() == v[5].getY());
}

TEST_CASE("ASTAR finds a valid path", "[weight=1]") {
  load_files();
  Search s(g);
  vector<Vertex> v = g.getVertices();
  vector<Vertex> path = s.astar(v[0], v[5]);
  REQUIRE(!path.empty());
  REQUIRE(path[0].getX() == v[0].getX());
  REQUIRE(path[0].getY() == v[0].getY());
  REQUIRE(path[path.size() - 1].getX() == v[5].getX());
  REQUIRE(path[path.size() - 1].getY() == v[5].getY());
}

TEST_CASE("ASTAR found correct path", "[weight=1]") {
  load_files();
  Search s(g);
  vector<Vertex> v = g.getVertices();
  vector<Vertex> path = s.astar(v[0], v[5]);

  vector<Vertex> correct;

  REQUIRE(path.size() == correct.size());
  for (int i = 0; i < path.size(); i++) {
    REQUIRE(path[i] == correct[i]);
  }
}