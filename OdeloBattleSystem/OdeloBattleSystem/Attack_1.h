#ifndef _ATTACK_1_H_
#define _ATTACK_1_H_

#include "OdeloBattleSystem.h"
#include <Windows.h>
#include <time.h>

typedef struct Odelo_Count
{
	int Attack_Point;
	bool check_position;
}OC;
OC Black_Attack_Check[g_nMax][g_nMax];
OC White_Attack_Check[g_nMax][g_nMax];


int b_check_2012181008_eunjea(int xPos, int yPos){
	int x,y;
	int tx,ty;	//임시변수
	int **b_pan_2012181008_eunjea = OdeloGame.Get_OdeloPan();

	if(BLACK==b_pan_2012181008_eunjea[yPos][xPos] || WHITE==b_pan_2012181008_eunjea[yPos][xPos]){
		return 0;				//그 자리에 이미 돌이 있을경우 함수를 빠져나온다
	}else{
		/*좌표에 테두리 검사*/
		for(y=-1; y<=1; ++y){
			for(x=-1; x<=1; ++x){
				if(xPos+x<0 || xPos+x>7 || yPos+y<0 || yPos+y>7){
					continue;
				}

				if(b_pan_2012181008_eunjea[yPos+y][xPos+x]==PAN || b_pan_2012181008_eunjea[yPos+y][xPos+x]==BLACK ){
					continue;	//좌표 주위 테두리에 돌이 없거나 같은 색의 돌이거나 힌트돌일 경우에는 다른 방향을 검사한다
				}
				else			//현재 턴에 돌과 다른색의 돌일 경우 해당 x,y방향으로 더 검사해본다.
					tx = x+x;	//검사하는 해당 방향으로 x좌표를 한칸씩 더 움직임
					ty = y+y;	//검사하는 해당 방향으로 y좌표를 한칸씩 더 움직임

					/*오델로 판의 끝 좌표를 벗어나지 않을경우 루프를 돌게한다*/
					while((0<=xPos+tx) && (0<=yPos+ty) && (xPos+tx<8) && (yPos+ty<8)){
						if(BLACK==b_pan_2012181008_eunjea[yPos+ty][xPos+tx]){
							//printf("x : %d, y : %d\n",xPos+tx,yPos+ty);
							return 1;	//해당 좌표가 같은턴이라면 놓을 수 있는 자리
						}
						else if(PAN==b_pan_2012181008_eunjea[yPos+ty][xPos+tx]){
							break;		//해당 좌표가 비어있거나 힌트돌이 있다면 다른 좌표를 탐색하게 빠져나온다
						}
						tx += x;		//검사하는 해당 방향으로 x좌표를 한칸씩 더 움직임
						ty += y;		//검사하는 해당 방향으로 y좌표를 한칸씩 더 움직임
					}
				}
			}
		}
	return 0;		//놓을 수 없는 자리로 리턴값 0 반환
}

