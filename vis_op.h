#ifndef vis_op
#define vis_op

#include "visualize.h"
#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

int add_line = 10;

void visPrintCurrentOperation(std::string operation_name)
{
    if (!IS_VIS)
        return;
    move(max_row / ratio + add_line, 0);
    clrtoeol();
    move(max_row / ratio + add_line, max_col / ratio);
    printw("%s", operation_name.c_str());
    mvchgat(max_row / ratio + add_line, max_col / ratio, operation_name.length(), A_STANDOUT, 0, NULL);
}

void visPrintSecondCurrentOperation(std::string operation_name)
{
    if (!IS_VIS)
        return;
    move(max_row / ratio + add_line + 2, 0);
    clrtoeol();
    move(max_row / ratio + add_line + 2, max_col / ratio);
    printw("%s", operation_name.c_str());
    mvchgat(max_row / ratio + add_line + 2, max_col / ratio, operation_name.length(), A_STANDOUT, 0, NULL);
}

void visPrintThirdCurrentOperation(std::string operation_name)
{
    if (!IS_VIS)
        return;
    move(max_row / ratio + add_line + 4, 0);
    clrtoeol();
    move(max_row / ratio + add_line + 4, max_col / ratio);
    printw("%s", operation_name.c_str());
    mvchgat(max_row / ratio + add_line + 4, max_col / ratio, operation_name.length(), A_STANDOUT, 0, NULL);
}

#endif