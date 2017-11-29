#include "OdeloBattleSystem.h"
#include "Action.h"

COdeloBattleSytem::COdeloBattleSytem()
{
	//Init();
}

//------ 함수 포인터를 셋팅	------
void COdeloBattleSytem::SetYourFunc(
		void (*pfuncBlackAttack) ( int *x, int *y ),
		void (*pfuncBlackDefence)( int  x, int  y ),
		void (*pfuncWhiteAttack) ( int *x, int *y ),
		void (*pfuncWhiteDefence)( int  x, int  y ) )
//--------------------------------
{
	// 흑돌 함수
	m_funcBlackAttack	= pfuncBlackAttack;
	m_funcBlackDefence	= pfuncBlackDefence;

	// 백돌 함수
	m_funcWhiteAttack	= pfuncWhiteAttack;
	m_funcWhiteDefence	= pfuncWhiteDefence;

}

//--------- 게임 시작 ------------
bool COdeloBattleSytem::BeginGame()
//--------------------------------
{
	int x = -1, y = -1;
	float fLimitTime = 0.0f;
	
	while( m_nCurrentGameCount < g_nGameCount )
	{

		// 무승부
		if( m_nBlack + m_nWhite >= g_nMax * g_nMax )
		{
			std::cout << "무승부 입니다.";
			++m_nCurrentGameCount;
			continue;
		}

		//------------------------------ 흑돌 공격, 백돌 방어------------------------------------
				
		getchar();
		
		StartTime();
		m_funcBlackAttack( &x, &y );		
		if( CheckTime( &m_fAttackExcuteTime ) )
		{
			std::cout << "●흑돌 Attack 수행시간 : " << m_fAttackExcuteTime << "초\n";
			std::cout << "제한시간 : " << g_fLimitTime <<"초를 초과하였으므로 흑돌은 졌습니다.";
			Init();
			++m_nCurrentGameCount;
			continue;
		}
		
		if( PutStone( x, y, BLACK ) )
		{
			++m_nCurrentGameCount;
			continue;
		}

		StartTime();
		m_funcWhiteDefence( x, y );
		if( CheckTime( &m_fDefenceExcuteTime ) )
		{
			std::cout << "○백돌 Defence 수행시간 : " << m_fDefenceExcuteTime << "초\n";
			std::cout << "제한시간 : " << g_fLimitTime <<"초를 초과하였으므로 흑돌은 졌습니다.";
			Init();
			++m_nCurrentGameCount;
			continue;
		}

		//------------------------------------------------------------------------------------------


		//------------------------------ 백돌 공격, 흑돌 방어------------------------------------
		getchar();

		StartTime();
		m_funcWhiteAttack( &x, &y );
		if( CheckTime( &m_fAttackExcuteTime ) )
		{
			std::cout << "○백돌 Attack 수행시간 : " << m_fAttackExcuteTime << "초\n";
			std::cout << "제한시간 : " << g_fLimitTime <<"초를 초과하였으므로 백돌은 졌습니다.";
			Init();
			++m_nCurrentGameCount;
			continue;
		}

		if( PutStone( x, y, WHITE ) )
		{
			++m_nCurrentGameCount;
			continue;
		}

		StartTime();
		m_funcBlackDefence( x, y );
		if( CheckTime( &m_fDefenceExcuteTime ) )
		{
			std::cout << "●흑돌 Denfence 수행시간 : " << m_fDefenceExcuteTime << "초\n";
			std::cout << "제한시간 : " << g_fLimitTime <<"초를 초과하였으므로 흑돌은 졌습니다.";
			Init();
			++m_nCurrentGameCount;
			continue;
		}

		//------------------------------------------------------------------------------------------
	}

	return true;
}


//--------- 게임 초기화 -----------
void COdeloBattleSytem::Init()
//---------------------------------
{
	::ZeroMemory( m_nOdeloPan, sizeof(m_nOdeloPan) );
	::ZeroMemory( m_nUserWin, sizeof(m_nUserWin) );

	m_nOdeloPan[3][3] = BLACK;
	m_nOdeloPan[3][4] = WHITE;
	m_nOdeloPan[4][3] = WHITE;
	m_nOdeloPan[4][4] = BLACK;

	m_bActive			= true;
	m_nOdeloType		= BLACK;
	m_nCurrentGameCount = 0;
	m_nBlack			= 0;
	m_nWhite			= 0;
	m_fAttackExcuteTime = 0.0f;
	m_fDefenceExcuteTime= 0.0f;


	if( QueryPerformanceFrequency( (LARGE_INTEGER*)&m_Freq ) )
	{
		QueryPerformanceCounter( (LARGE_INTEGER*)&m_nCurrentTime); 
		m_bPerHardware = true;
	}
	else
	{
		m_nCurrentTime	= timeGetTime();
		m_bPerHardware	= false;
	}	
	Draw();
}

