#ifndef visualize
#define visualize

#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <typeinfo>
#include <stdio.h>
#include <string.h>
#include <sstream>
//#include "visualize.h"
//#include "is_vis.h"

bool IS_VIS = false;

void visPrintCurrentArray();
void visSetAttr(int index, int attribute_to_set);
void visRemoveAttr(int index);
void visCrossBetween(int index1, int index2, int line);
struct IndexLength visFindByIndex(int index);

int max_row, max_col, cur_x, cur_y;
int merge_line, merge_cur_x;
std::string current_array, temp_merge_array;
std::string bosluk = " ";
int sleep_time = 500000;
int vis_wait_count = 0;

int row_ratio = 6;
int col_ratio = 6;
int ratio = 5;

bool first_quick = true;

struct IndexLength
{
    int index;
    int length;
};

void startScreen()
{
    initscr();
    cbreak();
    noecho();
    //raw();
    curs_set(0);
    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    getmaxyx(stdscr, max_row, max_col);
    merge_cur_x = max_col / ratio;
    move(max_row / ratio, max_col / ratio);
}

void endScreen()
{
    endwin();
}

void visWait()
{
    if (!IS_VIS)
        return;
    vis_wait_count++;
    refresh();
    usleep(sleep_time);
}

void visMergeCrossVertical(int index)
{
    if (!IS_VIS)
        return;
    IndexLength element = visFindByIndex(index);
    move(max_row / ratio + 1 + merge_line, max_col / ratio + element.index + element.length);
    printw("|");
}

void visCrossVertical(int index)
{
    if (!IS_VIS)
        return;
    IndexLength element = visFindByIndex(index);

    move(max_row / ratio + 2, max_col / ratio + element.index + element.length);
    printw("|");

    // current_array.replace(element.index+element.length,1,"| ");
    // move(max_row/ratio+2,max_col/ratio);
    // visPrintCurrentArray();
}

void visCrossVerticalToLeft(int index)
{
    if (!IS_VIS)
        return;
    IndexLength element = visFindByIndex(index);

    // char temp_char_vert = current_array.at(element.index);
    // std::string tpx;
    // tpx.push_back(temp_char_vert);
    // std::string temp_string_vert = "|" + tpx;
    // current_array.replace(element.index,1,temp_string_vert);
    //move(max_row/ratio+2,max_col/ratio);
    //visPrintCurrentArray();

    move(max_row / ratio + 2, max_col / ratio + element.index - 1);
    printw("|");
}

void visMergePrintElement(int index)
{
    if (!IS_VIS)
        return;
    int i;
    IndexLength element = visFindByIndex(index);
    //getyx(stdscr,cur_y,cur_x);
    move(max_row / ratio + 2 + merge_line, merge_cur_x);
    clrtoeol();
    move(max_row / ratio + 2 + merge_line, merge_cur_x);
    std::string to_write, space_count;
    to_write = current_array.substr(element.index, element.length);
    temp_merge_array += to_write + " ";
    printw("%s ", to_write.c_str());
    getyx(stdscr, cur_y, merge_cur_x);
    // for(i=0;i<element.length;i++)
    // {
    //     space_count+=" ";
    // }
    // current_array.replace(element.index,element.length,space_count);
    //move(max_row/ratio+line+1,max_col/ratio);
    //printw("%s",current_array.c_str());
}

void visMergeReprintArray(int l, int r)
{
    if (!IS_VIS)
        return;
    IndexLength element = visFindByIndex(l);
    move(max_row / ratio + 2 + merge_line, max_col / ratio);
    //printw("sa");
    //visWait();
    clrtoeol();
    move(max_row / ratio + 1 + merge_line, max_col / ratio);
    clrtoeol();
    move(max_row / ratio + 1 + merge_line, max_col / ratio);
    current_array.replace(element.index, temp_merge_array.length(), temp_merge_array);
    printw("%s", current_array.c_str());
    //
    move(max_row / ratio + merge_line, max_col / ratio);
    if (merge_line != 1)
    {
        printw("%s", current_array.c_str());
    }
    //visCrossBetween(l,r,merge_line-2);
    //
    temp_merge_array = "";
    merge_cur_x = max_col / ratio;
    merge_line--;
}

