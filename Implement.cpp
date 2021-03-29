#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<ctime>
#include<cstdlib>
using namespace std;

// DEADBEEF is used to represent the edge between two nodes doesn't exist 
const int DEADBEEF=9999;

// Node definitions
typedef struct Nodeinfo Node;
struct Nodeinfo
{
  int number;	
  int weight;	
  list<Node> edges;	
};

// Graph Class
class Graph
{
public:
  Graph();
  Graph(int Numbers, double density, int min, int max);
  int get_edge_value(int x, int y);
  void set_edge_value(int x, int y, int v);
  bool adjacent(int x, int y);
  list<int> neighbors(int x);
  int V();
  int E();
  list<int> vertices();
  void display();

private:
  int VerticesNum;			// Number of nodes of the Graph
  int EdgesNum;			// Number of edges of the Graph
  list<Node> AdjMatrix;		// Adjacency list representing the Graph
};

// Create an empty graph
Graph::Graph()
{
  VerticesNum = 0;
  EdgesNum = 0;
  AdjMatrix.clear();
}

// Construct Graph Class
// Create adjacency list with all nodes and empty edge list
Graph::Graph(int Numbers, double density, int min, int max)
{
  VerticesNum = Numbers;
  EdgesNum = 0;
  AdjMatrix.clear();

  for(int i=0; i<VerticesNum; ++i)
  {
    Node NewNode;
    NewNode.number = i;
    NewNode.weight = 0;
    NewNode.edges.clear();
    AdjMatrix.push_back(NewNode);
  }
  srand(time(0));
  for (int i=0; i<VerticesNum; ++i)
  {
    for (int j=i+1; j<VerticesNum; ++j)
    {
      double prob = (rand() % 100) / 100.0;
      if (prob < density)
      {
        int value = rand() % (max - min) + min;
        set_edge_value(i,j,value);
      }
    }
  }
}


// returns the value associated to the edge (x,y)
// returns INFINITY if edge doesn't exist
int Graph::get_edge_value(int x, int y)
{
  for(list<Node>::iterator i=AdjMatrix.begin(); i != AdjMatrix.end(); ++i)
  {
    if ((*i).number==x)
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
        if ((*j).number==y)
        return (*j).weight; 
      }
  }
  return DEADBEEF;
}

// sets the value associated to the edge (x,y) to value
void Graph::set_edge_value(int x, int y, int value)
{
  bool found;
  // for the matrix [x,y]
  for(list<Node>::iterator i=AdjMatrix.begin(); i != AdjMatrix.end(); ++i)
  {
    if ((*i).number==x)
    {
      found = false;
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
        if ((*j).number==y)
        {  
          (*j).weight=value;
          found = true;
        }
      }
      if (!found)
      {
        Node NewNode;
        NewNode.number = y;
        NewNode.weight = value;
        NewNode.edges.clear();
        (*i).edges.push_back(NewNode);
      }
    }
  }

  // for the matrix [y,x]
  for(list<Node>::iterator i=AdjMatrix.begin(); i != AdjMatrix.end(); ++i)
  {
    if ((*i).number==y)
    {
      found = false;
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
        if ((*j).number==x)
        {  
          (*j).weight=value;
          found = true;
        }
      }
      if (!found)
      {
        Node NewNode;
        NewNode.number = x;
        NewNode.weight = value;
        NewNode.edges.clear();
        (*i).edges.push_back(NewNode);
        ++EdgesNum;
      }
    }
  }
}

// tests whether there is an edge from node x to node y
bool Graph::adjacent(int x, int y)
{
  for(list<Node>::iterator i=AdjMatrix.begin(); i != AdjMatrix.end(); ++i)
  {
    if ((*i).number==x)
    {
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
        if ((*j).number==y)
        {  
          return true;
        }
      }
    }
  }
  return false;
}

//  lists all nodes y such that there is an edge from x to y
list<int> Graph::neighbors(int x)
{
  list<int> AdjNodes;
  for(list<Node>::iterator i=AdjMatrix.begin(); i != AdjMatrix.end(); ++i)
  {
    if ((*i).number==x)
    {
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
        AdjNodes.push_back((*j).number);
      }
    }
  }
  return AdjNodes;
}

// returns the number of vertices in the graph
int Graph::V()
{
  return VerticesNum;
}

// returns the number of edges in the graph
int Graph::E()
{
  return EdgesNum;
}

// returns a list contains all vertices in the Graph
list<int> Graph::vertices()
{
  list<int> nodes;
  for(list<Node>::iterator i=AdjMatrix.begin(); i != AdjMatrix.end(); ++i)
  {
    nodes.push_back((*i).number);
  }
  return nodes;
}

