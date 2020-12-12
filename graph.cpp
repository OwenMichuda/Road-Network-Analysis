#include "graph.h"

const Vertex Graph::InvalidVertex = Vertex(-1);
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_CS225INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight, Graph::InvalidLabel);

Graph::Graph(string connections_file, string vertices_file, bool weighted) 
    : weighted(weighted), directed(false), random(Random(0)) {

    vector<Vertex> vertex_v = readVertexCSV(vertices_file);
    for (Vertex v : vertex_v) {
        insertVertex(v);
    }

    vector<Edge> edge_v = readConnectionsCSV(connections_file, vertex_v);
    for (Edge e : edge_v) {
        insertEdge(e.source, e.dest);
        if (weighted) setEdgeWeight(e.source, e.dest, e.getWeight());
    }
}

vector<Vertex> Graph::readVertexCSV(string filename) {
    string line;
    vector<Vertex> result;

    ifstream file(filename);

    if (!file) {
        error("Vertex file does not exist at that address.");
        exit(1);
    }

    while (getline(file, line)) {
        size_t start;
        size_t end = 0;
        
        int idx, x, y;
        vector<string> out;
        while ((start = line.find_first_not_of(',', end)) != std::string::npos) {
            end = line.find(',', start);
            out.push_back(line.substr(start, end - start));
        }

        if (out.size() != 3) cout << "no";

        std::stringstream index(out[0]);
        std::stringstream x_str(out[1]);
        std::stringstream y_str(out[2]);

        index >> idx;
        y_str >> y;
        x_str >> x;

        Vertex v(idx, x, y);
        result.push_back(v);
    }
    return result;
}

vector<Edge> Graph::readConnectionsCSV(string filename, vector<Vertex> vertices) {
    string line;
    vector<Edge> result;

    ifstream file(filename);

    if (!file) {
        error("Connections file does not exist at that address.");
        exit(1);
    }

    while (getline(file, line)) {
        size_t start;
        size_t end = 0;
        
        int idx, v1, v2, w;
        vector<string> out;
        while ((start = line.find_first_not_of(',', end)) != std::string::npos) {
            end = line.find(',', start);
            out.push_back(line.substr(start, end - start));
        }

        if (out.size() != 4) cout << "no";

        std::stringstream index(out[0]);
        std::stringstream v1_str(out[1]);
        std::stringstream v2_str(out[2]);
        std::stringstream weight(out[3]);

        index >> idx;
        v1_str >> v1;
        v2_str >> v2;
        weight >> w;

        Vertex one(-1);
        Vertex two(-1);

        for (Vertex v : vertices) {
            if (v.getIndex() == v1) {
                one = v;
            } else if (v.getIndex() == v2) {
                two = v;
            }

            if (one.getIndex() != -1 && two.getIndex() != -1) break;
        }

        Edge e(one, two, w, "");
        result.push_back(e);
    }
    return result;
}

Graph::Graph(bool weighted) : weighted(weighted),directed(false),random(Random(0))
{
}

Graph::Graph(bool weighted, bool directed) : weighted(weighted),directed(directed),random(Random(0))
{
}

Graph::Graph(bool weighted, int numVertices, unsigned long seed)
    :weighted(weighted),
      directed(false),
     random(Random(seed)) 
{
    if (numVertices < 2)
    {
     error("numVertices too low");
     exit(1);
    }

    vector<Vertex> vertices;
    for (int i = 0; i < numVertices; i++)
    {
        insertVertex(i);
        vertices.push_back(i);
    }

    // make sure all vertices are connected
    random.shuffle(vertices);
    Vertex cur = vertices[0];
    for (size_t i = 0; i < vertices.size() - 1; ++i)
    {
        Vertex next = vertices[i + 1];
        insertEdge(cur, next);
        if (weighted) 
        {
            int weight = random.nextInt();
            setEdgeWeight(cur, next, weight);
        }
        cur = next;
    }

    // keep the graph from being overpopulated with edges,
    //  while still maintaining a little randomness
    int numFailures = 0;
    int idx = 0;
    random.shuffle(vertices);
    while (numFailures < 2) 
    {
        if (!insertEdge(vertices[idx], vertices[idx + 1])) 
        {
            ++numFailures;
        } 
        else 
        {
            // if insertEdge() succeeded...
            if (weighted)
                setEdgeWeight(vertices[idx], vertices[idx + 1],
                              random.nextInt());
            ++idx;
            if (idx >= numVertices - 2) 
            {
                idx = 0;
                random.shuffle(vertices);
            }
        }
    }
}

vector<Vertex> Graph::getAdjacent(Vertex source) const 
{
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end())
        return vector<Vertex>();
	
     else
    {
        vector<Vertex> vertex_list;
        const unordered_map <Vertex, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}


Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

Edge Graph::getEdge(Vertex source , Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    Edge ret = adjacency_list[source][destination];
    return ret;
}

vector<Edge> Graph::getEdges() const
{
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Vertex, Vertex>> seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
        {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end())
            {
                //this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source,destination));
                if(!directed)
                {
                    seen.insert(make_pair(destination, source));
                }
            }
        }
    }

    return ret;
}

bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}

Edge Graph::setEdgeLabel(Vertex source, Vertex destination, string label)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination] = new_edge;

    if(!directed)
    {
        Edge new_edge_reverse(destination,source, e.getWeight(), label);
        adjacency_list[destination][source] = new_edge_reverse;
    }
    return new_edge;
}