void visRemoveAttributes()
{
    if (!IS_VIS)
        return;
    mvchgat(max_row / ratio + 2, max_col / ratio, -1, A_NORMAL, 0, NULL);
}

void visCrossBetween(int index1, int index2, int line)
{
    if (!IS_VIS)
        return;
    IndexLength element1 = visFindByIndex(index1);
    IndexLength element2 = visFindByIndex(index2);
    mvchgat(max_row / ratio + 2 + line, max_col / ratio + element1.index, element2.index - element1.index + element2.length, A_UNDERLINE, 0, NULL);
}

void visPrintArrayToLine(int line)
{
    if (!IS_VIS)
        return;
    move(max_row / ratio + 2 + line, max_col / ratio);
    //move(max_row/ratio+2+line,max_col/ratio);
    printw("%s", current_array.c_str());
}

void visRemoveArrayFromLine(int line)
{
    if (!IS_VIS)
        return;
    move(max_row / ratio + 2 + line, max_col / ratio);
    clrtoeol();
    move(max_row / ratio + 2 + line, max_col / ratio);
}

void visAddLineBetween(int index1, int index2)
{
    if (!IS_VIS)
        return;
    int i;
    IndexLength element1 = visFindByIndex(index1);
    IndexLength element2 = visFindByIndex(index2);
    move(max_row / ratio + 3, max_col / ratio + element1.index + element1.length / 2);
    printw("|");
    move(max_row / ratio + 4, max_col / ratio + element1.index + element1.length / 2);
    for (i = max_col / ratio + element1.index + element1.length / 2; i <= max_col / ratio + element2.index + element2.length / 2; i++)
    {
        printw("-");
    }
    move(max_row / ratio + 3, max_col / ratio + element2.index + element2.length / 2);
    printw("|");
}

void visRemoveLineBetween()
{
    if (!IS_VIS)
        return;
    move(max_row / ratio + 3, 0);
    clrtoeol();
    move(max_row / ratio + 4, 0);
    clrtoeol();
}

void visVerticalLine(int index)
{
    if (!IS_VIS)
        return;
    IndexLength element = visFindByIndex(index);
    current_array.replace(element.index + element.length, 1, "| ");
}

void visReplaceWithSpace(int index1, int index2)
{
    if (!IS_VIS)
        return;
    IndexLength element1 = visFindByIndex(index1);
    IndexLength element2 = visFindByIndex(index2);
    std::string space_count1, current_item;
    int i;
    for (i = 0; i < element1.length; i++)
    {
        space_count1 += " ";
    }
    // for(i=0;i<element2.length;i++)
    // {
    //     space_count2+=" ";
    // }
    // space_count2+=" ";
    current_item = current_array.substr(element1.index, element1.length);
    current_array.replace(element1.index, element1.length, space_count1);
    visPrintCurrentArray();
    visWait();
    current_array.replace(element1.index, space_count1.length() + 1, "");
    space_count1 += " ";
    current_array.insert(element2.index, space_count1);
    visPrintCurrentArray();
    visWait();
    current_array.replace(element2.index, space_count1.length() - 1, current_item);
    visPrintCurrentArray();
    visWait();
}

void visAddSpace(int index)
{
    if (!IS_VIS)
        return;
    IndexLength element = visFindByIndex(index);
    current_array.insert(element.index + element.length, " ");
}

struct IndexLength visFindByIndex(int index)
{
    int i;
    size_t found;
    size_t before_found = -1;
    found = current_array.find(bosluk);
    for (i = 0; i < index; i++)
    {
        before_found = found;
        found = current_array.find(bosluk, found + 1);
    }

    IndexLength to_return;
    to_return.index = before_found + 1;
    to_return.length = found - before_found - 1;
    return to_return;
}

