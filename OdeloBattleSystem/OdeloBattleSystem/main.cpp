#include "OdeloBattleSystem.h"
//---- 이곳에 Header File을 Include 하세요 ----
// ex)
//#include "BLACK_4444444444.h"	
//#include "WHITE_6666666666.h"
//
#include "Attack_1.h"
#include "Attack_2.h"

//---------------------------------------------

int main()
{
	

	OdeloGame.Init();

	for(int i=0; i<g_nMax; i++)
	{
		for(int j=0; j<g_nMax; j++)
		{
			Black_Attack_Check[g_nMax][g_nMax].check_position = false;
			White_Attack_Check[g_nMax][g_nMax].check_position = false;
		}
	}

	Black_Attack_Check[3][5].check_position = true;
	Black_Attack_Check[3][5].Attack_Point = 1;
	Black_Attack_Check[5][3].check_position = true;
	Black_Attack_Check[5][3].Attack_Point = 1;
	Black_Attack_Check[4][2].check_position = true;
	Black_Attack_Check[4][2].Attack_Point = 1;
	Black_Attack_Check[2][4].check_position = true;
	Black_Attack_Check[2][4].Attack_Point = 1;
	White_Attack_Check[3][2].check_position = true;
	White_Attack_Check[3][2].Attack_Point = 1;
	White_Attack_Check[2][3].check_position = true;
	White_Attack_Check[2][3].Attack_Point = 1;
	White_Attack_Check[5][4].check_position = true;
	White_Attack_Check[5][4].Attack_Point = 1;
	White_Attack_Check[4][5].check_position = true;
	White_Attack_Check[4][5].Attack_Point = 1;
	//------------ 이곳에 자신의 함수를 넣으세요.-------------------------
	//
	// 앞에 2곳은 흑돌을 할 Attack, Defnece 함수이름 
	// 뒤에 2곳은 백돌을 할 Attack, Defence 함수이름을 넣으시면 됩니다.
	//
	//--------------------------------------------------------------------

	OdeloGame.SetYourFunc( 
		/*흑돌Attack*/ BlackAttack_2012181008_eunjae, /*흑돌Defence*/BlackDefence_2012181008_eunjae, 
		/*백돌Attack*/ WhiteAttack_2012181008_eunjae, /*백돌Defence*/WhiteDefence_2012181008_eunjae );

	if( OdeloGame.BeginGame() )
		OdeloGame.Result();

	return 0;
}