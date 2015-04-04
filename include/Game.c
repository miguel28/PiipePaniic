void Esperar(s32 s,ML_Background *Background){
   int i;
	for (i = 0; i < s * 58; i++){
		ML_DrawBackground(Background);
		ML_Refresh();
	}
}

void ExitForTheGame(){

	if(Wiimote[0].Held.Home) { 
		ML_DeleteImage(&pointerData); 
		ML_DeleteImage(&backgroundData); 
		ML_Exit(); 
	}

}
void Play_Music(void){
	if (!ML_IsPlayingMP3()) { 
		ML_PlayMP3FromBuffer(music_mp3, music_mp3_size); 
	}
}

void CheckDragBlock(void)
{
	int i;
	for(i=0; i<MAXNUMBLOCKS; i++)
	{
		if(Wiimote[0].Newpress.A && ML_IsWiimoteInSprite (0, &block[i]) && !PlacedBlock[i] && !Drag &&!PlayAnim1 &&  i == BlockCounter)
		{
			Drag = true;
			ASND_SetVoice(1, VOICE_MONO_8BIT, 32000, 0, (void *)Drag_snd_raw, Drag_snd_raw_size, 1500, 1500, NULL);
			IdDrag = i;
		}
	}
}
void DropBlock(void)
{
	if(!Wiimote[0].Held.A&&Drag)
	{
		Drag = false;
		ASND_SetVoice(1, VOICE_MONO_8BIT, 32000, 0, (void *)Drop_snd_raw, Drop_snd_raw_size, 1500, 1500, NULL);
		if(PlaceToGrid()==0)
		{
			PlacedBlock[IdDrag]=true;
			BlockCounter++;
			PlayAnim1=true;
			Anim1Frame=0;
		}
		else
		{
			block[IdDrag].x=16;
			block[IdDrag].y=432;
		}

	}
}
u8 PlaceToGrid(void)
{
	int Div1, Div2, Dif1,Dif2;

	///For X///
	Div1=block[IdDrag].x/32;
	Div2=Div1*32;
	Dif1=block[IdDrag].x-Div2;
	
	if(Dif1<=16)block[IdDrag].x=Div2;
	else block[IdDrag].x=(Div2+32);

	///For Y///
	Div1=block[IdDrag].y/32;
	Div2=Div1*32;
	Dif2=block[IdDrag].y-Div2;
	
	if(Dif2<=16)block[IdDrag].y=Div2;
	else block[IdDrag].y=(Div2+32);
	
	/// Check Space ///
	if(GetGridUsing((u8)(block[IdDrag].x>>5), (u8)(block[IdDrag].y>>5)))return 1;

	
	/// Check Angle ///
	//u8 Rot=0;
	int Angle;
	Angle=(int)block[IdDrag].angle;
	if(Angle>=-45 && Angle <45){ block[IdDrag].angle=0; Rot=D0; }
	if(Angle>=45 && Angle <135){ block[IdDrag].angle=90; Rot=D90; }
	if(Angle>=135 && Angle <225){ block[IdDrag].angle=180; Rot=D180; }
	if(Angle>=225 && Angle <315){ block[IdDrag].angle=270; Rot=D270; }
	if(Angle>=315 && Angle <405){ block[IdDrag].angle=0; Rot=D0; }
	if(Angle>=-135 && Angle <-45){ block[IdDrag].angle=-90; Rot=D270; }
	if(Angle>=-225 && Angle <-135){ block[IdDrag].angle=-180; Rot=D180; }
	if(Angle>=-315 && Angle <-225){ block[IdDrag].angle=-270; Rot=D90; }
	if(Angle>=-405 && Angle <-315){ block[IdDrag].angle=-360; Rot=D0; }

	SetGrid((u8)(block[IdDrag].x>>5), (u8)(block[IdDrag].y>>5), block[IdDrag].currentFrame, Rot, IdDrag);
	return 0;
}

void SetGrid(u8 x, u8 y, u8 type, u8 rot, u8 id)
{
	BlockGrid[(y*GRIDWIDTH)+x].Type=type;
	BlockGrid[(y*GRIDWIDTH)+x].Rotation=rot;
	BlockGrid[(y*GRIDWIDTH)+x].Using=1;
	BlockGrid[(y*GRIDWIDTH)+x].ID=id;
	waterD[id].x=x*32; waterD[id].y=y*32;
}

