/***************************************************************************//**
 * @file
 ******************************************************************************/
#include "dijkstras.h"

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * Constructor for dijkstras
 *
 * @param[in]      v - the graph
 *
 *****************************************************************************/
Dijkstras::Dijkstras(vector<vector<edge>> v)
{
    adj = v;
}

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function runs dijkstras
 *
 * @param[in]      start - start location for dijkstras
 *
 *****************************************************************************/
void Dijkstras::sssp(int start)
{
    dist.resize(MAX_VERTICES,20000000);
    parent.resize(adj.size(),-1);
    dist[start] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    //push first element into pq
    pq.push(make_pair(dist[start], start));

    //loop till empty
    while(!pq.empty())
    {
        //u is node and d is distance of that node from s
        int u = pq.top().second;
        int d = pq.top().first;

        //remove edge
        pq.pop();

        //if distance is greater current distance then ignore
        if(d > dist[u])
            continue;

        //loop through connected edges of u
        for(unsigned int i = 0; i < adj[u].size(); i++)
        {
            //v is the node u is connceted to w is its weight
            int v = adj[u][i].v;
            int w = adj[u][i].weight;

            //if w + curr w is less that in node v then store it
            if(w + dist[u] < dist[v])
            {
                dist[v] = w + dist[u];
                parent[v] = u;
                pq.push(make_pair(dist[v],v));
            }
        }
    }

}

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function gets the path found by dijkkstras
 *
 * @param[in]      dest - the path destination
 * @returns        the path
 *
 *****************************************************************************/
vector<int> Dijkstras::getPath(int dest)
{

    vector <int> path;
    stack<int> s;
    int u = dest;
    while(parent[u] != -1)
    {
        s.push(u);
        u = parent[u];
    }
    s.push(u);
    while(!s.empty())
    {
        int pos = s.top();
        if(pos < MAX_VERTICES)
        {
            path.push_back(pos);
        }
        s.pop();
    }
    return path;
}
