#pragma once
#include "OdeloBattleSystem.h"
#include "Attack_2.h"
#include <time.h>
static int **board;
static int **stone;
static int **stone2;
struct MyPoint
{
	int xPos;
	int yPos;
	int **board;
	int value;
	MyPoint *node[10];
};
struct MyPoint *head;
static int key_value[8][8] =
{100,  10, 75, 15, 15, 75,  10, 100,
10,  10, 20, 30, 30, 20,  10,  10,
75,  20, 50, 40, 40, 50,  20,  75,
15,  30, 40,  0,  0, 40,  30,  15,
15,  30, 40,  0,  0, 40,  30,	15,
75,  20, 50, 40, 40, 50,  20,  75,
10,  10, 20, 30, 30, 20,  10,  10,
100,  10, 75, 15, 15 , 75,  10, 100};
static int key_value3[8][8] =
{
	{100, -20, 10, 5, 5, 10, -20, 100},
	{-20, -50, -2, -2, -2, -2, -50, -20},
	{10, -2, 12,11,11,12, -2, 10},
	{5, -2, 11,11,11,11, -2, 10},
	{5, -2, 11,11,11,11, -2, 10},
	{10, -2, 12,11,11,12, -2, 10},
	{-20, -50, -2, -2, -2, -2, -50, -20},
	{100, -20, 10, 5, 5, 10, -20, 100}
};
static int key_value2[8][8] =
{
	{100, -20, 10, 5, 5, 10, -20, 100},
	{-20, -50, -2, -2, -2, -2, -50, -20},
	{10, -2, -1, -1, -1, -1, -2, 10},
	{5, -2, -1, -1, -1, -1, -2, 10},
	{5, -2, -1, -1, -1, -1, -2, 10},
	{10, -2, -1, -1, -1, -1, -2, 10},
	{-20, -50, -2, -2, -2, -2, -50, -20},
	{100, -20, 10, 5, 5, 10, -20, 100}
};
void SetBoards()
{
	board = new int*[g_nMax];
	stone = new int*[g_nMax];
	stone2 = new int*[g_nMax];
	head=(MyPoint*)malloc(sizeof(MyPoint));
	for(int i=0; i<g_nMax; i++) {
		board[i] = new int[g_nMax];
		stone[i] = new int[g_nMax];
		stone2[i] = new int[g_nMax];
	}
}
void CheckBoard(int x, int y, int type, int **board, int **stone)
{

	int dx, dy, _dx, _dy;
	for( int j = 0; j < 4; j++ )
	{
		dx = _dx = x ;
		dy = _dy = y ;

		dx = dx + g_Directiontable[ j ][ 0 ];
		dy = dy + g_Directiontable[ j ][ 1 ];

		_dx = _dx + g_Directiontable[ j + 4 ][ 0 ];
		_dy = _dy + g_Directiontable[ j + 4 ][ 1 ];
	//	if(board[dy][dx]==type)
		while( ( dx >= 0 && dx <= 7 ) && ( dy >= 0 && dy <= 7 ) )
		{

			if( board[ dy ][ dx ] == type ) //○○● , ○○  같은 돌인 경우
				break;
			else if( board[ dy ][ dx ] == PAN && board[dy - g_Directiontable[ j ][ 1 ]][dx - g_Directiontable[ j ][ 0 ]]!=type) {
					stone[dy][dx]=type;
					break;
			}

			else if( ( board[ dy ][ dx ] != PAN ) && ( board[ dy ][ dx ] != type ) )
			{	
				dx = dx + g_Directiontable[ j ][ 0 ];
				dy = dy + g_Directiontable[ j ][ 1 ];
			}

			else
				break;
		}
		while( ( _dx >= 0 && _dx <= 7 ) && ( _dy >= 0 && _dy <= 7 ) )
		{

			if( board[ _dy ][ _dx ] == type ) //○○● , ○○  같은 돌인 경우
				break;
			else if( board[ _dy ][ _dx ] == PAN && board[_dy - g_Directiontable[ j + 4 ][ 1 ]][_dx - g_Directiontable[ j + 4 ][ 0 ]]!=type)  {
					stone[_dy][_dx]=type;
					break;

			}
			else if( ( board[ _dy ][ _dx ] != PAN ) && ( board[ _dy ][ _dx ] != type ) )
			{	
				_dx = _dx + g_Directiontable[ j + 4 ][ 0 ];
				_dy = _dy + g_Directiontable[ j + 4 ][ 1 ];
			}


			else
				break;

		}
	}
}

