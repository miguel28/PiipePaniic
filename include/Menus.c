void Intro()
{
	ASND_SetVoice(1, VOICE_MONO_8BIT, 32000, 0, (void *)jaak_raw, jaak_raw_size, 1500, 1500, NULL);
	Esperar(3 , &intro);
	//ReadFAT();
	Esperar(3 , &splash);
	DrawTitle();
	MenuIndex=7;
}
void DrawTitle(){
	if(ChangeAlpha)MenuAlpha-=3;
	else MenuAlpha+=3;

	if(MenuAlpha>=250)ChangeAlpha=true;
	if(MenuAlpha<=32)ChangeAlpha=false;

	Press.alpha=MenuAlpha;

	ML_DrawBackground(&title);
	ML_DrawSprite(&Press);

	if(Wiimote[0].Newpress.A||
	Wiimote[0].Newpress.B||
	Wiimote[0].Newpress.Plus||
	Wiimote[0].Newpress.Minus||
	Wiimote[0].Newpress.Home||
	Wiimote[0].Newpress.One||
	Wiimote[0].Newpress.Two||
	Wiimote[0].Newpress.Up||
	Wiimote[0].Newpress.Down||
	Wiimote[0].Newpress.Left||
	Wiimote[0].Newpress.Right){
		MenuIndex=1;
		ReadFAT();
		ML_Refresh();
		//break;
	}
}
void SelectMenu()
{
	ML_DrawBackground(&background);
	ML_DrawSprite(&arrow1);
	ML_DrawSprite(&arrow2);
	ML_DrawSprite(&selbutton1);
	ML_DrawSprite(&selbutton2);
	ML_DrawSprite(&upperbar);
	ML_DrawSpriteText(&font, 15, 15, " Level: %02d", LevelNum); 
	ML_Cursor(&pointer,0);

	if(ML_IsWiimoteInSprite(0, &arrow1))
	{
		ML_SetSpriteScale(&arrow1, 1.2f, 1.2f);
		if(Wiimote[0].Newpress.A)
		{
			if(LevelNum>1)LevelNum--;
		}
	}
	else ML_SetSpriteScale(&arrow1, 1.0f, 1.0f);

	if(ML_IsWiimoteInSprite(0, &arrow2))
	{
		ML_SetSpriteScale(&arrow2, 1.2f, 1.2f);
		if(Wiimote[0].Newpress.A)
		{
			if(LevelNum<MAXLEVELS)LevelNum++;
		}
	}
	else ML_SetSpriteScale(&arrow2, 1.0f, 1.0f);
	
	if(ML_IsWiimoteInSprite(0, &selbutton1))
	{
		ML_SetSpriteScale(&selbutton1, 1.2f, 1.2f);
		if(Wiimote[0].Newpress.A)
		{
			MenuIndex=1;
		}
	}
	else ML_SetSpriteScale(&selbutton1, 1.0f, 1.0f);

	if(ML_IsWiimoteInSprite(0, &selbutton2))
	{
		ML_SetSpriteScale(&selbutton2, 1.2f, 1.2f);
		if(Wiimote[0].Newpress.A)
		{
			MenuIndex=2;
			ReInit();
			DrawLevel(LevelNum);
		}
	}
	else ML_SetSpriteScale(&selbutton2, 1.0f, 1.0f);


}

void MainMenu()
{
	int i;
	ML_DrawBackground(&background);
	for(i=0; i<4; i++)
	{
		ML_DrawSprite(&menubtns[i]);
	}

	ML_Cursor(&pointer,0);

	if(ML_IsWiimoteInSprite(0, &menubtns[0]))
	{
		if(Anim4ID!=0)
		{
			Anim4ID=0;
			Anim4Frame=0;
		}
		Anim4Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			MenuIndex=2;
			LevelNum=1;
			ReInit();
			DrawLevel(1);
		}
	}
	if(ML_IsWiimoteInSprite(0, &menubtns[1]))
	{
		if(Anim4ID!=1)
		{
			Anim4ID=1;
			Anim4Frame=0;
		}
		Anim4Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			MenuIndex=3;
			//DrawLevel(1);
		}
	}
	if(ML_IsWiimoteInSprite(0, &menubtns[2]))
	{
		if(Anim4ID!=2)
		{
			Anim4ID=2;
			Anim4Frame=0;
		}
		Anim4Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			MenuIndex=4;
			//DrawLevel(1);
		}
	}
	if(ML_IsWiimoteInSprite(0, &menubtns[3]))
	{
		if(Anim4ID!=3)
		{
			Anim4ID=3;
			Anim4Frame=0;
		}
		Anim4Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			MenuIndex=6;
			//DrawLevel(1);
		}
	}
	if(!ML_IsWiimoteInSprite(0, &menubtns[0])&&!ML_IsWiimoteInSprite(0, &menubtns[1])&&!ML_IsWiimoteInSprite(0, &menubtns[2])&&!ML_IsWiimoteInSprite(0, &menubtns[3]))
	{
		Anim4ID=-1;
		for(i=0; i<4; i++)menubtns[i].angle=0;
	}
	Anim4();
}

