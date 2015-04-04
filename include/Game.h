#include "music_mp3.h"
#include "bounce_raw.h"
#include "jaak_raw.h"
#include "Clock_raw.h"
#include "Drag_snd_raw.h"
#include "Drop_snd_raw.h"
#include "Flash1_raw.h"
#include "water_snd_raw.h"
#include "background_png.h"
#include "pointer_png.h"
#include "pointer2_png.h"
#include "font_png.h"
#include "font1_png.h"
#include "Titulo_png.h"
#include "splash720wii2011_png.h"
#include "intro_miguel_png.h"
#include "press_png.h"
#include "Blocks_png.h"
#include "grid_png.h"
#include "upperbar_png.h"
#include "metal1_png.h"
#include "metal2_png.h"
#include "metal3_png.h"
#include "water_png.h"
#include "water2_png.h"
#include "Black_png.h"
#include "youwin_png.h"
#include "youlose_png.h"
#include "button_png.h"
#include "minuspoints_png.h"
#include "menubtns_png.h"
#include "arrows_png.h"
#include "selbuttons_png.h"
#include "fatbtns_png.h"
#include "neo2012_png.h"
#include "press_png.h"

#define norm_fix(x)			((x)<<8)
#define fix_norm(x)			((x)>>8)
#define MAXNUMBLOCKS 160
#define GRIDWIDTH 20
#define GRIDHEIGHT 15
#define MAXLEVELS 20

ML_Image selbuttonsData, fatbtnsData;
ML_Sprite selbutton1, selbutton2,fatbtns[8];

ML_Image introData, splashData,BlackData, youwinData, youloseData, buttonData,minusData, menubtnsData, arrowData,titleData,PressData;
ML_Background intro, splash, Black,youwin, youlose,title;
ML_Sprite button, minus, menubtns[4], arrow1, arrow2, Press;

ML_Image backgroundData, pointerData, pointer2Data, fontData, font1Data, blockData, gridData;
ML_Sprite pointer, pointer2, font, font1, block[MAXNUMBLOCKS], waterD[MAXNUMBLOCKS];
ML_Background background, grid;

ML_Image upperbarData, metal1Data,metal2Data,metal3Data,waterData,water2Data;
ML_Sprite upperbar, metal1, metal2, metal3,water,water2;


typedef struct
{
	u8 Rotation;
	u8 Type;
	u8 Using;
	s8 ID;
	u8 Watered;
}BlockStruct;

BlockStruct BlockGrid[GRIDWIDTH*GRIDHEIGHT];

bool Drag;
u8 IdDrag;
bool PlacedBlock[MAXNUMBLOCKS];

enum {UP,DOWN,LEFT,RIGHT};
enum {D0,D90,D180,D270};

typedef struct
{
	u8 Created;
	u8 Grid[300];
	u8 StartX;
	u8 StartY;
	u8 FinishX;
	u8 FinishY;
	u16 Time;
	u8 Speed;
}SlotType;

SlotType FatSlot[8],TempFatSlot; 

char SpeedNames[5][11]=
{
	"Super Slow",
	"Slow",
	"Normal",
	"Fast",
	"Super Fast"
};

u8 Rot=0;//// Mover

void MK_InitLibraries(void);
void MK_LoadGfx(void);

void Esperar(s32 s,ML_Background *Background);
void Play_Music(void);
void ExitForTheGame();
void CheckDragBlock(void);
void DropBlock(void);
u8 PlaceToGrid(void);
void SetGrid(u8 x, u8 y, u8 type, u8 rot, u8 id);
void SetGridWatered(u8 x, u8 y);
u8 GetGridUsing(u8 x, u8 y);
u8 GetGridType(u8 x, u8 y);
u8 GetGridRot(u8 x, u8 y);
u8 GetGridID(u8 x, u8 y);
void DeleteFromGrid(u8 x, u8 y);

void DrawBlocks(void);
void DrawWaterBlocks();
void MK_Cursor(u8 Id);

/// In Game Vars ///
u8 BlockCounter=0;
u8 Anim1Frame=0;
bool PlayAnim1=true;

u16 Anim2Frame=0;
bool PlayAnim2=false;
u8 Anim2ID=0;

bool Anim3Play=false;
u8 Anim3Frame=0;
bool Anim3Stop=false;

u8 StartX,StartY;
u8 FinishX,FinishY;
u8 BlockNum;
u8 Direction;
u16 Delay;
float WaterStep;
u16 DelayCounter;
u8 SubDelayCounter=0;
u8 SubDelay=0;
u8 WaterX,WaterY;
float WaterXX,WaterYY;

u8 LevelNum=1;
s32 GlobalScore=0;

u16 Time; 
u8 Win;
u8 Lose=0;
u8 TimeCounter; 
bool Pause;
u8 Anim4Frame=0;
s8 Anim4ID=-1;
u8 Anim5Frame=0;
s8 Anim5ID=-1;

u8 CurrentSlot;
u8 SlotStep;
u8 PlayingFat;
bool ChangeAlpha;
u8 MenuAlpha;
/// In Game Vars ///

void PlayAnims();

void DrawLevel(u8 Level);
void SetBlock(u8 x, u8 y);
void SubWaterFlux();
void WaterFlux();
void ReInit();
void TimeFuntion();
void ScoreAdd(u16 score);
void ScoreSub(u16 score);

u8 MenuIndex=0;
void Intro();
void MainMenu();
void Anim4();
void Anim5();
void InGame();
void SelectSlot();
void Anim5();
void ReadFAT();
void WriteFAT();

void DropBlock2(void);
void SetStart();
void SetFinish();
void CreatingMenu();
void SelectSlot2();
void PlayCreate(u8 slot);
void DrawTitle();


#include "Init.c"
#include "Game.c"
#include "Levels.c"
#include "Menus.c"
#include "Fat.c" 
