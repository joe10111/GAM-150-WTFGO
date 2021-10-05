//------------------------------------------------------------------------------
// File Name:	LevelManager.c
// Project:		What The Food is Going On!
// Author(s): Joe Centeno
//
// All content © 2021 DigiPen(USA) Corporation, all rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "LevelManager.h"
#include "GameStateManager.h"
#include "Time.h"
#include <AEEngine.h>
#include "Graphics.h"
#include "Text.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
AEGfxTexture* blackSquare;

float alphaIn, alphaOut;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static int workWeekDayCount;
static const char* CurrentDay;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the ...
void LevelManagerInit()
{
	blackSquare = AEGfxTextureLoad("Assets/BlackSquare.png");
	alphaIn = 1.00f;
	alphaOut = 0.00f;
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void LevelManagerUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	if (AEInputCheckCurr('1'))
	{
		GameStateManagerSetNextState(GsMonday);
	}

	if (AEInputCheckCurr('2'))
	{
		GameStateManagerSetNextState(GsTuseday);
	}

	if (AEInputCheckCurr('3'))
	{
		GameStateManagerSetNextState(GsWensday);
	}

	if (AEInputCheckCurr('4'))
	{
		GameStateManagerSetNextState(GsThursday); 
	}

	if (AEInputCheckCurr('5'))
	{
		GameStateManagerSetNextState(GsFriday);
	}
	if (AEInputCheckCurr('7'))
	{
		GameStateManagerSetNextState(GsEndless);
	}
}

// Shutdown the ...
void LevelManagerShutdown()
{
}

 // When you need to start the work week call this function
 // Pass in the levelEnum you wish to start
 // Monday = 5, Tuseday = 6, Wensday = 7, Thursday = 8, Firday = 9 
void StartWorkWeek()
{
	workWeekDayCount = 0;
	GameStateManagerSetNextState(GsMonday);
}

// When you need to start the 24/7 mode (endless) call this function
void StartEndless()
{
	workWeekDayCount = 0;
}

void StartDay(int workDayCount)
{
	switch (workDayCount)
	{
	case 1: 
		CurrentDay = "Monday";
		workDayCount = 1;
	break;
	case 2:
		CurrentDay = "Tuseday";
		workDayCount = 2;
		break;
	case 3: 
		CurrentDay = "Wensday";
		workDayCount = 3;
		break;
	case 4:
		CurrentDay = "Thursday";
		workDayCount = 4;
		break;
	case 5:
		CurrentDay = "Friday";
		workDayCount = 5;
		break;
	}

	if (0 == AESysDoesWindowExist())
	{
		GameStateManagerSetNextState(GsQuit);
	}
	else
	{
		AESysPrintf("Current day: %s \n", CurrentDay);
	}
}

void EndDay(int workDayCount)
{
	switch (workDayCount)
	{
	case 1:
		workDayCount = 2;
		GameStateManagerSetNextState(GsTuseday);
		break;
	case 2:
		workDayCount = 3;
		GameStateManagerSetNextState(GsWensday);
		break;
	case 3:
		workDayCount = 4;
		GameStateManagerSetNextState(GsThursday);
		break;
	case 4:
		workDayCount = 5;
		GameStateManagerSetNextState(GsFriday);
		break;
	case 5:
		workDayCount = 1;
		GameStateManagerSetNextState(GsMonday);
		break;
	}
}

void IncreaseDayCount()
{
	workWeekDayCount++;
}

int GetDayCount()
{
	return workWeekDayCount;
}

// Finish Fading Level 
void LevelFadeIn(float dt)
{
	float pixelSizex = AEGfxGetWinMaxX();
	float pixelSizey = AEGfxGetWinMaxY();

	DrawSprite(blackSquare, 0, 0, 0, alphaIn, pixelSizex*2, pixelSizey *2);
	
	alphaIn -= 0.50f * dt;
	if (alphaIn <= 0.0f)
		alphaIn = 0.0f;
	//else
		//DrawGameText("Time to Cook", -100, 0, 60);
}

bool LevelFadeOut(float dt)
{
	float pixelSizex = AEGfxGetWinMaxX();
	float pixelSizey = AEGfxGetWinMaxY();

	DrawSprite(blackSquare, 0, 0, 0, alphaOut, pixelSizex * 4, pixelSizey * 4);

	alphaOut += 0.55f * dt;

	if (alphaOut > 1.0f)
	{
		return false;
	}
	else
	{
		//DrawGameText("Shift Over", -100, 0, 50);
		return true;
	}
}

	// Fade scence to black 

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