void Anim4()
{
	if(Anim4ID>=0)
	{
		if(Anim4Frame<15)
		{
			menubtns[Anim4ID].angle+=.2;
		}
		else if(Anim4Frame>=15&&Anim4Frame<45)
		{
			menubtns[Anim4ID].angle-=.2;
		}
		else if(Anim4Frame>=45&&Anim4Frame<60)
		{
			menubtns[Anim4ID].angle+=.2;
		}

		if(Anim4Frame==60)
		{
			Anim4Frame=0;
			menubtns[Anim4ID].angle=0;
		}
	}
}

void InGame(){
	ML_DrawBackground(&background);
	ML_DrawBackground(&grid);
	ML_DrawSprite(&upperbar);
	ML_DrawSprite(&metal1);
	ML_DrawSprite(&metal2);
	ML_DrawSprite(&button);

	DrawWaterBlocks();
	if(!Pause)PlayAnims();
	if(!Pause && !Lose && !Win)CheckDragBlock();
	if(!Pause && !Lose && !Win)DropBlock();
	DrawBlocks();
	if(!Pause)TimeFuntion();

	if(Wiimote[0].Newpress.B && !PlayAnim2 && !Pause && !Lose && !Win && GetGridUsing(pointer.x>>5, pointer.y>>5))DeleteFromGrid(pointer.x>>5, pointer.y>>5);
	//water.x=(32*WaterX)+((u8)WaterXX); water.y=(32*WaterY)+((u8)WaterYY);
	water.x=(32*WaterX)+WaterXX; water.y=(32*WaterY)+WaterYY;
	if(PlayAnim2)ML_DrawSprite(&minus);

	if(ML_IsWiimoteInSprite(0, &button) && !Pause && !Lose && !Win)
	{
		button.currentFrame = 1;
		if(Wiimote[0].Newpress.A && !Drag)
		{
			TimeCounter=0;
			Time=0;
			button.currentFrame = 2;
			WaterStep=4; Delay =8;
		}
		/*if(Wiimote[0].Held.A && Time==0)
		{
			DelayCounter++;
			button.currentFrame = 2;
		}*/
	}
	else
	{
		button.currentFrame = 0;
	}


	ML_DrawSpriteText(&font, 15, 15, " Level: %02d      Time: %d", LevelNum,Time); 
	ML_DrawSpriteText(&font, 15, 30, " Remaining Blocks: %d  Score: %08d", 100-BlockCounter+BlockNum,GlobalScore);
	
	if(Wiimote[0].Newpress.Plus && !Drag && !Lose && !Win)
	{
		if(Pause)Pause=false;
		else Pause=true;
	}
	

	if(Pause)
	{
		if(Wiimote[0].Newpress.Minus)
		{
			MenuIndex=1;
		}
		if(Wiimote[0].Newpress.One)
		{
			
			if(!PlayingFat)
			{
				ReInit();
				DrawLevel(LevelNum);
			}
			else 
			{
				ReInit();
				if(FatSlot[CurrentSlot].Created)PlayCreate(CurrentSlot);
				else MenuIndex=1;
			}
		}
		ML_DrawBackground(&Black);
	}

	if(Anim3Stop)
	{
		if(Wiimote[0].Newpress.Minus)
		{
			MenuIndex=1;
		}
		if(Wiimote[0].Newpress.A)
		{
			
			if(!PlayingFat)
			{
				ReInit();
				DrawLevel(LevelNum);
			}
			else
			{
				ReInit();
				if(FatSlot[CurrentSlot].Created)PlayCreate(CurrentSlot);
				else MenuIndex=1;
			}
		}
		ML_DrawBackground(&youlose);
	}
	if(Win)
	{
		if(!PlayingFat)
		{

			if(Wiimote[0].Newpress.Minus)
			{
				MenuIndex=1;
			}
			if(Wiimote[0].Newpress.A)
			{
				LevelNum++;
				ReInit();
				DrawLevel(LevelNum);
			}
			if(Wiimote[0].Newpress.B)
			{
				ReInit();
				DrawLevel(LevelNum);
			}
			ML_DrawBackground(&youwin);
		}
		else
		{
			MenuIndex = 1;
		}
	}
}