void Reverse(int x, int y, int type, int **board)
{
	int dx, dy, _dx, _dy;
	int count = 0;
	
	for( int j = 0; j < 4; j++ )
	{
		dx = _dx = x ;
		dy = _dy = y ;

		dx = dx + g_Directiontable[ j ][ 0 ];
		dy = dy + g_Directiontable[ j ][ 1 ];

		_dx = _dx + g_Directiontable[ j + 4 ][ 0 ];
		_dy = _dy + g_Directiontable[ j + 4 ][ 1 ];
		
		count = 0;	
		
		while( ( dx >= 0 && dx <= 7 ) && ( dy >= 0 && dy <= 7 ) )
		{
			
			if( board[ dy ][ dx ] == type ) //○○● , ○○  같은 돌인 경우
			{
				if(!(dx == x + g_Directiontable[ j ][ 0 ] && dy == y + g_Directiontable[ j ][ 1 ]))
				{
					dx = x + g_Directiontable[ j ][ 0 ];
					dy = y + g_Directiontable[ j ][ 1 ];
					for(int i=0; i<count; i++)
					{
						if(board[dy][dx] == BLACK)
							board[dy][dx] = WHITE;
						else if(board[dy][dx] == WHITE)
							board[dy][dx] = BLACK;

						dx = dx + g_Directiontable[ j ][ 0 ];
						dy = dy + g_Directiontable[ j ][ 1 ];
					}
					break;

				}
				else break;
			}
			
			else if( board[ dy ][ dx ] == PAN)  
				break;
		
			else if( ( board[ dy ][ dx ] != PAN ) && ( board[ dy ][ dx ] != type ) )
			{	
				dx = dx + g_Directiontable[ j ][ 0 ];
				dy = dy + g_Directiontable[ j ][ 1 ];
			}
					
		
			else
				break;

			count++;
		}

		count = 0;

		while( ( _dx >= 0 && _dx <= 7 ) && ( _dy >= 0 && _dy <= 7 ) )
		{
			
			if( board[ _dy ][ _dx ] == type ) //○○● , ○○  같은 돌인 경우
			{
				if(!(_dx == x + g_Directiontable[ j ][ 0 ] && _dy == y + g_Directiontable[ j ][ 1 ]))
				{
					_dx = x + g_Directiontable[ j + 4 ][ 0 ];
					_dy = y + g_Directiontable[ j + 4 ][ 1 ];
					for(int i=0; i<count; i++)
					{
						if(board[_dy][_dx] == BLACK)
							board[_dy][_dx] = WHITE;
						else if(board[_dy][_dx] == WHITE)
							board[_dy][_dx] = BLACK;

						_dx = _dx + g_Directiontable[ j + 4 ][ 0 ];
						_dy = _dy + g_Directiontable[ j + 4 ][ 1 ];
					}
					break;

				}
				else break;
			}
			
			else if( board[ _dy ][ _dx ] == PAN)  
				break;
		
			else if( ( board[ _dy ][ _dx ] != PAN ) && ( board[ _dy ][ _dx ] != type ) )
			{	
				_dx = _dx + g_Directiontable[ j + 4 ][ 0 ];
				_dy = _dy + g_Directiontable[ j + 4 ][ 1 ];
			}
					
		
			else
				break;

			count++;
		}
	}
}
void SetTree(int type, MyPoint *current)
{
	int **t_board;
	int temp=0;
	int save;
	MyPoint *now;
	t_board = new int*[g_nMax];
	for(int i=0; i<g_nMax; i++)
		t_board[i] = new int[g_nMax];
	t_board=current->board;
	now=(MyPoint*)malloc(sizeof(MyPoint));
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			if(current->board[i][j]==type)
				CheckBoard(j,i,type,current->board, stone2);
		}
	}
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			if(stone2[i][j]==type) {
				if(temp==0) 
					save=key_value[i][j];
				else if(save>key_value[i][j])
					continue;
				else if(save<key_value[i][j])
					temp=0;
				now->xPos=j;
				now->yPos=i;
				now->value=key_value[i][j];
				Reverse(j,i,type, t_board);
				now->board=t_board;
				current->node[temp++]=now;
				now=(MyPoint*)malloc(sizeof(MyPoint));
				t_board=OdeloGame.Get_OdeloPan();
			}
		}
	}
	current->node[temp]=NULL;
	
}
MyPoint* ExploreNode(MyPoint *current, int type);
static int save;
static MyPoint *now;
static int turn_black=0;
static int turn_white=0;
void Attack(int type, MyPoint *current, int *x, int *y)
{
	srand(time(NULL));
	int temp=0, cur_point[3]={0,0,0};
	int select;
	int **t_board;
	int save=0, t_index=0, t_index2=0;
	int index[30], index2[10];
	int t_size1=0, t_size2=0;
	int save_X=0, save_Y=0, save_value=0;
	now=(MyPoint*)malloc(sizeof(MyPoint));

	t_board = new int*[g_nMax];
	for(int i=0; i<g_nMax; i++)
		t_board[i] = new int[g_nMax];
	t_board=OdeloGame.Get_OdeloPan();
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++)
		{
			if(board[i][j]==type) {
				CheckBoard(j,i, type,board, stone);
			}
		}
	}
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++)
		{
			if(stone[i][j]==type)
			{
				if(temp==0) 
					save=key_value[i][j];
				else if(save>key_value[i][j])
					continue;
				else if(save<key_value[i][j])
					temp=0;
				save=key_value[i][j];
				now->xPos=j;
				now->yPos=i;
				now->value=key_value[i][j];
				Reverse(j,i,type, t_board);
				now->board=t_board;
				current->node[temp++]=now;
				now=(MyPoint*)malloc(sizeof(MyPoint));
				t_board=OdeloGame.Get_OdeloPan();
			}
		}
	}
	current->node[temp]=NULL;
	printf("complete : %d\n", temp);
	if(temp==0) {
		if(current->node[temp]==NULL) {
			*x=-1;
			*y=-1;
		}
		else {
			*x=current->node[temp]->xPos;
			*y=current->node[temp]->yPos;
		}
	}
	else {
		for(int i=0; i<temp; i++)
		{
			if(type==BLACK)
				SetTree(WHITE, current->node[i]);
			else
				SetTree(BLACK, current->node[i]);
		}
		t_index=0;
		index[t_index]=0;
		int j=1, save=0;
		save=current->node[0]->node[0]->value;
		for(int i=0; i<temp; i++) {
			while(current->node[i]->node[j]!=NULL) {
				if(save>current->node[i]->node[j]->value) {
					save=current->node[i]->node[j]->value;
					index[t_index]=i;
				}
				else if(save==current->node[i]->node[j]->value && i!=index[t_index]) {
					t_index+=1;
					index[t_index]=i;
				}
				j++;
			}
			j=0;
		}
		j=1;
		if(t_index>0) {
			
			t_size1=0;
			t_size2=0;

			save=0;
			
			for(int p=0; p<8; p++) {
				for(int q=0; q<8; q++) {
					if(current->node[index[0]]->board[p][q]==type)
						t_size1++;
				}
			}
			for(int i=1; i<t_index; i++)
			{
				for(int p=0; p<8; p++) {
					for(int q=0; q<8; q++) {
						if(current->node[index[i]]->board[p][q]==type)
							t_size2++;
					}
				}
				if(type==BLACK && turn_black<20) {
					if(t_size1>t_size2) {
						t_size1=t_size2;
						save=i;
					}
				}
				else if(type==BLACK && turn_black>20) {
					if(t_size1<t_size2) {
						t_size1=t_size2;
						save=i;
					}
				}
				if(type==WHITE && turn_white<20) {
					if(t_size1>t_size2) {
						t_size1=t_size2;
						save=i;
					}
				}
				else if(type==WHITE && turn_white>20) {
					if(t_size1<t_size2) {
						t_size1=t_size2;
						save=i;
					}
				}
				t_size2=0;
			}
			*x=current->node[index[save]]->xPos;
			*y=current->node[index[save]]->yPos;
		}
		
		else {
			*x=current->node[index[0]]->xPos;
			*y=current->node[index[0]]->yPos;
		}
		
	}
	if(type==BLACK)
		turn_black++;
	else
		turn_white++;
}