// Display the Graph
void Graph::display()
{
  cout << "   ";
  for(list<Node>::iterator i=AdjMatrix.begin(); i != AdjMatrix.end(); ++i)
    if ((*i).number < 10) 
      cout << " " << "0" << (*i).number;
    else
      cout << " " << (*i).number;
  cout << endl;
  for(list<Node>::iterator i=AdjMatrix.begin(); i != AdjMatrix.end(); ++i)
  {
    if ((*i).number < 10) 
      cout << " " << "0" << (*i).number;
    else
      cout << " " << (*i).number;
    int position=0; // display point now
    for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
    {
      int shift=(*j).number - position; // width between display point now and display node now
      for(int h=0; h<shift; ++h)
      {
        cout << " --";
        position++;
      }
      cout << "  " << (*j).weight;
      position++;
    }
    while (position < VerticesNum)
    {
      cout << " --";
      position++;
    }
    cout << endl;
  }
}


// NodeInfo Definitions
struct strNodeInfo
{
  int NodeNum;	// Node Number
  int ShortPath;		// Shortest path found to the Node
  int through;		// Node that precede Node Number in the shortest path
};
typedef struct strNodeInfo NodeInfo;

// Compare NodeInfo by NodeNum
bool compareNodeNum(NodeInfo& N1, NodeInfo& N2)
{
  if (N1.NodeNum < N2.NodeNum) return true;
  return false;
}

// Compare NodeInfo by ShortPath
bool compareShortPath(NodeInfo& N1, NodeInfo& N2)
{
  if (N1.ShortPath < N2.ShortPath) return true;
  return false;
}


// Class PriorityQueue
// The value of the PriorityQueue is to always have access to the vertex with the 
// next shortest link in the shortest path calculation at the top of the queue
class PriorityQueue {
  public:
    PriorityQueue();
    void chgPriority(NodeInfo n);
    void minPriority();
    bool contains(NodeInfo element);
    bool Shorter(NodeInfo n);
    void insert(NodeInfo element);
    NodeInfo top();
    int size();
    
  private:
    list<NodeInfo> pq;
};

// Constructor of PriorityQueue Class
// Creates an empty list of nodes
PriorityQueue::PriorityQueue()
{
  pq.clear();
}

// changes the priority (node value) of queue element
void PriorityQueue::chgPriority(NodeInfo n)
{
  for(list<NodeInfo>::iterator i=pq.begin(); i!=pq.end(); ++i)
    if ((*i).NodeNum == n.NodeNum)
    {
      (*i).ShortPath = n.ShortPath;
      (*i).through = n.through;
    }
  pq.sort(compareShortPath);
}

// removes the top element of the queue 
void PriorityQueue::minPriority()
{
  if (! pq.empty())
  {
    pq.pop_front();
  }
}

// does the queue contain element
bool PriorityQueue::contains(NodeInfo element)
{
  for(list<NodeInfo>::iterator i=pq.begin(); i!=pq.end(); ++i)
    if ((*i).NodeNum == element.NodeNum)
      return true;
  return false;
}

// check if node 'n' has a shorter path than the node with the same number in the queue
bool PriorityQueue::Shorter(NodeInfo n)
{
  for(list<NodeInfo>::iterator i=pq.begin(); i!=pq.end(); ++i)
    if ((*i).NodeNum == n.NodeNum)
      if ((*i).ShortPath > n.ShortPath) return true;
  return false;
}

// insert element into queue
void PriorityQueue::insert(NodeInfo element)
{
  pq.push_back(element);
  pq.sort(compareShortPath);
}

// returns the top element of the queue
NodeInfo PriorityQueue::top()
{
  NodeInfo n = {' ',0};
  if (! pq.empty())
  {
    list<NodeInfo>::iterator i=pq.begin();
    n.NodeNum = (*i).NodeNum;
    n.ShortPath = (*i).ShortPath;
    n.through = (*i).through;
  }
  return n;
}

// Return the number of elements
int PriorityQueue::size()
{
  return pq.size();
}


// ShortestPath Class
// Implements the mechanics of Dijkstra’s algorithm
class ShortestPath
{
  public:
    ShortestPath();
    ShortestPath(Graph g);
    list<int> path(int u, int w);
    int path_size(int u, int w);
  
  private:
    Graph graph;
};

// Construct ShortestPath Class
ShortestPath::ShortestPath()
{
}

// Constructor of ShortestPath Class that stores Graph used by Dijkstra's Algorithm 
ShortestPath::ShortestPath(Graph g)
{
  graph = g;
}