void SelectSlot()
{
	int i;
	ML_DrawBackground(&background);
	ML_DrawSpriteText(&font1, 50, 15, "    Select Slot"); 
	

	for(i=0; i<8; i++)
	{
		ML_DrawSprite(&fatbtns[i]);
	}

	ML_DrawSpriteText(&font1, 124, 94, " Slot 1"); 
	ML_DrawSpriteText(&font1, 124, 200, " Slot 2"); 
	ML_DrawSpriteText(&font1, 124, 310, " Slot 3"); 
	ML_DrawSpriteText(&font1, 124, 420, " Slot 4"); 
	ML_DrawSpriteText(&font1, 406, 94, " Slot 5"); 
	ML_DrawSpriteText(&font1, 406, 200, " Slot 6"); 
	ML_DrawSpriteText(&font1, 406, 310, " Slot 7"); 
	ML_DrawSpriteText(&font1, 406, 420, " Slot 8"); 

	ML_Cursor(&pointer,0);
	if(Wiimote[0].Newpress.Minus)
	{
		MenuIndex=1;
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[0]))
	{
		if(Anim5ID!=0)
		{
			Anim5ID=0;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			InitCreate(0);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[1]))
	{
		if(Anim5ID!=1)
		{
			Anim5ID=1;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			InitCreate(1);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[2]))
	{
		if(Anim5ID!=2)
		{
			Anim5ID=2;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			InitCreate(2);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[3]))
	{
		if(Anim5ID!=3)
		{
			Anim5ID=3;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			InitCreate(3);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[4]))
	{
		if(Anim5ID!=4)
		{
			Anim5ID=4;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			InitCreate(4);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[5]))
	{
		if(Anim5ID!=5)
		{
			Anim5ID=5;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			InitCreate(5);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[6]))
	{
		if(Anim5ID!=6)
		{
			Anim5ID=6;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			InitCreate(6);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[7]))
	{
		if(Anim5ID!=7)
		{
			Anim5ID=7;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			InitCreate(7);
		}
	}
	if(!ML_IsWiimoteInSprite(0, &fatbtns[0])&&!ML_IsWiimoteInSprite(0, &fatbtns[1])&&!ML_IsWiimoteInSprite(0, &fatbtns[2])&&!ML_IsWiimoteInSprite(0, &fatbtns[3])&&!ML_IsWiimoteInSprite(0, &fatbtns[4])&&!ML_IsWiimoteInSprite(0, &fatbtns[5])&&!ML_IsWiimoteInSprite(0, &fatbtns[6])&&!ML_IsWiimoteInSprite(0, &fatbtns[7]))
	{
		Anim5ID=-1;
		for(i=0; i<8; i++)fatbtns[i].angle=0;
	}
	Anim5();

}

void Anim5()
{
	if(Anim5ID>=0)
	{
		if(Anim5Frame<15)
		{
			fatbtns[Anim5ID].angle+=.2;
		}
		else if(Anim5Frame>=15&&Anim5Frame<45)
		{
			fatbtns[Anim5ID].angle-=.2;
		}
		else if(Anim5Frame>=45&&Anim5Frame<60)
		{
			fatbtns[Anim5ID].angle+=.2;
		}

		if(Anim5Frame==60)
		{
			Anim5Frame=0;
			fatbtns[Anim5ID].angle=0;
		}
	}
}

