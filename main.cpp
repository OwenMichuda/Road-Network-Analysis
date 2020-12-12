#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "vertex.h"
#include "graph.h"
#include "cs225/PNG.h"
#include "search.h"

using namespace std;

int main() {

	// set up for sample data
	string connections_file = "sampledata/oldenburg_road_network.csv";
	string vertices_file = "sampledata/OL_road_coords.csv";
	
	Graph g(connections_file, vertices_file, true);
	
	cs225::PNG png;
	png.readFromFile("background.png");

	Search search(g);

	cs225::PNG toReturn = g.render(g, png);
	toReturn = search.drawPath(toReturn);
	toReturn.writeToFile("outputMap.png");
<<<<<<< HEAD


=======
	
>>>>>>> refs/remotes/origin/master
	return 0;
}