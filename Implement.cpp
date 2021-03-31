#include<iostream>
#include<ctime>
#include<cstdlib>
#include<list>
using namespace std;

// DEADBEEF means no edge between two nodes 
const int DEADBEEF=9999;

// Node definitions
typedef struct NodeInfo Node;
struct NodeInfo
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


// Path info for node
struct NodePathInfo
{
  int NodeNum;      // Node Number
  int ShortPath;    // Shortest path found to the Node
  int through;      // Node that precede Node Number in the shortest path
};
typedef struct NodePathInfo NodePath;

// compare ShortPath for NodePath
bool compareShortPath(NodePath& N1, NodePath& N2)
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
    void chgPriority(NodePath n);
    void minPriority();
    bool contains(NodePath element);
    bool shorter(NodePath n);
    void insert(NodePath element);
    NodePath top();
    int size();
    
  private:
    list<NodePath> pqueue;
};

// Constructor of PriorityQueue Class
// Creates an empty list of nodes
PriorityQueue::PriorityQueue()
{
  pqueue.clear();
}

// changes the priority (node value) of queue element
void PriorityQueue::chgPriority(NodePath n)
{
  for(list<NodePath>::iterator i=pqueue.begin(); i!=pqueue.end(); ++i)
    if ((*i).NodeNum == n.NodeNum)
    {
      (*i).ShortPath = n.ShortPath;
      (*i).through = n.through;
    }
  pqueue.sort(compareShortPath);
}

// removes the top element of the queue 
void PriorityQueue::minPriority()
{
  if (! pqueue.empty())
  {
    pqueue.pop_front();
  }
}

// does the queue contain element
bool PriorityQueue::contains(NodePath element)
{
  for(list<NodePath>::iterator i=pqueue.begin(); i!=pqueue.end(); ++i)
    if ((*i).NodeNum == element.NodeNum)
      return true;
  return false;
}

// check if node 'n' has a shorter path than the node with the same number in the queue
bool PriorityQueue::shorter(NodePath n)
{
  for(list<NodePath>::iterator i=pqueue.begin(); i!=pqueue.end(); ++i)
    if ((*i).NodeNum == n.NodeNum)
      if ((*i).ShortPath > n.ShortPath) return true;
  return false;
}

// insert element into queue
void PriorityQueue::insert(NodePath element)
{
  pqueue.push_back(element);
  pqueue.sort(compareShortPath);
}

// returns the top element of the queue
NodePath PriorityQueue::top()
{
  NodePath n = {' ',0};
  if (! pqueue.empty())
  {
    list<NodePath>::iterator i=pqueue.begin();
    n.NodeNum = (*i).NodeNum;
    n.ShortPath = (*i).ShortPath;
    n.through = (*i).through;
  }
  return n;
}

// Return the number of elements
int PriorityQueue::size()
{
  return pqueue.size();
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
  list<int> points = graph.vertices();
  list<NodePath> pathway;

  // use Dijkstra's Algorithm to calculate shortest path from 'u' to 'w'
  NodePath currentmini;
  currentmini.NodeNum = u;        // set 'u' as currentmini because now the minimum is 0
  currentmini.ShortPath = 0;      // set shortest path 0 because 'u' to 'u' is 0
  currentmini.through = u;
  pathway.push_back(currentmini); // add 'u' to pathway list as the start
  points.remove(u);               // remove 'u' because it's the start point

  NodePath cursor;                // it's like cursor to find next node
  PriorityQueue queue;            // it's a queue contains info between different nodes to 'u'
  while ((!points.empty()) && (currentmini.NodeNum !=w))
  {
    // from currentmini to other points in the list, check the distance
    for(list<int>::iterator i = points.begin(); i != points.end(); ++i)
    {
      cursor.NodeNum = *i;
      cursor.ShortPath = currentmini.ShortPath + graph.get_edge_value(currentmini.NodeNum, *i);
      cursor.through = currentmini.NodeNum;
      if (!queue.contains(cursor))      // add point to queue if not there
        queue.insert(cursor);
      else if (queue.shorter(cursor))   // update queue point if the route now is shorter
        queue.chgPriority(cursor);
    }
    currentmini = queue.top();          // from the queue, select the current minimum path point
    queue.minPriority();                // remove it from the queue
    pathway.push_back(currentmini);     // add the current minimum distance point to pathway list
    points.remove(currentmini.NodeNum); // remove it from points list
  }
  
  // adding nodes from 'w' to 'u' to route list
  list<int> route;
  currentmini=pathway.back();
  route.push_front(currentmini.NodeNum);
  while(currentmini.NodeNum!=u)
  {
    for(list<NodePath>::iterator i=pathway.begin(); i != pathway.end(); ++i)
      if ((*i).NodeNum==currentmini.through)
      {
        currentmini=(*i);
        route.push_front(currentmini.NodeNum);
      }
  }
  return route;
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

void execution (Graph g)
{
// how many vertices
  cout << "Vertices Numbers: " << g.V() << endl;

// what are vertices
  list<int> ver = g.vertices();
  cout << "Vertices are: ";
  for(list<int>::iterator i = ver.begin(); i != ver.end(); ++i)
    cout << *i << " ";
  cout << endl;

// the real density
  int AllPossibleEdges = g.V() * (g.V()-1) / 2; // calculate all possible edges for graph
  double density = static_cast<double>(g.E())/static_cast<double>(AllPossibleEdges)*100;	// calculate real density
  cout << "Edges Numbers: " << g.E() << " (density: " << density << "%)" << endl;

// the edges 
  cout << "Edges are: " << endl;
  g.display();

// the shortest path
  int CompletionPath=0;
  int TotalLength=0; 
  int AvgLength=0;
  ShortestPath shortestpath(g);
  for (list<int>::iterator i=++ver.begin(); i != ver.end(); ++i) 
  {
    int start = ver.front();
    int destination = (*i);
    list<int> route = shortestpath.path(start,destination);
    int length = shortestpath.path_size(start,destination);
    if (length != DEADBEEF)
    {
      cout << "From Node" << start << " to Node " << destination << ":    " << "Distance between is " << length << ".    Route is ";
      for(list<int>::iterator i = route.begin(); i != route.end(); ++i)
        if (i != route.begin())
          cout << " -> " << *i;
        else
          cout << *i;
      cout << endl;
    }
    else
      cout << "From Node" << start << " to Node " << destination << ": " << "No Path" << endl;      
    if (length!=DEADBEEF)
    {
      CompletionPath++;		// Sum up reached nodes 
      TotalLength = TotalLength + length;	// Sum up shortest paths found
    }
  }  

  // average path length
  if (CompletionPath!=0)
    AvgLength = TotalLength / CompletionPath;	
  else
    AvgLength = 0;
  cout << endl;
  cout << "Total " << CompletionPath << " paths has been calculated. " << endl;
  cout << "Total path lengths are " << TotalLength << endl;
  cout << "Average path length is " << AvgLength << endl;

}

// main
int main()
{  
  // 50 nodes, 20% density, 1 min path, 10 max path
  Graph g1(50, 0.2, 1, 10);
  execution(g1);

  // 50 nodes, 40% density, 1 min path, 10 max path
//  Graph g2(50, 0.4, 1, 10);
//  execution(g2);
  
  return 0;  
}
