#include <MLlib.h>
#include <Math.h>
#include "../include/Game.h"

int main(int argc, char **argv) 
{
	MK_InitLibraries();
	MK_LoadGfx();

	Intro();
	
	while(1)/// Infinite Loop ///
	{
		ExitForTheGame();
		Play_Music();
		switch(MenuIndex)
		{
			case 1: 
				MainMenu();
				break;
			case 2:
				InGame();
				break;
			case 3:
				SelectMenu();
				break;
			case 4:
				SelectSlot();
				break;
			case 5:
				CreatingMenu();
				break;
			case 6:
				SelectSlot2();
				break;
			case 7:
				DrawTitle();
				break;
		}
		ML_Refresh();
	} 
	return 0;
}