void CreatingMenu()
{
	ML_DrawBackground(&background);
	ML_DrawBackground(&grid);
	ML_DrawSprite(&upperbar);
	ML_DrawSprite(&metal1);
	ML_DrawSprite(&metal2);

	//DrawWaterBlocks();
	DrawBlocks();
	if(SlotStep==0)
	{
		SetStart();
		ML_DrawSpriteText(&font, 15, 10, " Press A to Set Start "); 
		ML_DrawSpriteText(&font, 15, 40, " Press Select to exit");
	}
	else if(SlotStep==1)
	{
		SetFinish();
		ML_DrawSpriteText(&font, 15, 10, " Press A to Set Finish "); 
		ML_DrawSpriteText(&font, 15, 40, " Press Select to exit");
	}
	else 
	{
		if(BlockCounter<53)DropBlock2();
		if(Wiimote[0].Newpress.Plus)
		{
			FatSlot[CurrentSlot]=TempFatSlot;
			WriteFAT();
			MenuIndex=4;
		}
		ML_DrawSpriteText(&font, 15, 10, " Press A to Set Blocks");
		ML_DrawSpriteText(&font, 15, 20, " Remaining Blocks: %d", 52-BlockCounter);
		ML_DrawSpriteText(&font, 15, 40, " Press Start to Save");
	}
	
	ML_DrawSpriteText(&font, 350, 7, "        /\\ ");
	ML_DrawSpriteText(&font, 350, 15, " Time: %d ", TempFatSlot.Time);
	ML_DrawSpriteText(&font, 350, 22, "        \\/ ");
	
	ML_DrawSpriteText(&font, 350, 40, "Speed :< %s  > ", SpeedNames[TempFatSlot.Speed]);

	if(Wiimote[0].Newpress.Down && TempFatSlot.Time>40)TempFatSlot.Time--;
	if(Wiimote[0].Newpress.Up && TempFatSlot.Time<600)TempFatSlot.Time++;

	if(Wiimote[0].Newpress.Left && TempFatSlot.Speed>0)TempFatSlot.Speed--;
	if(Wiimote[0].Newpress.Right && TempFatSlot.Speed<4)TempFatSlot.Speed++;

	if(Wiimote[0].Newpress.Minus)
	{
		MenuIndex=4;
	}
	ML_Cursor(&pointer,0);
}

void SelectSlot2()
{
	int i;
	ML_DrawBackground(&background);
	ML_DrawSpriteText(&font1, 50, 15, "    Select Slot"); 
	

	for(i=0; i<8; i++)
	{
		ML_DrawSprite(&fatbtns[i]);
	}

	ML_DrawSpriteText(&font1, 124, 94, " Slot 1"); 
	ML_DrawSpriteText(&font1, 124, 200, " Slot 2"); 
	ML_DrawSpriteText(&font1, 124, 310, " Slot 3"); 
	ML_DrawSpriteText(&font1, 124, 420, " Slot 4"); 
	ML_DrawSpriteText(&font1, 406, 94, " Slot 5"); 
	ML_DrawSpriteText(&font1, 406, 200, " Slot 6"); 
	ML_DrawSpriteText(&font1, 406, 310, " Slot 7"); 
	ML_DrawSpriteText(&font1, 406, 420, " Slot 8"); 

	ML_Cursor(&pointer,0);
	if(Wiimote[0].Newpress.Minus)
	{
		MenuIndex=1;
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[0]))
	{
		if(Anim5ID!=0)
		{
			Anim5ID=0;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			ReInit();
			if(FatSlot[0].Created)PlayCreate(0);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[1]))
	{
		if(Anim5ID!=1)
		{
			Anim5ID=1;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			ReInit();
			if(FatSlot[1].Created)PlayCreate(1);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[2]))
	{
		if(Anim5ID!=2)
		{
			Anim5ID=2;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			ReInit();
			if(FatSlot[2].Created)PlayCreate(2);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[3]))
	{
		if(Anim5ID!=3)
		{
			Anim5ID=3;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			ReInit();
			if(FatSlot[3].Created)PlayCreate(3);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[4]))
	{
		if(Anim5ID!=4)
		{
			Anim5ID=4;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			ReInit();
			if(FatSlot[5].Created)PlayCreate(5);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[5]))
	{
		if(Anim5ID!=5)
		{
			Anim5ID=5;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			ReInit();
			if(FatSlot[5].Created)PlayCreate(5);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[6]))
	{
		if(Anim5ID!=6)
		{
			Anim5ID=6;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			ReInit();
			if(FatSlot[6].Created)PlayCreate(6);
		}
	}
	if(ML_IsWiimoteInSprite(0, &fatbtns[7]))
	{
		if(Anim5ID!=7)
		{
			Anim5ID=7;
			Anim5Frame=0;
		}
		Anim5Frame++;
		if(Wiimote[0].Newpress.A)
		{	
			ReInit();
			if(FatSlot[7].Created)PlayCreate(7);
		}
	}
	if(!ML_IsWiimoteInSprite(0, &fatbtns[0])&&!ML_IsWiimoteInSprite(0, &fatbtns[1])&&!ML_IsWiimoteInSprite(0, &fatbtns[2])&&!ML_IsWiimoteInSprite(0, &fatbtns[3])&&!ML_IsWiimoteInSprite(0, &fatbtns[4])&&!ML_IsWiimoteInSprite(0, &fatbtns[5])&&!ML_IsWiimoteInSprite(0, &fatbtns[6])&&!ML_IsWiimoteInSprite(0, &fatbtns[7]))
	{
		Anim5ID=-1;
		for(i=0; i<8; i++)fatbtns[i].angle=0;
	}
	Anim5();

}