void Attack2(int type, MyPoint *current, int *x, int *y)
{
	srand(time(NULL));
	int temp=0, cur_point[3]={0,0,0};
	int select;
	int **t_board;
	int save=0, t_index=0, t_index2=0;
	int index[10], index2[10];
	int t_size1=0, t_size2=0;
	int save_X=0, save_Y=0, save_value=0;
	now=(MyPoint*)malloc(sizeof(MyPoint));

	t_board = new int*[g_nMax];
	for(int i=0; i<g_nMax; i++)
		t_board[i] = new int[g_nMax];
	t_board=OdeloGame.Get_OdeloPan();
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++)
		{
			if(board[i][j]==type) {
				CheckBoard(j,i, type,board, stone);
			}
		}
	}
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++)
		{
			if(stone[i][j]==type)
			{
				if(temp==0) 
					save=key_value[i][j];
				else if(save>key_value[i][j])
					continue;
				else if(save<key_value[i][j])
					temp=0;
				save=key_value[i][j];
				now->xPos=j;
				now->yPos=i;
				now->value=key_value[i][j];
				Reverse(j,i,type, t_board);
				now->board=t_board;
				current->node[temp++]=now;
				now=(MyPoint*)malloc(sizeof(MyPoint));
				t_board=OdeloGame.Get_OdeloPan();
			}
		}
	}
	current->node[temp]=NULL;
	printf("complete : %d\n", temp);
	if(temp==0) {
		if(current->node[temp]==NULL) {
			*x=-1;
			*y=-1;
		}
		else {
			*x=current->node[temp]->xPos;
			*y=current->node[temp]->yPos;
		}
	}
	else {
		for(int i=0; i<temp; i++)
		{
			if(type==BLACK)
				SetTree(WHITE, current->node[i]);
			else
				SetTree(BLACK, current->node[i]);
		}
		t_index=0;
		index[t_index]=0;
		int j=1, save=0;
		save=current->node[0]->node[0]->value;
		for(int i=0; i<temp; i++) {
			while(current->node[i]->node[j]!=NULL) {
				if(save>current->node[i]->node[j]->value) {
					save=current->node[i]->node[j]->value;
					index[t_index]=i;
				}
				else if(save==current->node[i]->node[j]->value && i!=index[t_index]) {
					t_index+=1;
					index[t_index]=i;
				}
				j++;
			}
			j=0;
		}
		j=1;
		index2[0]=index[0];
		if(t_index>0) {
			for(int p=0; p<8; p++) {
				for(int q=0; q<8; q++) {
					if(current->node[index[0]]->board[p][q]==type)
						t_size1++;
				}
			}
			for(int i=0; i<t_index; i++) {
				while(current->node[index[t_index]]->node[j]!=NULL) {
					for(int p=0; p<8; p++) {
						for(int q=0; q<8; q++) {
							if(current->node[index[t_index]]->node[j]->board[p][q]==type)
								t_size2++;
						}
					}
					if(t_size1<t_size2) {
						t_index2=0;
						index2[t_index2]=i;
					}
					else if(t_size1==t_size2 && i!=index2[t_index2]) {
						t_index2++;
						index2[t_index2]=i;

					}
					j++;
					t_size2=0;
				}
			}
			t_size1=0;
			t_size2=0;

			save=0;
			for(int p=0; p<8; p++) {
				for(int q=0; q<8; q++) {
					if(current->node[index2[0]]->board[p][q]==type)
						t_size1++;
				}
			}
			for(int i=1; i<t_index2; i++)
			{
				for(int p=0; p<8; p++) {
					for(int q=0; q<8; q++) {
						if(current->node[index2[i]]->board[p][q]==type)
							t_size2++;
					}
				}
				if(t_size1>t_size2) {
					t_size1=t_size2;
					save=i;
				}
				t_size2=0;
			}
			
			*x=current->node[index2[save]]->xPos;
			*y=current->node[index2[save]]->yPos;
		}
		
		else {
			*x=current->node[index2[0]]->xPos;
			*y=current->node[index2[0]]->yPos;
		}
		
	}
	if(type==BLACK)
		turn_black++;
	else
		turn_white++;
}
MyPoint* ExploreNode(MyPoint *current, int type)
{
	MyPoint *now;
	now=(MyPoint*)malloc(sizeof(MyPoint));
	now=current->node[0];
	return now;

}
void BlackAttack_2012180023( int *x, int *y )
{
	SetBoards();
	board=OdeloGame.Get_OdeloPan();
	Attack(BLACK, head, x, y);

}
void BlackDefence_2012180023( int x, int y )
{
	SetBoards();
	board=OdeloGame.Get_OdeloPan();
	//printf("\n%d,%d\n", sX, sY);
}


void WhiteAttack_2012180023( int *x, int *y )
{
	Attack(WHITE, head, x, y);
}

void WhiteDefence_2012180023( int x, int y )
{
	SetBoards();
	board=OdeloGame.Get_OdeloPan();
	//printf("%d,%d", now->xPos, now->yPos);

}