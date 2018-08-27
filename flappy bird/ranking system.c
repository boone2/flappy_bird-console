#include "stdafx.h"

extern RANK RankingList[list_num];
extern HANDLE hOut;
extern FILE* fp;
extern int score;
extern char TepName[C];
extern WORD color[3];

int longest()
{
    int j = 0;

    for (int i = 1; i < list_num && RankingList[i].r_name[0] != -1; i++)
        if (strlen(RankingList[i].r_name) > strlen(RankingList[j].r_name))
            j = i;
    return strlen(RankingList[j].r_name);
}

void print_ranking()
{
    const int i = longest() / 2;
    COORD pos;

    pos.Y = 5;
    pos.X = 51;
    SetConsoleCursorPosition(hOut, pos);
    printf("ranking list");
    pos.Y = 7;
    pos.X = 44 - i;
    SetConsoleCursorPosition(hOut, pos);
    printf("ranking");
    pos.X = 54;
    SetConsoleCursorPosition(hOut, pos);
    printf("name");
    pos.X = 59 + i;
    SetConsoleCursorPosition(hOut, pos);
    printf("score");
    for (int j = 0; j < list_num && RankingList[j].r_name[0] != -1; j++)
    {
        pos.Y += 2;
        pos.X = 48 - i;
        SetConsoleCursorPosition(hOut, pos);
        printf("%d", RankingList[j].r_sort);
        pos.X = (SHORT)(56 - strlen(RankingList[j].r_name) / 2);
        SetConsoleCursorPosition(hOut, pos);
        printf("%s", RankingList[j].r_name);
        pos.X = 60 + i;
        SetConsoleCursorPosition(hOut, pos);
        printf("%d", RankingList[j].r_score);
    }
}

void input_name()
{
    int i;
    char tep;
    COORD pos = {24, 16};

    //pripare screen  -------------------------------------
    do
    {
        pos.Y--;
        SetConsoleCursorPosition(hOut, pos);
        printf("                              ");
    }
    while (pos.Y > 9);
    SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | color[2]);
    for (pos.Y = 9; pos.Y < 16; pos.Y += 6)
    {
        SetConsoleCursorPosition(hOut, pos);
        printf("                              ");
    }
    for (pos.Y = 10; pos.Y < 15; pos.Y++)
    {
        SetConsoleCursorPosition(hOut, pos);
        printf("  ");
        pos.X += 28;
        SetConsoleCursorPosition(hOut, pos);
        printf("  ");
        pos.X -= 28;
    }
    SetConsoleTextAttribute(hOut, color[1]);
    //---------------------------------------------------------
    pos.X = 33;
    pos.Y = 11;
    SetConsoleCursorPosition(hOut, pos);
    printf("Game Over !");
    pos.X = 28;
    pos.Y = 13;
    SetConsoleCursorPosition(hOut, pos);
    printf("Your name : %s", TepName);
    pos.X = 40;
    SetConsoleCursorPosition(hOut, pos);
    if ((tep = _getch()) != 13)
    {
        const int j = strlen(TepName);
        if (tep != '\b')
        {
            putchar(tep);
            pos.X = 41;
            if (j > 0) for (i = j; i > 1; i--) putchar(' ');
            else i = 1;
            SetConsoleCursorPosition(hOut, pos);
            TepName[0] = tep;
        }
        else
        {
            for (i = j; i > 0; i--) putchar(' ');
            SetConsoleCursorPosition(hOut, pos);
        }
        while ((tep = _getch()) != 13)
        {
            if (tep == '\b')
            {
                if (pos.X > 40)
                {
                    pos.X--;
                    i--;
                    SetConsoleCursorPosition(hOut, pos);
                    putchar(' ');
                    SetConsoleCursorPosition(hOut, pos);
                }
            }
            else
            {
                putchar(tep);
                pos.X++;
                TepName[i++] = tep;
            }
        }
        TepName[i] = 0;
    }
}

int cmpare(const char* l_name)
{
    int i = 0;
    char temp[C];

    while (l_name[i])
    {
        int j = 0;
        while (l_name[i] != '/' && l_name[i] != 0)
            temp[j++] = l_name[i++];
        temp[j] = 0;
        if (!strcmp(temp, TepName)) return 0;
        if (l_name[i] != 0) i++;
    }
    return 1;
}

void insert(int posi)
{
    int i;

    if (RankingList[posi].r_score - score)
    {
        for (i = list_num - 1; i > posi; i--)
        {
            RankingList[i] = RankingList[i - 1];
            RankingList[i].r_sort++;
        }
        strcpy_s(RankingList[posi].r_name, C, TepName);
        RankingList[posi].r_score = score;
    }
    else
    {
        if (cmpare(RankingList[posi].r_name))
        {
            strcat_s(RankingList[posi].r_name, C, "/");
            strcat_s(RankingList[posi].r_name, C, TepName);
            for (i = posi + 1; i < list_num; i++)
                RankingList[i].r_sort++;
        }
    }
}

void rank()
{
    int i;

    if (score >= RankingList[list_num - 1].r_score)
    {
        input_name();
        for (i = 0; i < list_num && score < RankingList[i].r_score; i++)
        {
        }
        insert(i);
        if (fopen_s(&fp, "RankingList.FBlog", "wb"))
        {
            system("cls");
            printf("\n\n\n\t\tfile write error !");
            _getch();
        }
        else
        {
            fwrite(RankingList, sizeof(RANK), list_num, fp);
            fwrite(TepName, sizeof(char), C, fp);
            fclose(fp);
        }
    }
    else
    {
        COORD pos = {24, 16};

        //pripare screen  -------------------------------------
        do
        {
            pos.Y--;
            SetConsoleCursorPosition(hOut, pos);
            printf("                              ");
        }
        while (pos.Y > 9);
        SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | color[2]);
        for (pos.Y = 9; pos.Y < 16; pos.Y += 6)
        {
            SetConsoleCursorPosition(hOut, pos);
            printf("                              ");
        }
        for (pos.Y = 10; pos.Y < 15; pos.Y++)
        {
            SetConsoleCursorPosition(hOut, pos);
            printf("  ");
            pos.X += 28;
            SetConsoleCursorPosition(hOut, pos);
            printf("  ");
            pos.X -= 28;
        }
        SetConsoleTextAttribute(hOut, color[1]);
        //-------------------------------------------------------
        pos.X = 33;
        pos.Y = 12;
        SetConsoleCursorPosition(hOut, pos);
        printf("Game Over !");
        Sleep(1000);
    }
}
