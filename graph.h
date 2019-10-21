#ifndef GRAPH_H
#define GRAPH_H
#include "playfield.h"
#include <bits/stdc++.h>

using namespace std;

/**Maximum number of vertices possible in the graph and some leeway*/ 
#define MAX_VERTICES (PLAYFIELD_WIDTH*PLAYFIELD_HEIGHT + 20)

/**Power that edge weight is raised to*/ 
#define EDGE_WEIGHT_POWER 4

/*!
 * @brief Each edge of the graph
 */
struct edge
{
    int u; ///< The vertex from which edge originates
    int v; ///< The vertext to which edge terminates
    int weight; ///< Weight of edge
    
    /*!* @brief Constructor for graph */
    edge(int _u,int _v, int _w)
    {
        u = _u;
        v = _v;
        weight = _w;
    }
};

/*!
 * @brief This is the class that constructs the graph
 */
class Graph
{
private:
    vector<vector<edge>>adj; ///< Adjacency list of graph
    int numEdges; ///<  Number of edges in the graph
public:
    Graph();
    Graph(const int *grid,int width,int height);
    vector<edge> adjacent(int);
    virtual void addEdge(int,int,int);
    int E() const;
    vector<vector<edge>> Vertices();
    void removeVertex(int num);
};

#endif