void SetGridWatered(u8 x, u8 y)
{
	BlockGrid[(y*GRIDWIDTH)+x].Watered=1;
}

u8 GetGridUsing(u8 x, u8 y)
{
	return BlockGrid[(y*GRIDWIDTH)+x].Using;
}
u8 GetGridType(u8 x, u8 y)
{
	return BlockGrid[(y*GRIDWIDTH)+x].Type;
}
u8 GetGridRot(u8 x, u8 y)
{
	return BlockGrid[(y*GRIDWIDTH)+x].Rotation;
}
u8 GetGridID(u8 x, u8 y)
{
	return BlockGrid[(y*GRIDWIDTH)+x].ID;
} 
u8 GetGridWatered(u8 x, u8 y)
{
	return BlockGrid[(y*GRIDWIDTH)+x].Watered;
}
void DeleteFromGrid(u8 x, u8 y)
{
	Anim2ID=BlockGrid[(y*GRIDWIDTH)+x].ID;
	if(Anim2ID>=BlockNum && !GetGridWatered(x,y))
	{
		waterD[Anim2ID].x=-32;
		BlockGrid[(y*GRIDWIDTH)+x].Type=0;
		BlockGrid[(y*GRIDWIDTH)+x].Rotation=0;
		BlockGrid[(y*GRIDWIDTH)+x].Using=0;
		Anim2Frame=0;
		PlayAnim2=true;
		BlockGrid[(y*GRIDWIDTH)+x].ID=-1;
	}
}
void DrawBlocks(void)
{
	int i;
	if(Drag)
	{
		ML_Cursor(&pointer2,0);
		for(i=0; i<MAXNUMBLOCKS; i++)
		{
			if(IdDrag!=i)ML_DrawSprite(&block[i]);
			
		}
		MK_Cursor(IdDrag);
		ML_DrawSprite(&metal3);
		ML_Cursor(&pointer2,0);	
	}
	else
	{
		for(i=0; i<MAXNUMBLOCKS; i++)
		{
			ML_DrawSprite(&block[i]);			
		}
		ML_DrawSprite(&metal3);
		ML_Cursor(&pointer,0);
	}
}

void DrawWaterBlocks(){
	int i;
	for(i=0; i<MAXNUMBLOCKS; i++)
	{
		ML_DrawSprite(&waterD[i]);	
	}	
	if(!Lose)ML_DrawSprite(&water); 	
}

void MK_Cursor(u8 Id)
{
	block[Id].angle=pointer2.angle;
	block[Id].x=pointer2.x-16;
	block[Id].y=pointer2.y-16;

	if(block[Id].x<64)block[Id].x=64;
	if(block[Id].y<64)block[Id].y=64;
	if(block[Id].x>640)block[Id].x=608;
	if(block[Id].y>480)block[Id].y=448;
	ML_DrawSprite(&block[Id]);
}

