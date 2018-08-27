#include "stdafx.h"

COORD map, bird[2], logo, choice;
HANDLE hOut;
FILE* fp;
RANK RankingList[list_num];
char TepName[C];
int flag, score;
WORD color[3];

struct
{
    COORD posi[6];
    int passageway[2];
} hinder[4];

void PrintScore()
{
    register COORD ScorePosition = {66, 16};
    register int i = score;

    do
    {
        ScorePosition.Y = 16;
        do
        {
            ScorePosition.Y--;
            SetConsoleCursorPosition(hOut, ScorePosition);
            printf("      ");
        }
        while (ScorePosition.Y > 11);
        SetConsoleTextAttribute(hOut, color[2]);
        switch (i % 10)
        {
        case 8:
            ScorePosition.Y = 14;
            SetConsoleCursorPosition(hOut, ScorePosition);
            printf("  ");
        case 9:
            ScorePosition.Y = 12;
            SetConsoleCursorPosition(hOut, ScorePosition);
            printf("  ");
        case 3:
            for (ScorePosition.Y = 13; ScorePosition.Y < 16; ScorePosition.Y += 2)
            {
                SetConsoleCursorPosition(hOut, ScorePosition);
                printf("    ");
            }
        case 7:
            ScorePosition.Y = 11;
            SetConsoleCursorPosition(hOut, ScorePosition);
            printf("    ");
        case 1:
            ScorePosition.X += 4;
            for (ScorePosition.Y = 11; ScorePosition.Y < 16; ScorePosition.Y++)
            {
                SetConsoleCursorPosition(hOut, ScorePosition);
                printf("  ");
            }
            ScorePosition.X -= 4;
            break;
        case 6:
            ScorePosition.Y = 14;
            SetConsoleCursorPosition(hOut, ScorePosition);
            printf("  ");
        case 5:
            for (ScorePosition.Y = 11; ScorePosition.Y < 16; ScorePosition.Y += 2)
            {
                SetConsoleCursorPosition(hOut, ScorePosition);
                printf("      ");
            }
            ScorePosition.Y = 12;
            SetConsoleCursorPosition(hOut, ScorePosition);
            printf("  ");
            ScorePosition.Y = 14;
            ScorePosition.X += 4;
            SetConsoleCursorPosition(hOut, ScorePosition);
            printf("  ");
            ScorePosition.X -= 4;
            break;
        case 4:
            for (ScorePosition.Y = 11; ScorePosition.Y < 13; ScorePosition.Y++)
            {
                SetConsoleCursorPosition(hOut, ScorePosition);
                printf("  ");
            }
            SetConsoleCursorPosition(hOut, ScorePosition);
            printf("    ");
            ScorePosition.X += 4;
            for (ScorePosition.Y = 11; ScorePosition.Y < 16; ScorePosition.Y++)
            {
                SetConsoleCursorPosition(hOut, ScorePosition);
                printf("  ");
            }
            ScorePosition.X -= 4;
            break;
        case 0:
            for (ScorePosition.Y = 11; ScorePosition.Y < 16; ScorePosition.Y += 4)
            {
                SetConsoleCursorPosition(hOut, ScorePosition);
                printf("      ");
            }
            for (ScorePosition.Y = 12; ScorePosition.Y < 15; ScorePosition.Y++)
            {
                SetConsoleCursorPosition(hOut, ScorePosition);
                printf("  ");
                ScorePosition.X += 4;
                SetConsoleCursorPosition(hOut, ScorePosition);
                printf("  ");
                ScorePosition.X -= 4;
            }
            break;
        case 2:
            for (ScorePosition.Y = 11; ScorePosition.Y < 16; ScorePosition.Y += 2)
            {
                SetConsoleCursorPosition(hOut, ScorePosition);
                printf("      ");
            }
            ScorePosition.Y = 14;
            SetConsoleCursorPosition(hOut, ScorePosition);
            printf("  ");
            ScorePosition.Y = 12;
            ScorePosition.X += 4;
            SetConsoleCursorPosition(hOut, ScorePosition);
            printf("  ");
            ScorePosition.X -= 4;
        }
        SetConsoleTextAttribute(hOut, color[1]);
        ScorePosition.X -= 7;
    }
    while (i /= 10);
}

