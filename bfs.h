/***************************************************************************//**
 * @file
 ******************************************************************************/
#ifndef BFS_H
#define BFS_H
#include "graph.h"

/*!
 * @brief This is the class that runs bfs on the graph
 */
class BFS
{
private:
    vector<vector<edge>> adj; /*!< adjacency list of the graph */
public:
    BFS(vector<vector<edge>> v);
    vector <int> traverse(int start);
};

#endif
