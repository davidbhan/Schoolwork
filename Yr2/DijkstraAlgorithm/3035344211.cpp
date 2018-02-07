#include <iostream> 
#include <string>
#include <sstream>
#include <assert.h>
#include <climits>
#include <queue>
#include <set>
#include <list>

using namespace std;

#define INF INT_MAX // Infinity 
typedef pair<int, int> ii; // pair of integers for priority queue in form of <weight, node>

// Graph class
class Graph {
private:
    int numNodes;
    int numEdges;
    int numStations;
    set<int> stations; // set of stations (to check if a node is a station)

public:
    list<ii> *adjacencyList; // adjacency list
    Graph(int n, int m, int k); // constructor
    void addEdge(int a, int b, int w); // function to add edge to a graph
    void addStation(int i); // function to add a station to the station set
    void delStation(int i); // function to remove a station from the station set
    int getStation(); // Returns the first value of the station set using iterator
    bool existStation(); // checks if there are any stations remaining in the station set
    bool isStation(int i); // returns if a node is a station or not (if > 0 then is a station)
    int getNumNodes(); // getter for numNodes
    int getNumStations(); // getter for numNtations
};

// Constructor for graph class
Graph::Graph(int n, int m, int k) {
    numNodes = n;
    numEdges = m;
    numStations = k;
    adjacencyList = new list<ii> [numNodes]; // Initialize the adjacency list
}

// Add edges to the adjacency matrix
void Graph::addEdge(int a, int b, int w) {
    adjacencyList[b-1].push_back(make_pair(a-1, w));
    adjacencyList[a-1].push_back(make_pair(b-1, w));
    return;
}

// Adds gas station ids to the graph class
void Graph::addStation(int i) {
    stations.insert(i);
    return;
}

// Removes a gas station from the graph class
void Graph::delStation(int i) {
    stations.erase(i);
    return;
}

// Gets first value of set 
int Graph::getStation() {
    return *stations.begin();
}

// Checks if there are still stations in the set
bool Graph::existStation() {
    return stations.empty();
}

// Checks if a node is a gas station or not
bool Graph::isStation(int i) {
    return stations.count(i) > 0;
}

// Getter for numNodes
int Graph::getNumNodes() {
    return numNodes;
}

int Graph::getNumStations() {
    return numStations;
}

// Solution to problem 1. Runs Dijkstra's algorithm until a gas station node is reached
int nearestGasStation(int source, Graph & g) {
    // Create an priority queue and distance array (where each index is a node)
    priority_queue< ii, vector <ii> , greater<ii> > pq; // Priority queue
    vector<int> dist(g.getNumNodes(), INF); // Distance array, initialize at infinity

    // Initialize the priority queue and the distance array with starting node
    pq.push(make_pair(0, source)); // Insert source to queue
    dist[source-1] = 0; // Set distance of source as 0

    // Some other variables to account for equidistant gas stations
    int stationid = g.getNumNodes() + 1; // Used for getting gas station with smallest id
    bool flag = false; // Used to check if there's a second, equidistant gas station

    // Start the priority queue
    while (!pq.empty()) { // Loop until priority queue is empty or gas station is reached        
        // Gets the first element in the priority queue and remove it from the list
        int currNode = pq.top().second; // the first element is the weight, the second is the node label
        int currWeight = pq.top().first;
        pq.pop();

        // Save our first encountered gas station as stationid since we've got our first solution
        if(g.isStation(currNode)) {
            if(!flag) { // Since this is our first time through, we store our solution
                stationid = currNode;
                flag = true; // Change our flag value since we've got a solution
                continue; // We continue because we don't need to expand the station node
            } 
        }

        // We continue our loop until we explore all equidistant nodes and return our solution
        if(flag && dist[currNode-1] > dist[stationid]) {
            return stationid;
        // If there's another equidistant node that's a gas station, we compare ids and change solution if needed
        } else if(flag && dist[currNode-1] == dist[stationid]) {
            if(g.isStation(currNode) && currNode < stationid) {
                stationid = currNode;
            }
            continue;
        }

        // Iterate through the adjacency list to find adjacent nodes
        list<ii>::iterator i;
        for (i = g.adjacencyList[currNode-1].begin(); i != g.adjacencyList[currNode-1].end(); ++i) {
            // Get vertex label and weight of current adjacent of u.
            int vertex = (*i).first+1;
            int weight = (*i).second;
 
            //  Update path to v through u if it's shorter
            if (dist[vertex-1] > dist[currNode-1] + weight) {
                dist[vertex-1] = dist[currNode-1] + weight;
                pq.push(make_pair(dist[vertex-1], vertex));
            }
        }
    }
    return stationid;
}

