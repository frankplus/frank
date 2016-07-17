/*
    Author: Pham Francesco (frankplus)
    Contact: pham.francesco@gmail.com

    Basic problem:  Write a set of constructors for declaring and initializing a graph. An edge will have a positive cost that is its distance.
    Have a procedure that produces a randomly generated set of edges with positive distances.  Assume the graphs are undirected.
    The random graph procedure should have edge density as a parameter and distance range as a parameter.
    So a graph whose density is 0.1 would have 10% of its edges picked at random and its edge distance would be selected at random
    from the distance range. The procedure should run through all possible undirected edges, say (i,j) and place the edge in the graph
    if a random probability calculation is less than the density. Compute for a set of randomly generated graphs an average shortest path.
    Turn in:  Printout of program, 200 words on what you learned, and output showing the average path length calculation.
    Use densities: 20% and 40% on a graph of 50 nodes with a distance range of 1.0 to 10.0.
    To get an average path length, compute the 49 paths.

    I've made all in the Graph class, it is a weighted undirected graph randomized in the constructor and it uses the edge list representation.
    the dijkstra's algoritm is implemented in the method averageShortestPaths() it works out the average of the shortest paths from 0 to each other vertexes.
    In the main function there's the monte carlo simulation, it takes all these averages and makes the average of the averages shortest paths of a lot of different graphs..
    i've done 5 monte carlo simulation, one for each 20%, 40%, 60 %, 80%, 100% density..
    each simulation calculates 200'000 different graphs so it makes the average of the averages shortest paths..
    these are the most accurate values that i can make:

    For density 0%: 0                      average edges: 0
    For density 20%: 6.97516         average edges: 245
    For density 40%: 4.70137         average edges: 490
    For density 60%: 3.86348           average edges: 735
    For density 80%: 3.40694         average edges: 980
    For density 100%: 3.11202       average edges: 1225
    execution time: 431 s

    Hope you understand my code..
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <ctime>
#include <cfloat>

using namespace std;

//define the value that will be take for infinite value
const double INF = DBL_MAX;

struct Edge{
    int endVertex; //this is the index of the vertex the egde points to
    double weight; //the weight in case of weighted graph
};

//prototypes of the Graph class
class Graph{
private:
    int nodes; //number of nodes
    vector<Edge> *edgeList; //array that contains the edge list (array of vectors, i.e. two dimension array)
public:
    Graph(int n, float density, double min, double max);
    ~Graph();
    int V();
    int E();
    bool adjacent(int x, int y);
    void printNeighbors(int x);
    void printEdges();
    void addEdge(int x, int y, double w);
    void delEdge(int x, int y);

    //this is the function that calculate the shortest paths from 0 to each other nodes and get the average
    double averageShortestPaths();
};

//main function
int main()
{
    //number of the steps for the monte carlo simulation
    long Steps = 200000;

    srand((unsigned)time(NULL));
    Graph *MyGraph;
    double avg;
    double total;

    //calculate the average of the average shortest paths for graphs which density is 20% and 40%
    for(float density=0.2; density<=1.0F; density+=0.2)
    {
        total = 0;
        for(long i=0; i<Steps; i++){
            MyGraph = new Graph(50,density,1.0,10.0);
            avg = MyGraph->averageShortestPaths();
            total += avg;
            delete MyGraph;
        }

        //show result and avarage of the edges
        cout << "For density " << density*100 << "%: "<< total/Steps << endl;
    }

    return 0;
}


//constructor of the random graph
Graph::Graph(int n, float density, double min, double max)
{
    edgeList = new vector<Edge>[n]; //allocate the array of vectors
    nodes = n;

    //iterating over all possible edges, picking a random number between 0 and 1,
    //and if the random number is less than the density the edge exists and other wise there is no edge.
    float rnd;
    double w;
    for(int i=0; i<V(); i++){
        for(int j=i+1; j<V(); j++){
            rnd = static_cast<float>(rand()%100)/100;
            if(rnd<density){
                w = (rand()/(double)RAND_MAX)*(max-min)+min; //randomize the weight in the range defined by min and max
                addEdge(i,j,w);
            }
        }
    }
}

Graph::~Graph(){
    delete[] edgeList;
}

//returns the number of vertices in the graph
int Graph::V(){
    return nodes;
}

//returns the number of edges in the graph
int Graph::E(){
    int edges = 0;
    for(int i=0; i<nodes; i++)
        edges += edgeList[i].size();
    return edges/2; //return the number of total edges
}

//tests whether there is an edge from node x to node y.
bool Graph::adjacent(int x, int y) {
    assert(x<nodes && y<nodes);
    for(int i=0; i<edgeList[x].size(); i++)
        if(edgeList[x][i].endVertex == y)
            return true;
    return false;
}

//lists all nodes y such that there is an edge from x to y.
void Graph::printNeighbors(int x) {
    assert(x<nodes);
    cout << "vertex " << x;
    for(int i=0; i<edgeList[x].size(); i++)
    {
        cout << "==>" << edgeList[x][i].weight << ':' << edgeList[x][i].endVertex;
    }
    cout << endl;
}

//print all the edges of the graph
void Graph::printEdges() {
    cout << "Edge list: " << endl;
    for(int i=0; i<nodes; i++)
        printNeighbors(i);
}

//adds to G the edge from x to y, if it is not there.
void Graph::addEdge(int x, int y, double w) {
    assert(x<nodes && y<nodes);
    if(!adjacent(x,y)) {
        Edge temp;

        //add the edge from x to y
        temp.endVertex = y;
        temp.weight = w;
        edgeList[x].push_back(temp);

        //add the edge from y to x
        temp.endVertex = x;
        temp.weight = w;
        edgeList[y].push_back(temp);
    }
}

//removes the edge from x to y, if it is there.
void Graph::delEdge(int x, int y) {
    assert(x<nodes && y<nodes);
    for(int i=0; i<edgeList[x].size(); i++)
        if(edgeList[x][i].endVertex == y)
        {
            edgeList[x].erase(edgeList[x].begin()+i);
            return;
        }

    //remove either the edge from y to x because it is an undirected graph
    for(int i=0; i<edgeList[y].size(); i++)
        if(edgeList[y][i].endVertex == x)
        {
            edgeList[y].erase(edgeList[y].begin()+i);
            return;
        }
}


//this is the function that calculate the shortest paths from 0 to each other nodes and get the average
double Graph::averageShortestPaths() {
    //array of labels which contain the distance (temporary or permanent)
    struct label{
        double distance;
        bool closeSet; //true means it is in the closed set
    } labels[nodes];

    //Label the start vertex as 0 and set it in the close set.
    labels[0].distance = 0;
    labels[0].closeSet = true;

    //initialize the labels array, INF means that we don't know the distance
    for(int i=1; i<nodes; i++) {
        labels[i].closeSet = false;
        labels[i].distance = INF;
    }

    //Label each vertex that is connected to the start
    //vertex with its distance (temporary label).
    int neighbor;
    for(int i=0; i<edgeList[0].size(); i++){
        neighbor = edgeList[0][i].endVertex;
        labels[neighbor].distance = edgeList[0][i].weight;
    }

    //main loop: run the algorithm until all the nodes are in the close set
    int vertexMinDist;
    double MinDist, dist;
    while(true)
    {
        //Box the smallest number
        vertexMinDist=-1;
        MinDist = INF;
        for(int i=0; i<nodes; i++) {
            if(labels[i].closeSet == false && labels[i].distance <= MinDist) {
                vertexMinDist = i;
                MinDist = labels[i].distance;
            }
        }
        assert(vertexMinDist!=-1);

        //set it in the closeSet
        labels[vertexMinDist].closeSet = true;

        //if all the nodes are in the close set, exit.
        int i;
        for(i=0; i<nodes; i++)
            if(labels[i].closeSet == false)
                break;
        if(i==nodes) break;

        //From this vertex, consider the distance to each connected vertex.
        for(int i=0; i<edgeList[vertexMinDist].size(); i++){
            neighbor = edgeList[vertexMinDist][i].endVertex;
            //If a distance is less than a distance already at this
            //vertex, cross out this distance and write in the new
            //distance. If there was no distance at the vertex,
            //write down the new distance.
            if(labels[neighbor].closeSet == false) {
                dist = labels[vertexMinDist].distance + edgeList[vertexMinDist][i].weight;
                if(dist < labels[neighbor].distance)
                    labels[neighbor].distance = dist;
            }
        }
    }

    //calculate the average of the paths 0-1, 0-2, 0-3 etc...
    double tot=0,vReach=0;
    for(int i=1; i<nodes; i++){
        dist = labels[i].distance;
        //cout << i << ": " << dist << endl;
        if(dist != INF) //if the node isn't reachable don't count it
        {
            tot += dist;
            vReach++;
        }
    }

    //if vReach==0 it means the 0 vertex haven't got any edge, return 0
    //otherwise return tot/vReach
    return vReach!=0 ? tot/vReach : 0;
}
