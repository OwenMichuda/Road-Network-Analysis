#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "vertex.h"
#include "graph.h"

using namespace std;

int main() {
	// read data csv files
	string connections_file = "sampledata/connections_test_data.csv";
	string vertices_file = "sampledata/vertices_test_data.csv";

	Graph g(connections_file, vertices_file, true);

	for (Vertex v : g.getVertices()) {
		//cout << v.getIndex() << "\n";
	}

	for (Edge e : g.getEdges()) {
		cout << e.getWeight() << "\n";
	}
	
	vector<Vertex> vert_vec;



	// create map object from file
	return 0;
}