void PlayAnims()
{
	if(Drag)
	{
		minus.x=pointer2.x-48;
		minus.y=pointer2.y-16;
	}
	else
	{
		minus.x=pointer.x-48;
		minus.y=pointer.y-16;
	}
	if(PlayAnim1&&(BlockCounter-BlockNum)<=100)
	{
		if(Anim1Frame==0)
		{
			block[BlockCounter].x=16;
			block[BlockCounter].y=304;
			block[BlockCounter+7].x=16;
			block[BlockCounter+7].y=80;
		}
		block[BlockCounter].y+=6;
		block[BlockCounter+1].y+=2;
		block[BlockCounter+2].y+=2;
		block[BlockCounter+3].y+=2;
		block[BlockCounter+4].y+=2;
		block[BlockCounter+5].y+=2;
		block[BlockCounter+6].y+=2;


		if(Anim1Frame>=0 && Anim1Frame<5)block[BlockCounter].angle+=5;
		if(Anim1Frame>=5 && Anim1Frame<15)block[BlockCounter].angle-=5;
		if(Anim1Frame>=15 && Anim1Frame<20)block[BlockCounter].angle+=5;
		if(Anim1Frame==20)PlayAnim1=false;
		Anim1Frame++;
	}
	if(PlayAnim2)
	{
		
		if(Anim2Frame==0)ML_SetSpriteScale(&minus, 0.01f, 0.01f);
		
		block[Anim2ID].angle+=25;
		ML_SetSpriteScale(&block[Anim2ID], 1-(Anim2Frame/30.0f), 1-(Anim2Frame/30.0f));
		if(Anim2Frame==14){
			PlayAnim2=false;
			block[Anim2ID].x=-32;
			ScoreSub(50);
		}
		Anim2Frame++;
		ML_SetSpriteScale(&block[Anim2ID], 1-(Anim2Frame/30.0f), 1-(Anim2Frame/30.0f));
		if(Anim2Frame>0 && Anim2Frame<10)ML_SetSpriteScale(&minus, Anim2Frame/8.0f, Anim2Frame/8.0f);
		
	}
	else ML_SetSpriteScale(&minus, 0.01f, 0.01f);

	if(Lose&& !Anim3Play)
	{
		Anim3Play=true;
		Anim3Frame=0;
	}
	if(Anim3Play)
	{
		Anim3Frame++;
		if(Anim3Frame==5)ASND_SetVoice(1, VOICE_MONO_8BIT, 32000, 0, (void *)water_snd_raw, water_snd_raw_size, 1500, 1500, NULL);
		if(Anim3Frame>=120)
		{
			//Anim3Play=false;
			Anim3Stop=true;
			Anim3Frame--;
		}
		ML_SetSpriteScale(&water2, Anim3Frame/70.0f, Anim3Frame/70.0f);
		
		water2.x=(WaterX*32)-48;
		water2.y=(WaterY*32)-48;
		switch(Direction)
		{
			case UP:
				water2.x+=16;
				break;
			case DOWN:
				water2.x+=16;
				water2.y+=32;
				break;
			case LEFT:
				water2.y+=16;
				break;
			case RIGHT:
				water2.x+=32;
				water2.y+=16;
				break;
		}
		
		
		ML_DrawSprite(&water2);
	}
}

void SubWaterFlux()
{
	if(DelayCounter<Delay)
	{
		switch(Direction)
		{
			case UP:
				WaterYY-=WaterStep;
				break;
			case DOWN:
				WaterYY+=WaterStep;
				break;
			case LEFT:
				WaterXX-=WaterStep;
				break;
			case RIGHT:
				WaterXX+=WaterStep;
				break;
		}
		if(WaterYY>16||WaterYY<16||WaterXX>16||WaterXX<16)
		{
			waterD[GetGridID(WaterX, WaterY)].currentFrame=1;
			SetGridWatered(WaterX, WaterY);
		}
	}
}

