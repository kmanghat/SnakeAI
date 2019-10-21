/***************************************************************************//**
 * @file
 ******************************************************************************/
#include "player.h"


int Player::num_moves = 0;
int Player::current_score = 0;

/**************************************************************************//**
 * @par Description:
 * This is the constructor for the player class.
 *****************************************************************************/
Player::Player() {}

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function runs BFS on the start node and returns the size of vector,
 * the number of reachable nodes.
 *
 * @param[in]      graph - the graph of the grid
 * @param[in]      start - node to run bfs on
 * @returns        the number of reachable nodes
 *
 *****************************************************************************/
int Player::reachableNodes(Graph graph,int start)
{
    BFS bfs(graph.Vertices());
    vector<int> traversal = bfs.traverse(start);
    return traversal.size();
}


/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function checks if the given row and column is clear.
 *
 * @param[in]      row - row of the grid
 * @param[in]      col - column of the grid
 * @returns        true if clear
 *
 *****************************************************************************/
bool Player::isClear(int row, int col, const int *grid)
{
    if(grid[row*PLAYFIELD_WIDTH + col] == 0)
    {
        return true;
    }
    return false;
}

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function gets all the available cells on the board
 *
 * @param[in]      grid - the 1D array of the playfield
 * @returns        the number of available cells
 *
 *****************************************************************************/
int Player::getAvailableCells(const int *grid)
{
    int count = 0;
    //calculates number of clear cells on the board
    for(int i = 0; i < PLAYFIELD_HEIGHT*PLAYFIELD_WIDTH; i++)
    {
        if(grid[i] != TAIL_VALUE)
        {
            count++;
        }
    }
    return count;
}

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function gets the location of the provided value on the 1D grid
 *
 * @param[in]      grid - the playfield grid
 * @param[in]      value - the value to be found
 * @returns        the location on the grid
 *
 *****************************************************************************/
int Player::getLoc(const int *grid, int value)
{
    //gets location of provided value
    for(int i = 0 ; i < PLAYFIELD_HEIGHT*PLAYFIELD_WIDTH; i++)
    {
        if(grid[i] == value)
        {
            return i;
        }
    }
    return 0;
}

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function checks if the current node is valid
 *
 * @param[in]      h_row- row of current node
 * @param[in]      h_col- column of current node
 * @returns        true if valid
 *
 *****************************************************************************/
bool Player::isValid(int h_row, int h_col)
{
    //Checks if row and col is valid
    if(h_row < 0 || h_col < 0 || h_row == PLAYFIELD_HEIGHT || h_col == PLAYFIELD_WIDTH)
    {
        return false;
    }
    return true;
}


/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function finds the best move to make if no path is found by dijkstras
 * It runs bfs on all 4 directions and moves in the direction that can visit
 * the most number of cells
 *
 * @param[in]      h_loc - location of head
 * @param[in]      graph- the graph of the playfield
 * @returns        the direction to move
 *
 *****************************************************************************/