void COdeloBattleSytem::PrintLog()
{
}

//--------- 경기 결과 출력---------
void COdeloBattleSytem::StartTime()
//---------------------------------
{
	if( m_bPerHardware )
	{
		QueryPerformanceCounter( (LARGE_INTEGER*)&m_nCurrentTime); 
	}
	else
	{
		m_nCurrentTime = timeGetTime();
	}
		
}
	

//--------- 경기 시간 초과---------
bool COdeloBattleSytem::CheckTime( float *fResultTime )
//---------------------------------
{
	if( m_bPerHardware )
	{
		QueryPerformanceFrequency( (LARGE_INTEGER*)&m_Freq );
		QueryPerformanceCounter( (LARGE_INTEGER*)&m_nLastTime); 

		*fResultTime = static_cast<float>( (m_nLastTime - m_nCurrentTime ) / static_cast<float>(m_Freq) );

		if( *fResultTime > g_fLimitTime )
			return true;
	}
	else
	{
		m_nLastTime = timeGetTime();

		*fResultTime = static_cast<float>( ( m_nLastTime - m_nCurrentTime ) * 0.0001f );

		if( *fResultTime > g_fLimitTime )
			return true;
	}	

	return false;
}

bool COdeloBattleSytem::IsPutStone(const int type)
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (CheckStone(j, i, type)) return true;
		}
	}
	return false;
}

void COdeloBattleSytem::GetPutPosition(std::vector<Action>& actions, const int type)
{
	Action a;

	for (int i = 0; i < g_nMax; ++i)
	{
		for (int j = 0; j < g_nMax; ++j)
		{
			if (CheckStone(j, i, type))
			{
				a.m_nPosX = j;
				a.m_nPosY = i;
				actions.push_back(a);
			}
		}
	}
}

int COdeloBattleSytem::PlayOut(const int x, const int y, const int type)
{
	if (type == BLACK)
	{
		if (CheckStone(x, y, type))
		{
			m_nOdeloPan[y][x] = BLACK;
			++m_Count;
			ReverseStone(x, y, type);
			++m_nBlack;
			switch (CheckWin(m_Count, BLACK))
			{
			case BLACKWIN:
				return BLACKWIN;
				break;

			case WHITEWIN:
				return WHITEWIN;
				break;

			case DROW:
				//std::cout << " 무승부입니다.\n ";
				return DROW;
				break;
			}
		}

		else
		{
			//std::cout << " 백돌이 승리하였습니다.\n ";
			return WHITEWIN;
		}

		m_nOdeloType = WHITE;
	}

	else
	{
		if (CheckStone(x, y, type))
		{
			m_nOdeloPan[y][x] = WHITE;
			++m_Count;
			ReverseStone(x, y, type);
			Draw();
			++m_nWhite;
			switch (CheckWin(m_Count, WHITE))
			{
			case BLACKWIN:
				//std::cout << " 흑돌이 승리하였습니다.\n ";
				return BLACKWIN;
				break;

			case WHITEWIN:
				//std::cout << " 백돌이 승리하였습니다.\n ";
				return WHITEWIN;
				break;

			case DROW:
				//std::cout << " 무승부입니다.\n ";
				return DROW;
				break;
			}
		}

		else
		{
			std::cout << " 흑돌이 승리하였습니다.\n ";
			return true;
		}
		m_nOdeloType = BLACK;
	}
	return -1;
}


//void COdeloBattleSytem::CopyPan(int out[8][8])
//{
//	for (int i = 0; i < 8; ++i)
//	{
//		for (int j = 0; j < 8; ++j)
//		{
//			out[i][j] = m_nOdeloPan[i][j];
//		}
//	}
//}

//--------- 경기 결과 출력---------
void COdeloBattleSytem::Result()
//---------------------------------
{

	std::cout<<"The End"<<std::endl;
}

