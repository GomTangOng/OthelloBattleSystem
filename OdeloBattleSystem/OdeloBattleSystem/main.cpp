#include "OdeloBattleSystem.h"
//---- �̰��� Header File�� Include �ϼ��� ----
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

	
	//------------ �̰��� �ڽ��� �Լ��� ��������.-------------------------
	//
	// �տ� 2���� �浹�� �� Attack, Defnece �Լ��̸� 
	// �ڿ� 2���� �鵹�� �� Attack, Defence �Լ��̸��� �����ø� �˴ϴ�.
	//
	//--------------------------------------------------------------------

	OdeloGame.SetYourFunc( 
		/*�浹Attack*/ BlackAttack_2012181008_eunjae, /*�浹Defence*/BlackDefence_2012181008_eunjae, 
		/*�鵹Attack*/ WhiteAttack_2012181008_eunjae, /*�鵹Defence*/WhiteDefence_2012181008_eunjae );

	if( OdeloGame.BeginGame() )
		OdeloGame.Result();

	return 0;
}