string Graph::getEdgeLabel(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidLabel;
    return adjacency_list[source][destination].getLabel();
}

int Graph::getEdgeWeight(Vertex source, Vertex destination) const
{
    if (!weighted)
        error("can't get edge weights on non-weighted graphs!");

    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

void Graph::insertVertex(Vertex v)
{
    // will overwrite if old stuff was there
    removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}


Vertex Graph::removeVertex(Vertex v)
{

    if (adjacency_list.find(v) != adjacency_list.end())
    {
        if(!directed){
            for (auto it = adjacency_list[v].begin(); it != adjacency_list[v].end(); it++)
            {
                Vertex u = it->first;
                adjacency_list[u].erase(v); 
            }
            adjacency_list.erase(v);
            return v;
        }
        
        adjacency_list.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++)
        {
            Vertex u = it2->first;
            if (it2->second.find(v)!=it2->second.end())
            {
                it2->second.erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
}

bool Graph::insertEdge(Vertex source, Vertex destination)
{
    if(adjacency_list.find(source)!= adjacency_list.end() 
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        //edge already exit
        return false;
    }

    if(adjacency_list.find(source)==adjacency_list.end())
    {
        adjacency_list[source] = unordered_map<Vertex, Edge>();
    }
        //source vertex exists
    adjacency_list[source][destination] = Edge(source, destination);
    if(!directed)
    {
        if(adjacency_list.find(destination)== adjacency_list.end())
        {
            adjacency_list[destination] = unordered_map<Vertex, Edge>();
        }
        adjacency_list[destination][source] = Edge(source, destination);
    }
    
    return true;
}

Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    // if undirected, remove the corresponding edge
    if(!directed)
    {
        adjacency_list[destination].erase(source);
    }
    return e;
}


Edge Graph::setEdgeWeight(Vertex source, Vertex destination, double weight)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    //std::cout << "setting weight: " << weight << std::endl;
    Edge new_edge(source, destination, weight, e.getLabel());
    adjacency_list[source][destination] = new_edge;

    if(!directed)
        {
            Edge new_edge_reverse(destination,source, weight, e.getLabel());
            adjacency_list[destination][source] = new_edge_reverse;
        }

    return new_edge;
}

bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }
    return true;
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination)== adjacency_list[source].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + to_string(source.getIndex()) + " -> " + to_string(destination.getIndex()));
        return false;
    }

    if(!directed)
    {
        if (assertVertexExists(destination,functionName) == false)
            return false;
        if(adjacency_list[destination].find(source)== adjacency_list[destination].end())
        {
            if (functionName != "")
                error(functionName + " called on nonexistent edge " + to_string(destination.getIndex()) + " -> " + to_string(source.getIndex()));
            return false;
        }
    }
    return true;
}

bool Graph::isDirected() const
{
    return directed;
}

void Graph::clear()
{
    adjacency_list.clear();
}


/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}

/**
 * Creates a name for snapshots of the graph.
 * @param title - the name to save the snapshots as
 */
void Graph::initSnapshot(string title)
{
    picNum = 0;
    picName = title;
}

/**
 * Prints the graph to stdout.
 */
void Graph::print() const
{
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        cout << it->first << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            std::stringstream ss;
            ss << it2->first; 
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            cout << std::left << std::setw(26) << vertexColumn;
            string edgeColumn = "edge label = \"" + it2->second.getLabel()+ "\"";
            cout << std::left << std::setw(26) << edgeColumn;
            if (weighted)
                cout << "weight = " << it2->second.getWeight();
            cout << endl;
        }
        cout << endl;
    }
}

/** 
 * Render graph onto png of map
 */
cs225::PNG Graph::render(Graph g, cs225::PNG png) const {

    vector<Vertex> vertices = g.getVertices();

    cs225::HSLAPixel black = cs225::HSLAPixel(226, 1, 0, 1);
    cs225::HSLAPixel pink = cs225::HSLAPixel(328, 1, 0.76, 1);
    double dx = 0.0;
    double dy = 0.0;
    double y;
    for (Vertex v : vertices) {
        // get the x and y
        vector<Vertex> adjacent = g.getAdjacent(v);
        for (Vertex a : adjacent) {
            // compute slope
            dx = v.getX() - a.getX();
            dy = v.getY() - a.getY();
            for (double x = a.getX(); x <= v.getX(); x++) {
                y = a.getY() + dy * (x - a.getX()) / dx;
                // access every y associated with every x to get every pixel
                for (int i = 0; i <= 10; i++) {
                    for (int j = 0; j <= 10; j++) {
                    cs225::HSLAPixel& pixel = png.getPixel(x + i, y + j);
                    // change color to black
                    pixel.h = 226;
                    pixel.s = 1;
                    pixel.l = 0;
                    pixel.a = 1;
                    }
                }
            }
        }
    }
    for (Vertex v : vertices) {
        double x_coor = v.getX();
        double y_coor = v.getY();
        // set the color of the correlating pixel (of the png) to pink
        for (int i = 0; i <= 10; i++) {
            for (int j = 0; j <= 10; j++) {
                cs225::HSLAPixel& pixel = png.getPixel(x_coor + i, y_coor + j);
                pixel.h = 328;
                pixel.s = 1;
                pixel.l = 0.76;
                pixel.a = 1;
            }
        }
    }
    return png;
}
