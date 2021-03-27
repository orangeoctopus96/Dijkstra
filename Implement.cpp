#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<ctime>
#include<cstdlib>
using namespace std;

// INFINIT is used to represent the edge between x and y doesn't exist 
const int INFINIT=999999;

//==============================================================================
// Node definitions
//==============================================================================
typedef struct Nodeinfo Node;
struct Nodeinfo
{
  int number;	
  int weight;	
  list<Node> edges;	
};

//==============================================================================
// Graph Class
// Implement Graph via adjacent list
//==============================================================================
class Graph
{
public:
  Graph();
  Graph(int VerticesNum, int initialValue);
  int get_edge_value(int x, int y);
  void set_edge_value(int x, int y, int v);
  bool adjacent(int x, int y);
  list<int> neighbors(int x);
  int V();
  int E();
  list<char> vertices();
  void show();

private:
  int VerticesNum;			// Number of nodes of the Graph
  int EdgesNum;			// Number of edges of the Graph
  list<Node> adjList;		// Adjacency list representing the Graph
}

// Create an empty graph
Graph::Graph()
{
  VerticesNum = 0;
  EdgesNum = 0;
  adjList.clear();
}

// returns the value associated to the edge (x,y)
// returns INFINITY if edge doesn't exist
int Graph::get_edge_value(int x, int y)
{
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
  {
    if ((*i).number==x)
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
        if ((*j).number==y)
        return (*j).weight; 
      }
  }
  return INFINIT;
}

// sets the value associated to the edge (x,y) to v
void Graph::set_edge_value(int x, int y, int value)
{
  bool found;
  // Add 'y' in the list of 'x' neighbors (if doesn't exist)
  // Set edge weight to value
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
  {
    if ((*i).number==x)
    {
      found = false;
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
        if ((*j).number==nodeNumbers[y])
        {  
          (*j).weight=v;
          found = true;
        }
      }
      if (!found)
      {
        Node NewNode;
        NewNode.number = y;
        NewNode.weight = v;
        NewNode.edges.clear();
        (*i).edges.push_back(NewNode);
      }
    }
  }

// tests whether there is an edge from node x to node y
bool Graph::adjacent(int x, int y)
{
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
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
  list<int> adjNodes;
  for(list<Node>::iterator i=adjList.begin(); i != adjList.end(); ++i)
  {
    if ((*i).number==x)
    {
      for(list<Node>::iterator j=(*i).edges.begin(); j != (*i).edges.end(); ++j)
      {
        adjNodes.push_back((*j).number);
      }
    }
  }
  return adjNodes;
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








