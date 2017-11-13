#ifndef _OdeloBATTLESYSTEM_H_
#define _OdeloBATTLESYSTEM_H_

#include <cstdio>
#include <iostream>
#include <windows.h>

using namespace std;

#pragma comment( lib, "winmm.lib" )

const int	g_nMax			= 8;	// 오목판 가로 세로 갯수
const int	g_nGameCount	= 1;	// 게임 횟수
const float	g_fLimitTime	= 2.0f; // AI Attack함수 Limit Time 2초 이상이면 게임에서 진다.

const int g_Directiontable[8][2] = { 
	{ -1, -1 }, {  0, -1 },			//왼위,			위
	{  1, -1 }, {  1,  0 },			//오른위,		오른
	{  1,  1 }, {  0,  1 },			//오른 아래,	    아래
	{ -1,  1 }, { -1,  0 }			//왼아래,		왼
};

enum{ PAN, BLACK, WHITE };
enum{ WHITEWIN, BLACKWIN, NOWIN, DROW };

class COdeloBattleSytem
{
	void (*m_funcBlackAttack)( int *x, int *y );	//흑돌 함수 포인터
	void (*m_funcBlackDefence)( int x, int y );
	
	void (*m_funcWhiteAttack)( int *x, int *y );	//백돌 함수 포인터
	void (*m_funcWhiteDefence)( int x, int y );

	int		m_nOdeloType;							// 오목알 타입
	int		m_nUserWin[2];							// 유저 승리
	int		m_nCurrentGameCount;					// 게임 횟수			
	int		m_nOdeloPan[g_nMax][g_nMax];			// 오목판

	bool	m_bActive;								// 게임 상태

	int		m_nBlack;								// 흑돌 턴 횟수
	int		m_nWhite;								// 흰돌 턴 횟수
	int		m_Count;								// 전체 턴 횟수

	__int64 m_nCurrentTime;							// 시간
	__int64 m_nLastTime;
	__int64 m_Freq;			
	bool	m_bPerHardware;							// QueryPerformanceFrequency 지원 여부	

	float	m_fAttackExcuteTime;					// Attack함수 수행시간
	float	m_fDefenceExcuteTime;					// Defence함수 수행시간


public:

	COdeloBattleSytem();

	void SetYourFunc(
		void (*pfuncBlackAttack)( int *x, int *y ),
		void (*pfuncBlackDefence)( int x, int y ),
		void (*pfuncWhiteAttack)( int *x, int *y ),
		void (*pfuncWhiteDefence)( int x, int y ) );

	int** Get_OdeloPan();

	// 게임 시작
	bool BeginGame();
	// 게임 상태 
	bool GetGameState() const { return m_bActive; }
	// 경기 결과 출력
	void Result();
	// 게임 초기화
	void Init();	

private:
	// 판 그리기
	void Draw();
	// 한수 둔다.
	bool PutStone(int x, int y, int type );
	// 승리 여부 판단
	int CheckWin(int CheckCount, int type);
	// 순서 변경( 흑, 백 )
//	void ChangeType();	
	
	// 수행 시간 체크
	void StartTime();
	bool CheckStone(int x, int y, int type);
	void ReverseStone(int x, int y, int type);
	bool CheckTime( float *fResultTime );


};

static COdeloBattleSytem OdeloGame;

#endif