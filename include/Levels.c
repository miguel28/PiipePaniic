void DrawLevel(u8 Level)
{
	if (Level>MAXLEVELS)
	{
		MenuIndex=1;
	}
	switch(Level)
	{
		case 1:
            StartX=4; StartY=10; FinishX=6; FinishY=11;
            BlockNum=2; Direction=DOWN; Delay =80; DelayCounter=0;
            WaterStep=0.4f; 
            Time=40;

            SetBlock(5,10);
            SetBlock(3,11);
            SetBlock(7,11);
            SetBlock(3,12);
            SetBlock(7,12);
            SetBlock(3,13);
			break;
		case 2:
            StartX=4; StartY=9; FinishX=6; FinishY=7;
            BlockNum=2; Direction=DOWN; Delay =80; DelayCounter=0;
            WaterStep=0.4f; 
            Time=60;

            SetBlock(5,4);
            SetBlock(6,4);
            SetBlock(4,5);
            SetBlock(7,5);
            SetBlock(4,6);
            SetBlock(8,6);
            SetBlock(3,7);
            SetBlock(9,7);
            SetBlock(2,8);
            SetBlock(2,9);
			break;
		case 3:
            StartX=5; StartY=9; FinishX=8; FinishY=9;
            BlockNum=2; Direction=DOWN; Delay =80; DelayCounter=0;
            WaterStep=0.4f; 
            Time=40;

            SetBlock(4,11);
            SetBlock(5,11);
            SetBlock(6,11);
            SetBlock(7,11);
            SetBlock(8,11);
            SetBlock(9,11);
			break;
		case 4:
            StartX=6; StartY=9; FinishX=8; FinishY=9;
            BlockNum=2; Direction=DOWN; Delay =80; DelayCounter=0;
            WaterStep=0.4f; 
            Time=60;

            SetBlock(7,7);
            SetBlock(7,8);
            SetBlock(7,9);
            SetBlock(7,10);
            SetBlock(7,11);
			break;
		case 5:
            StartX=6; StartY=8; FinishX=10; FinishY=8;
            BlockNum=2; Direction=DOWN; Delay =80; DelayCounter=0;
            WaterStep=0.4f; 
            Time=60;

            SetBlock(6,7);
            SetBlock(5,8);
            SetBlock(7,8);
            SetBlock(8,9);
            SetBlock(9,10);
			break;
		case 6:
            StartX=5; StartY=8; FinishX=8; FinishY=6;
            BlockNum=2; Direction=DOWN; Delay =80; DelayCounter=0;
            WaterStep=0.4f; 
            Time=80;

            SetBlock(5,6);
            SetBlock(4,7);
            SetBlock(6,7);
            SetBlock(4,8);
            SetBlock(7,8);
            SetBlock(4,9);
            SetBlock(8,9);
            SetBlock(4,10);
            SetBlock(4,11);
			break;
		case 7:
            StartX=5; StartY=10; FinishX=8; FinishY=5;
            BlockNum=2; Direction=DOWN; Delay =80; DelayCounter=0;
            WaterStep=0.4f; 
            Time=60;

            SetBlock(6,4);
            SetBlock(7,4);
            SetBlock(8,4);
            SetBlock(9,4);
            SetBlock(9,7);
            SetBlock(8,8);
            SetBlock(7,9);
            SetBlock(7,10);
			break;
		case 8:
            StartX=17; StartY=12; FinishX=9; FinishY=9;
            BlockNum=2; Direction=DOWN; Delay =80; DelayCounter=0;
            WaterStep=0.4f; 
            Time=80;

            SetBlock(12,11);
            SetBlock(15,11);
            SetBlock(16,11);
            SetBlock(12,12);
            SetBlock(9,13);
            SetBlock(10,13);
            SetBlock(11,13);
            SetBlock(12,13);
            SetBlock(13,13);
            SetBlock(14,13);
            SetBlock(15,13);

			break;
		case 9:
            StartX=5; StartY=6; FinishX=9; FinishY=9;
            BlockNum=2; Direction=DOWN; Delay =80; DelayCounter=0;
            WaterStep=0.4f; 
            Time=80;

            SetBlock(4,6);
            SetBlock(4,7);
            SetBlock(8,8);
            SetBlock(9,8);
            SetBlock(10,8);
            SetBlock(3,9);
            SetBlock(4,9);
            SetBlock(5,9);
            SetBlock(6,9);
            SetBlock(7,9);
            SetBlock(8,9);
            SetBlock(10,9);
            SetBlock(10,10);
			break;
		case 10:
            StartX=10; StartY=6; FinishX=4; FinishY=10;
            BlockNum=2; Direction=DOWN; Delay =80; DelayCounter=0;
            WaterStep=0.4f; 
            Time=120;

            SetBlock(9,5);
            SetBlock(10,5);
            SetBlock(11,5);
            SetBlock(9,6);
            SetBlock(11,6);
            SetBlock(9,7);
            SetBlock(11,7);
            SetBlock(9,8);
            SetBlock(9,9);
            SetBlock(9,10);
            SetBlock(9,11);
            SetBlock(9,12);
			break;
		case 11:
            StartX=3; StartY=2; FinishX=11; FinishY=2;
            BlockNum=2; Direction=DOWN; Delay =64; DelayCounter=0;
            WaterStep=0.5f; 
            Time=120;

            SetBlock(6,2);
            SetBlock(2,3);
            SetBlock(6,3);
            SetBlock(6,4);
            SetBlock(6,5);
            SetBlock(7,6);
            SetBlock(8,6);
            SetBlock(9,6);
            SetBlock(9,7);
            SetBlock(9,8);
			break;
		case 12:
            StartX=11; StartY=11; FinishX=11; FinishY=5;
            BlockNum=2; Direction=DOWN; Delay =64; DelayCounter=0;
            WaterStep=0.5f; 
            Time=120;

            SetBlock(9,6);
            SetBlock(13,6);
            SetBlock(9,7);
            SetBlock(10,7);
            SetBlock(11,7);
            SetBlock(12,7);
            SetBlock(13,7);
            SetBlock(11,8);
            SetBlock(11,9);
            SetBlock(10,10);
            SetBlock(11,10);
            SetBlock(12,10);
			break;
		case 13:
            StartX=17; StartY=6; FinishX=16; FinishY=4;
            BlockNum=2; Direction=DOWN; Delay =64; DelayCounter=0;
            WaterStep=0.5f; 
            Time=120;

            SetBlock(18,2);
            SetBlock(18,3);
            SetBlock(18,4);
            SetBlock(18,5);
            SetBlock(18,6);
            SetBlock(16,7);
            SetBlock(16,8);
            SetBlock(16,9);
            SetBlock(16,10);
            SetBlock(16,11);
			break;
		case 14:
            StartX=5; StartY=5; FinishX=9; FinishY=4;
            BlockNum=2; Direction=DOWN; Delay =32; DelayCounter=0;
            WaterStep=1.00001f; 
            Time=120;

            SetBlock(4,5);
            SetBlock(6,5);
            SetBlock(7,5);
            SetBlock(8,5);
            SetBlock(4,6);
            SetBlock(8,6);
            SetBlock(4,7);
            SetBlock(8,7);
            SetBlock(4,8);
            SetBlock(5,8);
            SetBlock(6,8);
            SetBlock(8,8);
            SetBlock(8,9);
            SetBlock(8,10);
			break;
		case 15:
            StartX=8; StartY=2; FinishX=13; FinishY=2;
            BlockNum=2; Direction=DOWN; Delay =32; DelayCounter=0;
            WaterStep=1.00001f; 
            Time=80;

            SetBlock(9,3);
            SetBlock(12,3);
            SetBlock(10,4);
            SetBlock(11,4);
            SetBlock(10,5);
            SetBlock(11,5);
            SetBlock(9,6);
            SetBlock(12,6);
            SetBlock(8,7);
            SetBlock(13,7);
			break;
		case 16:
            StartX=6; StartY=4; FinishX=8; FinishY=9;
            BlockNum=2; Direction=DOWN; Delay =32; DelayCounter=0;
            WaterStep=1.00001f; 
            Time=140;

            SetBlock(13,3);
            SetBlock(12,4);
            SetBlock(5,5);
            SetBlock(11,5);
            SetBlock(5,6);
            SetBlock(10,6);
            SetBlock(5,7);
            SetBlock(9,7);
            SetBlock(5,8);
            SetBlock(8,8);
            SetBlock(7,9);
            SetBlock(4,10);
            SetBlock(5,10);
            SetBlock(6,10);
            SetBlock(7,10);
            SetBlock(4,11);
            SetBlock(3,12);
            SetBlock(4,12);
			break;
		case 17:
             StartX=6; StartY=4; FinishX=13; FinishY=6;
            BlockNum=2; Direction=DOWN; Delay =32; DelayCounter=0;
            WaterStep=1.00001f; 
            Time=160;

            SetBlock(5,3);
            SetBlock(6,3);
            SetBlock(7,3);
            SetBlock(5,4);
            SetBlock(7,4);
            SetBlock(5,5);
            SetBlock(7,5);
            SetBlock(5,6);
            SetBlock(7,6);
            SetBlock(5,7);
            SetBlock(7,7);
            SetBlock(5,8);
            SetBlock(7,8);
            SetBlock(8,8);
            SetBlock(9,8);
            SetBlock(10,8);
            SetBlock(5,9);
            SetBlock(5,10);
            SetBlock(6,10);
            SetBlock(7,10);
            SetBlock(8,10);
            SetBlock(9,10);
            SetBlock(10,10);
			break;
		case 18:
            StartX=4; StartY=6; FinishX=10; FinishY=6;
            BlockNum=2; Direction=DOWN; Delay =32; DelayCounter=0;
            WaterStep=1.00001f; 
            Time=160;

            SetBlock(8,1);
            SetBlock(8,2);
            SetBlock(7,3);
            SetBlock(7,4);
            SetBlock(7,5);
            SetBlock(9,5);
            SetBlock(10,5);
            SetBlock(11,5);
            SetBlock(7,6);
            SetBlock(9,6);
            SetBlock(11,6);
            SetBlock(6,7);
            SetBlock(9,7);
            SetBlock(11,7);
            SetBlock(5,8);
            SetBlock(5,9);
            SetBlock(5,10);
			break;
		case 19:
            StartX=4; StartY=5; FinishX=17; FinishY=1;
            BlockNum=2; Direction=DOWN; Delay =16; DelayCounter=0;
            WaterStep=2.00001f; 
            Time=160;

            SetBlock(16,2);
            SetBlock(16,3);
            SetBlock(15,4);
            SetBlock(3,5);
            SetBlock(5,5);
            SetBlock(14,5);
            SetBlock(3,6);
            SetBlock(5,6);
            SetBlock(14,6);
            SetBlock(3,7);
            SetBlock(6,7);
            SetBlock(7,7);
            SetBlock(8,7);
            SetBlock(9,7);
            SetBlock(10,7);
            SetBlock(11,7);
            SetBlock(12,7);
            SetBlock(13,7);
            SetBlock(6,9);
            SetBlock(7,9);
            SetBlock(8,9);
            SetBlock(9,9);
            SetBlock(10,9);
            SetBlock(11,9);
            SetBlock(12,9);
            SetBlock(13,9);
			break;
		case 20:
            StartX=6; StartY=4; FinishX=8; FinishY=4;
            BlockNum=2; Direction=DOWN; Delay =16; DelayCounter=0;
            WaterStep=2.00001f; 
            Time=160;

            SetBlock(7,0);
            SetBlock(7,1);
            SetBlock(7,2);
            SetBlock(7,3);
            SetBlock(7,4);
            SetBlock(3,5);
            SetBlock(4,5);
            SetBlock(5,5);
            SetBlock(7,5);
            SetBlock(9,5);
            SetBlock(7,6);
            SetBlock(4,7);
            SetBlock(5,7);
            SetBlock(6,7);
            SetBlock(7,7);
            SetBlock(8,7);
            SetBlock(7,8);
            SetBlock(8,8);
            SetBlock(9,8);
            SetBlock(7,9);
            SetBlock(7,10);
            SetBlock(7,11);
            SetBlock(9,11);
            SetBlock(4,12);
            SetBlock(5,12);
            SetBlock(6,12);
            SetBlock(9,12);
            SetBlock(9,13);
            SetBlock(4,14);
            SetBlock(5,14);
            SetBlock(6,14);
            SetBlock(9,14);
			break;


	}
	BlockCounter=BlockNum;
	block[0].x=StartX*32; block[0].y=StartY*32; 
	block[0].currentFrame=1; 
	SetGrid(StartX, StartY, 0, 0, 0);
	block[1].x=FinishX*32; block[1].y=FinishY*32; 
	block[1].currentFrame=10;
	SetGrid(FinishX, FinishY, 10, 0, 1);
	WaterX=StartX; WaterY=StartY;
	PlayingFat=0;
	int i;
	for(i=BlockNum; i<BlockNum+7; i++)
	{
		block[i].y=304-32-((i-BlockNum)*32);
	}
}

void SetBlock(u8 x, u8 y)
{
	block[BlockNum].x=x*32; block[BlockNum].y=y*32; 
	block[BlockNum].currentFrame=0; 
	SetGrid(x, y, 0, 0, BlockNum);
	BlockNum++;
}