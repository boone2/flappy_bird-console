#pragma once
#include <time.h>
#include <stdio.h>
#include "Windows.h"
#include "conio.h"

#define list_num 5    //����ϵͳ�������
#define C 31       //���������

typedef struct
{
    char r_name[C];
    int r_score, r_sort;
} RANK;


void print_ranking();
void rank();
