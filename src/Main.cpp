// A C++ program to find strongly connected components in a given
// directed graph using Tarjan's algorithm (single DFS)
#include<iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#define NIL -1
using namespace std;

// A class that represents an directed graph
class Graph
{
    int V; // No. of vertices
    list<int>* adj; // A dynamic array of adjacency lists
    vector<vector<int>> scComponents;

    // A Recursive DFS based function used by SCC()
    void SCCUtil(int u, int disc[], int low[],
        stack<int>* st, bool stackMember[]);
public:
    Graph(int V); // Constructor
    void addEdge(int v, int w); // function to add an edge to graph
    void SCC(); // prints strongly connected components
    bool hasInbound(vector<int> component);
    bool hasOutbound(vector<int> component);
    int getMinimumEdges();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v - 1].push_back(w - 1);
}

// A recursive function that finds and prints strongly connected
// components using DFS traversal
// u --> The vertex to be visited next
// disc[] --> Stores discovery times of visited vertices
// low[] -- >> earliest visited vertex (the vertex with minimum
//			 discovery time) that can be reached from subtree
//			 rooted with current vertex
// *st -- >> To store all the connected ancestors (could be part
//		 of SCC)
// stackMember[] --> bit/index array for faster check whether
//				 a node is in stack
void Graph::SCCUtil(int u, int disc[], int low[], stack<int>* st,
    bool stackMember[])
{
    // A static variable is used for simplicity, we can avoid use
    // of static variable by passing a pointer.
    static int time = 0;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;

    // Go through all vertices adjacent to this
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i; // v is current adjacent of 'u'

        // If v is not visited yet, then recur for it
        if (disc[v] == -1)
        {
            SCCUtil(v, disc, low, st, stackMember);

            // Check if the subtree rooted with 'v' has a
            // connection to one of the ancestors of 'u'
            // Case 1 (per above discussion on Disc and Low value)
            low[u] = min(low[u], low[v]);
        }

        // Update low value of 'u' only of 'v' is still in stack
        // (i.e. it's a back edge, not cross edge).
        // Case 2 (per above discussion on Disc and Low value)
        else if (stackMember[v] == true)
            low[u] = min(low[u], disc[v]);
    }

    // head node found, pop the stack and print an SCC
    int w = 0; // To store stack extracted vertices

    if (low[u] == disc[u])
    {
        vector<int> currentComponent;
        while (st->top() != u) {
            w = (int)st->top();
            currentComponent.push_back(w);
            stackMember[w] = false;
            st->pop();
        }
        w = (int)st->top();
        currentComponent.push_back(w);
        scComponents.push_back(currentComponent);
        stackMember[w] = false;
        st->pop();
    }
    return;
}

// The function to do DFS traversal. It uses SCCUtil()
void Graph::SCC()
{
    int* disc = new int[V];
    int* low = new int[V];
    bool* stackMember = new bool[V];
    stack<int>* st = new stack<int>();

    // Initialize disc and low, and stackMember arrays
    for (int i = 0; i < V; i++)
    {
        disc[i] = NIL;
        low[i] = NIL;
        stackMember[i] = false;
    }

    // Call the recursive helper function to find strongly
    // connected components in DFS tree with vertex 'i'
    for (int i = 0; i < V; i++)
        if (disc[i] == NIL)
            SCCUtil(i, disc, low, st, stackMember);
}

bool includes(list<int> listToSearch, int item) {
    return find(listToSearch.begin(), listToSearch.end(), item) != listToSearch.end();
}

bool includes(vector<int> listToSearch, int item) {
    return find(listToSearch.begin(), listToSearch.end(), item) != listToSearch.end();
}

bool Graph::hasInbound(vector<int> component) {
    for (int vertex : component) {
        for (int i = 0; i < V; i++) {
            if (includes(adj[i], vertex) && !includes(component, i)) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::hasOutbound(vector<int> component) {
    for (int vertex : component) {
        for (int outboundVertex : adj[vertex]) {
            if (!includes(component, outboundVertex)) {
                return true;
            }
        }
    }
    return false;
}

int Graph::getMinimumEdges() {
    int noInbound = 0;
    int noOutbound = 0;

    for (int i = 0; i < scComponents.size(); i++) {
        vector<int> component = scComponents.at(i);

        bool componentHasInbound = hasInbound(component);
        bool componentHasOutbound = hasOutbound(component);
        
        if(!componentHasInbound) {
            noInbound ++;
        }
        if(!componentHasOutbound) {
            noOutbound ++;
        }
    }
    
    return noInbound > noOutbound ? noInbound : noOutbound;
}

Graph lerRotas(int numeroAeroportos, int numeroRotas) {
    int vertice1;
    int vertice2;
    Graph graph(numeroAeroportos);
    for (int i = 0; i < numeroRotas;i++) {
        cin >> vertice1 >> vertice2;
        graph.addEdge(vertice1, vertice2);
    }
    return graph;
}

int main() {
    int numeroAeroportos, numeroRotas;
    cin >> numeroAeroportos >> numeroRotas;

    Graph graph = lerRotas(numeroAeroportos, numeroRotas);

    graph.SCC();
    cout << graph.getMinimumEdges() << endl;
    return 0;
}
