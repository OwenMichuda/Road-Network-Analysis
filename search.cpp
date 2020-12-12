#include "search.h"

/**
 * Finds the shortest path between two vertices using BFS.
 * @return - the shortest path
 */
vector<Vertex> Search::BFS(Vertex start, Vertex end) const {
    vector<Vertex> visited;
    std::queue<Node*> queue;

    Node* startNode = new Node(start, NULL);

    queue.push(startNode);
    visited.push_back(start);

    Node* current;
    while(!queue.empty()) {
        current = queue.front();

        if (current->current == end) {
            break;
        }

        for (Vertex neighbor : graph.getAdjacent(current->current)) {
            if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                queue.push(new Node(neighbor, current));
                visited.push_back(neighbor);
            }
        }

        queue.pop();
    }

    vector<Vertex> path;
    while(current != NULL) {
        path.push_back(current->current);
        current = current->previous;
    } 
    std::reverse(path.begin(), path.end());

    return path;
}

/**
 * Finds the shortest path between two vertices using astar.
 * @return - the shortest path
 */
vector<Vertex> Search::astar(Vertex start, Vertex end) const {
    vector<Vertex> visited;
    std::priority_queue<Node*, std::vector<Node*>, NodeComparison> queue;

    Node* startNode = new Node(start, NULL, 0, heuristic(start, end));

    queue.push(startNode);
    visited.push_back(start);

    Node* current;
    while(!queue.empty()) {
        current = queue.top();
        queue.pop();

        if (current->current == end) {
            break;
        }

        for (Vertex neighbor : graph.getAdjacent(current->current)) {
            if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                double cost = current->cost + graph.getEdgeWeight(current->current, neighbor);
                double priority = cost + heuristic(neighbor, end);

                queue.push(new Node(neighbor, current, cost, priority));
                visited.push_back(neighbor);
            }
        }
    }

    vector<Vertex> path;
    while(current != NULL) {
        path.push_back(current->current);
        current = current->previous;
    } 
    std::reverse(path.begin(), path.end());

    return path;
}

/** Helper function to compute the heuristic for astar. */
double Search::heuristic(Vertex current, Vertex end) const {
    double x = end.getX() - current.getX();
    double y = end.getY() - current.getY();

    double distance = sqrt(pow(x, 2) + pow(y, 2));
    return distance;
}

/**
 * Draws astar and bfs paths to arbitrary points in graph.
 */ 
cs225::PNG Search::drawPath(cs225::PNG png) const {
    Vertex start = graph.getVertices().at(0);
    Vertex end = graph.getVertices().at(516);

    cs225::HSLAPixel green = cs225::HSLAPixel(151, 1, 0.45, 1);
    cs225::HSLAPixel blue = cs225::HSLAPixel(223, 1, 0.50, 1);
    cs225::HSLAPixel red = cs225::HSLAPixel(5, 1, 0.50, 1);


    vector<Vertex> bfs = BFS(start, end);
	std::cout << "BFS length: " << bfs.size() << std::endl;
    auto first_it = bfs.begin(); 
    auto second_it = ++bfs.begin();
    while (second_it != bfs.end()) {
        Vertex first = *first_it++;
        Vertex second = *second_it++;


		double dx, dy, startX, endX, startY, endY;
		if (std::abs(first.getX() - second.getX()) > std::abs(first.getY() - second.getY())) {
			if (second.getY() > first.getY()) {
				dy = second.getY() - first.getY();
			} else {
				dy = first.getY() - second.getY();
			}

			if (second.getX() > first.getX()) {
				dx = second.getX() - first.getX();
				startX = first.getX();
				startY = first.getY();
				endX = second.getX();
				endY = second.getY();
			} else {
				dx = first.getX() - second.getX();
				startX = second.getX();
				startY = second.getY();
				endX = first.getX();
				endY = first.getY();
			}
		} else {
			if (second.getX() > first.getX()) {
				dx = second.getX() - first.getX();
			} else {
				dx = first.getX() - second.getX();
			}

			if (second.getY() > first.getY()) {
				dy = second.getY() - first.getY();
				startX = first.getX();
				startY = first.getY();
				endX = second.getX();
				endY = second.getY();
			} else {
				dy = first.getY() - second.getY();
				startX = second.getX();
				startY = second.getY();
				endX = first.getX();
				endY = first.getY();
			}
		}

		if (dx > dy) {
			for (double x = startX; x <= endX; x++) {
				double y;
				if (startY < endY) {
            		y = startY + dy * (x - startX) / dx;
				} else {
					y = startY - dy * (x - startX) / dx;
				}
            
				for (double i = 0; i < 8; i++) {
					for (double j = 0; j < 8; j++) {
						if (x + i >= png.width()) break;
						if (y + j >= png.height()) break;

						// access every y associated with every x to get every pixel
						cs225::HSLAPixel& pixel = png.getPixel(x + i, y + j);
						// change color to black
						pixel = green;
					}
				}
        	}
		} else {
			for (double y = startY; y <= endY; y++) {
				double x;
				if (startX < endX) {
					x = startX + dx * (y - startY) / dy;
				} else {
					x = startX - dx * (y - startY) / dy;
				}
        
				for (double i = 0; i < 8; i++) {
					for (double j = 0; j < 8; j++) {
						if (x + i >= png.width()) break;
						if (y + j >= png.height()) break;

						// access every y associated with every x to get every pixel
						cs225::HSLAPixel& pixel = png.getPixel(x + i, y + j);
						// change color to black
						pixel = green;
					}
				}
        	}
		}
    }


    vector<Vertex> a = astar(start, end);
    first_it = a.begin(); 
    second_it = ++a.begin();
    while (second_it != a.end()) {
        Vertex first = *first_it++;
        Vertex second = *second_it++;


        double dx = second.getX() - first.getX();
        double dy = second.getY() - first.getY();
        for (double x = first.getX(); x <= second.getX(); x++) {
            double y = first.getY() + dy * (x - first.getX()) / dx;
            
            for (double i = 0; i < 8; i++) {
                for (double j = 0; j < 8; j++) {
                    if (x + i >= png.width()) break;
                    if (y + j >= png.height()) break;

                    // access every y associated with every x to get every pixel
                    cs225::HSLAPixel& pixel = png.getPixel(x + i, y + j);
                    // change color to blue
                    pixel = blue;
                }
            }
        }

    }

    for (double i = 0; i < 30; i++) {
        for (double j = 0; j < 30; j++) {
            cs225::HSLAPixel& s = png.getPixel(start.getX() + i, start.getY() + j);
            cs225::HSLAPixel& e = png.getPixel(end.getX() + i, end.getY() + j);

            s = red;
            e = red;
        }
    }

    return png;
}