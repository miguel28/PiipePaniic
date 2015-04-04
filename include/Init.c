void MK_InitLibraries(void)
{
	ML_Init();
	ML_InitMP3();
	ASND_Init();
	ML_InitFAT();
	ML_InitRand();
}
void MK_LoadGfx(void)
{
	int i;
	ML_LoadSpriteFromBuffer(&fontData, &font, font_png, 100, 100);
	ML_InitTile(&font, 8, 8);	
	ML_SetSpriteScale(&font, 1.5, 1.5);

	ML_LoadSpriteFromBuffer(&font1Data, &font1, font1_png, 100, 100);
	ML_InitTile(&font1, 8, 8);	
	ML_SetSpriteScale(&font1, 1.5, 1.5);

	ML_LoadBackgroundFromBuffer(&introData, &intro, intro_miguel_png, 0, 0);
	ML_LoadBackgroundFromBuffer(&splashData, &splash, neo2012_png, 0, 0);
	ML_LoadBackgroundFromBuffer(&titleData, &title, Titulo_png, 0, 0);
	
	////////Load Game GUI////////////////////////////
	ML_LoadBackgroundFromBuffer(&backgroundData, &background, background_png, 0, 0);
	ML_LoadBackgroundFromBuffer(&gridData, &grid, grid_png, 0, 0);
	ML_LoadBackgroundFromBuffer(&BlackData, &Black, Black_png, 0, 0);
	ML_LoadBackgroundFromBuffer(&youwinData, &youwin, youwin_png, 0, 0);
	ML_LoadBackgroundFromBuffer(&youloseData, &youlose, youlose_png, 0, 0);
	ML_LoadSpriteFromBuffer(&buttonData, &button, button_png, 640-64-16, 16);
	ML_InitTile(&button, 64, 32);
	ML_LoadSpriteFromBuffer(&minusData, &minus, minuspoints_png, 0, 0);

	ML_LoadSpriteFromBuffer(&PressData, &Press, press_png, 50, 368);
	ML_LoadSpriteFromBuffer(&pointerData, &pointer, pointer_png, 100, 100);
	ML_LoadSpriteFromBuffer(&pointer2Data, &pointer2, pointer2_png, 100, 100);
	ML_LoadSpriteFromBuffer(&upperbarData, &upperbar, upperbar_png, 0, 0);
	ML_LoadSpriteFromBuffer(&metal1Data, &metal1, metal1_png, 0, 416);
	ML_LoadSpriteFromBuffer(&metal2Data, &metal2, metal2_png, 0, 64);
	ML_LoadSpriteFromBuffer(&metal3Data, &metal3, metal3_png, 0, 64);
	ML_LoadSpriteFromBuffer(&waterData, &water, water_png, 0, 0);
	ML_LoadSpriteFromBuffer(&water2Data, &water2, water2_png, 0, 0);
	ML_InitTile(&water, 32, 32);

	ML_LoadSpriteFromBuffer(&arrowData, &arrow1, arrows_png, 96,176);
	ML_InitTile(&arrow1, 128, 128);
	ML_LoadSpriteFromBuffer(&arrowData, &arrow2, arrows_png, 416, 176);
	ML_InitTile(&arrow2, 128, 128);

	ML_LoadSpriteFromBuffer(&selbuttonsData, &selbutton1, selbuttons_png, 64,416);
	ML_InitTile(&selbutton1, 256, 64);
	ML_LoadSpriteFromBuffer(&selbuttonsData, &selbutton2, selbuttons_png, 320, 416);
	ML_InitTile(&selbutton2, 256, 64);

	selbutton2.currentFrame=1;
	arrow1.currentFrame=1;
	water.currentFrame=1;
	for(i=0; i<4; i++){
		ML_LoadSpriteFromBuffer(&fatbtnsData, &fatbtns[i], fatbtns_png, 85,(i*108)+64);
	}
	for(i=0; i<4; i++){
		ML_LoadSpriteFromBuffer(&fatbtnsData, &fatbtns[i+4], fatbtns_png, 362,(i*108)+64);
	}
	
	for(i=0; i<4; i++)
	{
		ML_LoadSpriteFromBuffer(&menubtnsData, &menubtns[i], menubtns_png, 64, (i*96)+80);
		ML_InitTile(&menubtns[i], 512, 64);
		menubtns[i].currentFrame=i;
	}

	for(i=0; i<MAXNUMBLOCKS; i++)
	{
		ML_LoadSpriteFromBuffer(&blockData, &block[i], Blocks_png, 16, -32);
		ML_InitTile(&block[i], 32, 32);
		block[i].currentFrame=ML_Rand(2,8);
		ML_LoadSpriteFromBuffer(&waterData, &waterD[i], water_png, 16, -32);
		ML_InitTile(&waterD[i], 32, 32);
	}
	for(i=0; i<GRIDWIDTH*GRIDHEIGHT; i++)
	{
		BlockGrid[i].Type=0;
		BlockGrid[i].Rotation=0;
		BlockGrid[i].Using=0;
		BlockGrid[i].ID=-1;
		BlockGrid[i].Watered=0;
	}

	

}