void WaterFlux()
{
	u8 TempType, TempRot;
	s8 xx=0,yy=0;
	if(DelayCounter<=1)
	{
		DelayCounter++;
		switch(Direction)
		{
			case UP:
				yy=-1;
				break;
			case DOWN:
				yy=1;
				break;
			case LEFT:
				xx=-1;
				break;
			case RIGHT:
				xx=1;
				break;
		}
		if(GetGridUsing(WaterX+xx, WaterY+yy)==1)
		{
			TempType = GetGridType(WaterX+xx, WaterY+yy);
			TempRot = GetGridRot(WaterX+xx, WaterY+yy);
			if(TempType==10&&Direction==UP)Win=1;
			if(TempType==0)Lose=1;/// Se triro bloque nulo
			if(TempType>=2 && TempType<=4)
			{
				if(Direction==UP||Direction==DOWN){
					if(TempRot==D0||TempRot==D180)
					{
						/// NO pasa nada ///
						ScoreAdd(400);
					}
					else
					{
						/// Se tiro Bloque recto volteado///
						Lose=1;
					}
				}
				else
				{
					if(TempRot==D90||TempRot==D270)
					{
						/// NO pasa nada ///
						ScoreAdd(400);
					}
					else
					{
						/// Se tiro Bloque recto volteado///
						Lose=1;
					}
				}
			}
			if(TempType==5)
			{
				SubDelay=1;
				SubDelayCounter=0;				
				if(Direction==UP||Direction==DOWN){
					if(TempRot==D0||TempRot==D180)
					{
						/// NO pasa nada ///
						ScoreAdd(400);
					}
					else
					{
						/// Se tiro Bloque recto volteado///
						Lose=1;
					}
				}
				else
				{
					if(TempRot==D90||TempRot==D270)
					{
						/// NO pasa nada ///
						ScoreAdd(400);
					}
					else
					{
						/// Se tiro Bloque recto volteado///
						Lose=1;
					}
				}
			}
			else
			{
				SubDelay=0;
			}
			if(TempType==6||TempType==7)
			{
				switch(Direction)
				{
					case UP:
						if(TempRot==D0||TempRot==D270)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D90)
						{
							/// No pasa nada ///
							//Direction=RIGHT;
							ScoreAdd(400);
						}
						else if(TempRot==D180)
						{
							/// No pasa nada ///
							//Direction=LEFT;
							ScoreAdd(400);
						}
						break;
					case DOWN:
						if(TempRot==D90||TempRot==D180)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D270)
						{
							/// No pasa nada ///
							//Direction=LEFT;
							ScoreAdd(400);
						}
						else if(TempRot==D0)
						{
							/// No pasa nada ///
							//Direction=RIGHT;
							ScoreAdd(400);
						}
						break;
					case LEFT:
						if(TempRot==D180||TempRot==D270)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D0)
						{
							/// No pasa nada ///
							//Direction=UP;
							ScoreAdd(400);
						}
						else if(TempRot==D90)
						{
							/// No pasa nada ///
							//Direction=DOWN;
							ScoreAdd(400);
						}
						break;
					case RIGHT:
						if(TempRot==D0||TempRot==D90)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D180)
						{
							/// No pasa nada ///
							//Direction=DOWN;
							ScoreAdd(400);
						}
						else if(TempRot==D270)
						{
							/// No pasa nada ///
							//Direction=UP;
							ScoreAdd(400);
						}
						break;
				}
			}
			if(TempType==8||TempType==9)
			{
				switch(Direction)
				{
					case UP:
						if(TempRot==D0||TempRot==D90)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D180)
						{
							/// No pasa nada ///
							//Direction=RIGHT;
							ScoreAdd(400);
						}
						else if(TempRot==D270)
						{
							/// No pasa nada ///
							//Direction=LEFT;
							ScoreAdd(400);
						}
						break;
					case DOWN:
						if(TempRot==D270||TempRot==D180)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D90)
						{
							/// No pasa nada ///
							//Direction=RIGHT;
							ScoreAdd(400);
						}
						else if(TempRot==D0)
						{
							/// No pasa nada ///
							//Direction=LEFT;
							ScoreAdd(400);
						}
						break;
					case RIGHT:
						if(TempRot==D90||TempRot==D180)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D0)
						{
							/// No pasa nada ///
							//Direction=UP;
							ScoreAdd(400);
						}
						else if(TempRot==D270)
						{
							/// No pasa nada ///
							//Direction=DOWN;
							ScoreAdd(400);
						}
						break;
					case LEFT:
						if(TempRot==D0||TempRot==D270)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D180)
						{
							/// No pasa nada ///
							//Direction=DOWN;
							ScoreAdd(400);
						}
						else if(TempRot==D90)
						{
							/// No pasa nada ///
							//Direction=UP;
							ScoreAdd(400);
						}
						break;
				}
			}
		}
		else
		{
			/// Se Tiro no hay bloque ///
			Lose=1;
		}
	}

	if(SubDelay)
	{
		SubDelayCounter++;
		if(SubDelayCounter>=3){
			DelayCounter++;
			SubDelayCounter=0;
			SubWaterFlux();
		}
	}
	else 
	{
		DelayCounter++;
		SubWaterFlux();
	}
	
	if(DelayCounter>=Delay)
	{
		DelayCounter=0;
		WaterYY=0;
		WaterXX=0;
		waterD[GetGridID(WaterX, WaterY)].currentFrame=1;
		SetGridWatered(WaterX, WaterY);
		switch(Direction)
		{
			case UP:
				WaterY--;
				break;
			case DOWN:
				WaterY++;
				break;
			case LEFT:
				WaterX--;
				break;
			case RIGHT:
				WaterX++;
				break;
		}
		if(GetGridUsing(WaterX, WaterY)==1)
		{
			TempType = GetGridType(WaterX, WaterY);
			TempRot = GetGridRot(WaterX, WaterY);

			if(TempType==0)Lose=1;;/// Se triro bloque nulo
			if(TempType>=2 && TempType<=4)
			{
				if(Direction==UP||Direction==DOWN){
					if(TempRot==D0||TempRot==D180)
					{
						/// NO pasa nada ///
					}
					else
					{
						/// Se tiro Bloque recto volteado///
						Lose=1;
					}
				}
				else
				{
					if(TempRot==D90||TempRot==D270)
					{
						/// NO pasa nada ///
					}
					else
					{
						/// Se tiro Bloque recto volteado///
						Lose=1;
					}
				}
			}
			if(TempType==5)
			{
				if(Direction==UP||Direction==DOWN){
					if(TempRot==D0||TempRot==D180)
					{
						/// NO pasa nada ///
					}
					else
					{
						/// Se tiro Bloque recto volteado///
						Lose=1;
					}
				}
				else
				{
					if(TempRot==D90||TempRot==D270)
					{
						/// NO pasa nada ///
					}
					else
					{
						/// Se tiro Bloque recto volteado///
						Lose=1;
					}
				}
			}

			if(TempType==6||TempType==7)
			{
				switch(Direction)
				{
					case UP:
						if(TempRot==D0||TempRot==D270)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D90)
						{
							/// No pasa nada ///
							Direction=RIGHT;
						}
						else if(TempRot==D180)
						{
							/// No pasa nada ///
							Direction=LEFT;
						}
						break;
					case DOWN:
						if(TempRot==D90||TempRot==D180)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D270)
						{
							/// No pasa nada ///
							Direction=LEFT;
						}
						else if(TempRot==D0)
						{
							/// No pasa nada ///
							Direction=RIGHT;
						}
						break;
					case LEFT:
						if(TempRot==D180||TempRot==D270)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D0)
						{
							/// No pasa nada ///
							Direction=UP;
						}
						else if(TempRot==D90)
						{
							/// No pasa nada ///
							Direction=DOWN;
						}
						break;
					case RIGHT:
						if(TempRot==D0||TempRot==D90)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D180)
						{
							/// No pasa nada ///
							Direction=DOWN;
						}
						else if(TempRot==D270)
						{
							/// No pasa nada ///
							Direction=UP;
						}
						break;
				}
			}
			if(TempType==8||TempType==9)
			{
				switch(Direction)
				{
					case UP:
						if(TempRot==D0||TempRot==D90)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D180)
						{
							/// No pasa nada ///
							Direction=RIGHT;
						}
						else if(TempRot==D270)
						{
							/// No pasa nada ///
							Direction=LEFT;
						}
						break;
					case DOWN:
						if(TempRot==D270||TempRot==D180)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D90)
						{
							/// No pasa nada ///
							Direction=RIGHT;
						}
						else if(TempRot==D0)
						{
							/// No pasa nada ///
							Direction=LEFT;
						}
						break;
					case RIGHT:
						if(TempRot==D90||TempRot==D180)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D0)
						{
							/// No pasa nada ///
							Direction=UP;
						}
						else if(TempRot==D270)
						{
							/// No pasa nada ///
							Direction=DOWN;
						}
						break;
					case LEFT:
						if(TempRot==D0||TempRot==D270)
						{
							/// Se tira lado del codo///
							Lose=1;
						}
						else if(TempRot==D180)
						{
							/// No pasa nada ///
							Direction=DOWN;
						}
						else if(TempRot==D90)
						{
							/// No pasa nada ///
							Direction=UP;
						}
						break;
				}
			}
		}
		else
		{
			/// Se Tiro no hay bloque ///
			Lose=1;
		}
	}
}
void ReInit()
{
	int i;
	for(i=0; i<MAXNUMBLOCKS; i++)
	{
		block[i].currentFrame=ML_Rand(2,8);
		block[i].x=16; block[i].y=-32;
		block[i].angle=0;
		ML_SetSpriteScale(&block[i], 1.0f, 1.0f);
		waterD[i].x=-32; waterD[i].y=0;
		waterD[i].currentFrame=0;
		PlacedBlock[i]=false;
	}
	for(i=0; i<GRIDWIDTH*GRIDHEIGHT; i++)
	{
		BlockGrid[i].Type=0;
		BlockGrid[i].Rotation=0;
		BlockGrid[i].Using=0;
		BlockGrid[i].ID=-1;
		BlockGrid[i].Watered=0;
	}
	for(i=BlockNum; i<BlockNum+7; i++)
	{
		block[i].y=304-32-((i-BlockNum)*32);
	}
	Lose=0;
	DelayCounter=0;
	WaterYY=0;
	WaterXX=0;
	Drag = false;
	BlockCounter=0;
	Anim1Frame=0;
	PlayAnim1=true;

	Anim2Frame=0;
	PlayAnim2=false;
	Anim2ID=0;
	Anim3Play=false;
	Anim3Frame=0;
	Anim3Stop=false;
	Pause=false;

	Time=0;
	Win=0;
	Lose=0;
	TimeCounter=0; 
}

