//------------------------------------------------------------------------------
// File Name:	Time.c
// Project:		What The Food is Going On!
// Author(s): Joe Centeno
//
// All content © 2021 DigiPen(USA) Corporation, all rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Time.h"
#include "GameStateManager.h"
#include <AEEngine.h>   
#include "Graphics.h"
#include "Player.h"


#define ZERO 0.0f
#define CLOCK_X -375.0f
#define CLOCK_Y 430.0f

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
AEGfxTexture* UiClock;
AEGfxTexture* UiClockHandBig;
AEGfxTexture* UiClockHandSmall;
AEGfxTexture* UiDayCounter;
AEGfxTexture* crosshair; // CrossHair Texture

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static float TimePassed;                   // Amount Of Time Passed In Level
static const float ShiftStart = 360.0f;    // Shift Start Amount of Time
static const float ShiftEnd = ZERO;        // Shift Ends When Time is Zero

static int ClockDegree;

static bool ShiftActive; // True if Shift & timer are active
static bool ShiftOver;   // True if Shift timer is Completed 


static int TimeIncrease = 1;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Time
void TimeInit()
{
	TimePassed = ShiftStart; // Set Time Passed to 
	ShiftActive = true;      // Set Shift Active to True when init is called 
	ShiftOver = false;       // Set Shift Over to False since shift Just started 

	UiClock = AEGfxTextureLoad("./Assets/ClockLayer1.png");
	UiClockHandBig = AEGfxTextureLoad("./Assets/ClockLayer2.png");
	UiClockHandSmall = AEGfxTextureLoad("./Assets/ClockLayer3.png");

	UiDayCounter = AEGfxTextureLoad("./Assets/ItemSprites/CalendarLayer1.png");

	crosshair = AEGfxTextureLoad("./Assets/Cross Hair.png");
}

// Update the Time
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void TimeUpdate(float dt)
{
	s32 mouseX;
	s32 mouseY;

	AEInputGetCursorPosition(&mouseX, &mouseY);

	float mouseWorldX;
	float mouseWorldY;

	AEGfxConvertScreenCoordinatesToWorld((float)mouseX, (float)mouseY, &mouseWorldX, &mouseWorldY);

     //ClockDegree = ((int)TimePassed + 90) % 360;
	 // if the shift has started and its not Shift over 
	if (ShiftActive == true && ShiftOver == false) 
	{
		if (AEInputCheckCurr('L'))
		{
			TimeIncrease = 30;
		}
		// De-Increment and Print Passed Time
		TimePassed -= dt * TimeIncrease;
		//AESysPrintf("Time Passed: %f \n", TimePassed);
	}
    
	 // If Passed Time is less then 0 and Shift is active and Shift is over
	if (TimePassed <= ShiftEnd && (ShiftActive == true && ShiftOver == false)) 
	{
		ShiftActive = false;
		ShiftOver = true;
	}

	 // If Shift Over is equal to True
	if (ShiftOver == true)
	{
		//TimePassed = 0.0f;                       // Reset Time
		//GameStateManagerSetNextState(GsRestart);
	}

	DrawSprite(UiClock, CLOCK_X, CLOCK_Y, 0.0f, 1, 120.0f, 120.0f);
	DrawSprite(UiClockHandSmall, CLOCK_X, CLOCK_Y, TimePassed, 1, 120.0f, 120.0f);
	DrawSprite(UiClockHandBig, CLOCK_X, CLOCK_Y, TimePassed * 15.0f, 1, 120.0f, 120.0f);
	DrawSprite(UiDayCounter, -CLOCK_X * 2.3f, CLOCK_Y, 0, 1, 120.0f, 120.0f);

	float aimOffSet = 0; //getCurrAimOffSet();

	DrawSprite(crosshair, (f32)mouseWorldX, (f32)mouseWorldY, 0, 1, 20 * aimOffSet + 30, 20 * aimOffSet + 30);
}

// Shutdown the Time
void TimeShutdown()
{
	TimePassed = 0.0f; // If Shutdown Reset Time
	ShiftOver = false; // Reset Shift Over 
}

float GetTimePassed()
{
	return TimePassed;
}

float GetShiftStart()
{
	return ShiftStart;
}

float GetShiftEnd()
{
	return ShiftEnd;
}

void StopTime()
{
	ShiftActive = false;
}

float GetTimeNormlized()
{
	return TimePassed - ShiftStart;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------