ValidMove Player::getNaiveDirection(int h_loc, Graph graph)
{
    //Calculates row and col of every direction
    int h_row = h_loc/PLAYFIELD_WIDTH;
    int h_col = h_loc%PLAYFIELD_WIDTH;
    int up_row = h_row+1;
    int up_col = h_col;
    int down_row = h_row - 1;
    int down_col = h_col;
    int left_row = h_row;
    int left_col = h_col - 1;
    int right_row = h_row;
    int right_col = h_col + 1;

    int bfs_up = 0;
    int bfs_down = 0;
    int bfs_left = 0;
    int bfs_right = 0;

    //checks if within bounds then runs it
    if(isValid(up_row,up_col))
    {
        bfs_up = reachableNodes(graph,h_loc+PLAYFIELD_WIDTH);
    }
    if(isValid(down_row,down_col))
    {
        bfs_down = reachableNodes(graph,h_loc-PLAYFIELD_WIDTH);
    }
    if(isValid(left_row,left_col))
    {
        bfs_left = reachableNodes(graph,h_loc-1);
    }
    if(isValid(right_row,right_col))
    {
        bfs_right = reachableNodes(graph,h_loc+1);
    }

    //Finds max cells that you can get to after running bfs
    int temp = max(bfs_up,bfs_down);
    int temp1 = max(bfs_left,temp);
    int max_final = max(bfs_right,temp1);

    //ensures that tail does not reach the last row to leave space for escape
    if(max_final == bfs_down && (bfs_left > 2 || bfs_right > 2) && (h_row == 1))
    {
        if(max_final != bfs_up)
        {
            max_final = max(bfs_left,bfs_right);
            bfs_down = -1;
        }
    }

    //Moves in the direction of max available nodes
    if(max_final == bfs_up)
    {
        return UP;
    }
    if(max_final == bfs_down)
    {
        return DOWN;
    }
    if(max_final == bfs_left)
    {
        return LEFT;
    }
    if(max_final == bfs_right)
    {
        return RIGHT;
    }
    return NONE;
}

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function checks if the game is hung
 *
 * @param[in]      score - the current score of the game
 * @returns        if the game is hung
 *
 *****************************************************************************/
bool Player::isHang(int score)
{
    //Makes sure the game is not stuck
    if(score == current_score)
    {
        num_moves++;
    }
    else
    {
        current_score = score;
        num_moves = 0;
    }

    if(num_moves > MOVE_THRESH)
    {
        return true;
    }
    return false;
}

/**************************************************************************//**
 * @author Keshav Manghat
 *
 * @par Description:
 * This function makes the move indicated by dijkstras or the naive method
 * if no path exists.
 *
 * @param[in]      pf - playfield
 * @returns        the move to be made
 *
 *****************************************************************************/
ValidMove Player::makeMove(Playfield *pf)
{
    //If the game seems to be stuck then I end it
    if(isHang(pf->getScore()))
    {
        return NONE;
    }
    const int *grid = pf->getGrid();
    //create a graph from the given grid and run dijkstras on it
    Graph G(grid,PLAYFIELD_WIDTH, PLAYFIELD_HEIGHT);
    vector <vector<edge>> graph = G.Vertices();
    Dijkstras dijkstras(graph);

    //Get path from head to food from dijkstras
    vector <int> path;
    int h_loc = getLoc(grid,HEAD_VALUE);
    int f_loc = getLoc(grid,FOOD_VALUE);
    dijkstras.sssp(h_loc);
    path = dijkstras.getPath(f_loc);

    //Gets the number of available cells in the grid
    int available = getAvailableCells(grid);
    //Set a threshhold value before visiting a node
    int thresh = available * PERCENT_AVAILABLE;
    int curr = path[0];
    int next = path[1];

    //remove the head of the snake so that it is blocked before running bfs
    //makes no sense if I don't remove it, every direction returns same number
    //of reachable nodes
    G.removeVertex(h_loc);

    //run BFS on the node that dijkstras tells me to move to,
    //if I can visit a certain numbe rof nodes from there then perform the move
    BFS bfs(G.Vertices());
    if(path.size() != 0)
    {
        if(next == curr - 1)
        {
            if(reachableNodes(G,curr-1) > thresh)
            {
                return LEFT;
            }
        }
        if(next == curr + 1)
        {
            if(reachableNodes(G,curr+1) > thresh)
            {
                return RIGHT;
            }
        }
        if(next == curr + PLAYFIELD_WIDTH)
        {
            if(reachableNodes(G,curr + PLAYFIELD_WIDTH) > thresh)
            {
                return UP;
            }
        }
        if(next == curr - PLAYFIELD_WIDTH)
        {
            if(reachableNodes(G,curr - PLAYFIELD_WIDTH) > thresh)
            {
                return DOWN;
            }
        }
    }
    //No move or path found go here
    return getNaiveDirection(h_loc,G);
}