// Creates an array of the distance of all nodes from a given source
vector<int> createDistanceArray(int source, Graph & g) {
    priority_queue< ii, vector <ii> , greater<ii> > pq; // Priority queue
    vector<int> dist(g.getNumNodes(), INF); // Vector for distances, initialize at infinity
    pq.push(make_pair(0, source)); // Insert source to queue
    dist[source-1] = 0; // Set distance of source as 0

    while (!pq.empty()) { // Loop until priority queue is empty or gas station is reached        
        int currNode = pq.top().second; // the first element is the weight, the second is the node label
        int currWeight = pq.top().first;
        pq.pop();

        // Iterate through the adjacency list to find adjacent nodes
        list<ii>::iterator i;
        for (i = g.adjacencyList[currNode-1].begin(); i != g.adjacencyList[currNode-1].end(); ++i) {
            // Get vertex label and weight of current adjacent of u.
            int vertex = (*i).first+1;
            int weight = (*i).second;
 
            //  Update path to v through u if it's shorter
            if (dist[vertex-1] > dist[currNode-1] + weight) {
                dist[vertex-1] = dist[currNode-1] + weight;
                pq.push(make_pair(dist[vertex-1], vertex));
            }
        }
    }
    return dist;
}

// Solution to problem 2. Runs Dijkstra's for every gas station, then finds lowest distance for each node
int calculateNumofReverseNeighbors(int u, Graph & g) {
    // Create a 2D vector (rows are stations, columns are the distances to each node)
    // The first row will be the target row for gas station u
    // First element of each row will be the stationid, with the rest of values being distances
    vector< vector<int> > distMatrix;
    distMatrix.resize(g.getNumStations(), vector<int>(g.getNumNodes()+1, 0));
    
    // Initialize first row (desired row) and delete station from set
    vector<int> tempDist = createDistanceArray(u, g);
    distMatrix[0][0] = u;
    for(int i = 0; i < g.getNumNodes(); i++) {
        distMatrix[0][i+1] = tempDist[i];
    }
    g.delStation(u);

    // Handle the rest of the stations
    int stationIndex = 1;
    int tempStation;
    while(!g.existStation()) {
        // Create a new distance array for each of the other stations
        tempStation = g.getStation();
        tempDist = createDistanceArray(tempStation, g);

        // Copy the distance array over into the total distance matrix and remove station from the set
        distMatrix[stationIndex][0] = tempStation;
        for(int i = 0; i < g.getNumNodes(); i++) {
            distMatrix[stationIndex][i+1] = tempDist[i];
        }     
        g.delStation(tempStation);


        stationIndex++;
    }

    // Now that we have distance matrix, we compare distances for each node and set a counter
    int num = 0;
    // For each node, we set a baseline from our target station and compare to other stations
    for(int i = 1; i < g.getNumNodes() + 1; i++) { // For each node (remember first index is stationid)
        int target = distMatrix[0][i]; // baseline from target station
        bool isMin = true; // This will be used as a flag to count, reset as true for every node

        // To compare othter stations, we check if there's a lower distance value and set flag to false
        for(int j = 1; j < g.getNumStations(); j++) { // For each other station
            if(distMatrix[j][i] < target) { // If shorter distance is found, it's no longer the min
                isMin = false;
            } else if(distMatrix[j][i] == target) {
                if(distMatrix[j][0] < u) { // If equidistant, and stationid is lower, no longer the min
                    isMin = false;
                }
            }
        }
        
        // If our target baseline is truly the min, then we incrememnt our counter
        if(isMin) {
            num++;
        }

    }
    return num;
}

int main() {
    // Initialize the graph
    int n, m; // the number of nodes, edges
    char dummy;
    cin >> n >> dummy >> m;
    int k; // the number of gas stations
    cin >> k; 
    Graph g(n,m,k);

    // Add the gas stations to a set
    string stationIds;
    cin >> stationIds; // comma-separated string of stationIDs
    stringstream ss(stationIds);
    int i;
    while(ss >> i) { // read each stationId and insert it into the set
        g.addStation(i);
        if(ss.peek() == ',') {
            ss.ignore();
        }
    }

    // Add the edges 
    for(int i = 0; i < m; i++) { 
        int a, b, w;
        cin >> a >> dummy >> b >> dummy >> w; // read edge and insert it to graph
        g.addEdge(a, b, w); 
    }

    // Checks to do problem 1 or problem 2
    string section; 
    cin >> section;
    if(section == "NearestGasStation") {
        int v;
        cin >> v;
        cout << nearestGasStation(v, g);
    } else if(section == "ReverseNeighbors") {
        int u;
        cin >> u;
        cout << calculateNumofReverseNeighbors(u, g);
    } else {
        cout << "wrong input file!" << endl; 
        assert (0);
    }
    return 0; 
}