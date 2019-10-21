/***************************************************************************//**
 * @file
 ******************************************************************************/
#ifndef DIJKSTRAS_H
#define DIJKSTRAS_H
#include "graph.h"
#include "bfs.h"

/*!
 * @brief This is the class that runs dijkstras on a graph
 */
class Dijkstras
{
private:
    vector <int> parent; /*!< To retrieve the path */  
    vector<int> dist; /*!< The distance array */ 
    vector<vector<edge>> adj; /*!< The graph adjacency list */ 
public:
    Dijkstras(vector<vector<edge>> v);
    void sssp(int start);
    vector<int> getPath(int dest);

};

#endif