void BlackAttack_2012181008_eunjae( int *x, int *y )
{
	int **b_pan_2012181008_eunjea = OdeloGame.Get_OdeloPan();	//오델로 판 변수
	int b_k_2012181008_eunjea = 0;								//놓을 수 있는 좌표의 갯수
	int b_put_2012181008_eunjea[30][2];							//놓을 수 있는 좌표 저장하는 변수
	int tx = 0 , ty = 0;										//놓을 곳 저장하는 임시 변수
	int num[30];												//놓을 수 있는 좌표의 확률 넣는 변수
	int max;													//최대 확률 넣는 변수
	int max_index;												//최대 확률이 있는 인덱스 저장하는 변수
	//srand(time(unsigned(NULL)));

	for(int i=0; i<8; ++i){						
		for(int j=0; j<8; ++j){
			if(b_check_2012181008_eunjea(j, i)){					//놓을 수 있는 좌표를 찾아 배열에 넣는다
				b_put_2012181008_eunjea[b_k_2012181008_eunjea][0]   = j;
				b_put_2012181008_eunjea[b_k_2012181008_eunjea++][1] = i;
			}
		}
	}

	if(b_k_2012181008_eunjea==0){
		return;
	}

	for(int i=0; i<b_k_2012181008_eunjea; ++i){
		/***********************모서리**************************/
		if(b_put_2012181008_eunjea[i][0]==0 && b_put_2012181008_eunjea[i][1]==0 ||	//왼쪽 위 모서리
			b_put_2012181008_eunjea[i][0]==7 && b_put_2012181008_eunjea[i][1]==7 ||	//오른쪽 밑 모서리
			b_put_2012181008_eunjea[i][0]==0 && b_put_2012181008_eunjea[i][1]==7 || //왼쪽 아래 모서리
			b_put_2012181008_eunjea[i][0]==7 && b_put_2012181008_eunjea[i][1]==0){	//오른쪽 아래 모서리

				//※모서리는 가장 중요한곳이므로 가중치 없이 모서리에
				//  놓을 수 있으면 곧바로 놓고 함수를 빠져나온다.
				
				*x = b_put_2012181008_eunjea[i][0];
				*y = b_put_2012181008_eunjea[i][1];

				return;
		}
		/***********************모서리 제외 한 끝변**************************/
		else if(1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==0 ||	//위쪽 변
			1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==7 ||		//아래쪽 변
			1<=b_put_2012181008_eunjea[i][1] && b_put_2012181008_eunjea[i][1]<=6 && b_put_2012181008_eunjea[i][0]==0 ||		//왼쪽 변
			1<=b_put_2012181008_eunjea[i][1] && b_put_2012181008_eunjea[i][1]<=6 && b_put_2012181008_eunjea[i][0]==7 ){		//오른쪽 변

				/*맨 위쪽 변*/
				if(1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==0){
					if(b_pan_2012181008_eunjea[0][0]==BLACK && b_pan_2012181008_eunjea[0][7]==BLACK){
						//===>두 쪽 모서리 둘다 인공지능이 가지고 있을때<===

						if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[2][0]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE  && b_pan_2012181008_eunjea[0][0]==PAN||
							b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[2][7]==BLACK && b_pan_2012181008_eunjea[1][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN){
								//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if(b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면

							num[i] = 98;

						}else if(b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE ||
							b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
								//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 나의 돌일때

								if(b_put_2012181008_eunjea[i][0]==2 && b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE){
									num[i] = 1;
								}else if(b_put_2012181008_eunjea[i][0]==5 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
									num[i] = 1;
								}else{
									num[i] = 75;
								}

						}else if(b_put_2012181008_eunjea[i][0]-1==WHITE || b_put_2012181008_eunjea[i][0]+1==WHITE){
							//놓을 좌표 양 옆중에 하나가 다른색일때

							if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
								num[i] = 3;
							}else{
								num[i] = 85;
							}

						}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치
							num[i] = 90;
						}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치
							num[i] = 80;
						}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치
							num[i] = 5;
						}

					}else if(b_pan_2012181008_eunjea[0][0]==PAN && b_pan_2012181008_eunjea[0][7]==BLACK ||
						b_pan_2012181008_eunjea[0][0]==BLACK && b_pan_2012181008_eunjea[0][7]==PAN){
							//===>두 쪽 모서리 중 하나 먹은 모서리가 인공지능이 먹은것일때<===

							if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[2][0]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN ||
								b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[2][7]==BLACK && b_pan_2012181008_eunjea[1][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_pan_2012181008_eunjea[0][7]==WHITE && b_put_2012181008_eunjea[i][0]!=6 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE ||
								b_pan_2012181008_eunjea[0][0]==WHITE && b_put_2012181008_eunjea[i][0]!=1 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
									//놓을 좌표 양 옆에 상대편 돌이 있고 먹었을때 상대방 모서리에 의해 먹히지 않을 조건일때

									num[i] = 98;	//★★★★★★테스트로 가중치 체크 해볼것

							}else if(b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE ||
								b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
									//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 나의 돌일때

									if(b_put_2012181008_eunjea[i][0]==2 && b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE){
										num[i] = 1;
									}else if(b_put_2012181008_eunjea[i][0]==5 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
										num[i] = 1;
									}else{
										num[i] = 75;
									}

							}else if(b_put_2012181008_eunjea[i][0]-1==WHITE || b_put_2012181008_eunjea[i][0]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색일때

								if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;
								}else{
									num[i] = 85;
								}

							}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치
								num[i] = 90;
							}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치
								num[i] = 80;
							}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치
								num[i] = 5;
							}

					}else if(b_pan_2012181008_eunjea[0][0]==BLACK && b_pan_2012181008_eunjea[0][7]==WHITE ||
						b_pan_2012181008_eunjea[0][0]==WHITE && b_pan_2012181008_eunjea[0][7]==BLACK){
							//===>두 쪽 모서리 중 하나는 인공지능이 하나는 상대방이 먹은것일때<===

							if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[2][0]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN ||
								b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[2][7]==BLACK && b_pan_2012181008_eunjea[1][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_pan_2012181008_eunjea[0][7]==WHITE && b_put_2012181008_eunjea[i][0]!=6 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE ||
								b_pan_2012181008_eunjea[0][0]==WHITE && b_put_2012181008_eunjea[i][0]!=1 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
									//놓을 좌표 양 옆에 상대편 돌이 있고 먹었을때 상대방 모서리에 의해 먹히지 않을 조건일때

									num[i] = 98;	//★★★★★★테스트로 가중치 체크 해볼것
							}else if(b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE ||
								b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
									//놓을 좌표 양 옆중에 하나가 다른색이라면

									if(b_put_2012181008_eunjea[i][0]==2 && b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE){
										num[i] = 1;
									}else if(b_put_2012181008_eunjea[i][0]==5 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
										num[i] = 1;
									}else{
										num[i] = 75;
									}

							}else if(b_put_2012181008_eunjea[i][0]-1==WHITE || b_put_2012181008_eunjea[i][0]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색일때

								if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;
								}else{
									num[i] = 85;
								}
							}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치
								num[i] = 90;
							}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치
								num[i] = 80;
							}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치
								num[i] = 5;
							}

					}else if(b_pan_2012181008_eunjea[0][7]==PAN && b_pan_2012181008_eunjea[0][0]==PAN){
						//===>두 쪽 모서리 둘다 아무도 안먹었을때<===

						if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[2][0]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN ||
							b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[1][7]==BLACK && b_pan_2012181008_eunjea[2][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN){
								//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if(b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면

							num[i] = 95;

						}else if(b_put_2012181008_eunjea[i][0]-1==PAN && b_put_2012181008_eunjea[i][0]+1==PAN){
							//아무것도 없다면
							num[i] = 99;

						}else if(b_put_2012181008_eunjea[i][0]-1==PAN && b_put_2012181008_eunjea[i][0]+1==WHITE ||
							b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==PAN){

								if(b_put_2012181008_eunjea[i][0]-1==PAN && b_put_2012181008_eunjea[i][0]+1==WHITE){//연속으로 상대돌이 놓여지고 그걸
									for(int j=1; b_put_2012181008_eunjea[i][0]+j<8; ++j){	 //다 먹을 수 있는지 조사
										if( (b_put_2012181008_eunjea[i][0]+j)==WHITE){
											continue;
										}else if((b_put_2012181008_eunjea[i][0]+j)==BLACK){	
											num[i] = 98;
											break;
										}else{		//빈칸
											num[i] = 15;
											break;
										}
									}
								}else{
									for(int j=1; 0 <= b_put_2012181008_eunjea[i][0]-j; ++j){
										if( (b_put_2012181008_eunjea[i][0]-j)==WHITE){
											continue;
										}else if((b_put_2012181008_eunjea[i][0]-j)==BLACK){	
											num[i] = 98;
											break;
										}else{		//빈칸
											num[i] = 15;
											break;
										}
									}
								}

						}else if(b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE ||
							b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
								//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 나의 돌일때

								if(b_put_2012181008_eunjea[i][0]==2 && b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE){
									num[i] = 1;
								}else if(b_put_2012181008_eunjea[i][0]==5 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
									num[i] = 1;
								}else{
									num[i] = 85;
								}

						}else if(b_put_2012181008_eunjea[i][0]-1==WHITE || b_put_2012181008_eunjea[i][0]+1==WHITE){
							//놓을 좌표 양 옆중에 하나가 다른색일때

							if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
								num[i] = 3;
							}else{
								num[i] = 85;
							}
						}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치
							num[i] = 90;
						}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치
							num[i] = 80;
						}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치
							num[i] = 5;
						}
					}else if(b_pan_2012181008_eunjea[0][7]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN ||
						b_pan_2012181008_eunjea[0][7]==PAN && b_pan_2012181008_eunjea[0][0]==WHITE){
							//==>모서리 한군대를 상대방이 가지고 있을 경우<==

							if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[2][0]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN ||
								b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[1][7]==BLACK && b_pan_2012181008_eunjea[2][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_put_2012181008_eunjea[i][0]-1!=0 && b_put_2012181008_eunjea[i][0]+1!=7 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
								//놓을 좌표 양 옆에 검정색이 있다면 그리고 그 양쪽이 모서리 부분이 아닐때

								num[i] = 55;

							}else if(b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE ||
								b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
									//놓을 좌표 양 옆중에 하나가 다른색이라면

									if(b_put_2012181008_eunjea[i][0]==2 && b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE){
										num[i] = 1;
									}else if(b_put_2012181008_eunjea[i][0]==5 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
										num[i] = 1;
									}else{
										num[i] = 75;
									}

							}else if(b_put_2012181008_eunjea[i][0]-1==WHITE || b_put_2012181008_eunjea[i][0]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색일때

								if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;
								}else{
									num[i] = 85;
								}

								//※모서리 하나를 상대방에게 먹혔으므로 Default-50
							}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치 - 50
								num[i] = 40;
							}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치 - 50
								num[i] = 30;
							}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치 - 50
								num[i] = -45;
							}
					}else if(b_pan_2012181008_eunjea[0][7]==WHITE && b_pan_2012181008_eunjea[0][0]==WHITE){
						//==>모서리 두군대 모두 상대방이 가지고 있을 경우<==

						if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[2][0]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN||
							b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[1][7]==BLACK && b_pan_2012181008_eunjea[2][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN){
								//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if(b_put_2012181008_eunjea[i][0]-1!=0 && b_put_2012181008_eunjea[i][0]+1!=7 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면 그리고 그 양쪽이 모서리 부분이 아닐때

							num[i] = 55;

						}else if(b_put_2012181008_eunjea[i][0]-1==WHITE || b_put_2012181008_eunjea[i][0]+1==WHITE){
							//놓을 좌표 양 옆중에 하나가 다른색이라면

							if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
								num[i] = 3;
							}else{
								num[i] = 85;
							}
							//※모서리 두개를 상대방에게 먹혔으므로 Default-60
						}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치 - 60
							num[i] = 30;
						}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치 - 60
							num[i] = 20;
						}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치 - 60
							num[i] = -55;
						}
					}
				}//end of 위쪽변
				
				/*맨 아래쪽 변*/
				else if(1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==7){
					if(b_pan_2012181008_eunjea[7][0]==BLACK && b_pan_2012181008_eunjea[7][7]==BLACK){
						//===>두 쪽 모서리 둘다 인공지능이 가지고 있을때<===

						if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[5][0]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN ||
							b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[5][7]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
								//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if(b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면

							num[i] = 98;

						}else if(b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE ||
							b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
								//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

								if(b_put_2012181008_eunjea[i][0]==2 && b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE){
									num[i] = 1;
								}else if(b_put_2012181008_eunjea[i][0]==5 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
									num[i] = 1;
								}else{
									num[i] = 75;
								}

						}else if(b_put_2012181008_eunjea[i][0]-1==WHITE || b_put_2012181008_eunjea[i][0]+1==WHITE){
							//놓을 좌표 양 옆중에 하나가 다른색일때

							if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
								num[i] = 3;
							}else{
								num[i] = 85;
							}
						}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치
							num[i] = 90;
						}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치
							num[i] = 80;
						}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치
							num[i] = 5;
						}
					}else if(b_pan_2012181008_eunjea[7][0]==PAN && b_pan_2012181008_eunjea[7][7]==BLACK ||
							b_pan_2012181008_eunjea[7][0]==BLACK && b_pan_2012181008_eunjea[7][7]==PAN){
							//===>두 쪽 모서리 중 하나 먹은 모서리가 인공지능이 먹은것일때<===

							if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[5][0]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN ||
								b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[5][7]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_pan_2012181008_eunjea[7][7]==WHITE && b_put_2012181008_eunjea[i][0]!=6 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE ||
								b_pan_2012181008_eunjea[7][0]==WHITE && b_put_2012181008_eunjea[i][0]!=1 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
									//놓을 좌표 양 옆에 상대편 돌이 있고 먹었을때 상대방 모서리에 의해 먹히지 않을 조건일때

									num[i] = 98;	//★★★★★★테스트로 가중치 체크 해볼것

							}else if(b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
								//놓을 좌표 양 옆에 검정색이 있다면

								num[i] = 98;

							}else if(b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE ||
									b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
									//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

									if(b_put_2012181008_eunjea[i][0]==2 && b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE){
										num[i] = 1;
									}else if(b_put_2012181008_eunjea[i][0]==5 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
										num[i] = 1;
									}else{
										num[i] = 75;
									}

							}else if(b_put_2012181008_eunjea[i][0]-1==WHITE || b_put_2012181008_eunjea[i][0]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색일때

								if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;
								}else{
									num[i] = 85;
								}
							}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치
								num[i] = 90;
							}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치
								num[i] = 80;
							}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치
								num[i] = 5;
							}
					}else if(b_pan_2012181008_eunjea[7][0]==PAN && b_pan_2012181008_eunjea[7][7]==PAN){
						//===>두 쪽 모서리 둘다 아무도 안먹었을때<===

						if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[5][0]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN||
							b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[5][7]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
								//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if(b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면

							num[i] = 95;

						}else if(b_put_2012181008_eunjea[i][0]-1==PAN && b_put_2012181008_eunjea[i][0]+1==PAN){
							//아무것도 없다면
							num[i] = 99;

						}else if(b_put_2012181008_eunjea[i][0]-1==PAN && b_put_2012181008_eunjea[i][0]+1==WHITE ||
								b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==PAN){

								if(b_put_2012181008_eunjea[i][0]-1==PAN && b_put_2012181008_eunjea[i][0]+1==WHITE){//연속으로 상대돌이 놓여지고 그걸
									for(int j=1; b_put_2012181008_eunjea[i][0]+j<8; ++j){	 //다 먹을 수 있는지 조사
										if( (b_put_2012181008_eunjea[i][0]+j)==WHITE){
											continue;
										}else if((b_put_2012181008_eunjea[i][0]+j)==BLACK){	
											num[i] = 98;
											break;
										}else{		//빈칸
											num[i] = 15;
											break;
										}
									}
								}else{
									for(int j=1; 0 <= b_put_2012181008_eunjea[i][0]-j; ++j){
										if( (b_put_2012181008_eunjea[i][0]-j)==WHITE){
											continue;
										}else if((b_put_2012181008_eunjea[i][0]-j)==BLACK){	
											num[i] = 98;
											break;
										}else{		//빈칸
											num[i] = 15;
											break;
										}
									}
								}


						}else if(b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE ||
							b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
								//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

								if(b_put_2012181008_eunjea[i][0]==2 && b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE){
									num[i] = 1;
								}else if(b_put_2012181008_eunjea[i][0]==5 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
									num[i] = 1;
								}else{
									num[i] = 85;
								}

						}else if(b_put_2012181008_eunjea[i][0]-1==WHITE || b_put_2012181008_eunjea[i][0]+1==WHITE){
							//놓을 좌표 양 옆중에 하나가 다른색일때

							if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
								num[i] = 3;
							}else{
								num[i] = 85;
							}
						}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치
							num[i] = 90;
						}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치
							num[i] = 80;
						}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치
							num[i] = 5;
						}

					}else if(b_pan_2012181008_eunjea[7][0]==BLACK && b_pan_2012181008_eunjea[7][7]==WHITE ||
							b_pan_2012181008_eunjea[7][0]==WHITE && b_pan_2012181008_eunjea[7][7]==BLACK){
							//===>두 쪽 모서리 중 하나는 인공지능이 하나는 상대방이 먹은것일때<===

							if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[5][0]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN||
								b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[5][7]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_pan_2012181008_eunjea[7][7]==WHITE && b_put_2012181008_eunjea[i][0]!=6 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE ||
								b_pan_2012181008_eunjea[7][0]==WHITE && b_put_2012181008_eunjea[i][0]!=1 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
									//놓을 좌표 양 옆에 상대편 돌이 있고 먹었을때 상대방 모서리에 의해 먹히지 않을 조건일때

									num[i] = 98;	//★★★★★★테스트로 가중치 체크 해볼것

							}else if(b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
									//놓을 좌표 양 옆에 검정색이 있다면

									num[i] = 98;

							}else if(b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE ||
								b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
									//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

									if(b_put_2012181008_eunjea[i][0]==2 && b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE){
										num[i] = 1;
									}else if(b_put_2012181008_eunjea[i][0]==5 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
										num[i] = 1;
									}else{
										num[i] = 75;
									}

							}else if(b_put_2012181008_eunjea[i][0]-1==WHITE || b_put_2012181008_eunjea[i][0]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색일때

								if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;
								}else{
									num[i] = 85;
								}
							}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치
								num[i] = 90;
							}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치
								num[i] = 80;
							}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치
								num[i] = 5;
							}
					}else if(b_pan_2012181008_eunjea[7][0]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN || 
							b_pan_2012181008_eunjea[7][0]==PAN && b_pan_2012181008_eunjea[7][7]==WHITE){
							//==>모서리 한군대를 상대방이 가지고 있을 경우<==

							if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[5][0]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN||
								b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[5][7]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_put_2012181008_eunjea[i][0]-1!=0 && b_put_2012181008_eunjea[i][0]+1!=7 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
								//놓을 좌표 양 옆에 검정색이 있다면 그리고 그 양쪽이 모서리 부분이 아닐때

								num[i] = 55;

							}else if(b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==WHITE){		
								//놓을 좌표 양 옆에 검정색이 있다면

								num[i] = 98;

							}else if(b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE ||
								b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
									//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

									if(b_put_2012181008_eunjea[i][0]==2 && b_put_2012181008_eunjea[i][0]-1==BLACK && b_put_2012181008_eunjea[i][0]+1==WHITE){
										num[i] = 1;
									}else if(b_put_2012181008_eunjea[i][0]==5 && b_put_2012181008_eunjea[i][0]-1==WHITE && b_put_2012181008_eunjea[i][0]+1==BLACK){
										num[i] = 1;
									}else{
										num[i] = 75;
									}

							}else if(b_put_2012181008_eunjea[i][0]-1==WHITE || b_put_2012181008_eunjea[i][0]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색일때

								if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;
								}else{
									num[i] = 85;
								}
								//※모서리 하나를 상대방에게 먹혔으므로 Default-50
							}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치 - 50
								num[i] = 40;
							}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치 - 50
								num[i] = 30;
							}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치 - 50
								num[i] = -45;
							}
					}else if(b_pan_2012181008_eunjea[7][7]==WHITE && b_pan_2012181008_eunjea[0][0]==WHITE){
						//==>모서리 두군대 모두 상대방이 가지고 있을 경우<==

						if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[5][0]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN||
							b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[5][7]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
							//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if( (b_put_2012181008_eunjea[i][0]-1)!=0 && (b_put_2012181008_eunjea[i][0]+1)!=7 && (b_put_2012181008_eunjea[i][0]-1)==WHITE && (b_put_2012181008_eunjea[i][0]+1)==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면 그리고 그 양쪽이 모서리 부분이 아닐때

							num[i] = 55;
							//※모서리 두개를 상대방에게 먹혔으므로 Default-60

						}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){	//Default 수치 - 60
							num[i] = 30;
						}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){	//Default 수치 - 60
							num[i] = 20;
						}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){	//Default 수치 - 60
							num[i] = -55;
						}
					}
				}//end of 맨 아래쪽 끝변

				/*맨 왼쪽 끝변*/
				else if(1<=b_put_2012181008_eunjea[i][1] && b_put_2012181008_eunjea[i][1]<=6 && b_put_2012181008_eunjea[i][0]==0){
					if(b_pan_2012181008_eunjea[0][0]==BLACK && b_pan_2012181008_eunjea[7][0]==BLACK){
						//===>두 쪽 모서리 둘다 인공지능이 가지고 있을때<===

						if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][2]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN ||
							b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][2]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN){
								//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if(b_put_2012181008_eunjea[i][1]-1==PAN && b_put_2012181008_eunjea[i][1]+1==WHITE || 
							b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==PAN){

								num[i] = 20;

						}else if(b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면

							num[i] = 98;

						}else if(b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE ||
							b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
								//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

								if(b_put_2012181008_eunjea[i][1]==2 && b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE){
									num[i] = 1;
								}else if(b_put_2012181008_eunjea[i][1]==5 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
									num[i] = 1;
								}else{
									num[i] = 75;
								}
						}else if(b_put_2012181008_eunjea[i][1]-1==WHITE || b_put_2012181008_eunjea[i][1]+1==WHITE){
							//놓을 좌표 양 옆중에 하나가 다른색이라면

							if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
								num[i] = 3;
							}else{
								num[i] = 85;
							}

						}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치
							num[i] = 90;
						}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치
							num[i] = 80;
						}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치
							num[i] = 5;
						}

					}else if(b_pan_2012181008_eunjea[7][0]==PAN && b_pan_2012181008_eunjea[0][0]==BLACK ||
						b_pan_2012181008_eunjea[7][0]==BLACK && b_pan_2012181008_eunjea[0][0]==PAN){
							//===>두 쪽 모서리 중 하나 먹은 모서리가 인공지능이 먹은것일때<===

							if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][2]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN||
								b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][2]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_pan_2012181008_eunjea[0][0]==WHITE && b_put_2012181008_eunjea[i][1]!=1 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE ||
								b_pan_2012181008_eunjea[7][0]==WHITE && b_put_2012181008_eunjea[i][1]!=6 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
									//놓을 좌표 양 옆에 상대편 돌이 있고 먹었을때 상대방 모서리에 의해 먹히지 않을 조건일때

									num[i] = 98;	//★★★★★★테스트로 가중치 체크 해볼것

							}else if(b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE ||
								b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
									//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

									if(b_put_2012181008_eunjea[i][1]==2 && b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE){
										num[i] = 1;
									}else if(b_put_2012181008_eunjea[i][1]==5 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
										num[i] = 1;
									}else{
										num[i] = 75;
									}
							}else if(b_put_2012181008_eunjea[i][1]-1==WHITE || b_put_2012181008_eunjea[i][1]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색이라면

								if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;
								}else{
									num[i] = 85;
								}

							}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치
								num[i] = 90;
							}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치
								num[i] = 80;
							}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치
								num[i] = 5;
							}
					}else if(b_pan_2012181008_eunjea[7][0]==PAN && b_pan_2012181008_eunjea[0][0]==PAN){
						//===>두 쪽 모서리 둘다 아무도 안먹었을때<===

						if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][2]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN||
							b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][2]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN){
								//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if(b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면

							num[i] = 95;

						}else if(b_put_2012181008_eunjea[i][1]-1==PAN && b_put_2012181008_eunjea[i][1]+1==PAN){
							//아무것도 없다면
							num[i] = 99;

						}else if(b_put_2012181008_eunjea[i][1]-1==PAN && b_put_2012181008_eunjea[i][1]+1==WHITE ||
							b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==PAN){

								if(b_put_2012181008_eunjea[i][1]-1==PAN && b_put_2012181008_eunjea[i][1]+1==WHITE){//연속으로 상대돌이 놓여지고 그걸
									for(int j=1; b_put_2012181008_eunjea[i][1]+j<8; ++j){	 //다 먹을 수 있는지 조사
										if( (b_put_2012181008_eunjea[i][1]+j)==WHITE){
											continue;
										}else if((b_put_2012181008_eunjea[i][1]+j)==BLACK){	
											num[i] = 98;
											break;
										}else{		//빈칸
											num[i] = 15;
											break;
										}
									}
								}else{
									for(int j=1; 0 <= b_put_2012181008_eunjea[i][1]-j; ++j){
										if( (b_put_2012181008_eunjea[i][1]-j)==WHITE){
											continue;
										}else if((b_put_2012181008_eunjea[i][1]-j)==BLACK){	
											num[i] = 98;
											break;
										}else{		//빈칸
											num[i] = 15;
											break;
										}
									}
								}

						}else if(b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE ||
							b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
								//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

								if(b_put_2012181008_eunjea[i][1]==2 && b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE){
									num[i] = 1;
								}else if(b_put_2012181008_eunjea[i][1]==5 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
									num[i] = 1;
								}else{
									num[i] = 85;
								}
						}else if(b_put_2012181008_eunjea[i][1]-1==WHITE || b_put_2012181008_eunjea[i][1]+1==WHITE){
							//놓을 좌표 양 옆중에 하나가 다른색이라면
							if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
								num[i] = 3;					 
							}else{
								num[i] = 85;
							}
						}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치
							num[i] = 90;
						}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치
							num[i] = 80;
						}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치
							num[i] = 5;
						}

					}else if(b_pan_2012181008_eunjea[7][0]==BLACK && b_pan_2012181008_eunjea[0][0]==WHITE ||
							b_pan_2012181008_eunjea[7][0]==WHITE && b_pan_2012181008_eunjea[0][0]==BLACK){
							//===>두 쪽 모서리 중 하나는 인공지능이 하나는 상대방이 먹은것일때<===

							if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][2]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN||
								b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][2]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_pan_2012181008_eunjea[0][0]==WHITE && b_put_2012181008_eunjea[i][1]!=1 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE ||
								b_pan_2012181008_eunjea[7][0]==WHITE && b_put_2012181008_eunjea[i][1]!=6 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
									//놓을 좌표 양 옆에 상대편 돌이 있고 먹었을때 상대방 모서리에 의해 먹히지 않을 조건일때

									num[i] = 98;	//★★★★★★테스트로 가중치 체크 해볼것

							}else if(b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE ||
								b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
									//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

									if(b_put_2012181008_eunjea[i][1]==2 && b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE){
										num[i] = 1;
									}else if(b_put_2012181008_eunjea[i][1]==5 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
										num[i] = 1;
									}else{
										num[i] = 75;
									}
							}else if(b_put_2012181008_eunjea[i][1]-1==WHITE || b_put_2012181008_eunjea[i][1]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색이라면
								if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;					 
								}else{
									num[i] = 85;
								}

							}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치
								num[i] = 90;
							}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치
								num[i] = 80;
							}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치
								num[i] = 5;
							}
					}else if(b_pan_2012181008_eunjea[7][0]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN || 
						b_pan_2012181008_eunjea[7][0]==PAN && b_pan_2012181008_eunjea[0][0]==WHITE){
							//==>모서리 한군대를 상대방이 가지고 있을 경우<==

							if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][2]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN||
								b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][2]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_put_2012181008_eunjea[i][1]-1!=0 && b_put_2012181008_eunjea[i][1]+1!=7 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
								//놓을 좌표 양 옆에 검정색이 있다면 그리고 그 양쪽이 모서리 부분이 아닐때

								num[i] = 55;

							}else if(b_put_2012181008_eunjea[i][1]-1==WHITE || b_put_2012181008_eunjea[i][1]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색이라면

								if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;
								}else{
									num[i] = 85;
								}
								//※모서리 하나를 상대방에게 먹혔으므로 Default-50
							}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치 - 50
								num[i] = 40;
							}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치 - 50
								num[i] = 30;
							}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치 - 50
								num[i] = -45;
							}

					}else if(b_pan_2012181008_eunjea[0][0]==WHITE && b_pan_2012181008_eunjea[7][0]==WHITE){
						//==>모서리 두군대 모두 상대방이 가지고 있을 경우<==

						if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][2]==BLACK && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][0]==PAN||
							b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][2]==BLACK && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][0]==PAN){
								//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if(b_put_2012181008_eunjea[i][1]-1!=0 && b_put_2012181008_eunjea[i][1]+1!=7 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면 그리고 그 양쪽이 모서리 부분이 아닐때

							num[i] = 55;
							//※모서리 두개를 상대방에게 먹혔으므로 Default-60
						}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치 - 60
							num[i] = 30;
						}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치 - 60
							num[i] = 20;
						}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치 - 60
							num[i] = -55;
						}
					}
				}//end of 맨 왼쪽 끝변

				/*맨 오른쪽 끝변*/
				else if(1<=b_put_2012181008_eunjea[i][1] && b_put_2012181008_eunjea[i][1]<=6 && b_put_2012181008_eunjea[i][0]==7){
					if(b_pan_2012181008_eunjea[0][7]==BLACK && b_pan_2012181008_eunjea[7][7]==BLACK){
						//===>두 쪽 모서리 둘다 인공지능이 가지고 있을때<==

						if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][5]==BLACK && b_pan_2012181008_eunjea[1][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN||
							b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][5]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
								//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if(b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면

							num[i] = 98;

						}else if(b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE ||
							b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
								//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

								if(b_put_2012181008_eunjea[i][1]==2 && b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE){
									num[i] = 1;
								}else if(b_put_2012181008_eunjea[i][1]==5 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
									num[i] = 1;
								}else{
									num[i] = 75;
								}
						}else if(b_put_2012181008_eunjea[i][1]-1==WHITE || b_put_2012181008_eunjea[i][1]+1==WHITE){
							//놓을 좌표 양 옆중에 하나가 다른색이라면

							if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
								num[i] = 3;
							}else{
								num[i] = 85;
							}
						}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치
							num[i] = 90;
						}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치
							num[i] = 80;
						}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치
							num[i] = 5;
						}
					}else if(b_pan_2012181008_eunjea[0][7]==PAN && b_pan_2012181008_eunjea[7][7]==BLACK ||
						b_pan_2012181008_eunjea[0][7]==BLACK && b_pan_2012181008_eunjea[7][7]==PAN){
							//===>두 쪽 모서리 중 하나 먹은 모서리가 인공지능이 먹은것일때<===

							if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][5]==BLACK && b_pan_2012181008_eunjea[1][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN||
								b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][5]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_pan_2012181008_eunjea[0][7]==WHITE && b_put_2012181008_eunjea[i][1]!=1 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE ||
								b_pan_2012181008_eunjea[7][7]==WHITE && b_put_2012181008_eunjea[i][1]!=6 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
									//놓을 좌표 양 옆에 상대편 돌이 있고 먹었을때 상대방 모서리에 의해 먹히지 않을 조건일때

									num[i] = 98;	//★★★★★★테스트로 가중치 체크 해볼것

							}else if(b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE ||
								b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
									//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

									if(b_put_2012181008_eunjea[i][1]==2 && b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE){
										num[i] = 1;
									}else if(b_put_2012181008_eunjea[i][1]==5 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
										num[i] = 1;
									}else{
										num[i] = 75;
									}
							}else if(b_put_2012181008_eunjea[i][1]-1==WHITE || b_put_2012181008_eunjea[i][1]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색이라면

								if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;
								}else{
									num[i] = 85;
								}

							}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치
								num[i] = 90;
							}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치
								num[i] = 80;
							}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치
								num[i] = 5;
							}
					}else if(b_pan_2012181008_eunjea[0][7]==PAN && b_pan_2012181008_eunjea[7][7]==PAN){
						//===>두 쪽 모서리 둘다 아무도 안먹었을때<===

						if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][5]==BLACK && b_pan_2012181008_eunjea[1][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN ||
							b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][5]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
								//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if(b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면

							num[i] = 95;

						}else if(b_put_2012181008_eunjea[i][1]-1==PAN && b_put_2012181008_eunjea[i][1]+1==PAN){
							//아무것도 없다면
							num[i] = 99;

						}else if(b_put_2012181008_eunjea[i][1]-1==PAN && b_put_2012181008_eunjea[i][1]+1==WHITE ||
							b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==PAN){

								if(b_put_2012181008_eunjea[i][1]-1==PAN && b_put_2012181008_eunjea[i][1]+1==WHITE){//연속으로 상대돌이 놓여지고 그걸
									for(int j=1; b_put_2012181008_eunjea[i][1]+j<8; ++j){	 //다 먹을 수 있는지 조사
										if( (b_put_2012181008_eunjea[i][1]+j)==WHITE){
											continue;
										}else if((b_put_2012181008_eunjea[i][1]+j)==BLACK){	
											num[i] = 98;
											break;
										}else{		//빈칸
											num[i] = 15;
											break;
										}
									}
								}else{
									for(int j=1; 0 <= b_put_2012181008_eunjea[i][1]-j; ++j){
										if( (b_put_2012181008_eunjea[i][1]-j)==WHITE){
											continue;
										}else if((b_put_2012181008_eunjea[i][1]-j)==BLACK){	
											num[i] = 98;
											break;
										}else{		//빈칸
											num[i] = 15;
											break;
										}
									}
								}

						}else if(b_put_2012181008_eunjea[i][1]-1==PAN && b_put_2012181008_eunjea[i][1]+1==WHITE ||
							b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==PAN){	

								num[i] = 15;

						}else if(b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE ||
							b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
								//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

								if(b_put_2012181008_eunjea[i][1]==2 && b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE){
									num[i] = 1;
								}else if(b_put_2012181008_eunjea[i][1]==5 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
									num[i] = 1;
								}else{
									num[i] = 85;
								}
						}else if(b_put_2012181008_eunjea[i][1]-1==WHITE || b_put_2012181008_eunjea[i][1]+1==WHITE){
							//놓을 좌표 양 옆중에 하나가 다른색이라면
							if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
								num[i] = 3;					 
							}else{
								num[i] = 85;
							}

						}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치
							num[i] = 90;
						}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치
							num[i] = 80;
						}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치
							num[i] = 5;
						}
					}else if(b_pan_2012181008_eunjea[0][7]==BLACK && b_pan_2012181008_eunjea[7][7]==WHITE ||
						b_pan_2012181008_eunjea[0][7]==WHITE && b_pan_2012181008_eunjea[7][7]==BLACK){
							//===>두 쪽 모서리 중 하나는 인공지능이 하나는 상대방이 먹은것일때<===

							if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][5]==BLACK && b_pan_2012181008_eunjea[1][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN||
								b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][5]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_pan_2012181008_eunjea[0][7]==WHITE && b_put_2012181008_eunjea[i][1]!=1 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE ||
								b_pan_2012181008_eunjea[7][7]==WHITE && b_put_2012181008_eunjea[i][1]!=6 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
									//놓을 좌표 양 옆에 상대편 돌이 있고 먹었을때 상대방 모서리에 의해 먹히지 않을 조건일때

									num[i] = 98;	//★★★★★★테스트로 가중치 체크 해볼것

							}else if(b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE ||
								b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
									//놓을 좌표 양 옆중에 하나가 다른색이고 나머지 하나가 내 돌일때

									if(b_put_2012181008_eunjea[i][1]==2 && b_put_2012181008_eunjea[i][1]-1==BLACK && b_put_2012181008_eunjea[i][1]+1==WHITE){
										num[i] = 1;
									}else if(b_put_2012181008_eunjea[i][1]==5 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==BLACK){
										num[i] = 1;
									}else{
										num[i] = 75;
									}
							}else if(b_put_2012181008_eunjea[i][1]-1==WHITE || b_put_2012181008_eunjea[i][1]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색이라면
								if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;					 
								}else{
									num[i] = 85;
								}
							}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치
								num[i] = 90;
							}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치
								num[i] = 80;
							}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치
								num[i] = 5;
							}
					}else if(b_pan_2012181008_eunjea[0][7]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN || 
							b_pan_2012181008_eunjea[0][7]==PAN && b_pan_2012181008_eunjea[7][7]==WHITE){
							//==>모서리 한군대를 상대방이 가지고 있을 경우<==

							if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][5]==BLACK && b_pan_2012181008_eunjea[1][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN||
								b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][5]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
									//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

									num[i] = 1;

							}else if(b_put_2012181008_eunjea[i][1]-1!=0 && b_put_2012181008_eunjea[i][1]+1!=7 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
								//놓을 좌표 양 옆에 검정색이 있다면 그리고 그 양쪽이 모서리 부분이 아닐때

								num[i] = 55;

							}else if(b_put_2012181008_eunjea[i][1]-1==WHITE || b_put_2012181008_eunjea[i][1]+1==WHITE){
								//놓을 좌표 양 옆중에 하나가 다른색이라면

								if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){//여기에 놓을시에 모서리를 먹힐 확률히 크므로 낮게 수치를 놓는다
									num[i] = 3;
								}else{
									num[i] = 85;
								}
								//※모서리 하나를 상대방에게 먹혔으므로 Default-50
							}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치 - 50
								num[i] = 40;
							}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치 - 50
								num[i] = 30;
							}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치 - 50
								num[i] = -45;
							}
					}else if(b_pan_2012181008_eunjea[7][7]==WHITE && b_pan_2012181008_eunjea[0][7]==WHITE){
						//==>모서리 두군대 모두 상대방이 가지고 있을 경우<==

						if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[0][5]==BLACK && b_pan_2012181008_eunjea[1][6]==WHITE && b_pan_2012181008_eunjea[0][7]==PAN||
							b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[7][5]==BLACK && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][7]==PAN){
								//해당 좌표에 놓을때 돌이 뒤집어지면서 가장 놓으면 안될 두번째 모서리를 먹었을때

								num[i] = 1;

						}else if(b_put_2012181008_eunjea[i][1]-1!=0 && b_put_2012181008_eunjea[i][1]+1!=7 && b_put_2012181008_eunjea[i][1]-1==WHITE && b_put_2012181008_eunjea[i][1]+1==WHITE){		
							//놓을 좌표 양 옆에 검정색이 있다면 그리고 그 양쪽이 모서리 부분이 아닐때

							num[i] = 55;
							//※모서리 두개를 상대방에게 먹혔으므로 Default-60
						}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){	//Default 수치 - 60
							num[i] = 30;
						}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){	//Default 수치 - 60
							num[i] = 20;
						}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){	//Default 수치 - 60
							num[i] = -55;
						}
					}
				}//end of 맨 오른쪽 끝변
		}//end of 끝변

		/**********************두번째 끝 변**************************/
		else if(1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==1 ||		//위쪽 두번째변
			1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==6 ||			//아래쪽 두번째변
			1<=b_put_2012181008_eunjea[i][1] && b_put_2012181008_eunjea[i][1]<=6 && b_put_2012181008_eunjea[i][0]==1 ||			//왼쪽 두번째변
			1<=b_put_2012181008_eunjea[i][1] && b_put_2012181008_eunjea[i][1]<=6 && b_put_2012181008_eunjea[i][0]==6){			//오른쪽 두번째변

				/*위쪽 두번째변*/
				if(1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==1){	
					if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[1][0]==BLACK && b_pan_2012181008_eunjea[0][0]==PAN||
						b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[1][6]==WHITE && b_pan_2012181008_eunjea[1][7]==BLACK && b_pan_2012181008_eunjea[0][7]==PAN){

							num[i] = 1;

					}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){

						num[i] = 1;

					}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){

						num[i] = 30;

					}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){

						num[i] = 20;

					}
				}
				/*아래쪽 두번쨰 변*/
				else if(1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==6){	
					if(b_put_2012181008_eunjea[i][0]==2 && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[6][0]==BLACK && b_pan_2012181008_eunjea[7][0]==PAN||
						b_put_2012181008_eunjea[i][0]==5 && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[6][7]==BLACK && b_pan_2012181008_eunjea[7][7]==PAN){

							num[i] = 1;

					}else if(b_put_2012181008_eunjea[i][0]==1 || b_put_2012181008_eunjea[i][0]==6){

						num[i] = 1;

					}else if(b_put_2012181008_eunjea[i][0]==3 || b_put_2012181008_eunjea[i][0]==4){

						num[i] = 30;

					}else if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){

						num[i] = 20;

					}
				}
				/*왼쪽 두번째변*/
				else if(1<=b_put_2012181008_eunjea[i][1] && b_put_2012181008_eunjea[i][1]<=6 && b_put_2012181008_eunjea[i][0]==1){	
					if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[1][1]==WHITE && b_pan_2012181008_eunjea[0][1]==BLACK && b_pan_2012181008_eunjea[0][0]==PAN||
						b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[6][1]==WHITE && b_pan_2012181008_eunjea[7][1]==BLACK && b_pan_2012181008_eunjea[7][0]==PAN){

							num[i] = 1;

					}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){

						num[i] = 1;

					}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){

						num[i] = 30;

					}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){

						num[i] = 20;

					}
				}
				/*오른쪽 두번째 변*/
				else if(1<=b_put_2012181008_eunjea[i][1] && b_put_2012181008_eunjea[i][1]<=6 && b_put_2012181008_eunjea[i][0]==6){	
					if(b_put_2012181008_eunjea[i][1]==2 && b_pan_2012181008_eunjea[1][6]==WHITE && b_pan_2012181008_eunjea[0][6]==BLACK && b_pan_2012181008_eunjea[0][7]==PAN||
						b_put_2012181008_eunjea[i][1]==5 && b_pan_2012181008_eunjea[6][6]==WHITE && b_pan_2012181008_eunjea[7][6]==BLACK && b_pan_2012181008_eunjea[7][7]==PAN){

							num[i] = 1;

					}else if(b_put_2012181008_eunjea[i][1]==1 || b_put_2012181008_eunjea[i][1]==6){

						num[i] = 1;

					}else if(b_put_2012181008_eunjea[i][1]==3 || b_put_2012181008_eunjea[i][1]==4){

						num[i] = 30;

					}else if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){

						num[i] = 20;

					}
				}
		}//end of 두번째 변
		/**********************세번째 끝 변**************************/
		else if(1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==2 ||		//위쪽 세번째변
			1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==5 ||			//아래쪽 세번째변
			1<=b_put_2012181008_eunjea[i][1] && b_put_2012181008_eunjea[i][1]<=6 && b_put_2012181008_eunjea[i][0]==2 ||			//왼쪽 세번째변
			1<=b_put_2012181008_eunjea[i][1] && b_put_2012181008_eunjea[i][1]<=6 && b_put_2012181008_eunjea[i][0]==5){			//오른쪽 세번째변

				/*위쪽 세번째 변*/
				if(1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==2){		
					if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){				//세번째 변에 모서리 부분
						num[i] = 70;
					}else{
						num[i] = 50;
					}
				}
				/*아래쪽 세번째 변*/
				else if(1<=b_put_2012181008_eunjea[i][0] && b_put_2012181008_eunjea[i][0]<=6 && b_put_2012181008_eunjea[i][1]==5){
					if(b_put_2012181008_eunjea[i][0]==2 || b_put_2012181008_eunjea[i][0]==5){				//세번째 변에 모서리 부분
						num[i] = 70;
					}else{
						num[i] = 50;
					}
				}
				/*왼쪽 세번째 변*/
				else if(1<=b_put_2012181008_eunjea[i][1] && b_put_2012181008_eunjea[i][1]<=6 && b_put_2012181008_eunjea[i][0]==2){
					if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){				//세번째 변에 모서리 부분
						num[i] = 70;
					}else{
						num[i] = 50;
					}
				}
				/*오른쪽 세번째 변*/
				else{
					if(b_put_2012181008_eunjea[i][1]==2 || b_put_2012181008_eunjea[i][1]==5){				//세번째 변에 모서리 부분
						num[i] = 70;
					}else{
						num[i] = 50;
					}
				}
		}
	}

	max = num[0];
	max_index = 0;

	for(int i=0; i<b_k_2012181008_eunjea; ++i){
		if(max < num[i]){
			max		  = num[i];
			max_index = i;
		}
	}

	*x = b_put_2012181008_eunjea[max_index][0];
	*y = b_put_2012181008_eunjea[max_index][1];
}

void BlackDefence_2012181008_eunjae( int x, int y )
{
	return;
}


#endif