# RESULTS

## I. Outcomes

Over the course of this three-week project, our group was able to implement two search algorithms as well as project a graphic representation of this onto a PNG. We were able to complete all the goals we outlined in our project goals document at the beginning of development. Despite working in different places and timezones, we were able to collaborate and communicate effectively to make sure all our goals were met.

This project is designed to take any two CSV files of vertices and edges with the format (index, x-coordinate, y-coordinate) and (index, vertex 1, vertex 2, weight) and produce a graph of the network. From there we use the BFS and A* search algorithms to find the shortest path between two arbitrary nodes (seen in Figure 2). 

## II. Discoveries

For this project we used BFS and A* search algorithms to find the shortest path between two nodes. These two algorithms are very similar. BFS finds the shortest path by the number of edges travelled. A* finds the shortest path in a similar way, but instead it takes edge weights into consideration. Both follow this basic structure:

  1. Designate start node
  2. Add to queue
  3. Add to list of visited nodes

In A*, nodes are added to the queue with priority, calculated as heuristic + weight + current cost. 

The graphic output involved using the PNG and HSLAPixel classes provided to us in several other labs/mps. Rendering the nodes turned out to be fairly simple once we discovered that implementing our Vertex object as class rather than a string typedef would give us a way to access the x and y coordinates of each "node". Rendering the edges took a bit of research into different line-drawing algorithms. We landed on a naive line-drawing algo because it was efficient enough for our implementation. To output the graph properly (as seen in Figure 1), we discovered that we had to increase the radius of each pixel by coloring the surrounding pixels of each vertex and edge. This allowed us to render our map in both an efficient and an effective way.

## III. Figures

Graphic output of blank network:

![Graphic Output of Graph](https://github-dev.cs.illinois.edu/cs225-fa20/eedowdy2-haniakd2-fkabba2-jamesom2/blob/master/map_output.png)

Shortest path between two nodes, BFS (green), and A* (blue):  

![Display of Shortest Path Between Nodes in Green](https://github-dev.cs.illinois.edu/cs225-fa20/eedowdy2-haniakd2-fkabba2-jamesom2/blob/master/outputMap.png)