void ActMap()
{
    static int posi = 1;

    for (map.X = posi; map.X < 77; map.X += 2)
    {
        map.Y = 0;
        SetConsoleCursorPosition(hOut, map);
        putchar(' ');
        map.Y = 23;
        SetConsoleCursorPosition(hOut, map);
        putchar(' ');
        map.X += 2;
        map.Y = 0;
        SetConsoleCursorPosition(hOut, map);
        putchar('/');
        map.Y = 23;
        SetConsoleCursorPosition(hOut, map);
        putchar('/');
    }
    switch (map.X)
    {
    case 77:
    case 78:
        map.Y = 0;
        SetConsoleCursorPosition(hOut, map);
        putchar(' ');
        map.Y = 23;
        SetConsoleCursorPosition(hOut, map);
        putchar(' ');
    }
    if (--posi == -1) posi = 3;
}

int BirdJudge()
{
    if (bird[1].Y > 22) return 1;

    for (register int i = 0; i < 4; i++)
    {
        if (hinder[i].posi[0].X >= 18 && hinder[i].posi[0].X <= 24)
            if (bird[1].Y < hinder[i].passageway[0] || bird[1].Y > hinder[i].passageway[1]) return 1;
        if (hinder[i].posi[5].X == 22 || hinder[i].posi[5].X == 21)
            if (bird[0].Y < hinder[i].passageway[0] || bird[0].Y > hinder[i].passageway[1]) return 1;
    }
    return 0;
}

int ActBird(int direct)
{
    //消除原来的鸟
    SetConsoleCursorPosition(hOut, bird[1]);
    putchar(' ');
    SetConsoleCursorPosition(hOut, bird[0]);
    putchar(' ');
    //改变坐标并判断
    bird[0].Y = bird[1].Y;
    bird[1].Y += direct;
    //
    SetConsoleCursorPosition(hOut, bird[1]);
    printf("●");
    SetConsoleCursorPosition(hOut, bird[0]);
    printf("o");
    if (BirdJudge()) return 1;
    return 0;
}

int HinderJudge(int i)
{
    if (hinder[i].posi[0].X == 24 || hinder[i].posi[0].X == 23)
        if (bird[1].Y < hinder[i].passageway[0] || bird[1].Y > hinder[i].passageway[1]) return 1;
    if (hinder[i].posi[0].X == 22 || hinder[i].posi[0].X == 21)
        if (bird[0].Y < hinder[i].passageway[0] || bird[0].Y > hinder[i].passageway[1]) return 1;
    return 0;
}

int ActHinder()
{
    register int i, j;

    for (i = 0; i < 4; i++)
    {
        if (hinder[i].posi[5].X <= 50)
            for (hinder[i].posi[5].Y = 1; hinder[i].posi[5].Y < 23; hinder[i].posi[5].Y++)
            {
                SetConsoleCursorPosition(hOut, hinder[i].posi[5]);
                putchar(' ');
            }
        for (j = 0; j < 6; j++)
            if (--hinder[i].posi[j].X < 0)
            {
                hinder[i].posi[j].X = 63;
                if (!j)
                {
                    hinder[i].passageway[0] = rand() % 14 + 3;
                    hinder[i].passageway[1] = hinder[i].passageway[0] + 4;
                }
            }
        if (HinderJudge(i)) return 1;
        if (hinder[i].posi[0].X <= 50)
        {
            SetConsoleTextAttribute(hOut, color[0]);
            for (hinder[i].posi[0].Y = 1; hinder[i].posi[0].Y < 23; hinder[i].posi[0].Y++)
                if (hinder[i].posi[0].Y < hinder[i].passageway[0] || hinder[i].posi[0].Y > hinder[i].passageway[1])
                {
                    SetConsoleCursorPosition(hOut, hinder[i].posi[0]);
                    putchar(' ');
                }
            SetConsoleTextAttribute(hOut, color[1]);
        }
    }
    return 0;
}

void MakeMap()
{
    register int i;

    SetConsoleCursorPosition(hOut, map);
    for (i = 0; i < 80; i += 4) printf(" // ");
    map.Y = 23;
    SetConsoleCursorPosition(hOut, map);
    for (i = 0; i < 80; i += 4) printf(" // ");
    printf("  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |");
}

void MakeHinder()
{
    register int i, j;

    hinder[0].posi[0].X = 80;
    for (i = 1; i < 6; i++)
        hinder[0].posi[i].X = hinder[0].posi[i - 1].X + 1;
    hinder[0].passageway[0] = rand() % 14 + 3;
    hinder[0].passageway[1] = hinder[0].passageway[0] + 4;
    for (i = 1; i < 4; i++)
    {
        hinder[i].posi[0].X = hinder[i - 1].posi[0].X + 16;
        for (j = 1; j < 6; j++)
            hinder[i].posi[j].X = hinder[i].posi[j - 1].X + 1;
        hinder[i].passageway[0] = rand() % 14 + 3;
        hinder[i].passageway[1] = hinder[i].passageway[0] + 4;
    }
}

