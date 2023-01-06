/**
 * @file src/viewTerminal.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view terminal implementation
 * @version 0.1
 * @date 2023-01-06
 * @copyright Copyright (c) 2023
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "viewTerminal.h"
#include "error.h"

static bool render(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return false;
    }
    if (!view->grid) {
        View_setError(NO_GRID_ERROR);
        return false;
    }
    printf("--PUISSANCE 4--\n");
    for (unsigned i=0; i<GRID_HEIGHT; i++) {
        bool is_floor = i==GRID_HEIGHT-1;
        printf("|");
        for (unsigned j=0; j<GRID_WIDTH; j++) {
            switch (view->grid->tab[i][j]) {
                case 1:
                    printf("X|");
                    break;
                case 2:
                    printf("O|");
                    break;
                default: printf("%c|",is_floor ? '_' : ' ');
            }
        }
        printf("\n");
    }
    printf("\n");
    View_setError(NO_ERROR);
    return true;
}

static short choiceColumn(View *view) {
    printf("Choisie la colonne où inséré ton pion (0-%d) : ",GRID_WIDTH-1);
    short val=-1;
    while (val<0 || val>=GRID_WIDTH) scanf("%hd",&val);
    View_setError(NO_ERROR);
    return val;
}

static bool showPlayer(View *view, Player *player) {
    if (!player) {
        View_setError(NO_PLAYER_ERROR);
        return false;
    }
    printf("%s\n",player->name);
    View_setError(NO_ERROR);
    return true;
}

static bool win(View *view, Player *player) {
    if (!player) {
        View_setError(NO_PLAYER_ERROR);
        return false;
    }
    printf("%s à gagner !!\n",player->name);
    View_setError(NO_ERROR);
    return true;
}

bool invalidColumn(View *view, unsigned char column) {
    if (column>=GRID_WIDTH) {
        View_setError(COLUMN_OUT_OF_RANGE_ERROR);
        return false;
    }
    printf("la colonne d'index %d n'est pas valide !\n",column);
    View_setError(NO_ERROR);
    return true;
}

static PlayerType choicePlayer(View *view) {
    printf("Choisie le type de joueur (human/ai_easy/ai_normal/ai_hard) : ");
    char s[16] = "none";
    while (strcmp(s,"human")!=0 && strcmp(s,"ai_easy")!=0 && strcmp(s,"ai_normal")!=0 && strcmp(s,"ai_hard")!=0) scanf("%15s",s);
    if (strcmp(s, "human") == 0) return PLAYER_HUMAN;
    else if (strcmp(s, "ai_easy") == 0) return PLAYER_AI_EASY;
    else if (strcmp(s, "ai_normal") == 0) return PLAYER_AI_NORMAL;
    else if (strcmp(s, "ai_hard") == 0) return PLAYER_AI_HARD;
    else return PLAYER_NONE;
}

static bool fakeChoiceColumn(struct View_ *view) {
    printf("choice column...\n");
    View_setError(NO_ERROR);
    return true;
}

static void destroy(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return;
    }
    free(view);
    View_setError(NO_ERROR);
}

View* ViewTerminal_create(Grid *grid) {
    if (!grid) {
        View_setError(NO_GRID_ERROR);
        return NULL;
    }
    View *v = (View *) malloc(sizeof(View));
    if (!v) {
        View_setError(NO_MEMORY_ERROR);
        return NULL;
    }
    *v = (View) {
            grid,
            NULL,
            render,
            choiceColumn,
            showPlayer,
            win,
            invalidColumn,
            choicePlayer,
            fakeChoiceColumn,
            destroy
    };
    View_setError(NO_ERROR);
    return v;
}