/***************************************************************************//**
 * @file
 ******************************************************************************/
#include "bfs.h"
/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * Constructor for bfs
 *
 * @param[in]      v - the adjacency list
 *
 *****************************************************************************/
BFS::BFS(vector<vector<edge>> v)
{
    adj = v;
}

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function runs bfs
 *
 * @param[in]      start - the start location for bfs
 * @returns        the result of bfs
 *
 *****************************************************************************/
vector<int> BFS::traverse(int start)
{
    //bfs
    bool visited[MAX_VERTICES];
    vector <int> res;
    for(int i = 0 ; i < MAX_VERTICES; i++)
    {
        visited[i] = false;
    }
    list<int> queue;
    visited[start] = true;
    queue.push_back(start);
    res.push_back(start);

    while(!queue.empty())
    {
        start = queue.front();
        res.push_back(start);
        queue.pop_front();

        for(unsigned int i = 0; i < adj[start].size(); i++)
        {
            if(!visited[adj[start][i].v])
            {
                visited[adj[start][i].v] = true;
                queue.push_back(adj[start][i].v);
            }
        }


    }
    return res;
}

