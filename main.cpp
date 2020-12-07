#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "vertex.h"

using namespace std;

int main() {
	// read data csv files
	string connections_file = "connections_test_data.csv";
	string vertices_file = "vertices_test_data.csv";
	
	ifstream connections;
	ifstream vertices;
	vector<Vertex> vert_vec;
	// iterate through csv file, creating edge object for each connection and adding to vector
	connections.open(connections_file);
	
	while (!connections.eof()) {

	}



	// create map object from file
	return 0;
}