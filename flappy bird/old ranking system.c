#include "stdafx.h"

extern int score;
extern HANDLE hOut;

COORD pos;

typedef struct _rank{
	char r_name[C];
	int r_score, r_sort;
}RANK;

int cmpare(char *l_name, char *name){
	int i = 0, j;
	char temp[C];
	
	while(l_name[i]){
		j = 0;
		while(l_name[i] != '/' && l_name[i] != 0)
			temp[j++] = l_name[i++];
		temp[j] = 0;
		if(!strcmp(temp, name)) return 0;
		if(l_name[i] != 0) i++;
	}
	return 1;
}

insert(RANK *list, int posi, char name[]){
	int i;
	
	if(list[posi].r_score - score){
		for(i = rank_num - 1; i > posi; i--){
			list[i] = list[i - 1];
			list[i].r_sort++;
		}
		strcpy(list[posi].r_name, name);
		list[posi].r_score = score;
	}
	else{
		if(cmpare(list[posi].r_name, name)){
			strcat(list[posi].r_name, "/");
			strcat(list[posi].r_name, name);
			for(i = posi + 1; i < rank_num; i++)
			    list[i].r_sort++;
		}
	} 
}

input_name(char name[]){
	int i, j;
	char tep;
	
	pos.X = 28;
	pos.Y = 12;
	SetConsoleCursorPosition(hOut, pos);
	printf("Your name : %s", name);
	pos.X = 40;
    SetConsoleCursorPosition(hOut, pos);
    if((tep=getch()) != 13){
	    j = strlen(name);
    	if(tep != '\b'){
    		putchar(tep);
			pos.X = 41;
        	for(i = j; i > 1; i--) putchar(' ');
        	SetConsoleCursorPosition(hOut, pos);
        	name[0] = tep;
        	pos.X = 41;
	    }
	    else{
    		for(i = j; i > 0; i--) putchar(' ');
        	SetConsoleCursorPosition(hOut, pos);
    	}
        while((tep=getch()) != 13){
        	if(tep == '\b'){
        		if(pos.X > 40){
       	        	pos.X--;
       	   	    	i--;
                	SetConsoleCursorPosition(hOut, pos);
       	   	    	putchar(' ');
                	SetConsoleCursorPosition(hOut, pos);
		        }
	        }
        	else{
        		putchar(tep);
	        	pos.X++;
   	    	    name[i++] = tep;
	        }
        }
        name[i] = 0;
    }
}

int longest(RANK *list){
	int i, j = 0;
	
	for(i = 1; i < rank_num && list[i].r_name[0] != -1; i++)
		if(strlen(list[i].r_name) > strlen(list[j].r_name))
		    j = i;
	return strlen(list[j].r_name);
}

print_rank(RANK *list){
	int i = longest(list) / 2, j;
	
	pos.Y = 5;
	pos.X = 34;
	SetConsoleCursorPosition(hOut, pos);
	printf("ranking list");
	pos.Y = 7; 
	pos.X = 27 - i;
	SetConsoleCursorPosition(hOut, pos);
	printf("ranking");
	pos.X = 37;
	SetConsoleCursorPosition(hOut, pos);
	printf("name");
	pos.X = 42 + i;
	SetConsoleCursorPosition(hOut, pos);
	printf("score");
	for(j = 0; j < rank_num && list[j].r_name[0] != -1; j++){
		pos.Y += 2;
		pos.X = 31 - i;
        SetConsoleCursorPosition(hOut, pos);
		printf("%d", list[j].r_sort);
		pos.X = 39 - strlen(list[j].r_name)/2;
        SetConsoleCursorPosition(hOut, pos);
        printf("%s", list[j].r_name);
        pos.X = 43 + i;
        SetConsoleCursorPosition(hOut, pos);
        printf("%d", list[j].r_score);
	}
}

rank(){
	RANK list[rank_num];
	FILE *fp;
	int i;
	char name[C];
	
	if(fp = fopen("rank_list.dat", "rb")){
		fread(name, sizeof(char), C, fp);
		fread(list, sizeof(RANK), rank_num, fp);
		fclose(fp);
		if(score >= list[rank_num - 1].r_score){
			input_name(name);
			for(i = 0; i < rank_num && score < list[i].r_score; i++);
			insert(list, i, name);
		}
		if((fp = fopen("rank_list.dat", "wb")) == NULL){
			system("cls");
			printf("\n\n\n            排行榜系统出现问题，请重新打开游戏, 按回车退出");
			while(getch() != '\n');
			exit(0);
		}
	}
	else{
		if((fp = fopen("rank_list.dat", "wb")) == NULL){
			system("cls");
			printf("\n\n\n            排行榜系统出现问题，请调试, 按回车退出");
			while(getch() != '\n');
			exit(0);
		}
    	memset(list, -1, rank_num*sizeof(RANK));
    	pos.X = 27;
	    pos.Y = 12;
        SetConsoleCursorPosition(hOut, pos);
        printf("your name : ");
    	strcpy(name, gets(list[0].r_name));
    	list[0].r_score = score;
    	list[0].r_sort = 1;
    	for(i = 1; i < rank_num; i++)
    	    list[i].r_sort = 2;
	}
	fwrite(name, sizeof(char), C, fp);
	fwrite(list, sizeof(RANK), rank_num, fp);
	fclose(fp);
	print_rank(list); 
}
