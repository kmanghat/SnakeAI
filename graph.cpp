#include "graph.h"
#include "playfield.h"

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * Constructor for the graph class
 *
 *****************************************************************************/
Graph::Graph()
{
    numEdges = 0;
    adj.resize(MAX_VERTICES);
}


/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * Constructor for the graph class when provided with a 1d grid
 *
 * @param[in]      grid - the 1d playfield
 * @param[in]      width - width of playfield
 * @param[in]      height - height of playfield
 *
 *****************************************************************************/
Graph::Graph(const int *grid,int width,int height)
{
    numEdges = 0;
    adj.resize(MAX_VERTICES);
    int di[4] = {1,-1,0,0};
    int dj[4] = {0,0,1,-1};
    for(int row = 0 ; row < height; row++)
    {
        for(int col = 0 ;  col < width; col++)
        {
            for(int k = 0 ; k < 4; k++)
            {
                int newRow = row + di[k];
                int newCol = col + dj[k];

                if(newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                {
                    int u = row*width+col;
                    int v = newRow*width + newCol;
                    if(grid[u] != TAIL_VALUE && grid[v] != TAIL_VALUE)
                    {
                        int r = row;
                        int c = col;
                        //This creates the mountain weighted graph, outer weights are lesser compared to inner
                        if(r > height/2)
                        {
                            r = (height-1)-r;
                        }
                        if(c > width/2)
                        {
                            c = (width-1)-c;
                        }
                        addEdge(u,v,pow(min(r,c),EDGE_WEIGHT_POWER));

                    }

                }
            }
        }
    }
}

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function removes a vertex from the graph
 *
 * @param[in]      num - the vertex number to be removed
 *
 *****************************************************************************/
void Graph:: removeVertex(int num)
{
    for(unsigned int i = 0 ; i < adj.size(); i++)
    {
        for(vector<edge>::iterator it = adj[i].begin(); it != adj[i].end();)
        {
            if(it->v == num || it->u == num)
            {
                it = adj[i].erase(it);
            }
            else
            {
                it++;
            }
        }
    }
}


/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * Getter for number of edges in the graph
 *
 * @returns number of edges
 *****************************************************************************/
int Graph::E() const
{
    return numEdges;
}


/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * Adds an edge from u to v with weight w
 *
 * @param[in]      u - vertex from which edge originates
 * @param[in]      v - vertex at which edge terminates
 * @param[in]      w - weight of edge
 *
 *****************************************************************************/
void Graph::addEdge(int u, int v,int w)
{
    adj[u].push_back(edge(u,v,w));
    numEdges++;
}


/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * Getter for adjacent edges
 *
 * @param[in]      v - the vertex of which adjacent edges are required
 * @returns        the adjacent edges
 *
 *****************************************************************************/
vector<edge> Graph::adjacent(int v)
{
    return adj[v];
}


/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * Getter for the graph adjacency list
 *
 * @returns adjacency list of graph
 *****************************************************************************/
vector<vector<edge>> Graph::Vertices()
{
    return adj;
}





