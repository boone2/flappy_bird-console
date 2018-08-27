#pragma once
#include <time.h>
#include <stdio.h>
#include "Windows.h"
#include "conio.h"

#define list_num 5    //排名系统最大保留数
#define C 31       //名字最长长度

typedef struct
{
    char r_name[C];
    int r_score, r_sort;
} RANK;


void print_ranking();
void rank();
