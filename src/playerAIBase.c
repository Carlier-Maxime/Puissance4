/**
 * @file test/playerAIBase.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player ai base implementation
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "playerAIBase.h"
#include "error.h"

static bool initRng=false; //!< boolean is false before initRandom()

/**
 * initialize random value
 */
static void initRandom() {
    srand(time(NULL)*GRID_WIDTH);
    initRng=true;
}

static void destroy(Player *player) {
    if (!player) {
        Player_setError(NO_SELF_ERROR);
        return;
    }
    free(player->name);
    free(player);
    Player_setError(NO_ERROR);
}

Player *PlayerAIBase_create(const char* name) {
    if (!name) {
        Player_setError(NO_NAME_ERROR);
        return NULL;
    }
    Player *player = malloc(sizeof(Player));
    if (!player) {
        Player_setError(NO_MEMORY_ERROR);
        return NULL;
    }
    *player = (Player) {
            strdup(name),
            NULL,
            destroy
    };
    if (!player->name) {
        Player_setError(NO_MEMORY_ERROR);
        return NULL;
    }
    Player_setError(NO_ERROR);
    if (!initRng) initRandom();
    return player;
}

/**
 * get a win table : contains true in the index column win and contains number of win in index=GRID_WIDTH
 * @param grid : the grid of the game
 * @param tokenValue : token value of player
 * @return win table, ex : [0,1,0,0,0,1,0,2] (GRID_WIDTH=7)
 */
unsigned char* getWinTable(Grid *grid, unsigned char tokenValue) {
    unsigned char *t = malloc(sizeof(unsigned char)*GRID_WIDTH);
    t[GRID_WIDTH]=0;
    for (unsigned char i = 0; i < GRID_WIDTH; i++) {
        grid->placeToken(grid,i,tokenValue);
        t[i]=grid->isInWinAlignment(grid,i);
        if (t[i]) t[GRID_WIDTH]++;
        grid->removeTopToken(grid,i);
    }
    return t;
}

/**
 * calculate the win weight of each column
 * @param grid : the grid
 * @param column : index of column
 * @param tokenValue : the value of token of player
 * @param depth : traversal depth to calculate the win weight of each column
 * @param enemyWinTable : a array boolean contains true in the index column win of enemy and contains number of win in index=GRID_WIDTH
 * @return win weight of each column
 */
double weightColumn(Grid *grid, unsigned char column, unsigned char tokenValue, unsigned char depth, const unsigned char enemyWinTable[GRID_WIDTH]) {
    Player_setError(NO_ERROR);
    if (!grid) {
        Player_setError(NO_GRID_ERROR);
        return -1;
    }
    if (column>=GRID_WIDTH) {
        Player_setError(COLUMN_OUT_OF_RANGE_ERROR);
        return -1;
    }
    if (tokenValue != 1 && tokenValue != 2) {
        Player_setError(TOKEN_VALUE_ERROR);
        return -1;
    }
    if (!grid->placeToken(grid,column,tokenValue)) return -1;
    if (grid->isInWinAlignment(grid,column)) {
        grid->removeTopToken(grid,column);
        return 100;
    }
    if (enemyWinTable[GRID_WIDTH]>1) {
        grid->removeTopToken(grid,column);
        return 0;
    }
    if (enemyWinTable[GRID_WIDTH]==1 && !enemyWinTable[column]) {
        grid->removeTopToken(grid,column);
        return 0;
    }
    if (depth==0) {
        grid->removeTopToken(grid,column);
        return 1;
    }
    if (grid->placeToken(grid,column,(tokenValue==1) ? 2 : 1)) {
        if (grid->isInWinAlignment(grid,column)) {
            grid->removeTopToken(grid,column);
            grid->removeTopToken(grid,column);
            return 1;
        }
    }
    double s=0, s2;
    unsigned char div=0, div2;
    for (unsigned char i=0; i<GRID_WIDTH; i++) {
        if (!grid->placeToken(grid,i,(tokenValue==1) ? 2 : 1)) continue;
        unsigned char *enemyWinTable2 = getWinTable(grid,(tokenValue==1) ? 2 : 1);
        s2=0;
        div2=0;
        for (unsigned char j=0; j<GRID_WIDTH; j++) {
            double w = weightColumn(grid,j,tokenValue,depth-1,enemyWinTable2);
            if (w!=-1) {
                s2+=w;
                div2++;
            }
        }
        free(enemyWinTable2);
        grid->removeTopToken(grid,i);
        if (div2>0) {
            s+=s2/div2;
            div++;
        }
    }
    grid->removeTopToken(grid,column);
    if (div>0) return 1+s/div;
    return 1;
}

short PlayerAIBase_choiceColumn(View *view, unsigned char tokenValue, unsigned char depth) {
    if (!view) {
        Player_setError(NO_VIEW_ERROR);
        return -1;
    }
    double l[GRID_WIDTH];
    short column=0;
    unsigned char *enemyWinTable = getWinTable(view->grid,(tokenValue)==1 ? 2 : 1);
    for (short i = 0; i < GRID_WIDTH; i++) {
        l[i] = weightColumn(view->grid,i,tokenValue,depth,enemyWinTable);
        if (l[i]==-1) return -1;
        if (l[i]>l[column]) column=i;
    }
    free(enemyWinTable);
    return column;
}