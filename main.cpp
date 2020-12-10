#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "vertex.h"
#include "graph.h"

using namespace std;

int main() {
	// read data csv files
	string connections_file = "connections_test_data.csv";
	string vertices_file = "vertices_test_data.csv";
	
	Graph g(connections_file, vertices_file, true);

	cout << g.getVertices().empty();
	cout << "Made project";

	vector<Vertex> vert_vec;
	



	// create map object from file
	return 0;
}