//--------- 게임판 그리기 --------
void COdeloBattleSytem::Draw()
//--------------------------------
{
	system("cls");
	for( int y = 0; y < g_nMax; y++)
	{
		for( int x = 0; x < g_nMax; x++)
		{
			
			if( m_nOdeloPan[ y ][ x ] == PAN )
			{
				if( x == 0 && y == 0 )
					std::cout<< "┌ ";
				else if( x == 7 && y == 7 )
					std::cout<< "┘";
				else if( x == 7 && y == 0  )
					std::cout<< "┐";
				else if( x == 0	 && y == 7 )
					std::cout<< "└ ";
				else if( y == 0 )
					std::cout<< "┬ ";
				else if( y == 7 )
					std::cout<< "┴ ";
				else if( x == 0 )
					std::cout<< "├ ";
				else if( x == 7 )
					std::cout<< "┤";
				else
					std::cout<< "┼ ";
			}
			else if( m_nOdeloPan[ y ][ x ] == BLACK )
				std::cout<< "○"; 
			else if( m_nOdeloPan[ y ][ x ] == WHITE )
				std::cout<< "●";
		}
		std::cout<< "\n";
	}
	
	printf("%s Attack  수행시간 : %.5f초\n", m_nOdeloType == BLACK ? "○흑돌" : "●백돌", m_fAttackExcuteTime );
	printf("%s Defence 수행시간 : %.5f초\n", m_nOdeloType == BLACK ? "●백돌" : "○흑돌", m_fDefenceExcuteTime );

	std::cout<< "○흑돌 턴수 : " << m_nBlack << "  ●백돌 턴수 : " << m_nWhite << std::endl;
	/*if (IsPutStone(m_nOdeloType))
		std::cout << "둘 곳 있음\n";
	else
		std::cout << "둘 곳 없음\n";*/

}

//--------- 승리 여부 판단 ----------
int COdeloBattleSytem::CheckWin(int CheckCount, int type)
//-----------------------------------
{
	int m_WhiteStoneCount = 0;
	int m_BlackStoneCount = 0;

	for(int i=0; i<g_nMax; i++)
	{
		for(int j=0; j<g_nMax; j++)
		{
			if(m_nOdeloPan[i][j] == WHITE)
				m_WhiteStoneCount++;
			else
				m_BlackStoneCount++;
		}
	}

	if(CheckCount > 0 && CheckCount < g_nMax * g_nMax - 4)
	{
		
		if(type == WHITE && m_BlackStoneCount == 0)
		{
			return WHITEWIN;
		}
		else if(type == BLACK && m_WhiteStoneCount == 0)
		{
			return BLACKWIN;
		}
		else return NOWIN;
	}

	else
	{
		if(m_WhiteStoneCount > m_BlackStoneCount)
		{
			std::cout<<m_WhiteStoneCount<<" "<<m_BlackStoneCount<<std::endl;
			return WHITEWIN;
		}
		else if(m_BlackStoneCount > m_WhiteStoneCount)
		{
			std::cout<<m_WhiteStoneCount<<" "<<m_BlackStoneCount<<std::endl;
			return BLACKWIN;
		}
		else
			return DROW;
	}

}

/*
//--------- 순서 변경( 흑, 백 ) -----
void COdeloBattleSytem::ChangeType()
//-----------------------------------
{



}
*/

//--------- 순서 변경( 흑, 백 ) -----
bool COdeloBattleSytem::PutStone(int x, int y, int type )
//-----------------------------------
{
	if( m_nOdeloPan[ y ][ x ] == PAN )
	{
	
		if( type == BLACK )
		{
			if(CheckStone(x,y,type))
			{
				m_nOdeloPan[ y ][ x ] = BLACK;
				++m_Count;
				ReverseStone(x, y, type);
				Draw();
				++m_nBlack;
				switch( CheckWin( m_Count, BLACK ) )
				{
				case BLACKWIN:
					std::cout << " 흑돌이 승리하였습니다.\n ";
					return true;
					break;

				case WHITEWIN:
					std::cout << " 백돌이 승리하였습니다.\n ";
					return true;
					break;

				case DROW:
					std::cout << " 무승부입니다.\n ";
					return true;
					break;
				}
			}

			else
			{
				std::cout << " 백돌이 승리하였습니다.\n ";
				return true;
			}

			m_nOdeloType = WHITE;
		}
		
		else
		{
			if(CheckStone(x,y,type))
			{
				m_nOdeloPan[ y ][ x ] = WHITE;
				++m_Count;
				ReverseStone(x, y, type);
				Draw();
				++m_nWhite;
				switch( CheckWin( m_Count, WHITE ) )
				{
				case BLACKWIN:
					std::cout << " 흑돌이 승리하였습니다.\n ";
					return true;
					break;

				case WHITEWIN:
					std::cout << " 백돌이 승리하였습니다.\n ";
					return true;
					break;

				case DROW:
					std::cout << " 무승부입니다.\n ";
					return true;
					break;
				}
			}

			else
			{
				std::cout << " 흑돌이 승리하였습니다.\n ";
				return true;
			}
			m_nOdeloType = BLACK;

		}
	}

	return false;
}