void TimeFuntion()
{
	TimeCounter++;
	if(TimeCounter==59&&Time>0)
	{
		TimeCounter=0;
		Time--;
	}
	if(Time==0 && !Lose && !Win)
	{
		WaterFlux();
	}
	if((Time==5||Time==4||Time==3||Time==2||Time==1) && TimeCounter==28)
		ASND_SetVoice(1, VOICE_MONO_8BIT, 32000, 0, (void *)Clock_raw, Clock_raw_size, 1500, 1500, NULL);
}

void ScoreAdd(u16 score)
{
	GlobalScore+= score;
}
void ScoreSub(u16 score)
{
	GlobalScore-= score;
	if(GlobalScore<=0)GlobalScore=0;
}

void InitCreate(u8 slot)
{
	int i;
	CurrentSlot= slot;

	for(i=0; i<MAXNUMBLOCKS; i++)
	{
		block[i].currentFrame=0;
		block[i].x=16; block[i].y=-32;
		block[i].angle=0;
		ML_SetSpriteScale(&block[i], 1.0f, 1.0f);
		waterD[i].x=-32; waterD[i].y=0;
		waterD[i].currentFrame=0;
		PlacedBlock[i]=false;
	}
	for(i=0; i<GRIDWIDTH*GRIDHEIGHT; i++)
	{
		BlockGrid[i].Type=0;
		BlockGrid[i].Rotation=0;
		BlockGrid[i].Using=0;
		BlockGrid[i].ID=-1;
		BlockGrid[i].Watered=0;
		TempFatSlot.Grid[i]=0;
	}
	/*TempFatSlot.StartX=0;
	TempFatSlot.StartY=0;
	TempFatSlot.StartX=0;
	TempFatSlot.StartY=0;*/
	TempFatSlot.Time=120;
	TempFatSlot.Speed=2;
	TempFatSlot.Created=1;

	block[0].currentFrame=1;
	block[1].currentFrame=10;
	Lose=0;
	DelayCounter=0;
	WaterYY=0;
	WaterXX=0;
	Drag = false;
	BlockCounter=0;
	Anim1Frame=0;
	PlayAnim1=true;

	Time=0;
	Win=0;
	Lose=0;
	TimeCounter=0; 
	SlotStep=0;
	MenuIndex=5;
}

