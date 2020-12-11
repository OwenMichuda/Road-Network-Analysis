#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "vertex.h"
#include "graph.h"
#include "cs225/PNG.h"

using namespace std;

int main() {
	// read data csv files
	string connections_file = "sampledata/oldenburg_road_network.csv";
	string vertices_file = "sampledata/OL_road_coords.csv";
	
	Graph g(connections_file, vertices_file, true);
	
	cs225::PNG png;
	png.readFromFile("mappng.png");

	vector<Vertex> vert_vec;

	cs225::PNG toReturn = g.render(g, png);
	toReturn.writeToFile("outputMap.png");


	
	// create map object from file
	return 0;
}