void COdeloBattleSytem::ReverseStone(int x, int y, int type)
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
			
			if( m_nOdeloPan[ dy ][ dx ] == type ) //○○● , ○○  같은 돌인 경우
			{
				if(!(dx == x + g_Directiontable[ j ][ 0 ] && dy == y + g_Directiontable[ j ][ 1 ]))
				{
					dx = x + g_Directiontable[ j ][ 0 ];
					dy = y + g_Directiontable[ j ][ 1 ];
					for(int i=0; i<count; i++)
					{
						if(m_nOdeloPan[dy][dx] == BLACK)
							m_nOdeloPan[dy][dx] = WHITE;
						else if(m_nOdeloPan[dy][dx] == WHITE)
							m_nOdeloPan[dy][dx] = BLACK;

						dx = dx + g_Directiontable[ j ][ 0 ];
						dy = dy + g_Directiontable[ j ][ 1 ];
					}
					break;

				}
				else break;
			}
			
			else if( m_nOdeloPan[ dy ][ dx ] == PAN)  
				break;
		
			else if( ( m_nOdeloPan[ dy ][ dx ] != PAN ) && ( m_nOdeloPan[ dy ][ dx ] != type ) )
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
			
			if( m_nOdeloPan[ _dy ][ _dx ] == type ) //○○● , ○○  같은 돌인 경우
			{
				if(!(_dx == x + g_Directiontable[ j ][ 0 ] && _dy == y + g_Directiontable[ j ][ 1 ]))
				{
					_dx = x + g_Directiontable[ j + 4 ][ 0 ];
					_dy = y + g_Directiontable[ j + 4 ][ 1 ];
					for(int i=0; i<count; i++)
					{
						if(m_nOdeloPan[_dy][_dx] == BLACK)
							m_nOdeloPan[_dy][_dx] = WHITE;
						else if(m_nOdeloPan[_dy][_dx] == WHITE)
							m_nOdeloPan[_dy][_dx] = BLACK;

						_dx = _dx + g_Directiontable[ j + 4 ][ 0 ];
						_dy = _dy + g_Directiontable[ j + 4 ][ 1 ];
					}
					break;

				}
				else break;
			}
			
			else if( m_nOdeloPan[ _dy ][ _dx ] == PAN)  
				break;
		
			else if( ( m_nOdeloPan[ _dy ][ _dx ] != PAN ) && ( m_nOdeloPan[ _dy ][ _dx ] != type ) )
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



bool COdeloBattleSytem::CheckStone(int x, int y, int type)
{
	int CheckPutStone = 0;
	bool Check_State = false;
	int type_opposite;
	int dx, dy;

	if(type == WHITE)
		type_opposite = BLACK;
	else if(type == BLACK)
		type_opposite = WHITE;

	if(m_nOdeloPan[y][x] != PAN)
		return false;

	else
	{
		for(int i=0; i<8; i++)
		{
			dx = x + g_Directiontable[i][0];
			dy = y + g_Directiontable[i][1];
			if(m_nOdeloPan[dy][dx] == PAN)
				Check_State = Check_State;

			else if(m_nOdeloPan[dy][dx] == type)
				Check_State = Check_State;

			else if(m_nOdeloPan[dy][dx] == type_opposite)
			{
				while(dy>=0 && dy<=7 && dx>=0 && dx<=7)
				{
					dx = dx + g_Directiontable[i][0];
					dy = dy + g_Directiontable[i][1];

					if(m_nOdeloPan[dy][dx] == type)
					{
						Check_State = true;
						break;
					}
					else if(m_nOdeloPan[dy][dx] == type_opposite)
					{
						continue;
					}
					else if(m_nOdeloPan[dy][dx] == PAN)
					{
						Check_State = Check_State;
					}
				}
			}
	
		}
		if(Check_State == false)
			return false;
	
		else return true;
	}
}


int** COdeloBattleSytem::Get_OdeloPan()
{
	int** OdeloPan;
	OdeloPan = new int*[g_nMax];
	for(int i=0; i<g_nMax; i++)
	{
		OdeloPan[i] = new int[g_nMax];
	}
	for(int i=0; i<g_nMax; i++)
	{
		for(int j=0; j<g_nMax; j++)
		{
			OdeloPan[i][j] = m_nOdeloPan[i][j];
		}
	}
	return OdeloPan;
}