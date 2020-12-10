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
  Graph g("test_connections.csv", "test_vertices.csv");

  vector<Vertex> vertices = g.getVertices();

  vector<Vertex> correct;
  correct.push_back(Vertex(0,1000,592));
  correct.push_back(Vertex(1,3486,1292));
  correct.push_back(Vertex(2,7234,6923));
  correct.push_back(Vertex(3,1245,8231));
  correct.push_back(Vertex(4,2359,4124));
  correct.push_back(Vertex(5,5329,3621));

  REQUIRE(!vertices.empty());
  REQUIRE(correct.size() == vertices.size());
  REQUIRE(correct == vertices);

  vector<Edge> edges = g.getEdges();

  vector<Edge> correct_edges;
  correct_edges.push_back(Edge(Vertex(0,1000,592), Vertex(1,3486,1292), 20, ""));
  correct_edges.push_back(Edge(Vertex(1,3486,1292), Vertex(2,7234,6923), 4, ""));
  correct_edges.push_back(Edge(Vertex(2,7234,6923), Vertex(3,1245,8231), 16, ""));
  correct_edges.push_back(Edge(Vertex(3,1245,8231), Vertex(4,2359,4124), 1, ""));
  correct_edges.push_back(Edge(Vertex(4,2359,4124), Vertex(0,1000,592), 50, ""));
  correct_edges.push_back(Edge(Vertex(4,2359,4124), Vertex(5,5329,3621), 11, ""));
  correct_edges.push_back(Edge(Vertex(5,5329,3621), Vertex(3,1245,8231), 19, ""));

  REQUIRE(!edges.empty());
  REQUIRE(correct_edges.size() == edges.size());
  REQUIRE(correct_edges == edges);
}

TEST_CASE("BFS finds a valid path", "[weight=1]") {
  // hania: modify as necessary to test bfs
  Graph g("test_connections.csv", "test_vertices.csv");
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
  // hania
  Graph g("test_connections.csv", "test_vertices.csv");
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
  // hania
  Graph g("test_connections.csv", "test_vertices.csv");
  Search s(g);
  vector<Vertex> v = g.getVertices();
  vector<Vertex> path = s.astar(v[0], v[5]);

  vector<Vertex> correct;

  REQUIRE(path.size() == correct.size());
  for (int i = 0; i < path.size(); i++) {
    REQUIRE(path[i] == correct[i]);
  }
}