bool Condition()
{
	return (pointer.x<640-32 && pointer.x>32 && pointer.y<480-32 && pointer.y>32);
}

void DropBlock2(void)
{
	if(Wiimote[0].Newpress.A)
	{
		IdDrag=BlockCounter;
		block[IdDrag].x=pointer.x-16;
		block[IdDrag].y=pointer.y-24;

		if(PlaceToGrid()==0 && Condition())
		{
			ASND_SetVoice(1, VOICE_MONO_8BIT, 32000, 0, (void *)Drop_snd_raw, Drop_snd_raw_size, 1500, 1500, NULL);
			PlacedBlock[IdDrag]=true;
			TempFatSlot.Grid[(block[IdDrag].y>>5)*GRIDWIDTH+(block[IdDrag].x>>5)]=1;
			BlockCounter++;
		}
		else
		{
			block[IdDrag].x=0;
			block[IdDrag].y=-32;
		}
	}
}

void SetStart()
{
	if(Wiimote[0].Newpress.A)
	{
		BlockCounter=0;
		IdDrag=BlockCounter;
		block[IdDrag].x=pointer.x-16;
		block[IdDrag].y=pointer.y-24;

		if(PlaceToGrid()==0&&Condition())
		{
			ASND_SetVoice(1, VOICE_MONO_8BIT, 32000, 0, (void *)Drop_snd_raw, Drop_snd_raw_size, 1500, 1500, NULL);
			PlacedBlock[IdDrag]=true;
			TempFatSlot.StartX=block[IdDrag].x>>5;
			TempFatSlot.StartY=block[IdDrag].y>>5;
			
			BlockCounter++;
			SlotStep=1;
		}
		else
		{
			block[IdDrag].x=0;
			block[IdDrag].y=-32;
		}
	}
}
void SetFinish()
{
	if(Wiimote[0].Newpress.A)
	{
		//BlockCounter=0;
		IdDrag=BlockCounter;
		block[IdDrag].x=pointer.x-16;
		block[IdDrag].y=pointer.y-24;

		if(PlaceToGrid()==0&&Condition())
		{
			ASND_SetVoice(1, VOICE_MONO_8BIT, 32000, 0, (void *)Drop_snd_raw, Drop_snd_raw_size, 1500, 1500, NULL);
			PlacedBlock[IdDrag]=true;
			TempFatSlot.FinishX=block[IdDrag].x>>5;
			TempFatSlot.FinishY=block[IdDrag].y>>5;
			BlockCounter++;
			SlotStep=2;
		}
		else
		{
			block[IdDrag].x=0;
			block[IdDrag].y=-32;
		}
	}
	/*if(Wiimote[0].Newpress.B)
	{
		block[0].x=0;
		block[0].y=-32;
		BlockCounter=0;
		SlotStep=0;
	}*/
}