void visSwap(int index1, int index2)
{
    if (!IS_VIS)
        return;
    visWait();
    visRemoveAttr(index2);
    visRemoveAttr(index1);
    visSetAttr(index1, 1);
    visSetAttr(index2, 1);
    visWait();

    IndexLength element1 = visFindByIndex(index1);
    IndexLength element2 = visFindByIndex(index2);
    std::string to_swap1 = current_array.substr(element1.index, element1.length);
    std::string to_swap2 = current_array.substr(element2.index, element2.length);
    move(max_row / ratio + 2, max_col / ratio);
    current_array.replace(element2.index, element2.length, to_swap1);
    current_array.replace(element1.index, element1.length, to_swap2);

    //refresh();
    //visSetAttr(index1,1);
    //visSetAttr(index2,1);
    //refresh();
    //usleep(sleep_time);
    //visPrintCurrentArray();
    //printw("%sx",dene.c_str());
}

void visRemoveAttr(int index)
{
    if (!IS_VIS)
        return;
    IndexLength element = visFindByIndex(index);
    mvchgat(max_row / ratio + 2, max_col / ratio + element.index, element.length, A_NORMAL, 0, NULL);
    refresh();
}

void visSetAttr(int index, int attribute_to_set)
{
    if (!IS_VIS)
        return;
    //visRemoveAttributes();
    // int i;
    // size_t found;
    // size_t before_found = -1;
    // std::cout << "cujrrent array " << current_array << "\n";
    // found = current_array.find(bosluk);
    // std::cout << "\r";
    // std::cout << "bosluk " << found << " before found " << before_found << "\n";
    // for(i=0;i<index;i++)
    // {
    //     before_found = found;
    //     found = current_array.find(bosluk,found+1);
    // }
    IndexLength element = visFindByIndex(index);
    switch (attribute_to_set)
    {
    case 0:
        //mvchgat(max_row/4+2, max_col/4+before_found+1, found-before_found-1, A_STANDOUT, 0, NULL);
        mvchgat(max_row / ratio + 2, max_col / ratio + element.index, element.length, A_STANDOUT, 0, NULL);
        // refresh();
        // usleep(sleep_time);
        break;
    case 1:
        //mvchgat(max_row/4+2, max_col/4+before_found+1, found-before_found-1, A_BLINK, 0, NULL);
        mvchgat(max_row / ratio + 2, max_col / ratio + element.index, element.length, A_BLINK, 0, NULL);
        break;
    case 2:
        //mvchgat(max_row/4+2, max_col/4+before_found+1, found-before_found-1, A_BLINK, 0, NULL);
        mvchgat(max_row / ratio + 2, max_col / ratio + element.index, element.length, A_UNDERLINE, 0, NULL);
        //refresh();
        //sleep(2);
        break;

    default:
        break;
    }
}

void visPrintCurrentArray()
{
    if (!IS_VIS)
        return;
    move(max_row / ratio + 2, 0);
    clrtoeol();
    move(max_row / ratio + 2, max_col / ratio);
    printw("%s", current_array.c_str());
}

template <typename T>
void visPrintArray(T arr, int size, std::string sorting_name)
{
    if (!IS_VIS)
        return;
    clear();

    std::string temp_str;
    std::stringstream ss;
    int i;

    //print sorting name
    move(max_row / ratio, max_col / 3);
    ss << sorting_name;
    temp_str = ss.str();
    printw("%s\n\n", temp_str.c_str());
    temp_str = "";
    move(max_row / ratio + 2, max_col / ratio);
    ss.str(" ");

    //std::cout << typeid(arr[0]).name() << " qwedqdqw\n";
    if (strcmp(typeid(arr[0]).name(), "f") == 0)
    {
        for (i = 0; i < size; i++)
        {
            ss << arr[i] << " ";
            printw("%g ", arr[i]);
        }
        current_array = ss.str();
        //std::cout << ss.str() << std::endl;
    }
    else
    {
        for (i = 0; i < size; i++)
        {
            temp_str = arr[i];
            current_array += temp_str + " ";
            printw("%s ", temp_str.c_str());
        }
    }

    if (current_array.length() > max_col * (float)(4.0 / 6))
    {
        refresh();
        endwin();
        std::cout << "The array is too big to visualize\n";
        exit(EXIT_SUCCESS);
    }
}

#endif
