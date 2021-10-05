//------------------------------------------------------------------------------
// File Name:	LevelManager.h
// Project:		What The Food is Going On!
// Author(s): Joe Centeno
//
// All content © 2021 DigiPen(USA) Corporation, all rights reserved.
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the ...
void LevelManagerInit();

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void LevelManagerUpdate(float dt);

// Shutdown the ...
void LevelManagerShutdown();

// These Two Functions are to start the two differnt modes from the menu 

void StartWorkWeek();

void StartEndless();

void StartDay(int workDayCount);

void EndDay(int workDayCount);

void IncreaseDayCount();

int GetDayCount();

void LevelFadeIn(float dt); // Fade scence from black to gameplay 
bool LevelFadeOut(float dt); // Fade scence to black from gamplay

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

