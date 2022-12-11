//
// Created by Lenovo on 11/12/2022.
//

#ifndef PUISSANCE4_VIEWTERMINAL_H
#define PUISSANCE4_VIEWTERMINAL_H

#include "view.h"

View* ViewTerminal_create(Grid *grid);
unsigned ViewTerminal_getErrorCode();
char* ViewTerminal_getErrorMsg();
void ViewTerminal_printError();

#endif //PUISSANCE4_VIEWTERMINAL_H