void logo_bird_ranking_choice()
{
    //bird & logo
    SetConsoleCursorPosition(hOut, logo);
    printf("Flappy Bird 2");
    SetConsoleCursorPosition(hOut, bird[1]);
    printf("●");
    SetConsoleCursorPosition(hOut, bird[0]);
    printf("ο");

    //ranking
    if (RankingList[0].r_name[0] != -1)
    {
        print_ranking();
    }

    //choice
    SetConsoleCursorPosition(hOut, choice);
    if (flag) printf("1.re");
    else
    {
        printf("1.");
        flag = 1;
    }
    printf("start      2.exit");
}

void PriScreen()
{
    COORD pos = {30, 5};

    SetConsoleCursorPosition(hOut, logo);
    printf("             ");
    SetConsoleCursorPosition(hOut, bird[0]);
    putchar(' ');
    SetConsoleCursorPosition(hOut, bird[1]);
    putchar(' ');
    SetConsoleCursorPosition(hOut, choice);
    printf("                     ");
    while (pos.Y < 18)
    {
        SetConsoleCursorPosition(hOut, pos);
        printf("                                                 ");
        pos.Y += 2;
    }
    flag = 1;
    logo.X = 17;
    bird[0].X = 21;
    bird[1].X = 23;
    SetConsoleCursorPosition(hOut, bird[0]);
    printf("ο");
    SetConsoleCursorPosition(hOut, bird[1]);
    printf("●");
    SetConsoleCursorPosition(hOut, logo);
    printf("Push \"space\" to fly !");
}

void initialize()
{
    bird[0].Y = 13;
    bird[1].Y = 13;
    logo.Y = 9;
    choice.Y = 20;
    choice.X = 29;
    map.X = map.Y = 0;
    if (RankingList[0].r_name[0] != -1)
    {
        bird[0].X = 21;
        bird[1].X = 23;
        logo.X = 17;
    }
    else
    {
        bird[0].X = 37;
        bird[1].X = 39;
        logo.X = 33;
    }
}

void game()
{
    register int i, j, k, l, speed;

start:
    initialize();
    MakeMap();
    logo_bird_ranking_choice();
    i = 1, j = 1, k = 1, l = -43, speed = 3;
    score = 0;
    MakeHinder();
    while (j)
    {
        Sleep(140);
        ActMap();
        if (!(i % 3)) ActBird(i / 6 % 2 ? 1 : -1);
        if (_kbhit())
        {
            switch (_getch())
            {
            case '1': j = 0;
                break;
            case '2': exit(0);
            }
        }
        i++;
    }
    PriScreen();
    PrintScore();
    while (i)
    {
        Sleep(140);
        ActMap();
        if (!(i % 3)) ActBird(i / 6 % 2 ? 1 : -1);
        if (_kbhit())
            if (_getch() == ' ')
            {
                SetConsoleCursorPosition(hOut, logo);
                printf("                     ");
                break;
            }
        i++;
    }
    i = 1;
    while (1)
    {
        Sleep(20);
        if (j == 5)
        {
            ActMap();
            if (ActHinder()) break;
            j = 0, l++;
        }
        if (l == 16)
        {
            score++;
            PrintScore();
            l = 0;
        }
        if (_kbhit())
            if (_getch() == ' ')
            {
                i = 1;
                speed = 3;
            }
        if (k >= speed)
        {
            if (i < 4)
            {
                speed += 1;
                if (bird[1].Y > 1)
                    if (ActBird(-1)) break;
            }
            else
            {
                if (speed > 1) speed -= 1;
                if (ActBird(1)) break;
            }
            k = 0, i++;
        }
        j++, k++;
    }
    rank();
    system("cls");
    goto start;
}

void FileRead()
{
    if (fopen_s(&fp, "RankingList.FBlog", "rb"))
    {
        TepName[0] = 0;
        memset(RankingList, -1, list_num * sizeof(RANK));
        for (int i = 0; i < list_num; i++)
            RankingList[i].r_sort = 1;
    }
    else
    {
        fread(RankingList, sizeof(RANK), list_num, fp);
        fread(TepName, sizeof(char), C, fp);
        fclose(fp);
    }
}

void main()
{
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    srand((unsigned int)time(NULL));
    system("color 3f");
    color[0] = BACKGROUND_INTENSITY | BACKGROUND_BLUE;
    color[1] = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | BACKGROUND_BLUE |
        BACKGROUND_GREEN;
    color[2] = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    flag = 0;
    FileRead();
    game();
}