void PlayCreate(u8 slot)
{
	int i;
	PlayingFat=1;
	CurrentSlot= slot;
	Direction=DOWN;
	for(i=0; i<300; i++)
	{
		if(FatSlot[slot].Grid[i])
		{
			u8 tempy = i/GRIDWIDTH;
			u8 tempx = i-(tempy*GRIDWIDTH);
			SetBlock(tempx,tempy);
		}
	}
	switch(FatSlot[slot].Time)
	{
		case 0:
			Delay=80; DelayCounter=0;
			WaterStep=0.4f; 
			break;
		case 1:
			Delay=64; DelayCounter=0;
			WaterStep=0.5f; 
			break;
		case 2:
			Delay=32; DelayCounter=0;
			WaterStep=1.000001f; 
			break;
		case 3:
			Delay=16; DelayCounter=0;
			WaterStep=2.000001f; 
			break;
		case 4:
			Delay=8; DelayCounter=0;
			WaterStep=4.000001f; 
			break;
	}
    
    Time=FatSlot[slot].Time;

	BlockCounter=BlockNum;
	block[0].x=FatSlot[slot].StartX*32; block[0].y=FatSlot[slot].StartY*32; 
	block[0].currentFrame=1; 
	SetGrid(FatSlot[slot].StartX, FatSlot[slot].StartY, 0, 0, 0);
	block[1].x=FatSlot[slot].FinishX*32; block[1].y=FatSlot[slot].FinishY*32; 
	block[1].currentFrame=10;
	SetGrid(FatSlot[slot].FinishX, FatSlot[slot].FinishY, 10, 0, 1);
	WaterX=FatSlot[slot].StartX; WaterY=FatSlot[slot].StartY;


	for(i=BlockNum; i<BlockNum+7; i++)
	{
		block[i].y=304-32-((i-BlockNum)*32);
	}
	MenuIndex=2;
}