// find shortest path between u-w and returns the sequence of vertices representing shorest path u-v1-v2-…-vn-w.
list<int> ShortestPath::path(int u, int w)
{
  // Initialization
  list<int> candidates = graph.vertices();
  list<int> desiredPath;
  list<NodeInfo> minPaths;
  PriorityQueue p;
  NodeInfo lastSelected, n;

  // Calculate shortest path from 'u' to 'w' (Dijkstra's Algorithm)
  candidates.remove(u);			// Remove 'u' from candidates list
  lastSelected.NodeNum = u;		// Set 'u' as lastSelected
  lastSelected.ShortPath = 0;
  lastSelected.through = u;
  minPaths.push_back(lastSelected);	// Add 'u' to minPath list

  while ((!candidates.empty()) && (lastSelected.NodeNum !=w))
  {
    // For each node in candidate list calculate the cost to reach that candidate through lastSelected 
    for(list<int>::iterator i=candidates.begin(); i != candidates.end(); ++i)
    {
      n.NodeNum=*i;
      n.ShortPath=lastSelected.ShortPath + graph.get_edge_value(lastSelected.NodeNum,*i);
      n.through=lastSelected.NodeNum;
      if (!p.contains(n))	// Add candidate to priority queue if doesn't exist 
        p.insert(n);
      else if (p.Shorter(n))	// Update candidate ShortPath in priority queue if a better path was found
        p.chgPriority(n);
    }
    lastSelected = p.top();			// Select the candidate with ShortPath from priority queue
    p.minPriority();				// Remove it from the priority queue
    minPaths.push_back(lastSelected);		// Add the candidate with min distance to minPath list
    candidates.remove(lastSelected.NodeNum);	// Remove it from candidates list
  }
  
  // Go backward from 'w' to 'u' adding nodes in that path to desiredPath list
  lastSelected=minPaths.back();
  desiredPath.push_front(lastSelected.NodeNum);
  while(lastSelected.NodeNum!=u)
  {
    for(list<NodeInfo>::iterator i=minPaths.begin(); i != minPaths.end(); ++i)
      if ((*i).NodeNum==lastSelected.through)
      {
        lastSelected=(*i);
        desiredPath.push_front(lastSelected.NodeNum);
      }
  }
  return desiredPath;
}

// return the path cost associated with the shortest path
int ShortestPath::path_size(int u, int w)
{
  int PathCost=0;
  int CurrentNode=0;
  list<int> NodePath;
  
  // Calculate the shortest path from 'u' to 'w' and then sum up edge weights in this path
  NodePath = path(u,w);
  CurrentNode=NodePath.front();
  NodePath.pop_front();
  for(list<int>::iterator i=NodePath.begin(); i!=NodePath.end(); ++i)
  {
    PathCost = PathCost + graph.get_edge_value(CurrentNode,(*i));
    CurrentNode = (*i);
  }
  return PathCost; 
}

// Overload operator << to print list<int> variables
ostream &operator<<(ostream &output, list<int> L)
{
   for(list<int>::iterator i=L.begin(); i != L.end(); ++i)
     output << *i << " ";
   return output;
}

void execution (Graph g)
{
  double density = static_cast<double>(g.E())/((static_cast<double>(g.V())*static_cast<double>(g.V())-1)/2)*100;	// calculate real density
// how many vertices
  cout << "Vertices Numbers: " << g.V() << endl;

// what are vertices
  list<int> ver = g.vertices();
  cout << "Vertices are: ";
  for(list<int>::iterator i=ver.begin(); i != ver.end(); ++i)
    cout << *i << " ";
  cout << endl;

// the real density
  cout << "Edges Numbers: " << g.E() << " (density: " << density << "%)" << endl;

// the whole graph
  cout << "Graph: " << endl;
  g.display();

// Display the shortest path
  int reachVert=0, TotalPath=0, AvgPath=0;
  ShortestPath sp(g);
  for (list<int>::iterator i=ver.begin(); i != ver.end(); ++i) 
  {
    int src = ver.front();
    int dst = (*i);
    list<int> p = sp.path(src,dst);
    int ps = sp.path_size(src,dst);
    if (ps != DEADBEEF)
      cout << "ShortestPath (" << src << " to " << dst << "): " << ps << " -> " << p << endl;
    else
      cout << "ShortestPath (" << src << " to " << dst << "): " << "** UNREACHABLE **" << endl;      
    if (ps!=DEADBEEF)
    {
      reachVert++;		// Sum up reached nodes 
      TotalPath += ps;	// Sum up shortest paths found
    }
  }  

  // Calculate average shortest path and print it out
  if (reachVert!=0)
    AvgPath = TotalPath / reachVert;	
  else
    AvgPath = 0;
  cout << endl << "AVG ShortestPath Size (reachVert: " << reachVert << " - TotalPath: " << TotalPath << "): " << AvgPath << endl;

}

// main
int main()
{  
  // 50 nodes, 20% density, 1 min path, 10 max path
  Graph g1(50, 0.2, 1, 10);
  execution(g1);

  // 50 nodes, 40% density, 1 min path, 10 max path
  Graph g2(50, 0.4, 1, 10);
  execution(g2);
  
  return 0;  
}
