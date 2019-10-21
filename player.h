/***************************************************************************//**
 * @file
 ******************************************************************************/
#ifndef __PLAYER_H
#define __PLAYER_H
#include <list>
#include "playfield.h"
#include "graph.h"
#include "dijkstras.h"
#include <bits/stdc++.h>

/**The percent of available vertices*/ 
#define PERCENT_AVAILABLE 0.50
/** The number of moves before it decides a hang state*/ 
#define MOVE_THRESH 500
/*!
 * @brief This is the player class that performs the move for the snake
 */
class Player
{
public:
    Player ();
    ValidMove makeMove(Playfield *);
private:
    static int num_moves; /*!< The number of moves performed without progress */
    static int current_score; /*!< The current score of the game */
    bool isHang(int);
    bool isClear(int row, int col, const int *grid);
    int getAvailableCells(const int *grid);
    int getLoc(const int *grid, int value);
    bool isValid(int h_row, int h_col);
    ValidMove getNaiveDirection(int h_loc, Graph graph);
    int reachableNodes(Graph graph,int start);
};

#endif

